#include "SimpleDblLinkList.h"


template<class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList()
{
	Init();
}

template<class ElemType>
SimpleDblLinkList<ElemType>::~SimpleDblLinkList()
{
}
template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::Insert(int position, const ElemType &e)
{//操作结果：在线性表的第position个位置前插入元素e
//position的取值范围为1≤position≤length（）+1
//position合法时返回SUCCESS，否则返回RANGE_ERROR
	if (position<1 || position>Length() + 1)
	{
		//position范围错
		return RANGE_ERROR;//位置不合法
	}
	else//position合法
	{
		DblNode<ElemType> *tmpPtr, *nextPtr, *newPtr;
		tmpPtr = GetElemPtr(position - 1);//取出指向第position-1个结点的指针
		nextPtr = tmpPtr->next;//next指向第position个结点
		newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);//生成新结点
		tmpPtr->next = newPtr;//修在向右的指针
		nextPtr->back = newPtr;//修改向左的指针
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::Delete(int position, ElemType &e)
//操作结果：删除线性表的第position个位置的元素，
//并用e返回其值。position的取值范围是1≤position≤length（），
{
	if (position<1 || position>Length())
	{
		//position范围错
		return RANGE_ERROR;
	}
	else {
		//POSITION合法
		DblNode<ElemType>*tmpPtr;
		tmpPtr = GetElemPtr(position);//取出指向第position个结点的指针
		tmpPtr->back->next = tmpPtr->next;//修改向右的指针
		tmpPtr->next->back = tmpPtr->back;//修改向左的指针
		e = tmpPtr->data;//用e返回被删除结点的元素值
		delete tmpPtr;//释放被删结点
		return SUCCESS;
	}
}
