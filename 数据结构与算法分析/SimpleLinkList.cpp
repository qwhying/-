#include "SimpleLinkList.h"

template<class ElemType>
node<ElemType>*SimpleLinkList<ElemType>::GetElemPtr(int position)const {
	node<ElemType> *tmpPtr = head;//用tmp遍历线性表以查找第position个结点
	int curPosition = 0;          //tmp所指结点位置

	while (tmpPtr != NULL && curPosition < position) {//顺指针查找
		tmpPtr = tmpPtr->next;
		curPosition++;
	}
	if (tmpPtr != NULL && curPosition == position)
	{
		//查找成功
		return tmpPtr;
	}
	else
	{//查找失败
		return NULL;
	}
}
/*template<class ElemType>
node<ElemType>*SimpleLinkList<ElemType>::Max()const {
	node<ElemType> *tmpPtr = head;
	node<ElemType> max = head->next->data;//第一个设为最大值
	node<ElemType> maxPtr = head->next;//最大值的地址附在第一个上
	int curPosition = 0;
	while (tmpPtr != NULL && curPosition < Length())
	{
		tmpPtr = tmpPtr->next;
		curPosition++;
		if (max < tmpPtr->data)
		{
			max = tmpPtr->data;
			maxPtr = tmpPtr;
		}
	}
	return maxPtr;
}*/
/*template<class ElemType>
int SimpleLinkList<ElemType>::number(const ElemType &e)const
{
	node<ElemType> *tmpPtr = head;
	int count = 0;
	while (tmpPtr != NULL)
	{
		if (tmpPtr->data == e)
			count++;
	}
	return count;
}*/
/*template<class ElemType>
void SimpleLinkList<ElemType>::create(ElemType a[], int n)const
{//根据一维数组来创建一个单链表
	head = new node<ElemType>;
	node<ElemType> *tmpPtr = new node<ElemType>(a[n - 1], NULL);
	for (int i = n-2; i>=0; i--) {//从末位向前创建单链表可以实现时间复杂度为0(n)
		tmpPtr = new node<ElemType>(a[i], tmpPtr);
	}
	head->next = tmpPtr;
}*/
/*template<class ElemType>
void SimpleLinkList<ElemType>::tidyup()
{
	node<ElemType> *tmpPtr = head;
	while (tmpPtr != NULL) {
		tmpPtr = tmpPtr->next;
		if (tmpPtr->data == tmpPtr->next->data)//若与后面的相等则应该删去
		{
			node<ElemType> *nextPtr = tmpPtr->next;
			tmpPtr->next = nextPtr->next;//删除结点
			delete nextPtr;//释放结点
		}
	}
}*/
template<class ElemType>
void SimpleLinkList<ElemType>::Init()//初始化线性表
{
	head = new node<ElemType>;//构造头指针
}
template<class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList()
{
	Init();
}
template<class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList()
{
	Clear();//清空线性表
	delete head;//释放头结点空间
}
template<class ElemType>
int SimpleLinkList<ElemType>::Length() const
{
	int count = 0;//计数器
	for(node<ElemType> *tmpPtr=head->next;tmpPtr!=NULL;tmpPtr=tmpPtr->next)
	{//用tmp依次指向每个元素
		count++;
	}
	return count;
}
template<class ElemType>
bool SimpleLinkList<ElemType>::Empty()const
{
	return head->next == NULL;//如果线性表为空返回true否则返回false
}
template<class ElemType>
void SimpleLinkList<ElemType>::Clear()
{
	ElemType tmpElem;//临时元素值
	while(Length()>0)
	{//线性表非空,则删除第1个元素
		Delete(1, tmpElem);
	}
}
template<class ElemType>
void SimpleLinkList<ElemType>::Traverse(void(*visit)(const ElemType &))const//依次对每个元素调用函数visit
{
	for (node<ElemType> *tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{//用tmp依次指向每个元素
		(*visit)(temPtr->data);//对线性表的每个元素调用（*visit）函数
	}
}
template<class ElemType>
StatusCode SimpleLinkList<ElemType>::GetElem(int position, ElemType &e)const
{//当线性表存在第POSITION个元素时，用e返回其值，返回ENTRY_FOUND,
	//否则返回NOT_PRESENT
	if(position<1||position>Length())
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
StatusCode SimpleLinkList<ElemType>::SetElem(int position, const ElemType &e)
{//将线性表的第position个位置的元素赋值为e
	if (position<1 || position>Length())
	{//范围错
		return RANGE_ERROR;
	}
	else{//position合法
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);//取出指向第position个结点的指针
		tmpPtr->data = e;//设置第Position个元素的值
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleLinkList<ElemType>::Insert(int position, const ElemType &e)//在第position个位置前插入元素e
{
	if (position<1 || position>length() + 1)
	{//position范围错
		return RANGE_ERROR;
	}
	else 
	{//position合法
		node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position-1);//取出指向第POSITION-1个结点的指针
		node<ElemType> *newPtr = new node<ElemType>(e, tmpPtr->next);//生成新的结点
		tmpPtr->next = newPtr;//将new插入到结点，即tmp与new相连
		return SUCCESS;
	}
}
template<class ElemType>
StatusCode SimpleLinkList<ElemType>::Delete(int position, ElemType &e)
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
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType> &copy)
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
SimpleLinkList<ElemType>& SimpleLinkList<ElemType>::operator=(const SimpleLinkList<ElemType> &copy)
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
