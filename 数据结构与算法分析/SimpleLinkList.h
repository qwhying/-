#pragma once
#include"node.h"
enum StatusCode { SUCCESS, FALL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERED, ENTRY_FOUND, VISITED, UNVISITED };
template<class ElemType>
class SimpleLinkList
{
protected:
	node<ElemType> *head;      //头节点指针
	//辅助函数模板
	node<ElemType> *GetElemPtr(int position)const;//返回指向第position个节点的指针
//	node<ElemType> *Max()const;
//	int number(const ElemType &e)const;
	void Init();
//	void create(ElemType a[],int n)const;
//	void tidyup();
public:
	SimpleLinkList();             //无参构造函数模板
	virtual ~SimpleLinkList();            //析构函数模板
	int Length() const;                 //求线性表长度
	bool Empty() const;                 //判断线性表是否为空
	void Clear();                       //将线性表清空
	void Traverse(void(*visit)(const ElemType &))const;//遍历线性表
	StatusCode GetElem(int position,ElemType &e)const;//求指定位置元素
	StatusCode SetElem(int position, const ElemType &e);//设置指定位置元素
	StatusCode Delete(int position, ElemType &e);//删除元素
	StatusCode Insert(int position, const ElemType &e);//插入元素
	SimpleLinkList(const SimpleLinkList<ElemType> &copy);//复制构造函数模板
	SimpleLinkList<ElemType> &operator=(const SimpleLinkList<ElemType> &copy);//重载赋值运算符
};

