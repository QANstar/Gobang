#pragma once
class CChessBoard
{
public:
	CImage m_chessmap[5]; // 棋盘图像
	int isDown[19][19];//是否已经拥有棋子0为无，1为黑棋，2为白棋
	int backgroundId;
private:
	LONG chessMap[19][19][2];//棋盘坐标数据
public:
	CChessBoard();
	void InitChessBoard();//初始化棋盘
	void InitChessDown();//初始化落子记录
	void AdjustPoint(CPoint& point, int& isDownX, int& isDownY);//调整点击坐标到棋盘坐标并获取所处棋盘位置
	void InitBackground();
};

