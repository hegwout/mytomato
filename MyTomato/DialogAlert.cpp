// DialogAlert.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyTomato.h"
#include "DialogAlert.h"
#include "afxdialogex.h"


// CDialogAlert �Ի���

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


// CDialogAlert ��Ϣ�������

 
BOOL CDialogAlert::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	AnimateWindow(1000, AW_CENTER | AW_ACTIVATE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
