
#include"utility.h"
#include"lk_stack.h"
#include<string>
using namespace std;
class Calculater
{

public:
	Calculater();
	~Calculater();
	void Run();//ִ�б��ʽ
	string formula;
private:
	LinkStack<double> OPND;//������ջ
	LinkStack<char> OPTR;//������ջ
	int isp(char op);//ջ��������
	int icp(char op);//վ��������
	double DoOperator(double x, char op, double y);//�γ�����ָ���������
	//void GetChar(char &ch);//����������ȡһ�ַ�ch���������ո񼰻س�
	bool IsOperator(char ch);//�ж�ch�Ƿ�Ϊ������
};

