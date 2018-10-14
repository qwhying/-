#pragma once
#include"SimpleLinkList.h"
template<class ElemType>
void Reverse(SimpleLinkList<ElemType>&la)
//操作结果：将la中元素按逆置
{
	ElemType aItem, bItem;
	for (int position = 1; position <= la.Length() / 2; position++)
	{
		//取出la中的元素
		la.GetElem(position, aItem);//取出la的第position个元素
		la.GetElem(la.Length() - position + 1, bItem);//取出la的第n-position+1个元素
		//互相交换位置存入la中
		la.SetElem(position, bItem);
		la.SetElem(la.Length() - position + 1, aItem);
	}
}