
// MFCDonwChessDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCDonwChess.h"
#include "MFCDonwChessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDonwChessDlg 对话框



CMFCDonwChessDlg::CMFCDonwChessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDONWCHESS_DIALOG, pParent)
	, downTimeShow(0)
	, nowChess(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDonwChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, downTimeShow);
	DDX_Text(pDX, IDC_EDIT2, nowChess);
}

BEGIN_MESSAGE_MAP(CMFCDonwChessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	//	ON_WM_MOUSEHOVER()
	//ON_WM_MOUSEMOVE()
	//ON_WM_MOUSELEAVE()
	ON_BN_CLICKED(IDCANCEL, &CMFCDonwChessDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCDonwChessDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCDonwChessDlg::OnBnClickedButton5)
	//ON_BN_CLICKED(IDC_BUTTON8, &CMFCDonwChessDlg::OnBnClickedButton8)
	//ON_BN_CLICKED(IDC_BUTTON7, &CMFCDonwChessDlg::OnBnClickedButton7)
	ON_COMMAND(ID_32771, &CMFCDonwChessDlg::SpringBackground)
	ON_COMMAND(ID_32772, &CMFCDonwChessDlg::SummerBackground)
	ON_COMMAND(ID_32773, &CMFCDonwChessDlg::BackgroundAutumn)
	ON_COMMAND(ID_32774, &CMFCDonwChessDlg::BackgroundWinter)
	ON_COMMAND(ID_32775, &CMFCDonwChessDlg::BackgroundNight)
	ON_COMMAND(ID_32776, &CMFCDonwChessDlg::StartMusic)
	ON_COMMAND(ID_32777, &CMFCDonwChessDlg::Help)
	ON_COMMAND(ID_32778, &CMFCDonwChessDlg::ShowOrder)
	ON_WM_DRAWITEM()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCDonwChessDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCDonwChessDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CMFCDonwChessDlg 消息处理程序

BOOL CMFCDonwChessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	chessBoard.InitBackground();
	// 初始化棋盘图片变量
	m_chess.Load(TEXT("res//Chess.png")); // 初始化棋子图片变量
	w_chess.Load(TEXT("res//WChess.png"));//初始化白棋子图片变量
	border.Load(TEXT("res//Border.png"));
	CString fileName = _T("res\\4.mp3");
	CString fileName2 = _T("res\\5.mp3");
	CString fileName3 = _T("res\\6.mp3");
	hwnd1 = MCIWndCreate(m_hWnd, NULL, MCIWNDF_NOPLAYBAR, fileName);
	hwnd2 = MCIWndCreate(m_hWnd, NULL, MCIWNDF_NOPLAYBAR, fileName2);
	hwnd3 = MCIWndCreate(m_hWnd, NULL, MCIWNDF_NOPLAYBAR, fileName3);
	isBlack = 1;
	isBlackBack = 0;
	isWhiteBack = 0;
	blackCMap.InitChessMap(19 * 19, "black");
	whiteCMap.InitChessMap(19 * 19, "white");
	isShowOrder = 0;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			AiScore[i][j] = 0;
		}
	}
	SetTimer(1, 200, NULL);
	downTime = 60;
	isStop = 0;
	isopen = 1;
	chessNum = 0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCDonwChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDonwChessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (isopen == 1)
		{
			::ShowWindow(hwnd1, SW_HIDE);
			MCIWndSetVolume(hwnd1, 100);
			MCIWndPlay(hwnd1);
		}
		CPaintDC dc(this); // 用于绘制的设备上下文
		// 显示棋盘背景图片
		chessBoard.m_chessmap[chessBoard.backgroundId].Draw(dc, 0, 0, 1980, 1080);
		for (int i = 0; i < pointVec.size(); i++)
		{
			if (i % 2 == 0)
			{
				BeTransparent(m_chess);//png透明化
				m_chess.Draw(dc, pointVec[i].x - 14.5, pointVec[i].y - 14.5, 29, 29); // 显示棋子
			}
			else
			{
				BeTransparent(w_chess);//png透明化
				w_chess.Draw(dc, pointVec[i].x - 14.5, pointVec[i].y - 14.5, 29, 29); // 显示棋子
			}
		}
		if (isShowOrder)
		{
			DrawOrderNum();
		}
		if (pointVec.size() > 0)
		{
			BeTransparent(border);//png透明化
			border.Draw(dc, pointVec[pointVec.size() - 1].x - 14.5, pointVec[pointVec.size() - 1].y - 14.5, 29, 29);
		}
		UpdateData(TRUE);
		if (isBlack)
		{
			nowChess = "黑";
		}
		else
		{
			nowChess = "白";
		}
		UpdateData(FALSE);
		CDialogEx::OnPaint();
	}

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDonwChessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CMFCDonwChessDlg::PreTranslateMessage(MSG* pMsg)
{

	return CDialogEx::PreTranslateMessage(pMsg);
}

//鼠标点击事件
void CMFCDonwChessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GetCursorPos(&point);//获取相对于屏幕坐标
	ScreenToClient(&point);//切换为窗口坐标
	int isDownX, isDownY;
	if (point.x >= 603 && point.x <= 1377 && point.y >= 162 && point.y <= 918)
	{
		if (!isStop)
		{
			chessBoard.AdjustPoint(point, isDownX, isDownY);//调整落子坐标
			int pointA = isDownX + isDownY * 19;
			if (chessBoard.isDown[isDownX][isDownY] == 0)
			{
				if (pointVec.size() > 0)//重绘上一个下子点的指示器
				{
					CRect clearBorder(pointVec[pointVec.size() - 1].x - 14.5, pointVec[pointVec.size() - 1].y - 14.5, pointVec[pointVec.size() - 1].x + 14.5, pointVec[pointVec.size() - 1].y + 14.5);
					InvalidateRect(clearBorder, TRUE);
				}
				CClientDC dc(this);

				if (isBlack == 1)
				{
					pointStack.push(point);//记录落子棋子坐标
					pointVec.push_back(point);
					BeTransparent(m_chess);//png透明化
					m_chess.Draw(dc, point.x - 14.5, point.y - 14.5, 29, 29); // 显示棋子
					chessBoard.isDown[isDownX][isDownY] = 1;
					//将连通棋子记录在无向图邻接表中
					blackCMap.LinkChess(isDownX, isDownY, chessBoard.isDown);
					//下回合
					isBlack = 0;
					isWhiteBack = 0;
					bool isBlackWin = 0;
					chessNum++;
					//检查连接分数
					if (CheckChessConnection(pointA, blackCMap))
					{
						//播放成功BGM
						::ShowWindow(hwnd2, SW_HIDE);
						MCIWndSetVolume(hwnd2, 1000);
						MCIWndPlay(hwnd2);
						if (aiOrPk == 0)
						{
							int playerScore = ((19 * 19) / chessNum) * 123 + 1000;//按下子数算分
							CString playerStr;
							playerStr.Format(_T("%d"), playerScore);
							WriteScore(playerScore);//分数记录在文件中
							MessageBox(TEXT("你赢了，得分是：" + playerStr));
						}
						else
						{
							MessageBox(TEXT("黑棋赢"));
						}
						//获胜各种量初始化
						isBlackWin = 1;
						isBlack = 1;
						chessBoard.InitChessDown();
						isBlackBack = 0;
						isWhiteBack = 0;
						while (!pointStack.empty())
						{
							pointStack.pop();
						}
						pointVec.clear();
						blackCMap.ResetChessMap();
						whiteCMap.ResetChessMap();
						chessNum = 0;
						Invalidate();
					}
					if (aiOrPk == 0 && !isBlackWin)//判断人机
					{
						BeTransparent(w_chess);//png透明化
						int aii, aij;
						AIDownChess(aii, aij);
						point.x = aij * 43 + 603;
						point.y = aii * 42 + 162;
						pointStack.push(point);//记录落子棋子坐标
						pointVec.push_back(point);
						w_chess.Draw(dc, point.x - 14.5, point.y - 14.5, 29, 29); // 显示棋子
						chessBoard.isDown[aij][aii] = 2;
						//将连通棋子记录在无向图邻接表中
						whiteCMap.LinkChess(aij, aii, chessBoard.isDown);
						//下回合
						isBlack = 1;
						isBlackBack = 0;
						pointA = aij + aii * 19;
						//检查连接分数
						if (CheckChessConnection(pointA, whiteCMap))
						{
							//播放失败BGM
							::ShowWindow(hwnd3, SW_HIDE);
							MCIWndSetVolume(hwnd3, 1000);
							MCIWndPlay(hwnd3);
							MessageBox(TEXT("你输了！"));
							//游戏结束各种量初始化
							isBlack = 1;
							chessBoard.InitChessDown();
							isBlackBack = 0;
							isWhiteBack = 0;
							while (!pointStack.empty())
							{
								pointStack.pop();
							}
							pointVec.clear();
							blackCMap.ResetChessMap();
							whiteCMap.ResetChessMap();
							chessNum = 0;
							Invalidate();
						}
					}
				}
				else
				{
					if (aiOrPk == 1)
					{
						pointStack.push(point);//记录落子棋子坐标
						pointVec.push_back(point);
						BeTransparent(w_chess);//png透明化
						w_chess.Draw(dc, point.x - 14.5, point.y - 14.5, 29, 29); // 显示棋子
						chessBoard.isDown[isDownX][isDownY] = 2;
						//将连通棋子记录在无向图邻接表中
						whiteCMap.LinkChess(isDownX, isDownY, chessBoard.isDown);
						//下回合
						isBlack = 1;
						isBlackBack = 0;
						//检查连接分数
						if (CheckChessConnection(pointA, whiteCMap))
						{
							//播放成功BGM
							::ShowWindow(hwnd2, SW_HIDE);
							MCIWndSetVolume(hwnd2, 1000);
							MCIWndPlay(hwnd2);
							MessageBox(TEXT("白棋赢"));
							//游戏结束各种量初始化
							isBlack = 1;
							chessBoard.InitChessDown();
							isBlackBack = 0;
							isWhiteBack = 0;
							while (!pointStack.empty())
							{
								pointStack.pop();
							}
							pointVec.clear();
							blackCMap.ResetChessMap();
							whiteCMap.ResetChessMap();
							chessNum = 0;
							Invalidate();
						}
					}
				}
				//判断棋子序号是否要显示
				if (isShowOrder)
				{
					downChessOrder(point);
				}
				BeTransparent(border);//png透明化
				border.Draw(dc, point.x - 14.5, point.y - 14.5, 29, 29);
				//回合结束计数初始化
				downTime = 60;
				//回合指示
				UpdateData(TRUE);
				if (isBlack)
				{
					nowChess = "黑";
				}
				else
				{
					nowChess = "白";
				}
				UpdateData(FALSE);
			}
		}
		else
		{
			MessageBox(TEXT("游戏已暂停"));
		}


	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

//关闭
void CMFCDonwChessDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

//清空棋盘
void CMFCDonwChessDlg::OnBnClickedButton4()
{
	//各种量初始和化
	isBlack = 1;
	chessBoard.InitChessDown();
	isBlackBack = 0;
	isWhiteBack = 0;
	while (!pointStack.empty())
	{
		pointStack.pop();
	}
	pointVec.clear();
	blackCMap.ResetChessMap();
	whiteCMap.ResetChessMap();
	downTime = 60;
	chessNum = 0;
	Invalidate();
	// TODO: 在此添加控件通知处理程序代码
}

//悔棋
void CMFCDonwChessDlg::OnBnClickedButton5()
{
	//悔棋

	if (!isBlackBack && !isWhiteBack)
	{
		if (!isBlack)//判断是否为黑棋回合悔棋
		{
			if (!isBlackBack)//黑棋本回合没悔棋可进行悔棋
			{
				if (!pointStack.empty())//判断栈是否为空
				{
					ChessBack();//悔棋
				}
			}
		}
		else//白棋回合
		{
			if (!isWhiteBack)
			{
				if (!pointStack.empty())
				{
					ChessBack();//悔棋
				}
			}
		}
	}
	else
	{
		MessageBox(TEXT("本回合已经悔过棋！"));
	}
	// TODO: 在此添加控件通知处理程序代码
}

//绘制落子次序
void CMFCDonwChessDlg::DrawOrderNum()
{
	int allchessCount = pointVec.size();//下子总数
	CClientDC dc(this); // 用于绘制的设备上下文
	dc.SetBkMode(TRANSPARENT); //设置背景为透明！
	CString str;
	for (int i = 0; i < pointVec.size(); i++)
	{
		if ((i + 1) % 2 == 0)//黑色数字为白，白色数字为黑
		{
			dc.SetTextColor(RGB(0, 0, 0));
		}
		else
		{
			dc.SetTextColor(RGB(255, 255, 255));
		}
		str.Format(_T("%d"), i + 1);//输出棋子的顺序号
	//调整不同位数的绘制位置
		if (i + 1 < 10)
		{
			dc.TextOut(pointVec[i].x - 6, pointVec[i].y - 10, str);
		}
		else if (i + 1 >= 10 && i + 1 < 100)
		{
			dc.TextOut(pointVec[i].x - 10, pointVec[i].y - 10, str);
		}
		else
		{
			dc.TextOut(pointVec[i].x - 14, pointVec[i].y - 10, str);
		}
	}

	// TODO: 在此处添加实现代码.
}

//png透明化
void CMFCDonwChessDlg::BeTransparent(CImage& pngImage)
{
	for (int i = 0; i < pngImage.GetWidth(); i++)//清楚图片周围白色区块
	{
		for (int j = 0; j < pngImage.GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char*>(pngImage.GetPixelAddress(i, j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}
	// TODO: 在此处添加实现代码.
}

// 检查棋子连接分数
int CMFCDonwChessDlg::CheckChessConnection(int pointA, CChessMap cMap)
{
	// TODO: 在此处添加实现代码.
	int n1 = 0;
	int n2 = 0;
	int n3 = 0;
	int n4 = 0;
	cMap.GetLinkNum(pointA, n1, n2, n3, n4);//分别得到横竖左斜和右斜的连接数
	if (n1 >= 5 || n2 >= 5 || n3 >= 5 || n4 >= 5)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

// 悔棋函数
void CMFCDonwChessDlg::ChessBack()
{
	int backPoint;
	CPoint oldPoint;
	oldPoint = pointStack.top();
	int i = (oldPoint.x - 603) / 43;
	int j = (oldPoint.y - 162) / 42;
	chessBoard.isDown[i][j] = 0;//改变此位置状态为未下棋
	//重绘此区域
	CRect clearPoint(oldPoint.x - 14.5, oldPoint.y - 14.5, oldPoint.x + 14.5, oldPoint.y + 14.5);
	InvalidateRect(clearPoint, TRUE);
	pointStack.pop();//悔棋棋子出栈
	pointVec.pop_back();
	backPoint = i + j * 19;
	if (!isBlack)//黑棋回合
	{
		isBlackBack = 1;//记录回退
		//重设此点无向图
		blackCMap.ResetChessNode(backPoint);
	}
	else//白棋回合
	{
		isWhiteBack = 1;//记录回退
		//重设此点无向图
		whiteCMap.ResetChessNode(backPoint);
	}
	//回合回溯
	isBlack = !isBlack;
	// TODO: 在此处添加实现代码.
}

//写文件
void CMFCDonwChessDlg::WriteScore(int score)
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFileName = _T("res//Chess.txt"); // 相对路径
	CString str1;
	if (!PathFileExists(strFileName)) {
		return;
	}
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
	{
		return;
	}
	file.SeekToEnd();// 文件指针指向文件末尾
	//记录下子的坐标
	str1.Format(_T("%d"), score);
	file.WriteString(str1);
	file.WriteString(_T("\n"));
	file.Close();

}

//背景（春）
void CMFCDonwChessDlg::SpringBackground()
{
	chessBoard.backgroundId = 0;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}

//背景（夏）
void CMFCDonwChessDlg::SummerBackground()
{
	chessBoard.backgroundId = 1;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}

//背景（秋）
void CMFCDonwChessDlg::BackgroundAutumn()
{
	chessBoard.backgroundId = 2;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}

//背景（东）
void CMFCDonwChessDlg::BackgroundWinter()
{
	chessBoard.backgroundId = 3;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}

//背景（夜）
void CMFCDonwChessDlg::BackgroundNight()
{
	chessBoard.backgroundId = 4;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}

//开启/暂停音乐
void CMFCDonwChessDlg::StartMusic()
{
	isopen = !isopen;//点击切换音乐播放状态
	if (isopen == 1)
	{
		::ShowWindow(hwnd1, SW_HIDE);
		MCIWndSetVolume(hwnd1, 100);
		MCIWndPlay(hwnd1);
	}
	else
	{
		MCIWndPause(hwnd1);
	}
	// TODO: 在此添加命令处理程序代码
}

//游戏帮助
void CMFCDonwChessDlg::Help()
{
	CModel modalWindow;
	modalWindow.DoModal();
}

//是否显示序号
void CMFCDonwChessDlg::ShowOrder()
{
	isShowOrder = !isShowOrder;
	Invalidate();
	// TODO: 在此添加命令处理程序代码
}

//单次显示序号
void CMFCDonwChessDlg::downChessOrder(CPoint orPoint)
{
	int allchessCount = pointVec.size();//下子总数
	CClientDC dc(this); // 用于绘制的设备上下文
	dc.SetBkMode(TRANSPARENT); //设置背景为透明！
	CString str;
	if (isBlack)//黑色数字为白，白色数字为黑
	{
		dc.SetTextColor(RGB(0, 0, 0));
	}
	else
	{
		dc.SetTextColor(RGB(255, 255, 255));
	}
	str.Format(_T("%d"), allchessCount);//输出棋子的顺序号
//调整不同位数的绘制位置
	if (allchessCount < 10)
	{
		dc.TextOut(orPoint.x - 6, orPoint.y - 10, str);
	}
	else if (allchessCount >= 10 && allchessCount < 100)
	{
		dc.TextOut(orPoint.x - 10, orPoint.y - 10, str);
	}
	else
	{
		dc.TextOut(orPoint.x - 14, orPoint.y - 10, str);
	}
	// TODO: 在此处添加实现代码.
}

//改变按钮样式
void CMFCDonwChessDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDCtl == IDC_BUTTON5 || nIDCtl == IDC_BUTTON4 || nIDCtl == IDC_BUTTON7 || nIDCtl == IDC_BUTTON9) //表示想重绘的控件
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);

		dc.FillSolidRect(&lpDrawItemStruct->rcItem, RGB(255, 255, 255));//按钮背景
		dc.Draw3dRect(&lpDrawItemStruct->rcItem, RGB(0, 0, 255), RGB(0, 0, 255));//3D按钮背景

		TCHAR buffer[MAX_PATH];
		ZeroMemory(buffer, MAX_PATH);
		::GetWindowText(lpDrawItemStruct->hwndItem, buffer, MAX_PATH);

		dc.SetBkMode(TRANSPARENT);//背景透明
		dc.SetTextColor(RGB(0, 0, 255));//改变文字颜色

		dc.DrawText(buffer, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//绘制按钮标题

		dc.Detach();
	}
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);

}

//AI选择下棋位置
void CMFCDonwChessDlg::AIDownChess(int& x, int& y)
{
	AiSetScore();
	int choice = 0;
	//选择法选择最大的权值
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (AiScore[i][j] > choice && chessBoard.isDown[j][i] == 0)
			{
				choice = AiScore[i][j];
				x = i;
				y = j;
			}
		}
	}


	// TODO: 在此处添加实现代码.
}

//AI计算权值
void CMFCDonwChessDlg::AiSetScore()
{
	//每次初始化
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			AiScore[i][j] = 0;
		}
	}
	//遍历每一组。考虑不同的情况来计算每一坐标的分数
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			int pointA = i * 19 + j;
			int numx = 0;
			int numy = 0;
			int numor = 0;
			int numol = 0;
			blackCMap.GetLinkNum(pointA, numx, numy, numor, numol);
			switch (numx)
			{
			case 1:
			{
				if (j + 1 >= 0 && j + 1 < 19 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
				{
					if (chessBoard.isDown[j + 1][i] == 0 && chessBoard.isDown[j - 1][i] == 0)
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 2;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 2;
					}
					else
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 1;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 1;
					}
				}
				break;
			}
			case 2:
			{
				if (j + 1 >= 0 && j + 1 < 19 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
				{
					if ((chessBoard.isDown[j + 1][i] == 0 && chessBoard.isDown[j - 2][i] == 0) || (chessBoard.isDown[j + 2][i] == 0 && chessBoard.isDown[j - 1][i] == 0))
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 5;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 5;
					}
					else
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 3;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 3;
					}
				}
				break;
			}
			case 3:
			{
				if (j + 1 >= 0 && j + 1 < 19 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
				{
					if ((chessBoard.isDown[j + 1][i] == 0 && chessBoard.isDown[j - 3][i] == 0) || (chessBoard.isDown[j + 3][i] == 0 && chessBoard.isDown[j - 1][i] == 0))
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 12;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 12;
					}
					else
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 8;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 8;
					}
				}
				break;
			}
			case 4:
			{
				if (j + 1 >= 0 && j + 1 < 19 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
				{
					AiScore[i][j + 1] = AiScore[i][j + 1] + 40;
					AiScore[i][j - 1] = AiScore[i][j - 1] + 40;
				}
				break;
			}
			default:
				break;
			}

			switch (numy)
			{
			case 1:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if (chessBoard.isDown[j][i + 1] == 0 && chessBoard.isDown[j][i - 1] == 0)
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 2;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 2;
					}
					else
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 1;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 1;
					}
				}
				break;
			}
			case 2:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j][i + 1] == 0 && chessBoard.isDown[j][i - 2] == 0) || (chessBoard.isDown[j][i + 2] == 0 && chessBoard.isDown[j][i - 1] == 0))
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 5;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 5;
					}
					else
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 3;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 3;
					}
				}
				break;
			}
			case 3:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j][i + 1] == 0 && chessBoard.isDown[j][i - 3] == 0) || (chessBoard.isDown[j][i + 3] == 0 && chessBoard.isDown[j][i - 1] == 0))
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 12;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 12;
					}
					else
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 8;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 8;
					}
				}
				break;
			}
			case 4:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					AiScore[i + 1][j] = AiScore[i + 1][j] + 40;
					AiScore[i - 1][j] = AiScore[i - 1][j] + 40;
				}
				break;
			}
			default:
				break;
			}

			switch (numor)
			{
			case 1:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if (chessBoard.isDown[j + 1][i + 1] == 0 && chessBoard.isDown[j - 1][i - 1] == 0)
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 2;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 2;
					}
					else
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 1;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 1;
					}
				}
				break;
			}
			case 2:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j + 1][i + 1] == 0 && chessBoard.isDown[j - 2][i - 2] == 0) || (chessBoard.isDown[j + 2][i + 2] == 0 && chessBoard.isDown[j - 1][i - 1] == 0))
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 5;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 5;
					}
					else
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 3;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 3;
					}
				}
				break;
			}
			case 3:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j + 1][i + 1] == 0 && chessBoard.isDown[j - 3][i - 3] == 0) || (chessBoard.isDown[j + 3][i + 3] == 0 && chessBoard.isDown[j - 1][i - 1] == 0))
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 12;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 12;
					}
					else
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 8;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 8;
					}
				}
				break;
			}
			case 4:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 40;
					AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 40;
				}
				break;
			}
			default:
				break;
			}

			switch (numol)
			{
			case 1:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if (chessBoard.isDown[j + 1][i - 1] == 0 && chessBoard.isDown[j - 1][i + 1] == 0)
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 2;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 2;
					}
					else
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 1;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 1;
					}
				}
				break;
			}
			case 2:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j - 1][i + 1] == 0 && chessBoard.isDown[j + 2][i - 2] == 0) || (chessBoard.isDown[j - 2][i + 2] == 0 && chessBoard.isDown[j + 1][i - 1] == 0))
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 5;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 5;
					}
					else
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 3;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 3;
					}
				}
				break;
			}
			case 3:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j - 1][i + 1] == 0 && chessBoard.isDown[j + 3][i - 3] == 0) || (chessBoard.isDown[j - 3][i + 3] == 0 && chessBoard.isDown[j + 1][i - 1] == 0))
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 12;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 12;
					}
					else
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 8;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 8;
					}
				}
				break;
			}
			case 4:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 40;
					AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 40;
				}
				break;
			}
			default:
				break;
			}

			numx = 0;
			numy = 0;
			numor = 0;
			numol = 0;
			whiteCMap.GetLinkNum(pointA, numx, numy, numor, numol);
			switch (numx)
			{
			case 1:
			{
				if (j + 1 >= 0 && j + 1 < 19 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
				{
					if (chessBoard.isDown[j + 1][i] == 0 && chessBoard.isDown[j - 1][i] == 0)
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 2;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 2;
					}
					else
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 1;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 1;
					}
				}
				break;
			}
			case 2:
			{
				if (j + 1 >= 0 && j + 1 < 19 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
				{
					if ((chessBoard.isDown[j + 1][i] == 0 && chessBoard.isDown[j - 2][i] == 0) || (chessBoard.isDown[j + 2][i] == 0 && chessBoard.isDown[j - 1][i] == 0))
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 6;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 6;
					}
					else
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 3;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 3;
					}
				}
				break;
			}
			case 3:
			{
				if (j + 1 >= 0 && j + 1 < 19 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
				{
					if ((chessBoard.isDown[j + 1][i] == 0 && chessBoard.isDown[j - 3][i] == 0) || (chessBoard.isDown[j + 3][i] == 0 && chessBoard.isDown[j - 1][i] == 0))
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 13;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 13;
					}
					else
					{
						AiScore[i][j + 1] = AiScore[i][j + 1] + 6;
						AiScore[i][j - 1] = AiScore[i][j - 1] + 6;
					}
				}
				break;
			}
			case 4:
			{
				if (j + 1 >= 0 && j + 1 < 19 && i >= 0 && i < 19 && j - 1 >= 0 && j - 1 < 19)
				{
					AiScore[i][j + 1] = AiScore[i][j + 1] + 100;
					AiScore[i][j - 1] = AiScore[i][j - 1] + 100;
				}
				break;
			}
			default:
				break;
			}

			switch (numy)
			{
			case 1:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if (chessBoard.isDown[j][i + 1] == 0 && chessBoard.isDown[j][i - 1] == 0)
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 2;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 2;
					}
					else
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 1;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 1;
					}
				}
				break;
			}
			case 2:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j][i + 1] == 0 && chessBoard.isDown[j][i - 2] == 0) || (chessBoard.isDown[j][i + 2] == 0 && chessBoard.isDown[j][i - 1] == 0))
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 6;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 6;
					}
					else
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 3;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 3;
					}
				}
				break;
			}
			case 3:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j][i + 1] == 0 && chessBoard.isDown[j][i - 3] == 0) || (chessBoard.isDown[j][i + 3] == 0 && chessBoard.isDown[j][i - 1] == 0))
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 13;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 13;
					}
					else
					{
						AiScore[i + 1][j] = AiScore[i + 1][j] + 6;
						AiScore[i - 1][j] = AiScore[i - 1][j] + 6;
					}
				}
				break;
			}
			case 4:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j >= 0 && j < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					AiScore[i + 1][j] = AiScore[i + 1][j] + 100;
					AiScore[i - 1][j] = AiScore[i - 1][j] + 100;
				}
				break;
			}
			default:
				break;
			}

			switch (numor)
			{
			case 1:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if (chessBoard.isDown[j + 1][i + 1] == 0 && chessBoard.isDown[j - 1][i - 1] == 0)
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 2;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 2;
					}
					else
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 1;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 1;
					}
				}
				break;
			}
			case 2:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j + 1][i + 1] == 0 && chessBoard.isDown[j - 2][i - 2] == 0) || (chessBoard.isDown[j + 2][i + 2] == 0 && chessBoard.isDown[j - 1][i - 1] == 0))
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 6;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 6;
					}
					else
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 3;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 3;
					}
				}
				break;
			}
			case 3:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j + 1][i + 1] == 0 && chessBoard.isDown[j - 3][i - 3] == 0) || (chessBoard.isDown[j + 3][i + 3] == 0 && chessBoard.isDown[j - 1][i - 1] == 0))
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 13;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 13;
					}
					else
					{
						AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 6;
						AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 6;
					}
				}
				break;
			}
			case 4:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					AiScore[i + 1][j + 1] = AiScore[i + 1][j + 1] + 100;
					AiScore[i - 1][j - 1] = AiScore[i - 1][j - 1] + 100;
				}
				break;
			}
			default:
				break;
			}

			switch (numol)
			{
			case 1:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if (chessBoard.isDown[j + 1][i - 1] == 0 && chessBoard.isDown[j - 1][i + 1] == 0)
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 2;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 2;
					}
					else
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 1;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 1;
					}
				}
				break;
			}
			case 2:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j - 1][i + 1] == 0 && chessBoard.isDown[j + 2][i - 2] == 0) || (chessBoard.isDown[j - 2][i + 2] == 0 && chessBoard.isDown[j + 1][i - 1] == 0))
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 6;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 6;
					}
					else
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 3;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 3;
					}
				}
				break;
			}
			case 3:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					if ((chessBoard.isDown[j - 1][i + 1] == 0 && chessBoard.isDown[j + 3][i - 3] == 0) || (chessBoard.isDown[j - 3][i + 3] == 0 && chessBoard.isDown[j + 1][i - 1] == 0))
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 13;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 13;
					}
					else
					{
						AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 6;
						AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 6;
					}
				}
				break;
			}
			case 4:
			{
				if (i + 1 >= 0 && i + 1 < 19 && j + 1 >= 0 && j + 1 < 19 && j - 1 >= 0 && j - 1 < 19 && i - 1 >= 0 && i - 1 < 19)
				{
					AiScore[i + 1][j - 1] = AiScore[i + 1][j - 1] + 100;
					AiScore[i - 1][j + 1] = AiScore[i - 1][j + 1] + 100;
				}
				break;
			}
			default:
				break;
			}

		}

	}
	// TODO: 在此处添加实现代码.
}

//计时
void CMFCDonwChessDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);
	if (downTime >= 0)
	{
		downTimeShow = downTime;
	}
	if (!isStop)
	{
		downTime--;
	}
	UpdateData(FALSE);
	if (downTime == 0)
	{
		MessageBox(TEXT("过时，系统自动下棋！"));

		CClientDC dc(this);
		CPoint point;
		//超时，AI帮助下棋
		if (pointVec.size() > 0)
		{
			CRect clearBorder(pointVec[pointVec.size() - 1].x - 14.5, pointVec[pointVec.size() - 1].y - 14.5, pointVec[pointVec.size() - 1].x + 14.5, pointVec[pointVec.size() - 1].y + 14.5);
			InvalidateRect(clearBorder, TRUE);
		}
		if (!isBlack)
		{
			BeTransparent(w_chess);//png透明化
			int aii, aij;
			if (pointVec.empty())
			{
				aii = aij = 9;
			}
			else
			{
				AIDownChess(aii, aij);
			}
			CPoint point;
			point.x = aij * 43 + 603;
			point.y = aii * 42 + 162;
			pointStack.push(point);//记录落子棋子坐标
			pointVec.push_back(point);
			w_chess.Draw(dc, point.x - 14.5, point.y - 14.5, 29, 29); // 显示棋子
			chessBoard.isDown[aij][aii] = 2;
			//将连通棋子记录在无向图邻接表中
			whiteCMap.LinkChess(aij, aii, chessBoard.isDown);
			//下回合
			isBlack = 1;
			isBlackBack = 0;
			int pointA = aij + aii * 19;
			//检查连接分数
			if (CheckChessConnection(pointA, whiteCMap))
			{
				//播放成功BGM
				::ShowWindow(hwnd2, SW_HIDE);
				MCIWndSetVolume(hwnd2, 1000);
				MCIWndPlay(hwnd2);
				MessageBox(TEXT("白棋赢"));
				isBlack = 1;
				chessBoard.InitChessDown();
				isBlackBack = 0;
				isWhiteBack = 0;
				while (!pointStack.empty())
				{
					pointStack.pop();
				}
				pointVec.clear();
				blackCMap.ResetChessMap();
				whiteCMap.ResetChessMap();
				Invalidate();
			}
		}
		else
		{
			BeTransparent(m_chess);//png透明化
			int aii, aij;
			if (pointVec.empty())
			{
				aii = aij = 9;
			}
			else
			{
				AIDownChess(aii, aij);
			}
			point.x = aij * 43 + 603;
			point.y = aii * 42 + 162;
			pointStack.push(point);//记录落子棋子坐标
			pointVec.push_back(point);
			m_chess.Draw(dc, point.x - 14.5, point.y - 14.5, 29, 29); // 显示棋子
			chessBoard.isDown[aij][aii] = 1;
			//将连通棋子记录在无向图邻接表中
			blackCMap.LinkChess(aij, aii, chessBoard.isDown);
			//下回合
			isBlack = 0;
			isWhiteBack = 0;
			int isBlackWin = 0;
			int pointA = aij + aii * 19;
			chessNum++;
			//检查连接分数
			if (CheckChessConnection(pointA, blackCMap))
			{
				//播放成功BGM
				::ShowWindow(hwnd2, SW_HIDE);
				MCIWndSetVolume(hwnd2, 1000);
				MCIWndPlay(hwnd2);
				int playerScore = ((19 * 19) / chessNum) * 123 + 1000;//按下子数算分
				CString playerStr;
				playerStr.Format(_T("%d"), playerScore);
				WriteScore(playerScore);//分数记录在文件中
				MessageBox(TEXT("你赢了，得分是：" + playerStr));
				isBlack = 1;
				chessBoard.InitChessDown();
				isBlackBack = 0;
				isWhiteBack = 0;
				while (!pointStack.empty())
				{
					pointStack.pop();
				}
				pointVec.clear();
				blackCMap.ResetChessMap();
				whiteCMap.ResetChessMap();
				isBlackWin = 1;
				Invalidate();
			}
			if (aiOrPk == 0 && !isBlackWin)
			{
				BeTransparent(w_chess);//png透明化
				int aii, aij;
				AIDownChess(aii, aij);
				point.x = aij * 43 + 603;
				point.y = aii * 42 + 162;
				pointStack.push(point);//记录落子棋子坐标
				pointVec.push_back(point);
				w_chess.Draw(dc, point.x - 14.5, point.y - 14.5, 29, 29); // 显示棋子
				chessBoard.isDown[aij][aii] = 2;
				//将连通棋子记录在无向图邻接表中
				whiteCMap.LinkChess(aij, aii, chessBoard.isDown);
				//下回合
				isBlack = 1;
				isBlackBack = 0;
				pointA = aij + aii * 19;
				//检查连接分数
				if (CheckChessConnection(pointA, whiteCMap))
				{
					//播放失败BGM
					::ShowWindow(hwnd3, SW_HIDE);
					MCIWndSetVolume(hwnd3, 1000);
					MCIWndPlay(hwnd3);
					MessageBox(TEXT("你输了"));
					isBlack = 1;
					chessBoard.InitChessDown();
					isBlackBack = 0;
					isWhiteBack = 0;
					while (!pointStack.empty())
					{
						pointStack.pop();
					}
					pointVec.clear();
					blackCMap.ResetChessMap();
					whiteCMap.ResetChessMap();
					Invalidate();
				}
			}
		}
		BeTransparent(border);//png透明化
		border.Draw(dc, point.x - 14.5, point.y - 14.5, 29, 29);
		downTime = 60;
		downTimeShow = 60;
	}
	CDialogEx::OnTimer(nIDEvent);
}

//暂停/继续游戏
void CMFCDonwChessDlg::OnBnClickedButton7()
{
	if (isStop == 0)
	{
		isStop = 1;
		MessageBox(TEXT("游戏暂停"));
	}
	else
	{
		isStop = 0;
		MessageBox(TEXT("游戏继续"));
	}
	// TODO: 在此添加控件通知处理程序代码
}

//结束游戏
void CMFCDonwChessDlg::OnBnClickedButton9()
{
	CDialogEx::OnCancel();
	// TODO: 在此添加控件通知处理程序代码
}
