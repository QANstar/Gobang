#pragma once
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "VFW32.lib")
#include <Mmsystem.h>
#include<windows.h>
#include <Vfw.h>
#include <RankList.h>
// CStartMenu 对话框

class CStartMenu : public CDialogEx
{
	DECLARE_DYNAMIC(CStartMenu)

public:
	CFont m_newFont;   // 新字体   
	CFont* m_pOldFont; // 选择新字体之前的字体  
	HWND hwnd2;
	int aop;
	CStartMenu(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStartMenu();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRankList rankList;
	CImage startBackground;
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedPvp();
	afx_msg void OnBnClickedRank();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
