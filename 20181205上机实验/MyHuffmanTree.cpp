#include "MyHuffmanTree.h"
#include<string>
#include<cstring>
#include"utility.h"
#include"huffman_tree_node.h"
#include"node.h"
#include"lk_list.h"
using namespace std;
template<class CharType,class WeightType>
//�����ֵܱ�ʾ����������ģ���ʵ�ֲ���
void MyHuffmanTree<CharType, WeightType>::Select(int cur, int &r1, int &r2)
{//���������nodes[1~cur]��ѡ��˫��Ϊ0��Ȩֵ��С���������r1,r2
	r1 = r2 = 0;//0��ʾ�ս��
	for (int pos = 1; pos <= cur; pos++)
	{//����Ȩֵ��С���������
		if(nodes[pos].parent!=0)continue;//ֻ����˫�ײ�Ϊ0�Ľ��
		if (r1 == 0)
		{
			//r1Ϊ�հ�pos��ֵ��r1
			r1 = pos;
		}
		else if (r2 == 0)
		{
			//r2Ϊ�գ���pos��ֵ��r2
			r2 = pos;
		}
		else if (nodes[pos].weight < nodes[r1].weight)
		{//nodes[pos]Ȩֵ��nodes[r1]��С����pos��ֵΪr1
			r1 = pos;
		}
		else if (nodes[pos].weight < nodes[r2].weight)
		{//nodes[pos]Ȩֵ��nodes[r2]��С����pos��ֵΪr2
			r2 = pos;
		}
	}
}
template<class CharType,class WeightType>
void MyHuffmanTree<CharType, WeightType>::CreatMyHuffmanTree(CharType ch[], WeightType w[], int n)
//������������ַ���Ȩֵ�����ַ����������������
{
	num = n;//Ҷ���ĸ���
	int m = 2 * n - 1;//������
	nodes = new HuffmanTreeNode<WeightType>[m + 1];//nodes[0]δ��
	LeafChars = new CharType[n + 1];//LeafChars[0]δ��
	LeafCharCodes = new string[n + 1];//LeafCharCodes[0]δ��

	int pos,pos_u;
	for (pos = 1,pos_u=1; pos <= n,pos_u<=256; pos_u++)
	{//�洢Ҷ�����Ϣ
		if (w[pos_u- 1] == 0)continue;//���Ȩ��Ϊ0�������ı���û�г�������ַ�����˵�ǰ���pos���䣬��pos_u��ȻҪ++
		else {
			nodes[pos].weight = w[pos_u - 1];
			LeafChars[pos] = ch[pos_u - 1];
			pos++;
		}

	}
	for (pos = n + 1; pos <= m; pos++)
	{//������������
		int r1, r2;
		Select(pos - 1, r1, r2);//nodes[1~pos-1]��ѡ��˫��Ϊ0��Ȩֵ��С���������r1��r2

		//�ϲ���r1��r2Ϊ������
		nodes[r1].parent = nodes[r2].parent = pos;//r1,r2˫��Ϊpos
		nodes[pos].leftChild = r1;//r1Ϊpos������
		nodes[pos].rightChild = r2;//r2Ϊpos���Һ���
		nodes[pos].weight = nodes[r1].weight + nodes[r2].weight;//pos��ȨΪr1,r2��Ȩֵ֮��
	}
	for (pos = 1; pos <= n; pos++)
	{//��n��Ҷ����ַ��ı���
		list<char> charCode;//�ݴ�Ҷ����ַ�������Ϣ
		for (unsigned int child = pos, parent = nodes[child].parent; parent != 0; child = parent, parent = nodes[child].parent)
		{//��Ҷ��㵽���ڵ����������
			if (nodes[parent].leftChild == child) charCode.insert(charCode.begin(), '0');
			//���֧����Ϊ��0��
			else charCode.insert(charCode.begin(), '1');//�ҷ�֧����Ϊ��1��
		}
		LeafCharCodes[pos].erase();
		for (char e : charCode)
		{
			LeafCharCodes[pos] += e;//charCode�д洢�ַ�����
		}
		curPos = m;//����ʱ�Ӹ��ڵ㿪ʼ��mΪ��
	}
}
template<class CharType,class WeightType>
MyHuffmanTree<CharType, WeightType>::MyHuffmanTree(CharType ch[], WeightType w[], int n, unsigned int(*ChIndex)(const CharType &))
//������������ַ���Ȩֵ���ַ��������ַ�λ��ӳ�乹���������
{
	CharIndex = ChIndex;//�ַ�λ��ӳ��
	CreatMyHuffmanTree(ch, w, n);//���ַ���Ȩֵ���ַ����������������
}
template<class CharType,class WeightType>
MyHuffmanTree<CharType, WeightType>::~MyHuffmanTree()
//������������ٹ�������
{
	if (nodes != NULL)delete []nodes;//�ͷŽ����Ϣ
	if (LeafChars != NULL)delete []LeafChars;//�ͷ�Ҷ����ַ���Ϣ
	if (LeafCharCodes != NULL)delete []LeafCharCodes;//�ͷ�Ҷ����ַ�������Ϣ
}
template<class CharType,class WeightType>
string MyHuffmanTree<CharType, WeightType>::Encode(CharType ch)
//��������������ַ�����
{
	return LeafCharCodes[(*CharIndex)(ch)];//�����ַ�����
}
template<class CharType,class WeightType>
list<CharType>MyHuffmanTree<CharType, WeightType>::Decode(string strCode)
//����������Ա��봮strCode�������룬���ر���ǰ���ַ�����
{
	list<CharType> charList;//����ǰ���ַ�����
	for (int pos = 0; pos < (int)strCode.length(); pos++)
	{//����ÿλ����
		if (strCode[pos] == '0')curPos = nodes[curPos].leftChild;//'0'��ʾ���֧
		else curPos = nodes[curPos].rightChild;//'1'��ʾ�ҷ�֧
		if (nodes[curPos].leftChild == 0 && nodes[curPos].rightChild == 0)
		{//����ʱ�Ӹ��ڵ㵽Ҷ���·���ĵ�ǰ���ΪҶ���
			charList.insert(charList.end(), LeafChars[curPos]);
			curPos = 2 * num - 1;//curPos�ع���ڵ�
		}

	}
	return charList;
}
template<class CharType,class WeightType>
MyHuffmanTree<CharType, WeightType>::MyHuffmanTree(const MyHuffmanTree<CharType, WeightType>&copy)
//����������ɹ�������copy�����¹��������������ƹ��캯��ģ��
{
	num = copy.num;//Ҷ���ĸ���
	curPos = copy.curPos;//��ǰ���
	int m = 2 * num - 1;//�������
	nodes = new HuffmanTreeNode<WeightType>[m + 1];//nodes[0]δ��
	LeafChars = new CharType[num + 1];//LeafChars[0]δ��
	LeafCharCodes = new string[num + 1];//LeafCharCodes[0]δ��
	CharIndex = copy.CharIndex;//�ַ�λ��ӳ��

	int pos;//��ʱ����
	for (pos = 1; pos <= m; pos++)
	{//���ƽ����Ϣ
		nodes[pos] = copy.nodes[pos];//�����Ϣ
	}

	for (pos = 1; pos <= num; pos++)
	{//����Ҷ����ַ���Ϣ��Ҷ����ַ�������Ϣ
		LeafChars[pos] = copy.LeafChars[pos];//Ҷ����ַ���Ϣ
		LeafCharCodes[pos] = copy.LeafCharCodes[pos];//Ҷ����ַ�������Ϣ
	}

}
template<class CharType,class WeightType>
MyHuffmanTree<CharType, WeightType>&MyHuffmanTree<CharType, WeightType>::operator=(const MyHuffmanTree<CharType, WeightType>&copy)
//�������������������COPY���Ƹ���ǰ���������������ظ�ֵ�����
{
	if (&copy != this)
	{
		if (nodes != NULL)delete[]nodes;//�ͷ�
		if (LeafChars != NULL)delete[]LeafChars;//�ͷ�
		if (LeafCharCodes != NULL)delete[]LeafCharCodes;//�ͷ�

		num = copy.num;//Ҷ������
		curPos = copy.curPos;//��ǰ���
		int m = 2 * num - 1;//�������
		nodes = new HuffmanTreeNode<WeightType>[m + 1];//nodes[0]δ��
		LeafChars = new CharType[num + 1];//0δ��
		LeafCharCodes = new string[num + 1];//0δ��
		CharIndex = copy.CharIndex;//�ַ�λ��ӳ��

		int pos;
		for (pos = 1; pos <= m; pos++)
		{//���ƽ����Ϣ
			nodes[pos] = copy.nodes[pos];//�����Ϣ
		}
		for (pos = 1; pos <= num; pos++)
		{//����Ҷ����ַ���Ϣ���ַ�����
			LeafChars[pos] = copy.LeafChars[pos];//�ַ�
			LeafCharCodes[pos] = copy.LeafCharCodes[pos];//�ַ�����
		}
	}
	return *this;
}