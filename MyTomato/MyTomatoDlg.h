
// MyTomatoDlg.h : 头文件
//

#pragma once


// CMyTomatoDlg 对话框
class CMyTomatoDlg : public CDialogEx
{
// 构造
public:
	CMyTomatoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYTOMATO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	BOOL isNotify;	
	BOOL isTop;		//窗口最前
	BOOL isRun;		//是否开机运行
	const int TIME_LENGTH = 1;
	int  time_left = 0;
	NOTIFYICONDATAW nid;
	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT onShowTask(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonNotify();
	afx_msg void OnIddMytomatoDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonNo();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnMenuRun();
	afx_msg void OnMenuExit();
	afx_msg void OnMuneTop();
	afx_msg void OnMenuShow();
	void InitFromIni();
	afx_msg void OnBnClickedButton2();
};
/***该系统需要处理的任务栏状态区的消息***/
 


#define WM_SHOWTASK (WM_USER+101)
