#include"DblNode.h"
template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item, DblNode<ElemType> *linkBack, DblNode<ElemType> *linkNext)
{
	//操作结果：构造一个数据与为item，和指针域为linkback和linknext的结点
	data = item;
	back = linkBack;
	next = linkNext;
}