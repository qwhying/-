#include "MyHuffmanTree.h"
#include<string>
#include<cstring>
#include"utility.h"
#include"huffman_tree_node.h"
#include"node.h"
#include"lk_list.h"
using namespace std;
template<class CharType,class WeightType>
//孩子兄弟表示哈夫曼树类模板的实现部分
void MyHuffmanTree<CharType, WeightType>::Select(int cur, int &r1, int &r2)
{//操作结果：nodes[1~cur]中选择双亲为0，权值最小的两个结点r1,r2
	r1 = r2 = 0;//0表示空结点
	for (int pos = 1; pos <= cur; pos++)
	{//查找权值最小的两个结点
		if(nodes[pos].parent!=0)continue;//只处理双亲不为0的结点
		if (r1 == 0)
		{
			//r1为空把pos赋值给r1
			r1 = pos;
		}
		else if (r2 == 0)
		{
			//r2为空，把pos赋值给r2
			r2 = pos;
		}
		else if (nodes[pos].weight < nodes[r1].weight)
		{//nodes[pos]权值比nodes[r1]更小，将pos赋值为r1
			r1 = pos;
		}
		else if (nodes[pos].weight < nodes[r2].weight)
		{//nodes[pos]权值比nodes[r2]更小，将pos赋值为r2
			r2 = pos;
		}
	}
}
template<class CharType,class WeightType>
void MyHuffmanTree<CharType, WeightType>::CreatMyHuffmanTree(CharType ch[], WeightType w[], int n)
//操作结果，由字符，权值，和字符个数构造哈夫曼树
{
	num = n;//叶结点的个数
	int m = 2 * n - 1;//结点个数
	nodes = new HuffmanTreeNode<WeightType>[m + 1];//nodes[0]未用
	LeafChars = new CharType[n + 1];//LeafChars[0]未用
	LeafCharCodes = new string[n + 1];//LeafCharCodes[0]未用

	int pos,pos_u;
	for (pos = 1,pos_u=1; pos <= n,pos_u<=256; pos_u++)
	{//存储叶结点信息
		if (w[pos_u- 1] == 0)continue;//如果权重为0，代表文本中没有出现这个字符，因此当前结点pos不变，而pos_u依然要++
		else {
			nodes[pos].weight = w[pos_u - 1];
			LeafChars[pos] = ch[pos_u - 1];
			pos++;
		}

	}
	for (pos = n + 1; pos <= m; pos++)
	{//建立哈夫曼树
		int r1, r2;
		Select(pos - 1, r1, r2);//nodes[1~pos-1]中选择双亲为0，权值最小的两个结点r1，r2

		//合并以r1，r2为根的树
		nodes[r1].parent = nodes[r2].parent = pos;//r1,r2双亲为pos
		nodes[pos].leftChild = r1;//r1为pos的左孩子
		nodes[pos].rightChild = r2;//r2为pos的右孩子
		nodes[pos].weight = nodes[r1].weight + nodes[r2].weight;//pos的权为r1,r2的权值之和
	}
	for (pos = 1; pos <= n; pos++)
	{//求n个叶结点字符的编码
		list<char> charCode;//暂存叶结点字符编码信息
		for (unsigned int child = pos, parent = nodes[child].parent; parent != 0; child = parent, parent = nodes[child].parent)
		{//从叶结点到根节点逆向求编码
			if (nodes[parent].leftChild == child) charCode.insert(charCode.begin(), '0');
			//左分支编码为‘0’
			else charCode.insert(charCode.begin(), '1');//右分支编码为‘1’
		}
		LeafCharCodes[pos].erase();
		for (char e : charCode)
		{
			LeafCharCodes[pos] += e;//charCode中存储字符编码
		}
		curPos = m;//译码时从根节点开始，m为根
	}
}
template<class CharType,class WeightType>
MyHuffmanTree<CharType, WeightType>::MyHuffmanTree(CharType ch[], WeightType w[], int n, unsigned int(*ChIndex)(const CharType &))
//操作结果：由字符，权值，字符个数和字符位置映射构造哈夫曼树
{
	CharIndex = ChIndex;//字符位置映射
	CreatMyHuffmanTree(ch, w, n);//由字符，权值和字符个数构造哈夫曼树
}
template<class CharType,class WeightType>
MyHuffmanTree<CharType, WeightType>::~MyHuffmanTree()
//操作结果，销毁哈夫曼树
{
	if (nodes != NULL)delete []nodes;//释放结点信息
	if (LeafChars != NULL)delete []LeafChars;//释放叶结点字符信息
	if (LeafCharCodes != NULL)delete []LeafCharCodes;//释放叶结点字符编码信息
}
template<class CharType,class WeightType>
string MyHuffmanTree<CharType, WeightType>::Encode(CharType ch)
//操作结果，返回字符编码
{
	return LeafCharCodes[(*CharIndex)(ch)];//返回字符编码
}
template<class CharType,class WeightType>
list<CharType>MyHuffmanTree<CharType, WeightType>::Decode(string strCode)
//操作结果，对编码串strCode进行译码，返回编码前的字符序列
{
	list<CharType> charList;//编码前的字符序列
	for (int pos = 0; pos < (int)strCode.length(); pos++)
	{//处理每位编码
		if (strCode[pos] == '0')curPos = nodes[curPos].leftChild;//'0'表示左分支
		else curPos = nodes[curPos].rightChild;//'1'表示右分支
		if (nodes[curPos].leftChild == 0 && nodes[curPos].rightChild == 0)
		{//译码时从根节点到叶结点路径的当前结点为叶结点
			charList.insert(charList.end(), LeafChars[curPos]);
			curPos = 2 * num - 1;//curPos回归根节点
		}

	}
	return charList;
}
template<class CharType,class WeightType>
MyHuffmanTree<CharType, WeightType>::MyHuffmanTree(const MyHuffmanTree<CharType, WeightType>&copy)
//操作结果，由哈夫曼树copy构造新哈夫曼树——复制构造函数模板
{
	num = copy.num;//叶结点的个数
	curPos = copy.curPos;//当前结点
	int m = 2 * num - 1;//结点总数
	nodes = new HuffmanTreeNode<WeightType>[m + 1];//nodes[0]未用
	LeafChars = new CharType[num + 1];//LeafChars[0]未用
	LeafCharCodes = new string[num + 1];//LeafCharCodes[0]未用
	CharIndex = copy.CharIndex;//字符位置映射

	int pos;//临时变量
	for (pos = 1; pos <= m; pos++)
	{//复制结点信息
		nodes[pos] = copy.nodes[pos];//结点信息
	}

	for (pos = 1; pos <= num; pos++)
	{//复制叶结点字符信息与叶结点字符编码信息
		LeafChars[pos] = copy.LeafChars[pos];//叶结点字符信息
		LeafCharCodes[pos] = copy.LeafCharCodes[pos];//叶结点字符编码信息
	}

}
template<class CharType,class WeightType>
MyHuffmanTree<CharType, WeightType>&MyHuffmanTree<CharType, WeightType>::operator=(const MyHuffmanTree<CharType, WeightType>&copy)
//操作结果，将哈夫曼树COPY复制给当前哈夫曼树——重载赋值运算符
{
	if (&copy != this)
	{
		if (nodes != NULL)delete[]nodes;//释放
		if (LeafChars != NULL)delete[]LeafChars;//释放
		if (LeafCharCodes != NULL)delete[]LeafCharCodes;//释放

		num = copy.num;//叶结点个数
		curPos = copy.curPos;//当前结点
		int m = 2 * num - 1;//结点总数
		nodes = new HuffmanTreeNode<WeightType>[m + 1];//nodes[0]未用
		LeafChars = new CharType[num + 1];//0未用
		LeafCharCodes = new string[num + 1];//0未用
		CharIndex = copy.CharIndex;//字符位置映射

		int pos;
		for (pos = 1; pos <= m; pos++)
		{//复制结点信息
			nodes[pos] = copy.nodes[pos];//结点信息
		}
		for (pos = 1; pos <= num; pos++)
		{//复制叶结点字符信息与字符编码
			LeafChars[pos] = copy.LeafChars[pos];//字符
			LeafCharCodes[pos] = copy.LeafCharCodes[pos];//字符编码
		}
	}
	return *this;
}