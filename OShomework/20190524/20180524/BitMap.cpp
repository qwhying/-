#include "BitMap.h"
#include <math.h>
#include <stdio.h>

void createEmptyBitMap(SBitMap& voBitMap, int vNumTotalBits)
{
	voBitMap.NumBits = vNumTotalBits;
	int NumWords = (int)ceil(vNumTotalBits / (double)g_NumBitsInWord);
	voBitMap.pMapData = new int[NumWords];

	for (int i = 0; i < NumWords; ++i) voBitMap.pMapData[i] = 0;
}

void markBitAt(int vBitPosition, SBitMap& vioBitMap)
{
	vioBitMap.pMapData[vBitPosition / g_NumBitsInWord] |= 1 << (vBitPosition % g_NumBitsInWord);
}

void clearBitAt(int vBitPosition, SBitMap& vioBitMap)
{ //将位示图中第vBitPosition位置为0
	vioBitMap.pMapData[vBitPosition / g_NumBitsInWord] &= ~(1 << (vBitPosition%g_NumBitsInWord));//按位取反再与操作
}

bool isAvailableBitAt(int vBitPosition, const SBitMap& vBitMap)
{//测试第vBitPosition位是否为0
	int temp = (vBitMap.pMapData[vBitPosition / g_NumBitsInWord]) & (~(1 << (vBitPosition%g_NumBitsInWord)));//第vBitPosition位置为0(临时用于判断)
	return temp == vBitMap.pMapData[vBitPosition / g_NumBitsInWord];//若相等返回1则表示确实为0，不为零返回0
}

int countClearBits(const SBitMap& vBitMap)
{ //统计vBitMap没有被占用的位数（为1表示占用，0表示没占用）
	int count = 0;//计数器
	for (int i = 0; i < vBitMap.NumBits; i++)
	{
		if (isAvailableBitAt(i, vBitMap))count++;
	}
	return count;
}

int findAndSetAvailableBit(SBitMap& voBitMap)
{//返回第一个没有被占用的位，并将其置1;没有则返回-1
	for (int i = 0; i < voBitMap.NumBits; i++)
	{
		if (isAvailableBitAt(i, voBitMap))
		{
			markBitAt(i, voBitMap);
			return i;
		}
	}
	return -1;//没有找到
}

void printfBitMap(const SBitMap& vBitMap)
{
	for (int i = 0; i < vBitMap.NumBits; ++i)
	{
		if (isAvailableBitAt(i, vBitMap)) printf("0 ");
		else printf("1 ");
	}
	printf("\n");
}