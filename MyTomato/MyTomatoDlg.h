
// MyTomatoDlg.h : ͷ�ļ�
//

#pragma once


// CMyTomatoDlg �Ի���
class CMyTomatoDlg : public CDialogEx
{
// ����
public:
	CMyTomatoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYTOMATO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	BOOL isNotify;	
	BOOL isTop;		//������ǰ
	BOOL isRun;		//�Ƿ񿪻�����
	const int TIME_LENGTH = 1;
	int  time_left = 0;
	NOTIFYICONDATAW nid;
	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
/***��ϵͳ��Ҫ�����������״̬������Ϣ***/
 


#define WM_SHOWTASK (WM_USER+101)
