#include <memory.h>
#include <stdio.h>
#include<string.h>
#include <locale.h>
#include "FileSystem.h"


void test()
{
	formatDisk();

	SBitMap InodeBitMap;
	createEmptyBitMap(InodeBitMap, g_NumInodes);

	SBitMap DataBlockBitMap;
	createEmptyBitMap(DataBlockBitMap, g_NumBlocks);

	createFile("test.txt",  0, 'f', 16);
	/**createFile("test1.txt", 0, 'f', g_MaxFileSize);
	createFile("test1.txt", 0, 'f', 0);*/

	memcpy(InodeBitMap.pMapData, g_Disk+g_BlockBitMapSize, g_InodeBitMapSize);   //从虚拟硬盘中读取Inode的位示图
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 //从虚拟硬盘读取数据块位示图
	printf("Inode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);

    SOpenFile* File1=openFile("test.txt");
	char *temp=new char[80];
	strcpy_s(temp,73,"123456789123456789123456789123456789123456789123456789123456789123456789");
	printf("将字符串\"123456789123456789123456789123456789123456789123456789123456789123456789\"写入文件:test.txt\n");
    writeData2File(temp,73,*File1);
	
	memcpy(InodeBitMap.pMapData, g_Disk + g_BlockBitMapSize, g_InodeBitMapSize);   //从虚拟硬盘中读取Inode的位示图
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 //从虚拟硬盘读取数据块位示图
	printf("Inode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);

	File1 = openFile("test.txt");
	memset(temp,0,80);
	printf("将文件中的内容读到temp中，并打印出来：\n");
	readDataFromFile(temp,72,*File1);
	printf("%s",temp);

	/*
	removeFile("test.txt", 0);
	removeFile("test.txt", 0);
	memcpy(InodeBitMap.pMapData, g_Disk+g_BlockBitMapSize, g_InodeBitMapSize);   //从虚拟硬盘中读取Inode的位示图
	memcpy(DataBlockBitMap.pMapData, g_Disk, g_BlockBitMapSize);                 //从虚拟硬盘读取数据块位示图
	printf("\nInode usage:");
	printfBitMap(InodeBitMap);
	printf("Block usage:");
	printfBitMap(DataBlockBitMap);*/

	delete InodeBitMap.pMapData;
	delete DataBlockBitMap.pMapData;
}

int main(void)
{
	setlocale(LC_ALL, "zh_CN.UTF-8");
	test();

	return 0;
} 