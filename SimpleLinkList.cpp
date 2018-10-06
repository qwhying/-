#include "SimpleLinkList.h"

template<class ElemType>
node<ElemType>*SimpleLinkList<ElemType>::GetElemPtr(int position)const {
	node<ElemType> *tmpPtr = head;//��tmp�������Ա��Բ��ҵ�position�����
	int curPosition = 0;          //tmp��ָ���λ��

	while (tmpPtr != NULL && curPosition < position) {//˳ָ�����
		tmpPtr = tmpPtr->next;
		curPosition++;
	}
	if (tmpPtr != NULL && curPosition == position)
	{
		//���ҳɹ�
		return tmpPtr;
	}
	else
	{//����ʧ��
		return NULL;
	}
}
template<class ElemType>
void SimpleLinkList<ElemType>::Init()//��ʼ�����Ա�
{
	head = new node<ElemType>;//����ͷָ��
}
template<class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList()
{
	Init();
}
template<class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList()
{
	Clear();//������Ա�
	delete head;//�ͷ�ͷ���ռ�
}
template<class ElemType>
int SimpleLinkList<ElemType>::Length() const
{
	int count = 0;//������
	for(node<ElemType> *tmpPtr=head->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
	{//��tmp����ָ��ÿ��Ԫ��
		count++;
	}
	return count;
}
template<class ElemType>
bool SimpleLinkList<ElemType>::Empty()const
{
	return head->next == NULL;//������Ա�Ϊ�շ���true���򷵻�false
}
template<class ElemType>
void SimpleLinkList<ElemType>::Clear()
{
	ElemType tmpElem;//��ʱԪ��ֵ
	while(Length()>0)
	{//���Ա�ǿ�,��ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}
template<class ElemType>
void SimpleLinkList<ElemType>::Traverse(void(*visit)(const ElemType &))const//���ζ�ÿ��Ԫ�ص��ú���visit
{
	for (node<ElemType> *tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{//��tmp����ָ��ÿ��Ԫ��
		(*visit)(temPtr->data);//�����Ա��ÿ��Ԫ�ص��ã�*visit������
	}
}
template<class ElemType>
StatusCode SimpleLinkList<ElemType>::GetElem(int position, ElemType &e)const
{//�����Ա���ڵ�POSITION��Ԫ��ʱ����e������ֵ������ENTRY_FOUND,
	//���򷵻�NOT_PRESENT
	if(position<1||position>Length())
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
StatusCode SimpleLinkList<ElemType>::SetElem(int position, const ElemType &e)
{//�����Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe
	if (position<1 || position>Length())
	{//��Χ��
		return RANGE_ERROR;
	}
	else{//position�Ϸ�
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//ȡ��ָ���position������ָ��
		tmpPtr->data = e;//���õ�Position��Ԫ�ص�ֵ
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleLinkList<ElemType>::Insert(int position, const ElemType &e)//�ڵ�position��λ��ǰ����Ԫ��e
{
	if (position<1 || position>length() + 1)
	{//position��Χ��
		return RANGE_ERROR;
	}
	else 
	{//position�Ϸ�
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position-1);//ȡ��ָ���POSITION-1������ָ��
		node<ElemType> *newPtr = new node<ElemType>(e, tmpPtr->next);//�����µĽ��
		tmpPtr->next = newPtr;//��new���뵽��㣬��tmp��new����
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleLinkList<ElemType>::Delete(int position, ElemType &e)
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
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType> &copy)
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
SimpleLinkList<ElemType>& SimpleLinkList<ElemType>::operator=(const SimpleLinkList<ElemType> &copy)
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