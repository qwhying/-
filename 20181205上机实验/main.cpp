#include"utility.h"
#include"MyHuffmanTree.h"
#include<string>
#include<cstring>
#include<fstream>
#include"MyHuffmanTree.cpp"
using namespace std;
/*class Text
{
public:
	string text;
};*/
int chars[256];
int statistics(string text) {//统计每个字符出现的次数和出现的不同的字符数
	int sum = 0;
	for (char e : text)//统计每个字符出现次数
	{
		chars[(int)e]++;
	}
	for (int i = 0; i < 256; i++)//统计不同字符数量
	{
		if (chars[i] != 0)sum++;
	}
	return sum;
}
unsigned int CharIndex(const char &ch)
//操作结果:字符位置映射
{
	//unsigned int result;//返回结果
	//if (ch == 'a') result = 1;//'a'的存储位置为1
	//else if (ch == 'b') result = 2;
	//else if (ch == 'c')result = 3;
	//result = (unsigned int)ch;
	unsigned int count = 0;
	for (int i = 0; i < 256; i++)
	{
		if ((char)i == ch) return ++count;
		else if (chars[i] != 0) count++;
	}
}
int main(void)
{
	string filename;//文件名
	ifstream infile;//输入文件流
	ofstream outfile;//输出文件流
	string text;//读入的字符串文本
	string code;//字符串编码（用于写入文件)
	while (true)
	{
		filename.clear();
		text.clear();
		code.clear();
		cout << "1.霍夫曼编码" << endl;
		cout << "2.霍夫曼译码" << endl;
		cout << "3.退出" << endl;
		cout << "请选择：";
		char ch = getchar();
		if (ch == '1') {
			cout << "请输入源文件名：";
			cin >> filename;
			memset(chars, 0, sizeof(chars));
			infile.open(filename);
			if (!infile.is_open())
			{
				cout << "无法打开文件 " << filename<< endl;
				cout << "程序终止" << endl;
				getchar();
				getchar();
				exit(EXIT_FAILURE);
			}
			else
			{
				cout << "打开文件成功！" << endl;
				string line;
				while (infile.good())
				{
					getline(infile, line);//按行读取
					text.append(line);
				}

			}
			int n = statistics(text);//统计字符串中各个字符出现的次数并且
			char ch[256];//字母表
			for (int i = 0; i < 256; i++)
				ch[i] = char(i);
			MyHuffmanTree<char, int>hmTree1(ch, chars, n, CharIndex);
			//MyHuffmanTree<char, int>hmTree(hmTree1);//复制构造函数
			MyHuffmanTree<char, int>hmTree = hmTree1;//赋值语句重载
			
			string strTmp;//临时字符串，存放单个字母的编码
			cout << "文本串" << text.c_str() << "编码为:";
			for (int pos = 0; pos < (int)text.length(); pos++)
			{
				strTmp = hmTree.Encode(text[pos]);//编码
				code.append(strTmp);//存入code中
				//cout << strTmp.c_str();
			}
			cout << code;
			cout << endl;
			filename.clear();
			cout << "请输入编码文件名：";
			cin >> filename;
			outfile.open(filename/*, ios::out | ios::binary*/);
			if (!outfile.is_open())
			{
				cout << "无法打开文件 " << filename<< endl;
				cout << "程序终止" << endl;
				getchar();
				getchar();
				exit(EXIT_FAILURE);
			}
			else
			{
				//Text text1;
				//text1.text = code;
				//outfile.write((char *)&text1, sizeof(Text));
				outfile << code;
				cout << "打开文件成功！成功存入文件！" << endl;
				//delete &text1;

			}
			infile.close();//关闭输入文件
			outfile.close();//关闭输出文件
			system("PAUSE");
		}
		else if (ch == '2')
		{
			filename.clear();
			text.clear();
			code.clear();
			cout << "请输入编码文件名：";
			cin >> filename;
			infile.open(filename/*, ios::in | ios::binary*/);
			if (!infile.is_open())
			{
				cout << "无法打开文件 " << filename << endl;
				cout << "程序终止" << endl;
				getchar();
				getchar();
				exit(EXIT_FAILURE);
			}
			else
			{
				//Text text2;
				//infile.read((char*)&text2,sizeof(Text));
				//code = text2.text;
				//delete &text2;
				cout << "打开文件成功！" << endl;
				infile >> code;
				cout << "编码串 " << code << "译码为：";
				infile.close();
				infile.open("in.txt");
				string line;
				while (infile.good())
				{
					getline(infile, line);//按行读取
					text.append(line);
				}
				int n = statistics(text);//统计字符串中各个字符出现的次数并且
				char ch[256];//字母表
				for (int i = 0; i < 256; i++)
					ch[i] = char(i);
				MyHuffmanTree<char, int>hmTree1(ch, chars, n, CharIndex);
				//MyHuffmanTree<char, int>hmTree(hmTree1);//复制构造函数
				MyHuffmanTree<char, int>hmTree = hmTree1;
				text.clear();
				list<char> lkText = hmTree.Decode(code);
				for (char c : lkText)
				{
					text = text + c;
				}
				cout << text;
			}
			filename.clear();
			cout << "请输入源文件名：";
			cin >> filename;
			outfile.open(filename);
			if (!outfile.is_open())
			{
				cout << "无法打开文件 " << filename << endl;
				cout << "程序终止" << endl;
				getchar();
				getchar();
				exit(EXIT_FAILURE);
			}
			else
			{
				outfile << text;
				cout << "打开文件成功！成功存入文件！" << endl;

			}
			infile.close();//关闭输入文件
			outfile.close();//关闭输出文件
			system("PAUSE");
		}
		else if(ch=='3')
		exit(1);
		else {
		cout << "输入有误，请重新输入，选择1、2、3之一";
}
	}
	//cout << "编码串" << strCode.c_str() << "译码为：";
	//list<char> lkText = hmTree.Decode(strCode);
	//strText = lkText;
	//strText.erase();
	//for (char e : lkText)
	//{
	//	strText = strText + e;
	//}
	//cout << strText.c_str() << endl;
	//system("PAUSE");//调用库函数system
	return 0;

}