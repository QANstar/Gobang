#pragma once
#include <ListUDG.h>
#include <string>
using namespace std;

class CChessMap
{
private:
	CListUDG xMap;
	CListUDG yMap;
	CListUDG orMap;
	CListUDG olMap;
	string chessVariety;
public:
	//初始化
	CChessMap(){}
	CChessMap(int n, string chessVar);
	void InitChessMap(int n, string chessVar);
	//在图中连接连通棋子
	void LinkChess(int isDownX, int isDownY, int isDown[19][19]);
	//计算某点开始连通棋子数量
	void GetLinkNum(int pointA, int& n1, int& n2, int& n3, int& n4);
	//重设棋子邻接表
	void ResetChessMap();
	//重设某点棋子邻接表
	void ResetChessNode(int backPoint);
};

