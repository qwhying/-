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
{ //��λʾͼ�е�vBitPositionλ��Ϊ0
	vioBitMap.pMapData[vBitPosition / g_NumBitsInWord] &= ~1 << (vBitPosition%g_NumBitsInWord);//��λȡ���������
}

bool isAvailableBitAt(int vBitPosition, const SBitMap& vBitMap)
{//���Ե�vBitPositionλ�Ƿ�Ϊ0
	int temp = vBitMap.pMapData[vBitPosition / g_NumBitsInWord] &= ~1 << (vBitPosition%g_NumBitsInWord);//��vBitPositionλ��Ϊ0(��ʱ�����ж�)
	return temp == vBitMap.pMapData[vBitPosition / g_NumBitsInWord];//����ȷ���1���ʾȷʵΪ0����Ϊ�㷵��0
}

int countClearBits(const SBitMap& vBitMap)
{ //ͳ��vBitMapû�б�ռ�õ�λ����Ϊ1��ʾռ�ã�0��ʾûռ�ã�
	int count = 0;//������
	for (int i = 0; i < vBitMap.NumBits; i++)
	{
		if (isAvailableBitAt(i, vBitMap))count++;
	}
	return count;
}

int findAndSetAvailableBit(SBitMap& voBitMap)
{//���ص�һ��û�б�ռ�õ�λ����������1;û���򷵻�-1
	for (int i = 0; i < voBitMap.NumBits; i++)
	{
		if (isAvailableBitAt(i, voBitMap))
		{
			markBitAt(i, voBitMap);
			return i;
		}
	}
	return -1;//û���ҵ�
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