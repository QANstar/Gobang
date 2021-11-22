// Model.cpp: 实现文件
//

#include "pch.h"
#include "MFCDonwChess.h"
#include "Model.h"
#include "afxdialogex.h"


// CModel 对话框

IMPLEMENT_DYNAMIC(CModel, CDialogEx)

CModel::CModel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CModel::~CModel()
{
}

void CModel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModel, CDialogEx)
END_MESSAGE_MAP()


// CModel 消息处理程序
