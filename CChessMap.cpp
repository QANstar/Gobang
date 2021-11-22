#include "pch.h"
#include "CChessMap.h"

CChessMap::CChessMap(int n, string chessVar)
{
	chessVariety = chessVar;
	xMap.InitList(n);
	yMap.InitList(n);
	orMap.InitList(n);
	olMap.InitList(n);
}

void CChessMap::InitChessMap(int n, string chessVar)
{
	chessVariety = chessVar;
	xMap.InitList(n);
	yMap.InitList(n);
	orMap.InitList(n);
	olMap.InitList(n);
}

//讲连通棋子记录在图中
void CChessMap::LinkChess(int isDownX, int isDownY, int isDown[19][19])
{
	int pointA = isDownX + isDownY * 19;
	int vi = 0;
	xMap.SetHave(pointA);
	yMap.SetHave(pointA);
	orMap.SetHave(pointA);
	olMap.SetHave(pointA);
	if (chessVariety=="black")
	{
		vi = 1;
	}
	else if (chessVariety == "white")
	{
		vi = 2;
	}
	if (isDown[isDownX + 1][isDownY] == vi && isDownX + 1 >= 0 && isDownX + 1 <= 18 && isDownY >= 0 && isDownY <= 18)
	{
		int pointB = isDownX + 1 + isDownY * 19;
		xMap.LinkNode(pointA, pointB);
	}
	if (isDown[isDownX - 1][isDownY] == vi && isDownX - 1 >= 0 && isDownX - 1 <= 18 && isDownY >= 0 && isDownY <= 18)
	{
		int pointB = isDownX - 1 + isDownY * 19;
		xMap.LinkNode(pointA, pointB);
	}
	if (isDown[isDownX][isDownY + 1] == vi && isDownX >= 0 && isDownX <= 18 && isDownY + 1 >= 0 && isDownY + 1 <= 18)
	{
		int pointB = isDownX + (isDownY + 1) * 19;
		yMap.LinkNode(pointA, pointB);
	}
	if (isDown[isDownX][isDownY - 1] == vi && isDownX >= 0 && isDownX <= 18 && isDownY - 1 >= 0 && isDownY - 1 <= 18)
	{
		int pointB = isDownX + (isDownY - 1) * 19;
		yMap.LinkNode(pointA, pointB);
	}
	if (isDown[isDownX + 1][isDownY + 1] == vi && isDownX + 1 >= 0 && isDownX + 1 <= 18 && isDownY + 1 >= 0 && isDownY + 1 <= 18)
	{
		int pointB = (isDownX + 1) + (isDownY + 1) * 19;
		orMap.LinkNode(pointA, pointB);
	}
	if (isDown[isDownX - 1][isDownY - 1] == vi && isDownX - 1 >= 0 && isDownX - 1 <= 18 && isDownY - 1 >= 0 && isDownY - 1 <= 18)
	{
		int pointB = (isDownX - 1) + (isDownY - 1) * 19;
		orMap.LinkNode(pointA, pointB);
	}
	if (isDown[isDownX - 1][isDownY + 1] == vi && isDownX - 1 >= 0 && isDownX - 1 <= 18 && isDownY + 1 >= 0 && isDownY + 1 <= 18)
	{
		int pointB = (isDownX - 1) + (isDownY + 1) * 19;
		olMap.LinkNode(pointA, pointB);
	}
	if (isDown[isDownX + 1][isDownY - 1] == vi && isDownX + 1 >= 0 && isDownX + 1 <= 18 && isDownY - 1 >= 0 && isDownY - 1 <= 18)
	{
		int pointB = (isDownX + 1) + (isDownY - 1) * 19;
		olMap.LinkNode(pointA, pointB);
	}
	// TODO: 在此处添加实现代码.
}

//获取连接棋子数量
void CChessMap::GetLinkNum(int pointA, int& n1, int& n2, int& n3, int& n4)
{
	xMap.TreeNum(pointA, n1);
	yMap.TreeNum(pointA, n2);
	orMap.TreeNum(pointA, n3);
	olMap.TreeNum(pointA, n4);
}

//重置图
void CChessMap::ResetChessMap()
{
	xMap.ResetList();
	yMap.ResetList();
	orMap.ResetList();
	olMap.ResetList();
}

//重置单个结点
void CChessMap::ResetChessNode(int backPoint)
{
	xMap.ResetNode(backPoint);
	yMap.ResetNode(backPoint);
	orMap.ResetNode(backPoint);
	olMap.ResetNode(backPoint);
}