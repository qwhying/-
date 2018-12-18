#include "Class.h"
#include<iostream>


Class::Class(int classnum, std::string name, int classperiod, int classSemester, int preconditon,int precondition2)
{
	classNumber = classnum;
	className = name;
	classPeriod = classperiod;
	this->classSemester= classSemester;
	classPrecondition = preconditon;
	classPrecondition2 = precondition2;

}
int Class::getcount()
{
	if (classPrecondition&&classPrecondition2)
		return 2;
	else if (classPrecondition || classPrecondition2)
		return 1;
	else return 0;
}
void Class::printclassName()
{
	std::cout << className << "  ";
}

Class::~Class()
{
}
