#include "editor.h"
#include<fstream>
#include<string>
#include<iostream>
#include<cctype>
using namespace std;
editor::editor()
{
	text = new SimpleDblLinkList<string>;
}
editor::~editor()
{
	delete text;
}
void editor::OpenFile(string file_name)
{
	filename = file_name;
	curline = 0;
	totallines = 0;
	infile.open(file_name);
	if (!infile.is_open())
	{
		cout << "无法打开文件" <<file_name<< endl;
		cout << "程序终止" << endl;
		getchar();
		getchar();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "打开文件成功" << endl;
		string line;
		while (infile.good())
		{
			getline(infile, line);
			text->Insert(++totallines, line);
			curline++;
		}
	}
}
void editor::ShowTheFile()
{
	string line;
	for(int i=1;i<=totallines;i++)
	{
		text->GetElem(i, line);
		cout << line << endl;
	}
}
void editor::ToTheFirstLine()
{
	curline = 1;
}
void editor::ToTheLastLine()
{
	curline = totallines;
}
void editor::ToThePreviousLine()
{
	if (curline == 1)cout << "当前行已为第一行！！！" << endl;
	else curline--;
}
void editor::ToTheNextLine()
{
	if (curline == totallines)cout << "当前行已为最后一行！！！" << endl;
	else curline++;
}
void editor::ToTheDesignatedLine(int whichline)
{
	if (whichline > totallines || whichline < 1)
	{
		cout << "您输入的行数不存在，请重新输入" << endl;
		cout << "请输入1到" << totallines << "之间的一个数" << endl;
	}
	else
		curline = whichline;
}
void editor::InsertAline(int numberofline, string newline)
{
	if (numberofline > totallines+1 || numberofline < 1)
	{
		cout << "您输入的行数不存在，请重新输入" << endl;
		cout << "请输入1到" << totallines << "之间的一个数" << endl;
	}
	else
	{
		curline = numberofline;
		text->Insert(curline, newline);
	    totallines++;
	}
}
void editor::DeleteAline(int numberofline)
{
	if (numberofline > totallines || numberofline < 1)
	{
		cout << "您输入的行数不存在，请重新输入" << endl;
		cout << "请输入1到" << totallines << "之间的一个数" << endl;
	}
	else 
	{
		string deleteline;
		curline = numberofline;
		text->Delete(curline, deleteline);
		curline--;
		cout << "您已删除第" << numberofline << "行，当前行为" << curline << endl;
		cout << "您删除的内容是:" << endl << deleteline << endl;
		totallines--;
	}
}
void editor::Count(int &lines, int &words)
{
	words = 0;
	string tmp;
	for (int tmpline = 1; tmpline <= totallines; tmpline++)
	{
	    text->GetElem(tmpline, tmp);
		words += countword(tmp);
	}
	lines = totallines;
}
int  editor::countword(string line)
{
	int words = 0;
	for (auto c : line)
	{
		if (!isspace(c))
			words++;
	}
	return words;
}
void editor::SaveFile()
{
	outfile.open(filename);
	if (!outfile.is_open())
	{
		cout << "无法打开文件" << filename << endl;
		cout << "程序终止" << endl;
		exit(EXIT_FAILURE);
	}
	else 
	{
		for (int i = 1; i <=totallines; i++)
		{
			string tmpline;
			text->GetElem(i, tmpline);
			outfile << tmpline << endl;
		}
		/*string tmpline;
		text->GetElem(totallines, tmpline);
		for (int i = 0; i < tmpline.length(); i++)
			outfile.put(tmpline[i]);*/
		//text->Clear();
		cout << "保存文件成功！！" << endl;
	}
}
void editor::Help()
{
	cout << "本编辑器需要使用命令操作，对文件进行行编辑，以下是命令列表：" << endl;
	cout << "1.打开文件请输入：o" << endl;
	cout << "2.将文件内容打印到屏幕上请输入：s" << endl;
	cout << "3.切换到第一行请输入：t1" << endl;
	cout << "4.切换到最后一行请输入: t2" << endl;
	cout << "5.切换到前一行请输入：t3" << endl;
	cout << "6.切换到下一行请输入：t4" << endl;
	cout << "7.切换到指定行请输入：t5 并在空格后输入行数(注意不要超过文件总行数!）" << endl;
	cout << "8.插入一行到指定行请输入：i 并在空格后输入行数(注意不要超过文件总行数!）,回车后输入插入内容" << endl;
	cout << "9.删除指定行请输入： d 并在空格后输入行数（注意不要超过文件总行数！）" << endl;
	cout << "10.替换当前行请输入：r 并在回车后开始输入替换内容" << endl;
	cout << "11.替换当前行内子串请输入：u 在空格后输入想要替换的子串并在回车后输入新子串" << endl;
	cout << "12.查找字串请输入： f 在空格后输入想要查找的子串" << endl;
	cout << "13.统计行数与字数请输入： c" << endl;
	cout << "14.重新读取文件请输入： a" << endl;
	cout << "15.保存分拣请输入： b" << endl;
	cout << "16.退出请输入：e" << endl;
}
void editor::Exit()
{
	infile.close();
	outfile.close();
}
void editor::ReReadFile()
{
	curline = 0;
	totallines = 0;
	infile.close();
	infile.open(filename);
	if (!infile.is_open())
	{
		cout << "无法打开文件" << filename << endl;
		cout << "程序终止" << endl;
		exit(EXIT_FAILURE);
	}
	else 
	{
		cout << "打开文件成功" << endl;
		string line;
		while (infile.good())
		{
			getline(infile, line);
			text->Insert(++totallines, line);
			curline++;
		}
	}
}
void editor::ReplaceCurrentLine(string newline)
{
	string deleteline;
	text->Delete(curline, deleteline);
	text->Insert(curline, newline);
}
void editor::ReplaceSubstring(string newstring,string prestring)
{
	string deleteline;
	text->Delete(curline, deleteline);
	deleteline.replace(FindSubstring(prestring),prestring.length(), newstring);
	text->Insert(curline, deleteline);
}
int editor::FindSubstring(string substring)
{
	string Curline;
	text->GetElem(curline, Curline);
	int position=Curline.find(substring);
	cout << "字串“" << substring << "”的位置是" << position << endl;
	return position;
}