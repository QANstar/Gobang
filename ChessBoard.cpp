#include "pch.h"
#include "ChessBoard.h"
//��ʼ��
void CChessBoard::InitChessDown()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			isDown[i][j] = 0;
		}
	}
}

CChessBoard::CChessBoard()
{
	InitChessDown();
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			chessMap[i][j][0] = 603 + i * 43;
			chessMap[i][j][1] = 162 + j * 42;
		}
	}
	backgroundId = 3;
}

void CChessBoard::InitChessBoard()
{
	InitChessDown();
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			chessMap[i][j][0] = 603 + i * 43;
			chessMap[i][j][1] = 162 + j * 42;
		}
	}
}

//��ս���굽������
void CChessBoard::AdjustPoint(CPoint& point, int& isDownX, int& isDownY)
{
	for (int i = 0; i < 19; i++)//�������x���굽������
	{
		if (point.x <= chessMap[i][0][0])
		{
			if ((chessMap[i][0][0] - point.x) < (point.x - chessMap[i - 1][0][0]))
			{
				point.x = chessMap[i][0][0];
				isDownX = i;
				break;
			}
			else
			{
				point.x = chessMap[i - 1][0][0];
				isDownX = i - 1;
				break;
			}
		}
	}
	for (int i = 0; i < 19; i++)//�������y���굽������
	{
		if (point.y <= chessMap[0][i][1])
		{
			if ((chessMap[0][i][1] - point.y) < (point.y - chessMap[0][i - 1][1]))
			{
				point.y = chessMap[0][i][1];
				isDownY = i;
				break;
			}
			else
			{
				point.y = chessMap[0][i - 1][1];
				isDownY = i - 1;
				break;
			}
		}
	}
}

//��ʼ������
void CChessBoard::InitBackground()
{
	m_chessmap[0].Load(TEXT("res//ChessBoard1.png"));
	m_chessmap[1].Load(TEXT("res//ChessBoard2.png"));
	m_chessmap[2].Load(TEXT("res//ChessBoard3.png"));
	m_chessmap[3].Load(TEXT("res//ChessBoard4.png"));
	m_chessmap[4].Load(TEXT("res//ChessBoard5.png"));
	// TODO: �ڴ˴����ʵ�ִ���.
}
