
#include"utility.h"
#include"lk_stack.h"
#include<string>
using namespace std;
class Calculater
{

public:
	Calculater();
	~Calculater();
	void Run();//执行表达式
	string formula;
private:
	LinkStack<double> OPND;//操作数栈
	LinkStack<char> OPTR;//操作符栈
	int isp(char op);//栈内优先数
	int icp(char op);//站外优先数
	double DoOperator(double x, char op, double y);//形成运算指令，进行运算
	//void GetChar(char &ch);//从输入流获取一字符ch，并跳过空格及回车
	bool IsOperator(char ch);//判断ch是否为操作符
};

