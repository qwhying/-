#pragma once
template<class ElemType>
class node
{
public:
	//���ݳ�Ա
	ElemType data;            //������
	node<ElemType> *next;     //ָ����
	//���캯��ģ��
	node();
	node(ElemType item, node<ElemType> *link = NULL);
	~node();
};

