#pragma once


// CModel 对话框

class CModel : public CDialogEx
{
	DECLARE_DYNAMIC(CModel)

public:
	CModel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CModel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
