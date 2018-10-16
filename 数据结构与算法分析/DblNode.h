#pragma once
enum StatusCode { SUCCESS, FALL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERED, ENTRY_FOUND, VISITED, UNVISITED };
template<class ElemType>
struct DblNode
{
	//���ݳ�Ա
	ElemType data;//������
	DblNode<ElemType> *back;//ָ��ǰ����ָ����
	DblNode<ElemType> *next;//ָ���̵�ָ����
	//���캯��ģ�壺
	DblNode();
	DblNode(ElemType, DblNode<ElemType> *linkBack = NULL, DblNode<ElemType>*linkNext = NULL);
};