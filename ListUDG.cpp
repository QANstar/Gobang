#include "pch.h"
#include "ListUDG.h"

//构造并初始化图
CListUDG::CListUDG(int inVexNum, CPoint inVexs[])
{
	mVexNum = inVexNum;
	for (int i = 0; i < mVexNum; i++)
	{
		mVexs[i].data = inVexs[i];
		mVexs[i].firstEdge = NULL;
		isHave[i] = 0;
	}
}

CListUDG::CListUDG(int inVexNum)
{
	mVexNum = inVexNum;
	for (int i = 0; i < mVexNum; i++)
	{
		mVexs[i].firstEdge = NULL;
		isHave[i] = 0;
	}
}

void CListUDG::InitList(int inVexNum)
{
	mVexNum = inVexNum;
	for (int i = 0; i < mVexNum; i++)
	{
		mVexs[i].firstEdge = NULL;
		isHave[i] = 0;
	}
}

void CListUDG::InitVisited()
{
	for (int i = 0; i < 19 * 19; i++)
	{
		visited[i] = 0;
	}
}

void CListUDG::ResetList()
{
	for (int i = 0; i < mVexNum; i++)
	{
		if (mVexs[i].firstEdge != NULL)
		{
			ENode* la = mVexs[i].firstEdge;
			ENode* lb;
			while (la)
			{
				lb = la;
				la = la->nextEdge;
				delete(lb);
			}
			mVexs[i].firstEdge = NULL;
		}
		isHave[i] = 0;
	}
}

void CListUDG::ResetNode(int bakcPoint)
{
	isHave[bakcPoint] = 0;
	if (mVexs[bakcPoint].firstEdge != NULL)
	{
		ENode* la = mVexs[bakcPoint].firstEdge;
		ENode* lc = mVexs[bakcPoint].firstEdge;
		while (la)
		{
			ENode* lb;
			ENode* ld;
			if (mVexs[la->ivex].firstEdge->ivex == bakcPoint)
			{
				ld = mVexs[la->ivex].firstEdge;
				mVexs[la->ivex].firstEdge = mVexs[la->ivex].firstEdge->nextEdge;
				delete(ld);
			}
			else
			{
				lc = mVexs[la->ivex].firstEdge;
				while (lc->nextEdge)
				{
					if (lc->nextEdge->ivex == bakcPoint)
					{
						ld = lc->nextEdge;
						lc->nextEdge = lc->nextEdge->nextEdge;
						delete(ld);
					}
				}
			}
			lb = la;
			la = la->nextEdge;
			delete(lb);
		}
		mVexs[bakcPoint].firstEdge = NULL;
	}
}

void CListUDG::TreeNum(int mapPoint, int& n)
{
	InitVisited();
	DFS(mapPoint, n);
	InitVisited();
}

//连接两个相关结点
void CListUDG::LinkNode(int inVexNum1, int inVexNum2)
{
	ENode* newNode = new ENode;
	newNode->ivex = inVexNum2;
	newNode->nextEdge = NULL;
	if (mVexs[inVexNum1].firstEdge == NULL)
	{
		mVexs[inVexNum1].firstEdge = newNode;
	}
	else
	{
		ENode* pa;
		pa = mVexs[inVexNum1].firstEdge;
		while (pa->nextEdge)
		{
			pa = pa->nextEdge;
		}
		pa->nextEdge = newNode;
	}
	ENode* newNode2 = new ENode;
	newNode2->ivex = inVexNum1;
	newNode2->nextEdge = NULL;
	if (mVexs[inVexNum2].firstEdge == NULL)
	{
		mVexs[inVexNum2].firstEdge = newNode2;
	}
	else
	{
		ENode* pa;
		pa = mVexs[inVexNum2].firstEdge;
		while (pa->nextEdge)
		{
			pa = pa->nextEdge;
		}
		pa->nextEdge = newNode2;
	}
}

void CListUDG::SetHave(int havePoint)
{
	isHave[havePoint] = 1;
}

//计算某点开始生成树的结点数量
void CListUDG::DFS(int mapPoint, int &n)
{
	if (visited[mapPoint] != 1)
	{
		if (isHave[mapPoint] == 1)
		{
			n++;
		}
		visited[mapPoint] = 1;
		ENode* ma = mVexs[mapPoint].firstEdge;
		if (ma != NULL)
		{
			DFS(ma->ivex, n);
			if (ma->nextEdge != NULL)
			{
				ma = ma->nextEdge;
				while (ma)
				{
					DFS(ma->ivex, n);
					ma = ma->nextEdge;
				}
			}
		}
	}
	
}