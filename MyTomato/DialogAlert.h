#pragma once


// CDialogAlert 对话框

class CDialogAlert : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAlert)

public:
	CDialogAlert(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogAlert();

// 对话框数据
	enum { IDD = IDD_DIALOG_ALERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMfcbutton1();
	virtual BOOL OnInitDialog();
};
