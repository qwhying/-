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
int statistics(string text) {//ͳ��ÿ���ַ����ֵĴ����ͳ��ֵĲ�ͬ���ַ���
	int sum = 0;
	for (char e : text)//ͳ��ÿ���ַ����ִ���
	{
		chars[(int)e]++;
	}
	for (int i = 0; i < 256; i++)//ͳ�Ʋ�ͬ�ַ�����
	{
		if (chars[i] != 0)sum++;
	}
	return sum;
}
unsigned int CharIndex(const char &ch)
//�������:�ַ�λ��ӳ��
{
	//unsigned int result;//���ؽ��
	//if (ch == 'a') result = 1;//'a'�Ĵ洢λ��Ϊ1
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
	string filename;//�ļ���
	ifstream infile;//�����ļ���
	ofstream outfile;//����ļ���
	string text;//������ַ����ı�
	string code;//�ַ������루����д���ļ�)
	while (true)
	{
		filename.clear();
		text.clear();
		code.clear();
		cout << "1.����������" << endl;
		cout << "2.����������" << endl;
		cout << "3.�˳�" << endl;
		cout << "��ѡ��";
		char ch = getchar();
		if (ch == '1') {
			cout << "������Դ�ļ�����";
			cin >> filename;
			memset(chars, 0, sizeof(chars));
			infile.open(filename);
			if (!infile.is_open())
			{
				cout << "�޷����ļ� " << filename<< endl;
				cout << "������ֹ" << endl;
				getchar();
				getchar();
				exit(EXIT_FAILURE);
			}
			else
			{
				cout << "���ļ��ɹ���" << endl;
				string line;
				while (infile.good())
				{
					getline(infile, line);//���ж�ȡ
					text.append(line);
				}

			}
			int n = statistics(text);//ͳ���ַ����и����ַ����ֵĴ�������
			char ch[256];//��ĸ��
			for (int i = 0; i < 256; i++)
				ch[i] = char(i);
			MyHuffmanTree<char, int>hmTree1(ch, chars, n, CharIndex);
			//MyHuffmanTree<char, int>hmTree(hmTree1);//���ƹ��캯��
			MyHuffmanTree<char, int>hmTree = hmTree1;//��ֵ�������
			
			string strTmp;//��ʱ�ַ�������ŵ�����ĸ�ı���
			cout << "�ı���" << text.c_str() << "����Ϊ:";
			for (int pos = 0; pos < (int)text.length(); pos++)
			{
				strTmp = hmTree.Encode(text[pos]);//����
				code.append(strTmp);//����code��
				//cout << strTmp.c_str();
			}
			cout << code;
			cout << endl;
			filename.clear();
			cout << "����������ļ�����";
			cin >> filename;
			outfile.open(filename/*, ios::out | ios::binary*/);
			if (!outfile.is_open())
			{
				cout << "�޷����ļ� " << filename<< endl;
				cout << "������ֹ" << endl;
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
				cout << "���ļ��ɹ����ɹ������ļ���" << endl;
				//delete &text1;

			}
			infile.close();//�ر������ļ�
			outfile.close();//�ر�����ļ�
			system("PAUSE");
		}
		else if (ch == '2')
		{
			filename.clear();
			text.clear();
			code.clear();
			cout << "����������ļ�����";
			cin >> filename;
			infile.open(filename/*, ios::in | ios::binary*/);
			if (!infile.is_open())
			{
				cout << "�޷����ļ� " << filename << endl;
				cout << "������ֹ" << endl;
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
				cout << "���ļ��ɹ���" << endl;
				infile >> code;
				cout << "���봮 " << code << "����Ϊ��";
				infile.close();
				infile.open("in.txt");
				string line;
				while (infile.good())
				{
					getline(infile, line);//���ж�ȡ
					text.append(line);
				}
				int n = statistics(text);//ͳ���ַ����и����ַ����ֵĴ�������
				char ch[256];//��ĸ��
				for (int i = 0; i < 256; i++)
					ch[i] = char(i);
				MyHuffmanTree<char, int>hmTree1(ch, chars, n, CharIndex);
				//MyHuffmanTree<char, int>hmTree(hmTree1);//���ƹ��캯��
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
			cout << "������Դ�ļ�����";
			cin >> filename;
			outfile.open(filename);
			if (!outfile.is_open())
			{
				cout << "�޷����ļ� " << filename << endl;
				cout << "������ֹ" << endl;
				getchar();
				getchar();
				exit(EXIT_FAILURE);
			}
			else
			{
				outfile << text;
				cout << "���ļ��ɹ����ɹ������ļ���" << endl;

			}
			infile.close();//�ر������ļ�
			outfile.close();//�ر�����ļ�
			system("PAUSE");
		}
		else if(ch=='3')
		exit(1);
		else {
		cout << "�����������������룬ѡ��1��2��3֮һ";
}
	}
	//cout << "���봮" << strCode.c_str() << "����Ϊ��";
	//list<char> lkText = hmTree.Decode(strCode);
	//strText = lkText;
	//strText.erase();
	//for (char e : lkText)
	//{
	//	strText = strText + e;
	//}
	//cout << strText.c_str() << endl;
	//system("PAUSE");//���ÿ⺯��system
	return 0;

}