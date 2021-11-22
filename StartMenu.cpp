// StartMenu.cpp: 实现文件
//

#include "pch.h"
#include "MFCDonwChess.h"
#include "StartMenu.h"
#include "afxdialogex.h"


// CStartMenu 对话框

IMPLEMENT_DYNAMIC(CStartMenu, CDialogEx)

CStartMenu::CStartMenu(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	CString fileName = _T("res\\2.mp3");
	hwnd2 = MCIWndCreate(m_hWnd, NULL, MCIWNDF_NOPLAYBAR, fileName);
	startBackground.Load(TEXT("res//Start1.png"));
	m_newFont.CreatePointFont(300, _T("仿宋"));
}

CStartMenu::~CStartMenu()
{
}

void CStartMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStartMenu, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStartMenu::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &CStartMenu::OnBnClickedCancel)
	ON_BN_CLICKED(PVP, &CStartMenu::OnBnClickedPvp)
	ON_BN_CLICKED(Rank, &CStartMenu::OnBnClickedRank)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CStartMenu 消息处理程序


void CStartMenu::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	aop = 0;
	MCIWndPause(hwnd2);
	CDialogEx::OnOK();
}

void CStartMenu::OnPaint()
{

	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	::ShowWindow(hwnd2, SW_HIDE);
	MCIWndSetVolume(hwnd2, 100);
	MCIWndPlay(hwnd2);
	startBackground.Draw(dc, -120, 0, 800, 1113);
	// 设置   
	m_pOldFont = (CFont*)dc.SelectObject(&m_newFont);
	dc.SetBkMode(TRANSPARENT); //设置背景为透明！   
	// 设置文本颜色为红色   
	dc.SetTextColor(RGB(255, 204, 153));
	// 在指定位置输出文本   
	dc.TextOut(195, 20, _T("萌子棋"));
}


void CStartMenu::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CStartMenu::OnBnClickedPvp()
{
	aop = 1;
	MCIWndPause(hwnd2);
	CDialogEx::OnOK();
	// TODO: 在此添加控件通知处理程序代码
}


void CStartMenu::OnBnClickedRank()
{
	rankList.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CStartMenu::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDCtl == PVP || nIDCtl == IDOK || nIDCtl == IDCANCEL || nIDCtl == Rank) //表示想重绘的控件
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
