#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;
int main() {
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
		while (infile.good()) {
			getline(infile,line);//���ж�ȡ�ļ�
			if (line.find("//") == 0)continue;//�������'//'��ͷ����ע�ͣ���Ҫ����
			else if (line == "")continue;//����Ҳ����
			else {
				
			}
		}
	}
	getchar();
	infile.close();
	return 0;

}