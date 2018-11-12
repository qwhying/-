#include "Calculater.h"
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
#include<sstream>

Calculater::Calculater()
{
	OPND.Clear();
	OPTR.Clear();
}


Calculater::~Calculater()
{
	OPND.Clear();
	OPTR.Clear();
}

int Calculater::icp(char op)//定义运算符的优先级（栈外）
{
	switch (op)
	{
	case '+':
		return 2;
		break;
	case '-':
		return 2;
		break;
	case '*':
		return 4;
		break;
	case '/':
		return 4;
		break;
	case '(':
		return 6;
		break;
	case ')':
		return 1;
		break;
	case '=':
		return 0;
		break;
	}

}
int Calculater::isp(char op)//定义运算符的优先级（栈内）
{
	switch (op)
	{
	case '+':
		return 3;
		break;
	case '-':
		return 3;
		break;
	case '*':
		return 5;
		break;
	case '/':
		return 5;
		break;
	case '(':
		return 1;
		break;
	case ')':
		return 7;
		break;
	case '=':
		return 0;
		break;
	}
}
double Calculater::DoOperator(double x, char op, double y)//进行运算
{
	switch (op) {
	case '+':return x + y;
		break;
	case '-':return x - y;
		break;
	case '*':return x * y;
		break;
	case '/':return x / y;
		break;
	default:
		break;
	}
}
/*void Calculater::GetChar(char &ch)
{
	while (ch = getchar() == '\n' || ch == ' ') {
		if (ch == '\n')
			break;
	}
}*/
bool Calculater::IsOperator(char ch)//判断是否是一个有效的运算符
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/'||ch=='('||ch==')'||ch=='=');
}
void Calculater::Run()
{
	cout << "请输入表达式：（以等号结尾）" << endl;
	getline(cin,this->formula);
	//OPTR.Push('=');
	while (true) {
		char temp = formula[0];
		if (isdigit(temp))
		{
			stringstream ss(formula);
			double temp;
			ss >> temp;

			for (int i = 0; i < formula.length(); i++)
			{
				if (this->IsOperator(formula[i]))
				{
					formula.erase(0, i);
					break;
				}
			}
			OPND.Push(temp);
		}
		else if(this->IsOperator(temp))
		{
			char isp;
			OPTR.Top(isp);
			if (OPTR.Length()==0||this->isp(isp) < this->icp(temp))
			{
				OPTR.Push(temp);
				formula.erase(0,1);
				continue;
			}
			else if (this->isp(isp) > this->icp(temp))
			{
				OPTR.Pop(isp);
				double num1, num2;
				OPND.Pop(num2);
				OPND.Pop(num1);
				double ans=this->DoOperator(num1, isp, num2);
				OPND.Push(ans);
			}
			else if (this->isp(isp) == this->icp(temp))
			{
				OPTR.Pop(isp);
				formula.erase(0, 1);
			}
		}
		if (OPND.Length()==1&&OPTR.Length()==1) {
			double ans;
			OPND.Pop(ans);
			cout << ans << endl;
			break;
		}
	}
}