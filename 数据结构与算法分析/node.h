#pragma once
enum StatusCode { SUCCESS, FALL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERED, ENTRY_FOUND, VISITED, UNVISITED };
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

