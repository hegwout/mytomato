#pragma once


// CDialogAlert �Ի���

class CDialogAlert : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAlert)

public:
	CDialogAlert(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogAlert();

// �Ի�������
	enum { IDD = IDD_DIALOG_ALERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMfcbutton1();
	virtual BOOL OnInitDialog();
};
