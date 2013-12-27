// DialogAlert.cpp : 实现文件
//

#include "stdafx.h"
#include "MyTomato.h"
#include "DialogAlert.h"
#include "afxdialogex.h"


// CDialogAlert 对话框

IMPLEMENT_DYNAMIC(CDialogAlert, CDialogEx)

CDialogAlert::CDialogAlert(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogAlert::IDD, pParent)
{

}

CDialogAlert::~CDialogAlert()
{
}

void CDialogAlert::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CDialogAlert, CDialogEx)
	 
END_MESSAGE_MAP()


// CDialogAlert 消息处理程序

 
BOOL CDialogAlert::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	AnimateWindow(1000, AW_CENTER | AW_ACTIVATE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
