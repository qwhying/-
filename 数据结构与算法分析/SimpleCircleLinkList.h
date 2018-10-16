#pragma once
#include"node.h"
template<class ElemType>
class SimpleCircleLinkList
{
protected:
	//循环链表数据成员
	node<ElemType> *head;//头指针
	//辅助模板函数
	node<ElemType> *GetElemPtr(int position) const;//返回指向第position个结点的指针
	void Init();//初始化链表
public:
	SimpleCircleLinkList();//无参数的构造函数
	virtual~SimpleCircleLinkList();//析构函数模板
	int Length() const;//求线性表长度
	bool Empty() const;//判断线性表是否为空
	void Clear();//将线性表清空
	void Traverse(void(*visit)(const ElemType &));//遍历线性表
	StatusCode GetElem(int position, ElemType &e) const;//求指定位置的元素
	StatusCode SetElem(int position, const ElemType& e);//设置置顶位置的元素值
	StatusCode Delete(int position, ElemType& e);//删除元素
	StatusCode Insert(int position, ElemType& e);//插入元素
	SimpleCircleLinkList(const SimpleCircleLinkList<ElemType>&copy);//复制构造函数
	SimpleCircleLinkList<ElemType>&operator=(const SimpleCircleLinkList<ElemType>&copy);
	//重载赋值运算符
};
