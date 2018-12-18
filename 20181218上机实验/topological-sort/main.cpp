#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<sstream>
#include<vector>
#include<list>
#include<queue>
#include"Class.h"
using namespace std;
vector<int> topsort(vector<int> countarray, vector<list<int>> datalink)
{//拓扑排序算法，输出结果是一个排序后的课程顺序，以课程编号表示
	queue<int> q;//入度为0的课程队列（即没有前提的课程队列）
	vector<int> answer;//输出答案
	for (int i = 0; i <(int)countarray.size(); i++)
	{
		if (countarray[i] == 0)
		{//建立入度为0的队列
			q.push(i);
		}
	}
	while (!q.empty())//如果队列不为空
	{
		int temp = q.front();//先从队首弹出一个入度为0的课
		answer.push_back(temp);//输出到答案
		q.pop();//从图中删除结点
		while (!datalink[temp].empty())
		{//将弹出课的所有后继课程的入度减1
			countarray[datalink[temp].back()-1]--;
			if (countarray[datalink[temp].back()-1] == 0)
				q.push(datalink[temp].back()-1);//如果减1后入度为0，则进队
			datalink[temp].pop_back();
		}
		
	}
	if (answer.size() < countarray.size())//如果输出的结点数少于图中的结点数，则说明图中存在回路无法完成排序
	{
		cout << "图中存在回路，无法进行拓扑排序!" << endl;
		getchar();
		exit(1);
	}
	return answer;

}
void show_out(int classinsemesters[], vector<int> answer, vector<Class> allclasses,int semesters)
{

	int cursemester = 0;//当前学期
	int classnum = 0;//当前学期课程数量
	vector<vector<string>> classtable;
	classtable.resize(8);
	for (int i = 0; i < allclasses.size(); i++)
	{
		if(allclasses[i].classSemester)
			classtable[allclasses[i].classSemester-1].push_back(allclasses[i].className);
	}
	bool first = true;
	for (int i = 0; i < allclasses.size(); i++)
	{
		if (classnum == classinsemesters[cursemester]&&i<answer.size())
		{
			cout << endl;
			cursemester++;
			classnum = 0;
			cout << "第" << cursemester+1 << "学期： ";
			while (!classtable[cursemester].empty())
			{
				string temp=classtable[cursemester].back();
				classtable[cursemester].pop_back();
				cout << temp << "  ";
				classnum++;
			}
		}
		else if (cursemester == 0 && first) {
			cout << "第" << cursemester + 1 << "学期： "; first = !first;
			while (!classtable[cursemester].empty())
			{
				string temp = classtable[cursemester].back();
				classtable[cursemester].pop_back();
				cout << temp << "  ";
				classnum++;
			}
		}
		else if (classnum == classinsemesters[cursemester]&&i >= answer.size())
		{
			
			cout << endl;
			cursemester++;
			classnum = 0;
			cout << "第" << cursemester + 1 << "学期： ";
			while (!classtable[cursemester].empty())
			{
				string temp = classtable[cursemester].back();
				classtable[cursemester].pop_back();
				cout << temp << "  ";
				classnum++;
			}
			if (cursemester == classtable.size() - 1)
			{
				return;
			}
		}
		allclasses[answer[i]].classSemester = cursemester + 1;
		classnum++;
		allclasses[answer[i]].printclassName();
	}
}
int main() {
	int classNumofeachSemester[8];
	vector<Class> Allclasses;
	ifstream infile;
	infile.open("course_inf.txt");//文件输入流
	if (!infile.is_open()) {
		cout << "文件打开失败！程序终止！" << endl;
		getchar();
		exit(EXIT_FAILURE);
	}
	else {
		string line;

		cout << "文件打开成功！" << endl;
		while (infile.good()) 
		{
			getline(infile,line);//按行读取文件
			if (line.find("//") == 0)continue;//如果行以'//'开头则是注释，需要跳过
			else if (line == "")continue;//空行也跳过
			else if(line[0]=='c'){//课程表的读入
				string tmp;
				int tmpClassNumber;//临时变量，存储某一节课的课程编号
				string tmpClassName;//课程名称
				int tmpClassPeriod;//学时数
				int tmpClassSemester;//指定开课学期
				int tmpClassPrecondition;//先决条件
				int tmpClassPrecondition2;//先决条件2
				stringstream ss;//字符串流（自动跳过空格）
				stringstream buff1,buff2,buff3;//缓冲器，用于将课程编号转变成整数
				ss << line;
				ss >> tmp;
				buff1 << tmp.substr(1, 2);
				buff1 >> tmpClassNumber;
				ss >> tmpClassName;
				ss >> tmpClassPeriod;
				ss >> tmpClassSemester;
				tmp.clear();
				ss >> tmp;
				if (tmp == "") {
					tmpClassPrecondition = 0;
					tmpClassPrecondition2 = 0;
				}
				else {
					buff2 << tmp.substr(1, 2);
					buff2 >> tmpClassPrecondition;
					tmp.clear();
					ss >> tmp;
					if (tmp == "") tmpClassPrecondition2 = 0;
					else {
						buff3 << tmp.substr(1, 2);
						buff3 >> tmpClassPrecondition2;
					}
				}
				/*cout << tmpClassNumber << " " << tmpClassName << " " << tmpClassPeriod << " " << tmpClassSemester << " " << tmpClassPrecondition;
				cout << " " << tmpClassPrecondition2 << endl;*/
				Class a(tmpClassNumber, tmpClassName, tmpClassPeriod, tmpClassSemester, tmpClassPrecondition, tmpClassPrecondition2);
				Allclasses.push_back(a);
			}
			else {//下面为各学期所开的课程数
				stringstream ss;
				ss << line;
				for (int i = 0; i < 8; i++)
				{
					ss >> classNumofeachSemester[i];

				}

			}
		}
	}
	infile.close();
	vector<int> count;//count数组，用于存放每个课（结点）的入度（前提课程数）
	for (Class i : Allclasses)
	{
		if(i.classSemester==0)
		count.push_back(i.getcount());
	}
	vector<list<int>> datalink;//AOV网邻接表，表中存放每个课的后继课程
	datalink.resize(count.size());
	for (int i = 0; i <(int)count.size(); i++)//初始化AOV网络邻接表
	{
		if (count[i])//有前提条件的课
		{
			if (count[i] == 2)//如果有两个前提条件课
			{
				datalink[Allclasses[i].classPrecondition - 1].push_back(i + 1);//那么将这节课存放进它的前提条件1课的AOV表中
				datalink[Allclasses[i].classPrecondition2 - 1].push_back(i + 1);//将这节课存放进它的前提条件2课的AOV表中
			}
			else//如果有一个前提条件课
				datalink[Allclasses[i].classPrecondition - 1].push_back(i + 1);//将它存放进入AOV表中
		}
	}
	cout << "拓扑排序结果：（以课程号表示）" << endl;
	vector<int> answer = topsort(count, datalink);
	for (int i = 0; i < answer.size(); i++)
	{
		cout <<"c"<< answer[i]+1 << " ";
		cout << endl;
	}
	cout << "按照学期排课表可得：" << endl;
	show_out(classNumofeachSemester, answer, Allclasses,8);//输出
	getchar();
	return 0;

}