#pragma once
template<class ElemType>
class node
{
public:
	//数据成员
	ElemType data;            //数据域
	node<ElemType> *next;     //指针域
	//构造函数模板
	node();
	node(ElemType item, node<ElemType> *link = NULL);
	~node();
};

