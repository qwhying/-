#ifndef DATASTRUCTURE_H_
#define DATASTRUCTURE_H_

const short g_MaxNumFiles    = 10;
const short g_MaxFileNameLen = 10;

struct SDirectoryEntry               //Ŀ¼��
{
	bool IsInUse;
	short InodeNum;		
	char FileName[g_MaxFileNameLen + 1];
};

struct SDirectory
{
	char FileName[g_MaxFileNameLen + 1];
	SDirectoryEntry FileSet[g_MaxNumFiles];   //�ٶ�һ��Ŀ¼ֻ�ܴ洢g_MaxNumFiles���ļ�	
};

bool addFile2Directory(const char* vFileName, short vInodeNum, SDirectory& voDirectory);  //��Ŀ¼�����vFileName�ļ�,�ļ���Ӧ��INodeΪvInodeNum
bool removeFileFromDirectory(const char *vFileName, SDirectory& vioDirectory);            //��Ŀ¼���Ƴ�vFileName�ļ�
int  findFileInodeNum(const char* vFileName, const SDirectory& vDirectory);               //����vFileName�ļ���INode���
int  findFileIndex(const char* vFileName, const SDirectory& vDirectory);                  //�����ļ���ΪvFileName���±꣬�������򷵻�-1
SDirectory createEmptyDirectory();   

#endif