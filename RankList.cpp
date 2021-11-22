// RankList.cpp: 实现文件
//

#include "pch.h"
#include "MFCDonwChess.h"
#include "RankList.h"
#include "afxdialogex.h"


// CRankList 对话框

IMPLEMENT_DYNAMIC(CRankList, CDialogEx)

CRankList::CRankList(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
	background.Load(TEXT("res//Start2.png"));
}

CRankList::~CRankList()
{
}

void CRankList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, rankListWin);
}


BEGIN_MESSAGE_MAP(CRankList, CDialogEx)
	ON_BN_CLICKED(ShowRank, &CRankList::OnBnClickedShowrank)
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CRankList 消息处理程序


void CRankList::ReadList()
{
	CString strFileName = _T("res//Chess.txt"); // 相对路径

	if (!PathFileExists(strFileName)) {
		return;
	}
	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeRead))
	{
		return;
	}

	CString strValue = _T("");
	while (file.ReadString(strValue))
	{
		int sce= _ttoi(strValue);
		vecResult.push_back(sce); // 把文件到行数据写到向量的末尾
	}
	file.Close();
	Sort(0, vecResult.size() - 1);
	// 弹出一个文件中的字符串
	CString strLineNum;
	//strLineNum.Format(_T("%d"), vecResult.size());//输出文件的行数，有几行就是几行

	// 文件内容显示在编辑框中
	rankListWin.SetWindowText(_T(""));//清空编辑框
	int ranking = 0;
	for (int i = vecResult.size() - 1; i >= 0 ; i--) {
		CString str, str2;
		ranking++;
		str2.Format(_T("%d"), ranking);
		str.Format(_T("%d"), vecResult[i]);
		rankListWin.ReplaceSel(str2 + _T(":"));
		rankListWin.ReplaceSel(str + _T("分"));
		str.Format(L"\r\n");
		rankListWin.ReplaceSel(str);
	}

	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此处添加实现代码.
}


void CRankList::OnBnClickedShowrank()
{
	ReadList();
	// TODO: 在此添加控件通知处理程序代码
}


int CRankList::QuickSort(int low, int high)
{
	int pivotkey;
	pivotkey = vecResult[low];
	while (low < high)
	{
		while (low < high && vecResult[high] >= pivotkey)
		{
			--high;
		}
		vecResult[low] = vecResult[high];
		while (low < high && vecResult[low] <= pivotkey)
		{
			++low;
		}
		vecResult[high] = vecResult[low];
	}
	vecResult[low] = pivotkey;
	return low;
}


void CRankList::Sort(int low, int high)
{
	
	int pivotloc;
	if (low < high)
	{
		pivotloc = QuickSort(low, high);
		Sort(low, pivotloc - 1);
		Sort(pivotloc + 1, high);
	}
	// TODO: 在此处添加实现代码.
}


void CRankList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	background.Draw(dc, -200, -50, 844, 906);
}


void CRankList::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDCtl == ShowRank || nIDCtl == IDCANCEL) //表示想重绘的控件
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
