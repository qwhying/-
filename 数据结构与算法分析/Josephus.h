#pragma once
#include"SimpleCircleLinkList.h"
#include<iostream>
using namespace std;
void Josephus(int n, int m)/*���������
						   n����Χ��һ��ԲȦ����һ���˿�ʼ����������m���˳��У��ٴ���һ���˿�ʼ����1����mֱ�����ʣ��һ����*/
{
	SimpleCircleLinkList<int> la;//�����ѭ������
	int position = 0;//�����������������е����
	int out, winer;
	for (int k = 1; k <= n; k++)
		la.Insert(k, k);//����������Ϊ1��2��������n��ѭ������
	cout << "�����ߣ�";
	for (int i = 1; i < n; i++)//ѭ��n-1�Σ���n-1���˳���
	{
		for (int j = 1; j <= m; j++)//��1������m
		{
			position++;
			if (position > la.Length())
				position = 1;
		}
		la.Delete(position--, out);//������m���˳���
		cout << out << " ";
	}
	la.GetElem(1, winer);//ʣ�µ�һ����Ϊ��ʤ��
	cout << endl << "��ʤ��:" << winer << endl;
	}
}