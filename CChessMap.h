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
	//��ʼ��
	CChessMap(){}
	CChessMap(int n, string chessVar);
	void InitChessMap(int n, string chessVar);
	//��ͼ��������ͨ����
	void LinkChess(int isDownX, int isDownY, int isDown[19][19]);
	//����ĳ�㿪ʼ��ͨ��������
	void GetLinkNum(int pointA, int& n1, int& n2, int& n3, int& n4);
	//���������ڽӱ�
	void ResetChessMap();
	//����ĳ�������ڽӱ�
	void ResetChessNode(int backPoint);
};

