#pragma once
enum StatusCode { SUCCESS, FALL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERED, ENTRY_FOUND, VISITED, UNVISITED };
template<class ElemType>
struct DblNode
{
	//数据成员
	ElemType data;//数据域
	DblNode<ElemType> *back;//指向前驱的指针域
	DblNode<ElemType> *next;//指向后继的指针域
	//构造函数模板：
	DblNode();
	DblNode(ElemType, DblNode<ElemType> *linkBack = NULL, DblNode<ElemType>*linkNext = NULL);
};