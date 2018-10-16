#pragma once
#include"DblNode.h"
template<class ElemType>
class SimpleDblLinkList
{
protected://ѭ������ʵ�ֵľݳ�Ա
	DblNode<ElemType> *head;//ͷ�ڵ�ָ��
	//��������ģ��
	DblNode<ElemType> *GetElemPtr(int position)const;//����ָ���position���ڵ��ָ��
	void Init();//��ʼ��
public:
	SimpleDblLinkList();//�޲����Ĺ��캯��ģ��
	virtual ~SimpleDblLinkList();//��������ģ��
	int Length() const;//�����Ա���
	bool Empty() const;//�ж����Ա��Ƿ�Ϊ��
	void Clear();//�����Ա����
	void Traverse(void(*visit)(const ElemType &));//�������Ա�
	StatusCode GetElem(int position, ElemType &e) const;//��ָ��λ�õ�Ԫ��
	StatusCode SetElem(int position, const ElemType& e);//�����ö�λ�õ�Ԫ��ֵ
	StatusCode Delete(int position, ElemType& e);//ɾ��Ԫ��
	StatusCode Insert(int position, const ElemType& e);//����Ԫ��
	SimpleDblLinkList(const SimpleDblLinkList<ElemType>&copy);//���ƹ��캯��
	SimpleDblLinkList<ElemType>&operator=(const SimpleDblLinkList<ElemType>&copy);
	//���ظ�ֵ�����
};

