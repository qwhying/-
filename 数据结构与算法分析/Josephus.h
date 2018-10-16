#pragma once
#include"SimpleCircleLinkList.h"
#include<iostream>
using namespace std;
void Josephus(int n, int m)/*操作结果：
						   n个人围城一个圆圈，第一个人开始报数，报道m个人出列，再从下一个人开始，从1报到m直到最后剩下一个人*/
{
	SimpleCircleLinkList<int> la;//定义空循环链表
	int position = 0;//报数到的人再链表中的序号
	int out, winer;
	for (int k = 1; k <= n; k++)
		la.Insert(k, k);//建立数据域为1，2，。。。n的循环链表
	cout << "出列者：";
	for (int i = 1; i < n; i++)//循环n-1次，让n-1个人出列
	{
		for (int j = 1; j <= m; j++)//从1报数到m
		{
			position++;
			if (position > la.Length())
				position = 1;
		}
		la.Delete(position--, out);//报数到m的人出列
		cout << out << " ";
	}
	la.GetElem(1, winer);//剩下的一个人为优胜者
	cout << endl << "优胜者:" << winer << endl;
	}
}