// DialogView.cpp : implementation file
//

#include "stdafx.h"
#include "MyTomato.h"
#include "DialogView.h"
#include "afxdialogex.h"

#include "SQLiteHelper.h"
#include "LogFile.h"
#include <vector>
#include <string>

// CDialogView dialog

IMPLEMENT_DYNAMIC(CDialogView, CDialogEx)

CDialogView::CDialogView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogView::IDD, pParent)
{

}

CDialogView::~CDialogView()
{
	DestroyWindow();
}

void CDialogView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW, m_list);
}


BEGIN_MESSAGE_MAP(CDialogView, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_VIEW, &CDialogView::OnLbnSelchangeListView)
END_MESSAGE_MAP()


// CDialogView message handlers


BOOL CDialogView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	//TODO: ²éÑ¯Êý¾Ý
	SQLiteHelper helper;
	std::vector<std::wstring> list = helper.GetList();
	for ( auto v:list ){  
		auto a = v.c_str();	

		CString s(a);
		m_list.AddString(s);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogView::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	//DestroyWindow();
	CDialogEx::OnCancel();
}


void CDialogView::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();
	//delete this;
}


void CDialogView::OnLbnSelchangeListView()
{
	// TODO: Add your control notification handler code here
}
