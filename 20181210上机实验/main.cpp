#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;
int main() {
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
		while (infile.good()) {
			getline(infile,line);//按行读取文件
			if (line.find("//") == 0)continue;//如果行以'//'开头则是注释，需要跳过
			else if (line == "")continue;//空行也跳过
			else {
				
			}
		}
	}
	getchar();
	infile.close();
	return 0;

}