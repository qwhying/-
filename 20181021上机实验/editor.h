#include<string>
#include<cstring>
#include<fstream>
#include"SimpleDblLinkList.h"
#include"SimpleDblLinkList.cpp"
using namespace std;
class editor
{
private:
	int curline;
	int totallines;
	string filename;
	ifstream infile;
	ofstream outfile;
	SimpleDblLinkList<string> *text;
	static int countword(string line);
public:
	void OpenFile(string file_name);
	void ShowTheFile();
	void ToTheFirstLine();
	void ToTheLastLine();
	void ToThePreviousLine();
	void ToTheNextLine();
	void ToTheDesignatedLine(int whichline);
	void InsertAline(int numberofline,string newline);
	void DeleteAline(int numberofline);
	void ReplaceCurrentLine(string newline);
	void ReplaceSubstring(string newstring,string prestring);
	int FindSubstring(string substring);
	void Count(int &lines, int &words);
	void ReReadFile();
	void Help();
	void SaveFile();
	void Exit();


	editor();
	~editor();
};

