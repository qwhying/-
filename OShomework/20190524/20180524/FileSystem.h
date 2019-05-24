#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include <math.h>
#include "BitMap.h"
#include "Directory.h"

const short g_BlockSize   = 64;
const short g_NumBlocks   = 128;
const short g_NumInodes   = 32;
const short g_MaxNumBlock = 13;
const short g_MaxFileSize = g_MaxNumBlock * g_BlockSize;

const int g_InodeBitMapSize = ((g_NumInodes+g_NumBitsInWord-1) / g_NumBitsInWord) * sizeof(int);
const int g_BlockBitMapSize = ((g_NumBlocks+g_NumBitsInWord-1) / g_NumBitsInWord) * sizeof(int);

struct SInode
{
	char FileType;                    //'f'��ʾһ���ļ���'d'��ʾĿ¼�ļ�
	short FileSize;
	short NumBlocks;
	short NumLinks;
	short BlockNums[g_MaxNumBlock];
};

struct SOpenFile
{
	short InodeNum;	
	int CurSeekPos;                  //�洢��ǰ��д��λ��
	SInode Inode;
};

const int g_DiskSize = g_BlockBitMapSize + g_InodeBitMapSize + sizeof(SInode) * g_NumInodes + g_BlockSize * g_NumBlocks;
extern char g_Disk[g_DiskSize];

bool createFile(const char* vFileName, int vDirInodeNum, char FileType='d', int vFileSize=sizeof(SDirectory));
bool removeFile(const char* vFileName, int vDirInodeNum);

bool allocateDisk(SInode& voInode, int fileSize, SBitMap& vioBlockBitMap);   //�����ļ���С��BitMap�������
void deallocateDisk(const SInode& vInode, SBitMap& vioBlockBitMap);          //�����ļ�INode���մ���
void saveInode2Disk(const SInode& vInode, int vInodeNum);
SInode loadInodeFromDisk(int vInodeNum);

SDirectory loadDirectoryFromDisk(int vDirInodeNum);
void saveDirectory2Disk(int vDirInodeNum, const SDirectory& vDirectory);
void formatDisk();

#endif