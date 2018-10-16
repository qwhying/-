#include "node.h"
#include<stdio.h>

template<class ElemType>
node<ElemType>::node()
{
	next = NULL;
}
template<class ElemType>
node<ElemType>::node(ElemType item, node<ElemType>* link)
{
	data = item;
	next = link;
}
template<class ElemType>
node<ElemType>::~node()
{
}