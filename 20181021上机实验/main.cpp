#include"editor.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	editor a;//�����༭����
	bool exit = false;
	cout << "��ӭʹ��QW�ı��༭����" << endl;
	while (!exit) {
		cout << "�������������������help��ѯ����" << endl;
		string command;
		cin >> command;
		switch (command[0])
		{
		case 'o': 
		{
			string file;
			cout << "�������ļ�����";
			cin >> file;
			a.OpenFile(file);//���ļ�
			break;
		}
		case 's':
		{
			a.ShowTheFile();
			break;
		}
		case 't':
		{
			switch (command[1])
			{
			case '1':
			{
				a.ToTheFirstLine();
				break;
			}
			case '2':
			{
				a.ToTheLastLine();
				break;
			}
			case '3':
			{
				a.ToThePreviousLine();
				break;
			}
			case '4':
			{
				a.ToTheNextLine();
				break;
			}
			case '5':
			{
				int whichline;
				cin >> whichline;
				a.ToTheDesignatedLine(whichline);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 'i':
		{
			int whichline;
			cin >> whichline;
			getchar();
			string newline;
			getline(cin, newline);
			a.InsertAline(whichline, newline);
			break;
		}
		case 'd':
		{
			int whichline;
			cin >> whichline;
			a.DeleteAline(whichline);
			break;
		}
		case 'r':
		{
			string newline;
			cin >> newline;
			a.ReplaceCurrentLine(newline);
			break;
		}
		case 'u':
		{
			string prestring;
			cin >> prestring;
			string newstring;
			cin >> newstring;
			a.ReplaceSubstring(prestring,newstring);
			break;
		}
		case 'f':
		{
			string substring;
			cin >> substring;
			a.FindSubstring(substring);
			break;
		}
		case 'c':
		{
			int lines=0,words= 0;
			a.Count(lines, words);
			cout << "һ���� " << lines << " ��,�� " << words << " ����" << endl;
			//cout<<"��ǰ����"
			break;
		}
		case 'a':
		{
			a.ReReadFile();
			break;
		}
		case 'b':
		{
			a.SaveFile();
			break;
		}
		case 'e':
		{
			a.Exit();
			exit = true;
			break;
		}
		default:
		{
			a.Help();
			break;
		}
		}
	}
	/*SimpleDblLinkList<string> *text;
	string absdf;
	text = new SimpleDblLinkList<string>;
	text->Insert(1, "a");
	text->GetElem(1,absdf);
	cout << absdf << endl;*/
	return 0;
}
