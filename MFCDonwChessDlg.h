
// MFCDonwChessDlg.h: 头文件
//
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "VFW32.lib")
#include <Mmsystem.h>
#include<windows.h>
#include <Vfw.h>
#include <Digitalv.h>
#include <stack>
#include <Model.h>
#include <ListUDG.h>
#include <Chess.h>
#include <CChessMap.h>
#include <string.h>
#include <ChessBoard.h>
#include<vector>
#include <locale>
#include "resource.h"
#include <StartMenu.h>
#include <afxsock.h>
#pragma once



// CMFCDonwChessDlg 对话框
class CMFCDonwChessDlg : public CDialogEx
{
	// 构造
public:
	CMFCDonwChessDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDONWCHESS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HWND hwnd1;
	HWND hwnd2;
	HWND hwnd3;
	bool isBlack;//是不是黑棋回合
	CChessBoard chessBoard;//棋盘
	CImage m_chess; // 黑棋子
	CImage w_chess;//白棋子
	CImage border;//当前一步边框
	bool isBlackBack;//黑棋是否悔棋
	bool isWhiteBack;//白棋是否悔棋
	bool isStop;//游戏暂停
	bool isopen;//音乐开关
	CChessMap blackCMap;//黑子无向图
	CChessMap whiteCMap;//白子无向图
	int AiScore[19][19];//AI判断分数
	int aiOrPk;//人机判断
	int downTime;//下棋剩余时间
	int downTimeShow;//剩余时间
	CString nowChess;// 当前棋子
	int chessNum;//下子数量
private:
	std::stack<CPoint> pointStack;//记录坐标的栈
	std::vector<CPoint> pointVec;//记录坐标的向量
	bool isShowOrder;//是否显示序号
private:
	void BeTransparent(CImage& pngImage);//png透明化
	int CheckChessConnection(int pointA, CChessMap cMap);// 检查棋子连接分数							
	void ChessBack(); // 悔棋函数
public:
	//读写文件
	void WriteScore(int score);
	//afx_msg void OnBnClickedButton7();
	virtual BOOL PreTranslateMessage(MSG* pMsg);//键盘键鼠输入事件
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//点击事件，下棋功能
	afx_msg void OnBnClickedCancel();//关闭
	afx_msg void OnBnClickedButton4();//清空棋盘
	afx_msg void OnBnClickedButton5();//悔棋功能
	void DrawOrderNum();//绘制落子次序
	//背景改变
	afx_msg void SpringBackground();
	afx_msg void SummerBackground();
	afx_msg void BackgroundAutumn();
	afx_msg void BackgroundWinter();
	afx_msg void BackgroundNight();
	//音乐开关
	afx_msg void StartMusic();
	//帮助
	afx_msg void Help();
	//显示关闭序号
	afx_msg void ShowOrder();
	//单次显示序号
	void downChessOrder(CPoint orPoint);
	//改变按钮样式
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//AI下子
	void AIDownChess(int& x, int& y);
	//AI设置棋盘下子分数
	void AiSetScore();
	//计时器
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//开启暂停游戏
	afx_msg void OnBnClickedButton7();
	//结束游戏
	afx_msg void OnBnClickedButton9();
};
