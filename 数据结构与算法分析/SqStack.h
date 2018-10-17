#pragma once
#define DEFAULT_SIZE 100//Ĭ��Ԫ�ظ���
#define DEFAULT_INFINITY 1000000//Ĭ�������
enum StatusCode { SUCCESS, FALL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERED, ENTRY_FOUND, VISITED, UNVISITED };
template<class ElemType>
class SqStack
{
protected:
	//˳��ջ�����ݳ�Ա
	int count;//Ԫ�ظ���
	int maxSize;//ջ���Ԫ�ظ���
	ElemType *elems;//Ԫ�ش洢�ռ�
	//��������ģ��
	bool Full() const;//�ж�ջ�Ƿ�����
	void Init(int size);//��ʼ��ջ
public:
	                                   /*�����������ͷ������������ر���ϵͳĬ�Ϸ�������*/
	SqStack(int size = DEFAULT_SIZE);  /*���캯��ģ��*/
	virtual~SqStack();                 //��������ģ��
	int Length()const;                 //��ջ����
	bool Empty()const;                 //�ж�ջ�Ƿ�Ϊ��
	void Clear();                      //���ջ
	void Traverse(void(*visit)(const ElemType &))const;//����ջ
	StatusCode Push(const ElemType &e);//��ջ
	StatusCode Top(ElemType &e)const;  //����ջ��Ԫ��
	StatusCode Pop(ElemType &e);       //��ջ
	SqStack(const SqStack<ElemType> &copy);//���ƹ��캯��ģ��
	SqStack<ElemType>&operator=(const SqStack<ElemType>&copy);//���ظ�ֵ�����

};