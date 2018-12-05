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
	HuffmanTreeNode<WeightType> *nodes;//存储结点信息
	CharType *LeafChars;//叶节点字符信息
	string *LeafCharCodes;//叶结点字符编码信息
	int curPos;//译码时从根节点到叶结点路径路径的当前结点
	int num;//叶结点个数
	unsigned int(*CharIndex)(const CharType &);//字符位置映射
	//辅助函数模板
	void Select(int cur, int &rl, int &r2);//nodes[1~cur]中选取双亲为0，权值最小的两个结点r1，r2
	void CreatMyHuffmanTree(CharType ch[], WeightType w[], int n);//由字符，权值和字符个数构造哈夫曼树
public:
	MyHuffmanTree(CharType ch[],WeightType W[],int n,unsigned int (*ChIndex)(const CharType &));//由字符、权值、字符个数和字符位置映射数构造哈夫曼树
	virtual~MyHuffmanTree();
	string Encode(CharType ch);//编码
	list<CharType> Decode(string strCode);//译码
	MyHuffmanTree(const MyHuffmanTree<CharType, WeightType>&copy);//复制构造函数模板
	MyHuffmanTree<CharType, WeightType>&operator=(const MyHuffmanTree<CharType, WeightType>& copy);//重载复制运算符
};

