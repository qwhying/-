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
{//���������㷨����������һ�������Ŀγ�˳���Կγ̱�ű�ʾ
	queue<int> q;//���Ϊ0�Ŀγ̶��У���û��ǰ��Ŀγ̶��У�
	vector<int> answer;//�����
	for (int i = 0; i <(int)countarray.size(); i++)
	{
		if (countarray[i] == 0)
		{//�������Ϊ0�Ķ���
			q.push(i);
		}
	}
	while (!q.empty())//������в�Ϊ��
	{
		int temp = q.front();//�ȴӶ��׵���һ�����Ϊ0�Ŀ�
		answer.push_back(temp);//�������
		q.pop();//��ͼ��ɾ�����
		while (!datalink[temp].empty())
		{//�������ε����к�̿γ̵���ȼ�1
			countarray[datalink[temp].back()-1]--;
			if (countarray[datalink[temp].back()-1] == 0)
				q.push(datalink[temp].back()-1);//�����1�����Ϊ0�������
			datalink[temp].pop_back();
		}
		
	}
	if (answer.size() < countarray.size())//�������Ľ��������ͼ�еĽ��������˵��ͼ�д��ڻ�·�޷��������
	{
		cout << "ͼ�д��ڻ�·���޷�������������!" << endl;
		getchar();
		exit(1);
	}
	return answer;

}
void show_out(int classinsemesters[], vector<int> answer, vector<Class> allclasses,int semesters)
{

	int cursemester = 0;//��ǰѧ��
	int classnum = 0;//��ǰѧ�ڿγ�����
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
			cout << "��" << cursemester+1 << "ѧ�ڣ� ";
			while (!classtable[cursemester].empty())
			{
				string temp=classtable[cursemester].back();
				classtable[cursemester].pop_back();
				cout << temp << "  ";
				classnum++;
			}
		}
		else if (cursemester == 0 && first) {
			cout << "��" << cursemester + 1 << "ѧ�ڣ� "; first = !first;
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
			cout << "��" << cursemester + 1 << "ѧ�ڣ� ";
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
	infile.open("course_inf.txt");//�ļ�������
	if (!infile.is_open()) {
		cout << "�ļ���ʧ�ܣ�������ֹ��" << endl;
		getchar();
		exit(EXIT_FAILURE);
	}
	else {
		string line;

		cout << "�ļ��򿪳ɹ���" << endl;
		while (infile.good()) 
		{
			getline(infile,line);//���ж�ȡ�ļ�
			if (line.find("//") == 0)continue;//�������'//'��ͷ����ע�ͣ���Ҫ����
			else if (line == "")continue;//����Ҳ����
			else if(line[0]=='c'){//�γ̱�Ķ���
				string tmp;
				int tmpClassNumber;//��ʱ�������洢ĳһ�ڿεĿγ̱��
				string tmpClassName;//�γ�����
				int tmpClassPeriod;//ѧʱ��
				int tmpClassSemester;//ָ������ѧ��
				int tmpClassPrecondition;//�Ⱦ�����
				int tmpClassPrecondition2;//�Ⱦ�����2
				stringstream ss;//�ַ��������Զ������ո�
				stringstream buff1,buff2,buff3;//�����������ڽ��γ̱��ת�������
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
			else {//����Ϊ��ѧ�������Ŀγ���
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
	vector<int> count;//count���飬���ڴ��ÿ���Σ���㣩����ȣ�ǰ��γ�����
	for (Class i : Allclasses)
	{
		if(i.classSemester==0)
		count.push_back(i.getcount());
	}
	vector<list<int>> datalink;//AOV���ڽӱ����д��ÿ���εĺ�̿γ�
	datalink.resize(count.size());
	for (int i = 0; i <(int)count.size(); i++)//��ʼ��AOV�����ڽӱ�
	{
		if (count[i])//��ǰ�������Ŀ�
		{
			if (count[i] == 2)//���������ǰ��������
			{
				datalink[Allclasses[i].classPrecondition - 1].push_back(i + 1);//��ô����ڿδ�Ž�����ǰ������1�ε�AOV����
				datalink[Allclasses[i].classPrecondition2 - 1].push_back(i + 1);//����ڿδ�Ž�����ǰ������2�ε�AOV����
			}
			else//�����һ��ǰ��������
				datalink[Allclasses[i].classPrecondition - 1].push_back(i + 1);//������Ž���AOV����
		}
	}
	cout << "���������������Կγ̺ű�ʾ��" << endl;
	vector<int> answer = topsort(count, datalink);
	for (int i = 0; i < answer.size(); i++)
	{
		cout <<"c"<< answer[i]+1 << " ";
		cout << endl;
	}
	cout << "����ѧ���ſα�ɵã�" << endl;
	show_out(classNumofeachSemester, answer, Allclasses,8);//���
	getchar();
	return 0;

}