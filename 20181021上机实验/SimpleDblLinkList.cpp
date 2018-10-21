#include "SimpleDblLinkList.h"
#include"DblNode.h"
#include<stdio.h>

template<class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList()
{
	Init();
}
template<class ElemType>
DblNode<ElemType>* SimpleDblLinkList<ElemType>::GetElemPtr(int position)const
/*操作结果：返回指向第position个元素的指针*/
{
	if (position == 0)
	{                                           //头节点的序号为0
		return head;
	}
	DblNode<ElemType>* tmpPtr = head->next;     //用tmp遍历线性表以查找第position个点
	int curPosition = 1;
	while (tmpPtr != head && curPosition < position)
	{                                           //顺指针向后查找，知道tmp指向第position个结点
		tmpPtr = tmpPtr->next;
		curPosition++;
	}
	if (tmpPtr != head && curPosition == position)
	{//查找成功
		return tmpPtr;
	}
	else
	{//查找失败
		return NULL;
	}
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
		nextPtr = tmpPtr->next;//nextPtr指向第position个结点
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
template<class ElemType>
int SimpleDblLinkList<ElemType>::Length()const
{//操作结果：返回线性表元素个数
	int count = 0;//计数器
	for (DblNode<ElemType> * tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//用Tmp依次指向每个元素
		count++;//对线性表每个元素进行计数
	}
	return count;
}
template<class ElemType>
bool SimpleDblLinkList<ElemType>::Empty()const
{//操作结果，空返回true否则返回false
	return head->next == head;
}
template<class ElemType>
void SimpleDblLinkList<ElemType>::Traverse(void(*visit)(const ElemType &))
{//操作结果：依次对线性表的每个元素，调用函数（*visit）
	for (DblNode<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//用tmp依次指向每个元素
		(*visit)(tmpPtr->data);//对线性表的每个元素调用函数（*visit）
	}
}
template<class ElemType>
void SimpleDblLinkList<ElemType>::Clear()
{
	ElemType tmpElem;//临时元素值
	while (Length() > 0)
	{//线性表非空,则删除第1个元素
		Delete(1, tmpElem);
	}
}
template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::GetElem(int position, ElemType &e)const
{//当线性表存在第POSITION个元素时，用e返回其值，返回ENTRY_FOUND,
	//否则返回NOT_PRESENT
	if (position<1 || position>Length())
	{//position范围错
		return RANGE_ERROR;
	}
	else {//position 合法
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//取出指向第position个结点的指针
		e = tmpPtr->data;              //用e返回第position个元素的值
		return ENTRY_FOUND;
	}
}
template<class ElemType>
StatusCode SimpleDblLinkList<ElemType>::SetElem(int position, const ElemType &e)
{//将线性表的第position个位置的元素赋值为e
	if (position<1 || position>Length())
	{//范围错
		return RANGE_ERROR;
	}
	else {//position合法
		DblNode<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//取出指向第position个结点的指针
		tmpPtr->data = e;//设置第Position个元素的值
		return SUCCESS;
	}
}
template<class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList(const SimpleDblLinkList<ElemType> &copy)
{                                                 //由线性表copy构造新的线性表-复制构造函数模板
	int copyLength = copy.Length();//copy的长度
	ElemType e;
	Init();//初始化新链表
	for (int curPosition = 1; curPosition <= copyLength; curPosition++) {//复制数据元素
		copy.GetElem(curPosition, e);//取出第cur个元素
		Insert(Length() + 1, e);//将e插入到当前线性表
	}
}
template<class ElemType>
SimpleDblLinkList<ElemType>& SimpleDblLinkList<ElemType>::operator=(const SimpleDblLinkList<ElemType> &copy)
{
	if (&copy != this) {
		int copyLength = copy.Length();//copy的长度
		ElemType e;
		Init();//初始化当前线性表
		for (int curPosition = 1; curPosition <= copyLength; curPosition++)
		{//复制数据元素
			copy.GetElem(curPosition, e);//取出第cur个元素
			Insert(Length() + 1, e);//将e插入到当前线性表
		}
	}
	return *this;
}
template<class ElemType>
void SimpleDblLinkList<ElemType>::Init()
{//初始化线性表
	head = new DblNode<ElemType>;//构造头指针
	head->next = head;//空循环链表的头节点后继为头节点本身
}


