#pragma once
#define DEFAULT_SIZE 100//默认元素个数
#define DEFAULT_INFINITY 1000000//默认无穷大
enum StatusCode { SUCCESS, FALL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERED, ENTRY_FOUND, VISITED, UNVISITED };
template<class ElemType>
class SqStack
{
protected:
	//顺序栈的数据成员
	int count;//元素个数
	int maxSize;//栈最大元素个数
	ElemType *elems;//元素存储空间
	//辅助函数模板
	bool Full() const;//判断栈是否已满
	void Init(int size);//初始化栈
public:
	                                   /*抽象数据类型方法声明及重载编译系统默认方法声明*/
	SqStack(int size = DEFAULT_SIZE);  /*构造函数模板*/
	virtual~SqStack();                 //析构函数模板
	int Length()const;                 //求栈长度
	bool Empty()const;                 //判断栈是否为空
	void Clear();                      //清空栈
	void Traverse(void(*visit)(const ElemType &))const;//遍历栈
	StatusCode Push(const ElemType &e);//入栈
	StatusCode Top(ElemType &e)const;  //返回栈顶元素
	StatusCode Pop(ElemType &e);       //出栈
	SqStack(const SqStack<ElemType> &copy);//复制构造函数模板
	SqStack<ElemType>&operator=(const SqStack<ElemType>&copy);//重载赋值运算符

};