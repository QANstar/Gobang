// PlayerConnect.cpp: 实现文件
//

#include "pch.h"
#include "MFCDonwChess.h"
#include "PlayerConnect.h"
#include "afxdialogex.h"


// CPlayerConnect 对话框

IMPLEMENT_DYNAMIC(CPlayerConnect, CDialogEx)

CPlayerConnect::CPlayerConnect(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CPlayerConnect::~CPlayerConnect()
{
}

void CPlayerConnect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, ServerIP);
	DDX_Control(pDX, IDC_EDIT1, ServerPort);
}


BEGIN_MESSAGE_MAP(CPlayerConnect, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPlayerConnect::OnBnClickedOk)
END_MESSAGE_MAP()


// CPlayerConnect 消息处理程序


void CPlayerConnect::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
