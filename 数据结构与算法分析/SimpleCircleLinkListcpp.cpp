#include"SimpleCircleLinkList.h"
#include<stdio.h>
template<class ElemType>
node<ElemType>* SimpleCircleLinkList<ElemType>::GetElemPtr(int position)const
//�������������ָ���position��Ԫ�ص�ָ��
{
	if (position == 0)
	{//ͷ�ڵ�����Ϊ0
		return head;
	}
	node<ElemType>* tmpPtr = head->next;//��tmp�������Ա��Բ��ҵ�position����
	int curPosition = 1;
	while (tmpPtr!=head&&curPosition<position)
	{//˳ָ�������ң�֪��tmpָ���position�����
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
void SimpleCircleLinkList<ElemType>::Init()
{//��ʼ�����Ա�
	head = new node<ElemType>;//����ͷָ��
	head->next = head;//��ѭ�������ͷ�ڵ���Ϊͷ�ڵ㱾��
}
template<class ElemType>
int SimpleCircleLinkList<ElemType>::Length()const
{//����������������Ա�Ԫ�ظ���
	int count = 0;//������
	for (node<ElemType> * tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//��Tmp����ָ��ÿ��Ԫ��
		count++;//�����Ա�ÿ��Ԫ�ؽ��м���
	}
	return count;
}
template<class ElemType>
bool SimpleCircleLinkList<ElemType>::Empty()const
{//����������շ���true���򷵻�false
	return head->next == head;
}
template<class ElemType>
void SimpleCircleLinkList<ElemType>::Traverse(void(*visit)(const ElemType &))
{//������������ζ����Ա��ÿ��Ԫ�أ����ú�����*visit��
	for (node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//��tmp����ָ��ÿ��Ԫ��
		(*visit)(tmpPtr->data);//�����Ա��ÿ��Ԫ�ص��ú�����*visit��
	}
}
template<class ElemType>
SimpleCircleLinkList<ElemType>::SimpleCircleLinkList()
{
	Init();
}
template<class ElemType>
SimpleCircleLinkList<ElemType>::~SimpleCircleLinkList()
{
	Clear();//������Ա�
	delete head;//�ͷ�ͷ���ռ�
}
template<class ElemType>
void SimpleCircleLinkList<ElemType>::Clear()
{
	ElemType tmpElem;//��ʱԪ��ֵ
	while (Length() > 0)
	{//���Ա�ǿ�,��ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}
template<class ElemType>
StatusCode SimpleCircleLinkList<ElemType>::GetElem(int position, ElemType &e)const
{//�����Ա���ڵ�POSITION��Ԫ��ʱ����e������ֵ������ENTRY_FOUND,
	//���򷵻�NOT_PRESENT
	if (position<1 || position>Length())
	{//position��Χ��
		return RANGE_ERROR;
	}
	else {//position �Ϸ�
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//ȡ��ָ���position������ָ��
		e = tmpPtr->data;              //��e���ص�position��Ԫ�ص�ֵ
		return ENTRY_FOUND;
	}
}
template<class ElemType>
StatusCode SimpleCircleLinkList<ElemType>::SetElem(int position, const ElemType &e)
{//�����Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe
	if (position<1 || position>Length())
	{//��Χ��
		return RANGE_ERROR;
	}
	else {//position�Ϸ�
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//ȡ��ָ���position������ָ��
		tmpPtr->data = e;//���õ�Position��Ԫ�ص�ֵ
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleCircleLinkList<ElemType>::Insert(int position,ElemType &e)//�ڵ�position��λ��ǰ����Ԫ��e
{
	if (position<1 || position>length() + 1)
	{//position��Χ��
		return RANGE_ERROR;
	}
	else
	{//position�Ϸ�
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);//ȡ��ָ���POSITION-1������ָ��
		node<ElemType> *newPtr = new node<ElemType>(e, tmpPtr->next);//�����µĽ��
		tmpPtr->next = newPtr;//��new���뵽��㣬��tmp��new����
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleCircleLinkList<ElemType>::Delete(int position, ElemType &e)
{//ɾ�����Ա��position��λ�õ�Ԫ�أ�����e������ֵ
	if (position<1 || position>length())
	{//��Χ��
		return RANGE_ERROR;
	}
	else {//��Χ�Ϸ�
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);//ȡ��position-1������ָ��
		node<ElemType> *nextPtr = tmpPtr->next;//nextptrΪtmp�ĺ��
		tmpPtr->next = nextPtr->next;//ɾ�����
		e = nextPtr->data;//��e���ر�ɾ�����Ԫ��ֵ
		delete nextPtr;//�ͷű�ɾ�����
		return SUCCESS;
	}
}
template<class ElemType>
SimpleCircleLinkList<ElemType>::SimpleCircleLinkList(const SimpleCircleLinkList<ElemType> &copy)
{//�����Ա�copy�����µ����Ա�-���ƹ��캯��ģ��
	int copyLength = copy.Length();//copy�ĳ���
	ElemType e;
	Init();//��ʼ��������
	for (int curPosition = 1; curPosition <= copyLength; curPosition++) {//��������Ԫ��
		copy.GetElem(curPosition, e);//ȡ����cur��Ԫ��
		Insert(Length() + 1, e);//��e���뵽��ǰ���Ա�
	}
}
template<class ElemType>
SimpleCircleLinkList<ElemType>& SimpleCircleLinkList<ElemType>::operator=(const SimpleCircleLinkList<ElemType> &copy)
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
