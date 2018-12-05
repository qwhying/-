#pragma once
#include<string.h>
#include<string>
#include<list>
#include"utility.h"
#include"huffman_tree_node.h"
using namespace std;
template<class CharType,class WeightType>
class MyHuffmanTree
{
private:
	HuffmanTreeNode<WeightType> *nodes;//�洢�����Ϣ
	CharType *LeafChars;//Ҷ�ڵ��ַ���Ϣ
	string *LeafCharCodes;//Ҷ����ַ�������Ϣ
	int curPos;//����ʱ�Ӹ��ڵ㵽Ҷ���·��·���ĵ�ǰ���
	int num;//Ҷ������
	unsigned int(*CharIndex)(const CharType &);//�ַ�λ��ӳ��
	//��������ģ��
	void Select(int cur, int &rl, int &r2);//nodes[1~cur]��ѡȡ˫��Ϊ0��Ȩֵ��С���������r1��r2
	void CreatMyHuffmanTree(CharType ch[], WeightType w[], int n);//���ַ���Ȩֵ���ַ����������������
public:
	MyHuffmanTree(CharType ch[],WeightType W[],int n,unsigned int (*ChIndex)(const CharType &));//���ַ���Ȩֵ���ַ��������ַ�λ��ӳ���������������
	virtual~MyHuffmanTree();
	string Encode(CharType ch);//����
	list<CharType> Decode(string strCode);//����
	MyHuffmanTree(const MyHuffmanTree<CharType, WeightType>&copy);//���ƹ��캯��ģ��
	MyHuffmanTree<CharType, WeightType>&operator=(const MyHuffmanTree<CharType, WeightType>& copy);//���ظ��������
};

