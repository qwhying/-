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
		cout << "�޷����ļ�" <<file_name<< endl;
		cout << "������ֹ" << endl;
		getchar();
		getchar();
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "���ļ��ɹ�" << endl;
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
	if (curline == 1)cout << "��ǰ����Ϊ��һ�У�����" << endl;
	else curline--;
}
void editor::ToTheNextLine()
{
	if (curline == totallines)cout << "��ǰ����Ϊ���һ�У�����" << endl;
	else curline++;
}
void editor::ToTheDesignatedLine(int whichline)
{
	if (whichline > totallines || whichline < 1)
	{
		cout << "����������������ڣ�����������" << endl;
		cout << "������1��" << totallines << "֮���һ����" << endl;
	}
	else
		curline = whichline;
}
void editor::InsertAline(int numberofline, string newline)
{
	if (numberofline > totallines+1 || numberofline < 1)
	{
		cout << "����������������ڣ�����������" << endl;
		cout << "������1��" << totallines << "֮���һ����" << endl;
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
		cout << "����������������ڣ�����������" << endl;
		cout << "������1��" << totallines << "֮���һ����" << endl;
	}
	else 
	{
		string deleteline;
		curline = numberofline;
		text->Delete(curline, deleteline);
		curline--;
		cout << "����ɾ����" << numberofline << "�У���ǰ��Ϊ" << curline << endl;
		cout << "��ɾ����������:" << endl << deleteline << endl;
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
		cout << "�޷����ļ�" << filename << endl;
		cout << "������ֹ" << endl;
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
		cout << "�����ļ��ɹ�����" << endl;
	}
}
void editor::Help()
{
	cout << "���༭����Ҫʹ��������������ļ������б༭�������������б�" << endl;
	cout << "1.���ļ������룺o" << endl;
	cout << "2.���ļ����ݴ�ӡ����Ļ�������룺s" << endl;
	cout << "3.�л�����һ�������룺t1" << endl;
	cout << "4.�л������һ��������: t2" << endl;
	cout << "5.�л���ǰһ�������룺t3" << endl;
	cout << "6.�л�����һ�������룺t4" << endl;
	cout << "7.�л���ָ���������룺t5 ���ڿո����������(ע�ⲻҪ�����ļ�������!��" << endl;
	cout << "8.����һ�е�ָ���������룺i ���ڿո����������(ע�ⲻҪ�����ļ�������!��,�س��������������" << endl;
	cout << "9.ɾ��ָ���������룺 d ���ڿո������������ע�ⲻҪ�����ļ�����������" << endl;
	cout << "10.�滻��ǰ�������룺r ���ڻس���ʼ�����滻����" << endl;
	cout << "11.�滻��ǰ�����Ӵ������룺u �ڿո��������Ҫ�滻���Ӵ����ڻس����������Ӵ�" << endl;
	cout << "12.�����ִ������룺 f �ڿո��������Ҫ���ҵ��Ӵ�" << endl;
	cout << "13.ͳ�����������������룺 c" << endl;
	cout << "14.���¶�ȡ�ļ������룺 a" << endl;
	cout << "15.����ּ������룺 b" << endl;
	cout << "16.�˳������룺e" << endl;
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
		cout << "�޷����ļ�" << filename << endl;
		cout << "������ֹ" << endl;
		exit(EXIT_FAILURE);
	}
	else 
	{
		cout << "���ļ��ɹ�" << endl;
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
	cout << "�ִ���" << substring << "����λ����" << position << endl;
	return position;
}