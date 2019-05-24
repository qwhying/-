#ifndef BITMAP_H_
#define BITMAP_H_

const short g_NumBitsInWord = sizeof(int) * 8;

struct SBitMap
{
	int NumBits;   //λʾͼ��С
	int *pMapData;
};

int countClearBits(const SBitMap& vBitMap);                        //ͳ��vBitMapû�б�ռ�õ�λ����Ϊ1��ʾռ�ã�0��ʾûռ�ã�
int findAndSetAvailableBit(SBitMap& voBitMap);                     //���ص�һ��û�б�ռ�õ�λ����������1;û���򷵻�-1
bool isAvailableBitAt(int vBitPosition, const SBitMap& vBitMap);   //���Ե�vBitPositionλ�Ƿ�Ϊ0
void createEmptyBitMap(SBitMap& voBitMap, int vNumTotalBits);      //����һ����СΪvNumTotalBits�Ŀ�λʾͼ
void markBitAt(int vBitPosition, SBitMap& vioBitMap);              //��λʾͼ�е�vBitPositionλ��Ϊ1
void clearBitAt(int vBitPosition, SBitMap& voBitMap);              //��λʾͼ�е�vBitPositionλ��Ϊ0
void printfBitMap(const SBitMap& vBitMap);                         //��ӡλʾͼ

#endif