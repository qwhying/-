#pragma once
#include<string>
struct Class
{
	int classNumber;//�γ̱��
	std::string className;//�γ���
	int classPeriod;//�γ�ѧʱ
	int classSemester;//����ѧ��
	int classPrecondition;
	int classPrecondition2;
	int getcount();
	void printclassName();
	Class(int classnum, std::string name, int classperiod, int classSemester, int preconditon,int precondition2);
	~Class();
};

