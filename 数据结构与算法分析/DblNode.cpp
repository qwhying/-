#include"DblNode.h"
template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item, DblNode<ElemType> *linkBack, DblNode<ElemType> *linkNext)
{
	//�������������һ��������Ϊitem����ָ����Ϊlinkback��linknext�Ľ��
	data = item;
	back = linkBack;
	next = linkNext;
}