#pragma once
#include"SimpleLinkList.h"
template<class ElemType>
void Reverse(SimpleLinkList<ElemType>&la)
//�����������la��Ԫ�ذ�����
{
	ElemType aItem, bItem;
	for (int position = 1; position <= la.Length() / 2; position++)
	{
		//ȡ��la�е�Ԫ��
		la.GetElem(position, aItem);//ȡ��la�ĵ�position��Ԫ��
		la.GetElem(la.Length() - position + 1, bItem);//ȡ��la�ĵ�n-position+1��Ԫ��
		//���ཻ��λ�ô���la��
		la.SetElem(position, bItem);
		la.SetElem(la.Length() - position + 1, aItem);
	}
}