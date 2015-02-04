#pragma once
#include "afxwin.h"


// CDialogView dialog

class CDialogView : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogView)

public:
	CDialogView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogView();

// Dialog Data
	enum { IDD = IDD_DIALOG_VIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	CListBox m_list;
	afx_msg void OnLbnSelchangeListView();
};
