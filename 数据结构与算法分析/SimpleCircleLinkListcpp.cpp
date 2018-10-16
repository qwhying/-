#include"SimpleCircleLinkList.h"
#include<stdio.h>
template<class ElemType>
node<ElemType>* SimpleCircleLinkList<ElemType>::GetElemPtr(int position)const
//操作结果：返回指向第position个元素的指针
{
	if (position == 0)
	{//头节点的序号为0
		return head;
	}
	node<ElemType>* tmpPtr = head->next;//用tmp遍历线性表以查找第position个点
	int curPosition = 1;
	while (tmpPtr!=head&&curPosition<position)
	{//顺指针向后查找，知道tmp指向第position个结点
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
void SimpleCircleLinkList<ElemType>::Init()
{//初始化线性表
	head = new node<ElemType>;//构造头指针
	head->next = head;//空循环链表的头节点后继为头节点本身
}
template<class ElemType>
int SimpleCircleLinkList<ElemType>::Length()const
{//操作结果：返回线性表元素个数
	int count = 0;//计数器
	for (node<ElemType> * tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//用Tmp依次指向每个元素
		count++;//对线性表每个元素进行计数
	}
	return count;
}
template<class ElemType>
bool SimpleCircleLinkList<ElemType>::Empty()const
{//操作结果，空返回true否则返回false
	return head->next == head;
}
template<class ElemType>
void SimpleCircleLinkList<ElemType>::Traverse(void(*visit)(const ElemType &))
{//操作结果：依次对线性表的每个元素，调用函数（*visit）
	for (node<ElemType> *tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{//用tmp依次指向每个元素
		(*visit)(tmpPtr->data);//对线性表的每个元素调用函数（*visit）
	}
}
template<class ElemType>
SimpleCircleLinkList<ElemType>::SimpleCircleLinkList()
{
	Init();
}
template<class ElemType>
SimpleCircleLinkList<ElemType>::~SimpleCircleLinkList()
{
	Clear();//清空线性表
	delete head;//释放头结点空间
}
template<class ElemType>
void SimpleCircleLinkList<ElemType>::Clear()
{
	ElemType tmpElem;//临时元素值
	while (Length() > 0)
	{//线性表非空,则删除第1个元素
		Delete(1, tmpElem);
	}
}
template<class ElemType>
StatusCode SimpleCircleLinkList<ElemType>::GetElem(int position, ElemType &e)const
{//当线性表存在第POSITION个元素时，用e返回其值，返回ENTRY_FOUND,
	//否则返回NOT_PRESENT
	if (position<1 || position>Length())
	{//position范围错
		return RANGE_ERROR;
	}
	else {//position 合法
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//取出指向第position个结点的指针
		e = tmpPtr->data;              //用e返回第position个元素的值
		return ENTRY_FOUND;
	}
}
template<class ElemType>
StatusCode SimpleCircleLinkList<ElemType>::SetElem(int position, const ElemType &e)
{//将线性表的第position个位置的元素赋值为e
	if (position<1 || position>Length())
	{//范围错
		return RANGE_ERROR;
	}
	else {//position合法
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//取出指向第position个结点的指针
		tmpPtr->data = e;//设置第Position个元素的值
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleCircleLinkList<ElemType>::Insert(int position,ElemType &e)//在第position个位置前插入元素e
{
	if (position<1 || position>length() + 1)
	{//position范围错
		return RANGE_ERROR;
	}
	else
	{//position合法
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);//取出指向第POSITION-1个结点的指针
		node<ElemType> *newPtr = new node<ElemType>(e, tmpPtr->next);//生成新的结点
		tmpPtr->next = newPtr;//将new插入到结点，即tmp与new相连
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleCircleLinkList<ElemType>::Delete(int position, ElemType &e)
{//删除线性表第position个位置的元素，并用e返回其值
	if (position<1 || position>length())
	{//范围错
		return RANGE_ERROR;
	}
	else {//范围合法
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);//取出position-1个结点的指针
		node<ElemType> *nextPtr = tmpPtr->next;//nextptr为tmp的后继
		tmpPtr->next = nextPtr->next;//删除结点
		e = nextPtr->data;//用e返回被删除结点元素值
		delete nextPtr;//释放被删除结点
		return SUCCESS;
	}
}
template<class ElemType>
SimpleCircleLinkList<ElemType>::SimpleCircleLinkList(const SimpleCircleLinkList<ElemType> &copy)
{//由线性表copy构造新的线性表-复制构造函数模板
	int copyLength = copy.Length();//copy的长度
	ElemType e;
	Init();//初始化新链表
	for (int curPosition = 1; curPosition <= copyLength; curPosition++) {//复制数据元素
		copy.GetElem(curPosition, e);//取出第cur个元素
		Insert(Length() + 1, e);//将e插入到当前线性表
	}
}
template<class ElemType>
SimpleCircleLinkList<ElemType>& SimpleCircleLinkList<ElemType>::operator=(const SimpleCircleLinkList<ElemType> &copy)
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
