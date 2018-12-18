#pragma once
#include<string>
struct Class
{
	int classNumber;//课程编号
	std::string className;//课程名
	int classPeriod;//课程学时
	int classSemester;//开课学期
	int classPrecondition;
	int classPrecondition2;
	int getcount();
	void printclassName();
	Class(int classnum, std::string name, int classperiod, int classSemester, int preconditon,int precondition2);
	~Class();
};

