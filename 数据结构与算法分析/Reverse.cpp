#include"SqStack.h"
#include"SqStack.cpp"
#include<iostream>
using namespace std;
void Reverse1()
//��ʼ����������һ������n��n������
//������������෴��˳�����n������
{
	int n, e;
	SqStack<int> tmpS;//��ʱջ
	cout << "����һ��������";
	cin >> n;
	while (n <= 0)
	{
		//��֤nΪ������
		cout << "��������Ϊ����0������������n��";
		cin >> n;
	}
	cout << "������" << n << "��������" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> e;
		tmpS.Push(e);
	}
	cout << "��������෴˳�������" << endl;
	while (!tmpS.Empty())
	{
		//��ջ�������
		tmpS.Pop(e);
		cout << e << " ";
	}
}
int main()
{
	Reverse1();
	return 0;
}