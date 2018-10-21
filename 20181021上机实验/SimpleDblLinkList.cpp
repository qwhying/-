#include "SimpleDblLinkList.h"
#include"DblNode.h"
#include<stdio.h>

template<class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList()
{
	Init();
}
template<class ElemType>
DblNode<ElemType>* SimpleDblLinkList<ElemType>::GetElemPtr(int position)const
/*�������������ָ���position��Ԫ�ص�ָ��*/
{
	if (position == 0)
	{                                           //ͷ�ڵ�����Ϊ0
		return head;
	}
	DblNode<ElemType>* tmpPtr = head->next;     //��tmp�������Ա��Բ��ҵ�position����
	int curPosition = 1;
	while (tmpPtr != head && curPosition < position)
	{                                           //˳ָ�������ң�֪��tmpָ���position�����
		tmpPtr = tmpPtr->next;
		curPosition++;
	}
	if (tmpPtr != head && curPosition == position)
	{//���ҳɹ�
		return tmpPtr;
	}
	else
	{//����ʧ��
		return NULL;
	}
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
		nextPtr = tmpPtr->next;//nextPtrָ���position�����
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
template<class ElemType>
int SimpleDblLinkList<ElemType>::Length()const
{//����������������Ա�Ԫ�ظ���
	int count = 0;//������
	for (DblNode<ElemType> * tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//��Tmp����ָ��ÿ��Ԫ��
		count++;//�����Ա�ÿ��Ԫ�ؽ��м���
	}
	return count;
}
template<class ElemType>
bool SimpleDblLinkList<ElemType>::Empty()const
{//����������շ���true���򷵻�false
	return head->next == head;
}
template<class ElemType>
void SimpleDblLinkList<ElemType>::Traverse(void(*visit)(const ElemType &))
{//������������ζ����Ա��ÿ��Ԫ�أ����ú�����*visit��
	for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//��tmp����ָ��ÿ��Ԫ��
		(*visit)(tmpPtr->data);//�����Ա��ÿ��Ԫ�ص��ú�����*visit��
	}
}
template<class ElemType>
void SimpleDblLinkList<ElemType>::Clear()
{
	ElemType tmpElem;//��ʱԪ��ֵ
	while (Length() > 0)
	{//���Ա�ǿ�,��ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}
template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::GetElem(int position, ElemType &e)const
{//�����Ա���ڵ�POSITION��Ԫ��ʱ����e������ֵ������ENTRY_FOUND,
	//���򷵻�NOT_PRESENT
	if (position<1 || position>Length())
	{//position��Χ��
		return RANGE_ERROR;
	}
	else {//position �Ϸ�
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//ȡ��ָ���position������ָ��
		e = tmpPtr->data;              //��e���ص�position��Ԫ�ص�ֵ
		return ENTRY_FOUND;
	}
}
template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::SetElem(int position, const ElemType &e)
{//�����Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe
	if (position<1 || position>Length())
	{//��Χ��
		return RANGE_ERROR;
	}
	else {//position�Ϸ�
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//ȡ��ָ���position������ָ��
		tmpPtr->data = e;//���õ�Position��Ԫ�ص�ֵ
		return SUCCESS;
	}
}
template<class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList(const SimpleDblLinkList<ElemType> &copy)
{                                                 //�����Ա�copy�����µ����Ա�-���ƹ��캯��ģ��
	int copyLength = copy.Length();//copy�ĳ���
	ElemType e;
	Init();//��ʼ��������
	for (int curPosition = 1; curPosition <= copyLength; curPosition++) {//��������Ԫ��
		copy.GetElem(curPosition, e);//ȡ����cur��Ԫ��
		Insert(Length() + 1, e);//��e���뵽��ǰ���Ա�
	}
}
template<class ElemType>
SimpleDblLinkList<ElemType>& SimpleDblLinkList<ElemType>::operator=(const SimpleDblLinkList<ElemType> &copy)
{
	if (&copy != this) {
		int copyLength = copy.Length();//copy�ĳ���
		ElemType e;
		Init();//��ʼ����ǰ���Ա�
		for (int curPosition = 1; curPosition <= copyLength; curPosition++)
		{//��������Ԫ��
			copy.GetElem(curPosition, e);//ȡ����cur��Ԫ��
			Insert(Length() + 1, e);//��e���뵽��ǰ���Ա�
		}
	}
	return *this;
}
template<class ElemType>
void SimpleDblLinkList<ElemType>::Init()
{//��ʼ�����Ա�
	head = new DblNode<ElemType>;//����ͷָ��
	head->next = head;//��ѭ�������ͷ�ڵ���Ϊͷ�ڵ㱾��
}


