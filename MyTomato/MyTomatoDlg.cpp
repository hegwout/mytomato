
// MyTomatoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyTomato.h"
#include "MyTomatoDlg.h"
#include "DialogAlert.h"
#include "afxdialogex.h"
#include "mmsystem.h"

#include "SQLiteHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuShow();
	afx_msg void OnMuneTop();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_MENU_SHOW, &CAboutDlg::OnMenuShow)
	ON_COMMAND(ID_MUNE_TOP, &CAboutDlg::OnMuneTop)
END_MESSAGE_MAP()


// CMyTomatoDlg �Ի���



CMyTomatoDlg::CMyTomatoDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CMyTomatoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyTomatoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyTomatoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK, onShowTask)
	ON_BN_CLICKED(IDC_BUTTON_NOTIFY, &CMyTomatoDlg::OnBnClickedButtonNotify)
	ON_COMMAND(IDD_MYTOMATO_DIALOG, &CMyTomatoDlg::OnIddMytomatoDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_NO, &CMyTomatoDlg::OnBnClickedButtonNo)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMyTomatoDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyTomatoDlg::OnBnClickedButton1)
	ON_COMMAND(ID_MENU_RUN, &CMyTomatoDlg::OnMenuRun)
	ON_COMMAND(ID_MENU_EXIT, &CMyTomatoDlg::OnMenuExit)
	ON_COMMAND(ID_MUNE_TOP, &CMyTomatoDlg::OnMuneTop)
	ON_COMMAND(ID_MENU_SHOW, &CMyTomatoDlg::OnMenuShow) 
END_MESSAGE_MAP()


// CMyTomatoDlg ��Ϣ�������

BOOL CMyTomatoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	InitFromIni();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	isNotify = false;
	CString cp("");
	cp.Format(_T("%02d:00"), TIME_LENGTH);
	SetDlgItemText(IDC_STATIC_TIMER, cp);
	if ( isTop )
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	if (!isNotify)
	{

		nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
		nid.hWnd = this->m_hWnd;
		nid.uID = IDR_MAINFRAME;
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
		nid.uCallbackMessage = WM_SHOWTASK;//�Զ������Ϣ����,ע��:�������Ϣ���û��Զ�����Ϣ
		nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
		wcscpy_s(nid.szTip, _T("�ҵķ���"));//��Ϣ��ʾ��Ϊ"�ƻ���������"
		wcscpy_s(nid.szInfo, _T("�ҵķ���"));
		wcscpy_s(nid.szInfoTitle, _T("�ҵķ���"));

		nid.dwInfoFlags = NIIF_INFO;
		nid.uTimeout = 5000;
		Shell_NotifyIcon(NIM_ADD, &nid);//�����������ͼ��
		isNotify = true;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMyTomatoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyTomatoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyTomatoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMyTomatoDlg::onShowTask(WPARAM wParam, LPARAM lParam)//wParam���յ���ͼ���ID����lParam���յ���������Ϊ
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP:			//�Ҽ�����ʱ������ݲ˵�������ֻ��һ��"�ر�"
	{
									LPPOINT lpoint = new tagPOINT;
									::GetCursorPos(lpoint);			//�õ����λ��
									CMenu menu, *pSubMenu;
									//menu.CreatePopupMenu();				//����һ������ʽ�˵�			
									//menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�ر�"));   //���Ӳ˵���"�ر�"�����������ϢWM_DESTROY�������ڣ������أ��������������			
									//menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);//ȷ������ʽ�˵���λ��			
									menu.LoadMenuW(IDR_MENU1);
									pSubMenu = menu.GetSubMenu(0);
									
									pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);

									//SetForegroundWindow();
									HMENU hmenu = menu.Detach();   //��Դ����
									menu.DestroyMenu();
									delete lpoint;
	}break;
	case WM_LBUTTONDBLCLK:    //˫������Ĵ���
	{

								  this->ShowWindow(SW_SHOW);    //�򵥵���ʾ���������¶�
	}break;
	}
	return 0;
}


void CMyTomatoDlg::OnBnClickedButtonNotify()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������	

	//AnimateWindow(1000,AW_HIDE|AW_BLEND);      //���Ի�����ʧ����
	// KillTimer(0);
	//ShowWindow(SW_HIDE);//����������

}


void CMyTomatoDlg::OnIddMytomatoDialog()
{
	// TODO:  �ڴ���������������
}




void CMyTomatoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


void CMyTomatoDlg::OnBnClickedButtonNo()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


void CMyTomatoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (time_left == 0)
	{
		KillTimer(1);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), ::GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
		SetDlgItemText(IDC_BUTTON_START, _T("��ʼ"));
		//TODO: ������ʾ����
		CDialogAlert  *pDlg = new CDialogAlert;
		pDlg->Create(IDD_DIALOG_ALERT, this);
		pDlg->ShowWindow(SW_SHOW);
		
		

	}
	else
	{
		time_left--;
		CString text("");
		text.Format(_T("%02d:%02d"), time_left / 60, time_left % 60);
		SetDlgItemText(IDC_STATIC_TIMER, text);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMyTomatoDlg::OnBnClickedButtonStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (time_left > 0)
	{
		KillTimer(1);
		SetDlgItemText(IDC_BUTTON_START, _T("��ʼ"));
		time_left = 0;
		CString cp("");
		cp.Format(_T("%02d:00"), TIME_LENGTH);
		SetDlgItemText(IDC_STATIC_TIMER, cp);
	}
	else
	{
		time_left = TIME_LENGTH * 60;
		CWnd::SetTimer(1, 1000, NULL);
		SetDlgItemText(IDC_BUTTON_START, _T("ֹͣ"));
	}

}


void CMyTomatoDlg::OnBnClickedButton1()
{ 
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SQLiteHelper  helper ;
	CString s = CString("");
	s.Format(_T("%d"), helper.TestSQL());
	AfxMessageBox(s);
}



void CMyTomatoDlg::OnMenuRun()
{
	// TODO:  �ڴ���������������
	//������´���
	HKEY   RegKey;
	CString   sPath;

	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int   nPos;

	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);

	CString   lpszFile = sPath + "\\MyTomato.exe";//���������Ҫ���ҵ�ִ���ļ�����  
	CFileFind   fFind;

	BOOL   bSuccess;
	bSuccess = fFind.FindFile(lpszFile);

	fFind.Close();
	if (bSuccess)
	{
		CString   fullName;

		fullName = lpszFile;
		RegKey = NULL;

		RegOpenKey(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &RegKey);

		RegSetValueEx(RegKey, _T("MyTomato"), 0,
			REG_SZ,
			(const unsigned   char*)(LPCTSTR)fullName,
			fullName.GetLength()
			);//�����������Ҫ��ע�����ע�������   

		this->UpdateData(FALSE);
	}
	else
	{
		//theApp.SetMainSkin();  
		::AfxMessageBox(_T("û�ҵ�ִ�г����Զ�����ʧ��"));

		exit(0);
	}
	return ;
}


void CMyTomatoDlg::OnMenuExit()
{
	// TODO:  �ڴ���������������
	::PostQuitMessage(0);
}


void CAboutDlg::OnMenuShow()
{
	// TODO:  �ڴ���������������
	 
	if (IsWindowVisible())
		ShowWindow(SW_HIDE);
	else
		ShowWindow(SW_SHOWNORMAL);
}


void CAboutDlg::OnMuneTop()
{
	// TODO:  �ڴ���������������
}


void CMyTomatoDlg::OnMuneTop()
{
	// TODO:  �ڴ��������������� 
	
}


void CMyTomatoDlg::OnMenuShow()
{
	// TODO:  �ڴ���������������
	if (IsWindowVisible())
		ShowWindow(SW_HIDE);
	else
		ShowWindow(SW_SHOWNORMAL);
}



void CMyTomatoDlg::InitFromIni()
{ 
	CString strSection = _T("Setting");
	CString strSectionKey = _T("isTop");	
	CString strValue = _T("1");
	CString strFilePath;
	wchar_t strBuff[256];
	GetCurrentDirectoryW(256, strBuff);  //��ȡ��ǰ·��
	strFilePath.Format(_T("%s//tomato.ini"), strBuff);
	GetPrivateProfileString(strSection, strSectionKey, NULL, strBuff, 80, strFilePath);
	strValue = strBuff;
	if (strValue.IsEmpty())
	{
		WritePrivateProfileString(strSection, strSectionKey, _T("1"), strFilePath);
	}
	isTop = strValue.Trim().Left(1) == "1" ? true : false; 
	 
	
}


void CMyTomatoDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialog dlg(IDD_DIALOG_ALERT);
	//dlg.SetWindowTextW(_T(""));
	//dlg.DoModal();
	
	CDialogAlert  *pDlg = new CDialogAlert;
	pDlg->Create(IDD_DIALOG_ALERT, this);
	pDlg->ShowWindow(SW_SHOW);
}

 