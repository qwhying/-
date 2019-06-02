#include "FileSystem.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

char g_Disk[g_DiskSize] = {'\0'};
SDirectory g_RootDir = createEmptyDirectory();

bool createFile(const char* vFileName, int vDirInodeNum, char FileType, int vFileSize)
{
	if (vDirInodeNum >= g_NumInodes) return false;
	if (vFileSize > g_MaxFileSize) return false;//文件过大

	SDirectory TempDirectory = loadDirectoryFromDisk(vDirInodeNum);

	bool IsSuccess = true;
	if (findFileInodeNum(vFileName, TempDirectory) != -1) IsSuccess = false;
	else
	{	
		SBitMap InodeBitMap; 
		createEmptyBitMap(InodeBitMap, g_NumInodes);
		memcpy(InodeBitMap.pMapData, g_Disk+g_BlockBitMapSize, g_InodeBitMapSize);            //从虚拟硬盘中读取Inode位示图
		                 //位示图在硬盘中g_Disk+g_BlockBitMapSize表示跳过物理快位示图定位到Inode位示图，将地址赋值给指针PMapData

		int InodeIndex = findAndSetAvailableBit(InodeBitMap);
		if (InodeIndex == -1) IsSuccess = false;
		else if (!addFile2Directory(vFileName, InodeIndex, TempDirectory)) IsSuccess =  false;
		else 
		{
			
			SBitMap DataBlockBitMap;
			createEmptyBitMap(DataBlockBitMap, g_NumBlocks);
			memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                      //从虚拟硬盘读取数据块位示图

			SInode TempInode;
			if (!allocateDisk(TempInode, vFileSize, DataBlockBitMap)) IsSuccess =  false;	
			else 
			{
				printf("Creating file %s(type:%c) size %d at %s\n", vFileName, FileType, vFileSize, TempDirectory.FileName);
				TempInode.FileType = FileType;
				saveInode2Disk(TempInode, InodeIndex);                                       //将Inode信息写回虚拟硬盘
				memcpy(g_Disk, DataBlockBitMap.pMapData, g_BlockBitMapSize);                 //将数据块位示图写回虚拟硬盘
				memcpy(g_Disk+g_BlockBitMapSize, InodeBitMap.pMapData, g_InodeBitMapSize);   //将Inode位示图写回虚拟硬盘
				saveDirectory2Disk(vDirInodeNum, TempDirectory);
				if (FileType == 'd')
				{
					SDirectory SubDir = createEmptyDirectory();
					strncpy_s(SubDir.FileName, vFileName, g_MaxFileNameLen); 
					saveDirectory2Disk(InodeIndex, SubDir);
				}
			}
			delete DataBlockBitMap.pMapData;
		}
		delete InodeBitMap.pMapData;
	}
	return IsSuccess;
}

bool removeFile(const char* vFileName, int vDirInodeNum)
{
	SDirectory TempDirectory = loadDirectoryFromDisk(vDirInodeNum);

	//...       从目录中找到文件对应的Inode编号，根据Inode编号读出Inode数据，完成文件的删除
    bool IsSuccess = true;
	int InodeNum=findFileInodeNum(vFileName,TempDirectory);
	if(InodeNum==-1) IsSuccess=false;
	else
	{
		SBitMap InodeBitMap;
		createEmptyBitMap(InodeBitMap, g_NumInodes);
        memcpy(InodeBitMap.pMapData, g_Disk+g_BlockBitMapSize, g_InodeBitMapSize); //从虚拟硬盘中读取Inode位示图

        SInode TempInode=loadInodeFromDisk(InodeNum);
		SBitMap DataBlockBitMap;
		createEmptyBitMap(DataBlockBitMap, g_NumBlocks);
		memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);

		deallocateDisk(TempInode, DataBlockBitMap);
		clearBitAt(InodeNum,InodeBitMap);
		memset(g_Disk + g_BlockBitMapSize + g_InodeBitMapSize + sizeof(SInode)*InodeNum, 0, sizeof(SInode));
		memcpy(g_Disk, DataBlockBitMap.pMapData, g_BlockBitMapSize);                 //将数据块位示图写回虚拟硬盘
		memcpy(g_Disk + g_BlockBitMapSize, InodeBitMap.pMapData, g_InodeBitMapSize);   //将Inode位示图写回虚拟硬盘
		if(TempInode.FileType=='d')//如果是目录,将目录中所有子文件删除
		{
			SDirectory tempDirectory=loadDirectoryFromDisk(InodeNum);
			for(short i=0;i<g_MaxNumFiles;i++)
			{
				removeFile(tempDirectory.FileSet[i].FileName,InodeNum);
			}
		}
		
	    removeFileFromDirectory(vFileName, TempDirectory);
	    saveDirectory2Disk(vDirInodeNum, TempDirectory);                          //将目录内容重新写回虚拟硬盘
	    return true;
	}
	return IsSuccess;
}

SDirectory loadDirectoryFromDisk(int vDirInodeNum)
{
	SOpenFile DirOpenFile;
	DirOpenFile.CurSeekPos = 0;
	DirOpenFile.InodeNum = vDirInodeNum;
	DirOpenFile.Inode = loadInodeFromDisk(vDirInodeNum);     //根据INode编号，读取目录的Inode信息
	assert(DirOpenFile.Inode.FileType == 'd');

	SDirectory TempDir;
	readDataFromFile(&TempDir, sizeof(SDirectory), DirOpenFile);

	return TempDir;
}

void saveDirectory2Disk(int vDirInodeNum, const SDirectory& vDirectory)
{
	SOpenFile DirOpenFile;
	DirOpenFile.CurSeekPos = 0;
	DirOpenFile.InodeNum = vDirInodeNum;
	DirOpenFile.Inode = loadInodeFromDisk(vDirInodeNum);     //根据INode编号，读取目录的Inode信息
	assert(DirOpenFile.Inode.FileType == 'd');
	
	writeData2File(&vDirectory, sizeof(SDirectory), DirOpenFile);
}

void formatDisk()
{
	memset(g_Disk, 0, g_DiskSize);

	SBitMap InodeDiskBitMap;
	createEmptyBitMap(InodeDiskBitMap, g_NumInodes);                                   //创建Inode位示图
	markBitAt(0, InodeDiskBitMap);                                                     //为目录分配Inode，默认为第0个Inode
	memcpy(g_Disk+g_BlockBitMapSize, InodeDiskBitMap.pMapData, g_InodeBitMapSize);     //将Inode位示图写回虚拟硬盘
	delete InodeDiskBitMap.pMapData;

	SBitMap DataBlockBitMap;
	createEmptyBitMap(DataBlockBitMap, g_NumBlocks);                                   //创建数据块位示图

	SDirectory Directory = createEmptyDirectory();                                     //创建根目录
	strcpy_s(Directory.FileName, "/");
	SInode DirInode;
	DirInode.FileType  = 'd';
	allocateDisk(DirInode, sizeof(SDirectory), DataBlockBitMap);                       //分配根目录数据块
	
	memcpy(g_Disk + g_BlockBitMapSize + g_InodeBitMapSize, &DirInode, sizeof(SInode)); //将目录Inode信息写回                               //将Inode信息写回虚拟硬盘
	memcpy(g_Disk, DataBlockBitMap.pMapData, g_BlockBitMapSize);                       //将数据块位示图写回虚拟硬盘
	delete DataBlockBitMap.pMapData;

	saveDirectory2Disk(0, Directory);
}

bool allocateDisk(SInode& voInode, int vFileSize, SBitMap& vioBlockBitMap)
{
	voInode.FileSize  = vFileSize;
	voInode.NumLinks  = 1;
	voInode.NumBlocks = (int)ceil(vFileSize / (double)g_BlockSize);

	if (countClearBits(vioBlockBitMap) < voInode.NumBlocks) return false;		

	for (int i=0; i<voInode.NumBlocks; ++i) voInode.BlockNums[i] = findAndSetAvailableBit(vioBlockBitMap);
	for (int i=voInode.NumBlocks; i<g_MaxNumBlock; ++i) voInode.BlockNums[i] = -1;
	
	return true;
}

void deallocateDisk(const SInode& vInode, SBitMap& vioCBitMap)
{
	//回收磁盘块
	for(int i=0;i<vInode.NumBlocks;i++) 
		clearBitAt(vInode.BlockNums[i],vioCBitMap);
}

SInode loadInodeFromDisk(int vInodeNum)
{
	SInode DirInode;
	memcpy(&DirInode, g_Disk + g_BlockBitMapSize + g_InodeBitMapSize + sizeof(SInode)*vInodeNum, sizeof(SInode)); 

	return DirInode;
}

void saveInode2Disk(const SInode& vInode, int vInodeNum)
{
	memcpy(g_Disk + g_BlockBitMapSize + g_InodeBitMapSize + sizeof(SInode)*vInodeNum, &vInode, sizeof(SInode)); 
}

SOpenFile* openFile(const char* vFileName)                  //假设输入的是完整路径，因此从根目录开始查找文件
{
	SDirectory TempDir = loadDirectoryFromDisk(0);          //读取根目录内容

	int FileInodeNum = -1;
	SInode FileInode;
	char *pStr = new char[strlen(vFileName)+1];
	strcpy_s(pStr,strlen(vFileName)+1,vFileName);
	char *p;
	char *pTemp = strtok_s(pStr, "/",&p);                        //以'/'分割字符串
	while (pTemp != NULL)                                   //按路径依次查找文件
	{
		FileInodeNum = findFileInodeNum(pTemp, TempDir);
		if (FileInodeNum == -1) return NULL;
		else 
		{
			FileInode = loadInodeFromDisk(FileInodeNum);
			if (FileInode.FileType == 'd') TempDir = loadDirectoryFromDisk(FileInodeNum);
		}
		pTemp = strtok_s(NULL, "/",&p);
	}
	delete[] pStr;
	if (FileInode.FileType == 'd') return NULL;             //假如打开的是目录，返回NULL表示不能写入

	SOpenFile *pOpenFile = new SOpenFile();
	pOpenFile->CurSeekPos = 0;
	pOpenFile->InodeNum = FileInodeNum;
	pOpenFile->Inode = FileInode;
	return pOpenFile;
}

int readDataFromFile(void *vDestination, int vNumBytes, SOpenFile& vioFile)
{
	int FileLength = vioFile.Inode.FileSize;
	if ((vNumBytes <= 0) || (vioFile.CurSeekPos >= FileLength)) return 0;   //读取到了文件末尾
	if ((vioFile.CurSeekPos + vNumBytes) > FileLength) vNumBytes = FileLength - vioFile.CurSeekPos;//若要读的长度超过了文件末尾，则只读到文件末尾

	int FirstBlock = vioFile.CurSeekPos / g_BlockSize;                      //计算起始和末尾的数据块，这里计算的结果表示Inode.BlockNums[]数组中的下标范围
	int LastBlock  = (vioFile.CurSeekPos + vNumBytes - 1) / g_BlockSize;
	int NumBlocks  = 1 + LastBlock - FirstBlock;//块数

	char *pDiskDataPos = g_Disk + g_BlockBitMapSize + g_InodeBitMapSize + sizeof(SInode) * g_NumInodes;	//磁盘数据位置
	char *pBuff = new char[NumBlocks * g_BlockSize];//缓冲区
	char *pTemp = pBuff;
	for (int i=FirstBlock; i<=LastBlock; ++i)	
	{//按块拷贝数据
		memcpy(pTemp, pDiskDataPos + g_BlockSize*vioFile.Inode.BlockNums[i], g_BlockSize);
		pTemp += g_BlockSize;
	}

	memcpy(vDestination, &pBuff[vioFile.CurSeekPos % g_BlockSize], vNumBytes);
	delete[] pBuff;
	vioFile.CurSeekPos += vNumBytes;
	return vNumBytes;//返回实际读入的字符数
}

int writeData2File(const void *vSrc, int vNumBytes, SOpenFile& vioFile)
{
	if (vNumBytes <= 0) return 0;

	if (vioFile.CurSeekPos + vNumBytes > g_MaxFileSize) vNumBytes = g_MaxFileSize - vioFile.CurSeekPos;  //超过了最大文件长度
	if (vioFile.CurSeekPos + vNumBytes > vioFile.Inode.FileSize)   //如果写入内容超过了文件原始分配的大小，怎么办？
	{
		int AddBlocks=(int)ceil((vioFile.CurSeekPos+vNumBytes-vioFile.Inode.NumBlocks*g_BlockSize)/(double)g_BlockSize);//额外需要的空间
		if(vioFile.Inode.NumBlocks+AddBlocks>g_MaxNumBlock)return 0;//如果超过了一个文件最多的块数
		SBitMap DataBlockBitMap;
		createEmptyBitMap(DataBlockBitMap, g_NumBlocks);
		memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                      //从虚拟硬盘读取数据块位示图
		if(countClearBits(DataBlockBitMap)<AddBlocks)return 0;
		//如果还有剩余磁盘块，分配额外的磁盘块
		vioFile.Inode.FileSize=vioFile.CurSeekPos+vNumBytes;
		int temp=vioFile.Inode.NumBlocks;//原来文件的块数
		vioFile.Inode.NumBlocks+=AddBlocks;
		for(int i=0;i<AddBlocks;i++)
			vioFile.Inode.BlockNums[i+temp]=findAndSetAvailableBit(DataBlockBitMap);
		saveInode2Disk(vioFile.Inode,vioFile.InodeNum);
		memcpy(g_Disk, DataBlockBitMap.pMapData, g_BlockBitMapSize);                 //将数据块位示图写回虚拟硬盘
		delete DataBlockBitMap.pMapData;
		//...
	}
	//完成文件的写入
	int FirstBlock = vioFile.CurSeekPos / g_BlockSize;                      //计算起始和末尾的数据块，这里计算的结果表示Inode.BlockNums[]数组中的下标范围
	int LastBlock  = (vioFile.CurSeekPos + vNumBytes - 1) / g_BlockSize;
	int NumBlocks  = 1 + LastBlock - FirstBlock;//块数

	char *pDiskDataPos = g_Disk + g_BlockBitMapSize + g_InodeBitMapSize + sizeof(SInode) * g_NumInodes;	//磁盘数据位置
	char *pBuff = new char[NumBlocks * g_BlockSize];//缓冲区
	char *pTemp = pBuff;

    //从磁盘拷贝到缓冲区
	for (int i=FirstBlock; i<=LastBlock; ++i)	
	{//按块拷贝数据
		memcpy(pTemp, pDiskDataPos + g_BlockSize*vioFile.Inode.BlockNums[i], g_BlockSize);
		pTemp += g_BlockSize;
	}
	
	//将需要写入的拷贝到缓冲区指定位置
    memcpy(pBuff+vioFile.CurSeekPos%g_BlockSize,vSrc,vNumBytes);
	pTemp=pBuff;

	//将缓冲区内容写回磁盘
	for (int i=FirstBlock; i<=LastBlock; ++i)	
	{//按块拷贝数据
		memcpy(pDiskDataPos + g_BlockSize*vioFile.Inode.BlockNums[i], pTemp, g_BlockSize);
		pTemp += g_BlockSize;
	}
	delete[] pBuff;
	vioFile.CurSeekPos += vNumBytes;
	return vNumBytes;//返回实际写入的字符数
}
