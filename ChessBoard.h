#pragma once
class CChessBoard
{
public:
	CImage m_chessmap[5]; // ����ͼ��
	int isDown[19][19];//�Ƿ��Ѿ�ӵ������0Ϊ�ޣ�1Ϊ���壬2Ϊ����
	int backgroundId;
private:
	LONG chessMap[19][19][2];//������������
public:
	CChessBoard();
	void InitChessBoard();//��ʼ������
	void InitChessDown();//��ʼ�����Ӽ�¼
	void AdjustPoint(CPoint& point, int& isDownX, int& isDownY);//����������굽�������겢��ȡ��������λ��
	void InitBackground();
};

