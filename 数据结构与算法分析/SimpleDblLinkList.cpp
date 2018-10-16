#include "SimpleDblLinkList.h"


template<class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList()
{
	Init();
}

template<class ElemType>
SimpleDblLinkList<ElemType>::~SimpleDblLinkList()
{
}
template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::Insert(int position, const ElemType &e)
{//��������������Ա�ĵ�position��λ��ǰ����Ԫ��e
//position��ȡֵ��ΧΪ1��position��length����+1
//position�Ϸ�ʱ����SUCCESS�����򷵻�RANGE_ERROR
	if (position<1 || position>Length() + 1)
	{
		//position��Χ��
		return RANGE_ERROR;//λ�ò��Ϸ�
	}
	else//position�Ϸ�
	{
		DblNode<ElemType> *tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);//ȡ��ָ���position-1������ָ��
		nextPtr = tmpPtr->next;//nextָ���position�����
		newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);//�����½��
		tmpPtr->next = newPtr;//�������ҵ�ָ��
		nextPtr->back = newPtr;//�޸������ָ��
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::Delete(int position, ElemType &e)
//���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ�أ�
//����e������ֵ��position��ȡֵ��Χ��1��position��length������
{
	if (position<1 || position>Length())
	{
		//position��Χ��
		return RANGE_ERROR;
	}
	else {
		//POSITION�Ϸ�
		DblNode<ElemType>*tmpPtr;
		tmpPtr = GetElemPtr(position);//ȡ��ָ���position������ָ��
		tmpPtr->back->next = tmpPtr->next;//�޸����ҵ�ָ��
		tmpPtr->next->back = tmpPtr->back;//�޸������ָ��
		e = tmpPtr->data;//��e���ر�ɾ������Ԫ��ֵ
		delete tmpPtr;//�ͷű�ɾ���
		return SUCCESS;
	}
}
