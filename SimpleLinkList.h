#pragma once
#include"node.h"
enum StatusCode { SUCCESS, FALL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERED, ENTRY_FOUND, VISITED, UNVISITED };
template<class ElemType>
class SimpleLinkList
{
protected:
	node<ElemType> *head;      //ͷ�ڵ�ָ��
	//��������ģ��
	node<ElemType> *GetElemPtr(int position)const;//����ָ���position���ڵ��ָ��
//	node<ElemType> *Max()const;
//	int number(const ElemType &e)const;
	void Init();
//	void create(ElemType a[],int n)const;
//	void tidyup();
public:
	SimpleLinkList();             //�޲ι��캯��ģ��
	virtual ~SimpleLinkList();            //��������ģ��
	int Length() const;                 //�����Ա���
	bool Empty() const;                 //�ж����Ա��Ƿ�Ϊ��
	void Clear();                       //�����Ա����
	void Traverse(void(*visit)(const ElemType &))const;//�������Ա�
	StatusCode GetElem(int position,ElemType &e)const;//��ָ��λ��Ԫ��
	StatusCode SetElem(int position, const ElemType &e);//����ָ��λ��Ԫ��
	StatusCode Delete(int position, ElemType &e);//ɾ��Ԫ��
	StatusCode Insert(int position, const ElemType &e);//����Ԫ��
	SimpleLinkList(const SimpleLinkList<ElemType> &copy);//���ƹ��캯��ģ��
	SimpleLinkList<ElemType> &operator=(const SimpleLinkList<ElemType> &copy);//���ظ�ֵ�����
};

