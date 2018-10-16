#pragma once
#include"DblNode.h"
template<class ElemType>
class SimpleDblLinkList
{
protected://循环链表实现的据成员
	DblNode<ElemType> *head;//头节点指针
	//辅助函数模板
	DblNode<ElemType> *GetElemPtr(int position)const;//返回指向第position个节点的指针
	void Init();//初始化
public:
	SimpleDblLinkList();//无参数的构造函数模板
	virtual ~SimpleDblLinkList();//析构函数模板
	int Length() const;//求线性表长度
	bool Empty() const;//判断线性表是否为空
	void Clear();//将线性表清空
	void Traverse(void(*visit)(const ElemType &));//遍历线性表
	StatusCode GetElem(int position, ElemType &e) const;//求指定位置的元素
	StatusCode SetElem(int position, const ElemType& e);//设置置顶位置的元素值
	StatusCode Delete(int position, ElemType& e);//删除元素
	StatusCode Insert(int position, const ElemType& e);//插入元素
	SimpleDblLinkList(const SimpleDblLinkList<ElemType>&copy);//复制构造函数
	SimpleDblLinkList<ElemType>&operator=(const SimpleDblLinkList<ElemType>&copy);
	//重载赋值运算符
};

