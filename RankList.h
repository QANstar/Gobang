#pragma once
#include <vector>

// CRankList 对话框

class CRankList : public CDialogEx
{
	DECLARE_DYNAMIC(CRankList)

public:

	CImage background;
	std::vector <int> vecResult;
	CRankList(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRankList();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ReadList();
	CEdit rankListWin;
	afx_msg void OnBnClickedShowrank();
	int QuickSort(int low, int high);
	void Sort(int low, int high);
	afx_msg void OnPaint();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
