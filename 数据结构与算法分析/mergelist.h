#pragma once
#include"SimpleLinkList.h"
template<class ElemType>
void MergeList(const SimpleLinkList<ElemType>& la, const SimpleLinkList<ElemType>& lb, SimpleLinkList<ElemType>& lc)
//初始条件：la和lb中数据元素递增有序
//操作结果：将la和lb合并为lc，使lc中元素仍递增有序
{
	ElemType aItem, bItem;//la和lb中当前数据元素
	int aLength = la.Length(), bLength = lb.Length();//la和lb长度
	int  aPosition = 1, bPosition = 1;//la和lb当前元素序号

	lc.Clea();
	while (aPosition <= aLength && bPosition <= bLength)
	{//取出la和lb中数据元素进行归并
		la.GetElem(aPosition, aItem);//取出la中数据元素
		lb.GetElem(bPosition, bItem);//取出lb中数据元素
		if (aItem < bItem) {//归并aItem
			lc.Insert(lc.Length() + 1, aItem);//插入aItem到lc
			aPosition++;//指向la下一数据元素
		}
		else {
			//归并bItem
			lc.Insert(lc.Length() + 1, bItem);//插入bItem到lc
			bPosition++;//指向lb下一数据元素
		}
	}
	while (aPosition <= aLength) {
		//归并la中剩余数据元素
		la.GetElem(aPosition, aItem);
		lc.Insert(lc.Length() + 1, aItem);
		aPosition++;
	}
	while (bPosition <= bLength) {//归并lb中剩余数据元素
		lb.GetElem(bPosition, bItem);
		lc.Insert(lc.Length() + 1, bItem);
		bPosition++;
	}

}
	