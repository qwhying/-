#include"SqStack.h"
#include"SqStack.cpp"
#include<iostream>
using namespace std;
void Reverse1()
//初始条件：读入一个整数n和n个整数
//操作结果：按相反的顺序输出n个整数
{
	int n, e;
	SqStack<int> tmpS;//临时栈
	cout << "输入一个整数：";
	cin >> n;
	while (n <= 0)
	{
		//保证n为正整数
		cout << "整数不能为负或0，请重新输入n：";
		cin >> n;
	}
	cout << "请输入" << n << "个整数：" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> e;
		tmpS.Push(e);
	}
	cout << "按输入的相反顺序输出：" << endl;
	while (!tmpS.Empty())
	{
		//出栈，并输出
		tmpS.Pop(e);
		cout << e << " ";
	}
}
int main()
{
	Reverse1();
	return 0;
}