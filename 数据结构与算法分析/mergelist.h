#pragma once
#include"SimpleLinkList.h"
template<class ElemType>
void MergeList(const SimpleLinkList<ElemType>& la, const SimpleLinkList<ElemType>& lb, SimpleLinkList<ElemType>& lc)
//��ʼ������la��lb������Ԫ�ص�������
//�����������la��lb�ϲ�Ϊlc��ʹlc��Ԫ���Ե�������
{
	ElemType aItem, bItem;//la��lb�е�ǰ����Ԫ��
	int aLength = la.Length(), bLength = lb.Length();//la��lb����
	int  aPosition = 1, bPosition = 1;//la��lb��ǰԪ�����

	lc.Clea();
	while (aPosition <= aLength && bPosition <= bLength)
	{//ȡ��la��lb������Ԫ�ؽ��й鲢
		la.GetElem(aPosition, aItem);//ȡ��la������Ԫ��
		lb.GetElem(bPosition, bItem);//ȡ��lb������Ԫ��
		if (aItem < bItem) {//�鲢aItem
			lc.Insert(lc.Length() + 1, aItem);//����aItem��lc
			aPosition++;//ָ��la��һ����Ԫ��
		}
		else {
			//�鲢bItem
			lc.Insert(lc.Length() + 1, bItem);//����bItem��lc
			bPosition++;//ָ��lb��һ����Ԫ��
		}
	}
	while (aPosition <= aLength) {
		//�鲢la��ʣ������Ԫ��
		la.GetElem(aPosition, aItem);
		lc.Insert(lc.Length() + 1, aItem);
		aPosition++;
	}
	while (bPosition <= bLength) {//�鲢lb��ʣ������Ԫ��
		lb.GetElem(bPosition, bItem);
		lc.Insert(lc.Length() + 1, bItem);
		bPosition++;
	}

}
	