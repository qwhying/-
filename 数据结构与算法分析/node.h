#pragma once
enum StatusCode { SUCCESS, FALL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERED, ENTRY_FOUND, VISITED, UNVISITED };
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

