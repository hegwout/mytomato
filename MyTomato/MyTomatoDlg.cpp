
// MyTomatoDlg.cpp : 实现文件
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



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CMyTomatoDlg 对话框



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


// CMyTomatoDlg 消息处理程序

BOOL CMyTomatoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	InitFromIni();

	// TODO:  在此添加额外的初始化代码
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
		nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称,注意:这里的消息是用户自定义消息
		nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
		wcscpy_s(nid.szTip, _T("我的番茄"));//信息提示条为"计划任务提醒"
		wcscpy_s(nid.szInfo, _T("我的番茄"));
		wcscpy_s(nid.szInfoTitle, _T("我的番茄"));

		nid.dwInfoFlags = NIIF_INFO;
		nid.uTimeout = 5000;
		Shell_NotifyIcon(NIM_ADD, &nid);//在托盘区添加图标
		isNotify = true;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyTomatoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyTomatoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CMyTomatoDlg::onShowTask(WPARAM wParam, LPARAM lParam)//wParam接收的是图标的ID，而lParam接收的是鼠标的行为
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP:			//右键起来时弹出快捷菜单，这里只有一个"关闭"
	{
									LPPOINT lpoint = new tagPOINT;
									::GetCursorPos(lpoint);			//得到鼠标位置
									CMenu menu, *pSubMenu;
									//menu.CreatePopupMenu();				//声明一个弹出式菜单			
									//menu.AppendMenu(MF_STRING, WM_DESTROY, _T("关闭"));   //增加菜单项"关闭"，点击则发送消息WM_DESTROY给主窗口（已隐藏），将程序结束。			
									//menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);//确定弹出式菜单的位置			
									menu.LoadMenuW(IDR_MENU1);
									pSubMenu = menu.GetSubMenu(0);
									
									pSubMenu->TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);

									//SetForegroundWindow();
									HMENU hmenu = menu.Detach();   //资源回收
									menu.DestroyMenu();
									delete lpoint;
	}break;
	case WM_LBUTTONDBLCLK:    //双击左键的处理
	{

								  this->ShowWindow(SW_SHOW);    //简单的显示主窗口完事儿
	}break;
	}
	return 0;
}


void CMyTomatoDlg::OnBnClickedButtonNotify()
{

	// TODO: 在此添加控件通知处理程序代码	

	//AnimateWindow(1000,AW_HIDE|AW_BLEND);      //可以缓慢消失窗口
	// KillTimer(0);
	//ShowWindow(SW_HIDE);//隐藏主窗口

}


void CMyTomatoDlg::OnIddMytomatoDialog()
{
	// TODO:  在此添加命令处理程序代码
}




void CMyTomatoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


void CMyTomatoDlg::OnBnClickedButtonNo()
{
	// TODO:  在此添加控件通知处理程序代码
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


void CMyTomatoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (time_left == 0)
	{
		KillTimer(1);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), ::GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
		SetDlgItemText(IDC_BUTTON_START, _T("开始"));
		//TODO: 弹出提示窗口
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
	// TODO:  在此添加控件通知处理程序代码
	if (time_left > 0)
	{
		KillTimer(1);
		SetDlgItemText(IDC_BUTTON_START, _T("开始"));
		time_left = 0;
		CString cp("");
		cp.Format(_T("%02d:00"), TIME_LENGTH);
		SetDlgItemText(IDC_STATIC_TIMER, cp);
	}
	else
	{
		time_left = TIME_LENGTH * 60;
		CWnd::SetTimer(1, 1000, NULL);
		SetDlgItemText(IDC_BUTTON_START, _T("停止"));
	}

}


void CMyTomatoDlg::OnBnClickedButton1()
{ 
	// TODO:  在此添加控件通知处理程序代码
	SQLiteHelper  helper ;
	CString s = CString("");
	s.Format(_T("%d"), helper.TestSQL());
	AfxMessageBox(s);
}



void CMyTomatoDlg::OnMenuRun()
{
	// TODO:  在此添加命令处理程序代码
	//添加以下代码
	HKEY   RegKey;
	CString   sPath;

	GetModuleFileName(NULL, sPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	sPath.ReleaseBuffer();
	int   nPos;

	nPos = sPath.ReverseFind('\\');
	sPath = sPath.Left(nPos);

	CString   lpszFile = sPath + "\\MyTomato.exe";//这里加上你要查找的执行文件名称  
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
			);//这里加上你需要在注册表中注册的内容   

		this->UpdateData(FALSE);
	}
	else
	{
		//theApp.SetMainSkin();  
		::AfxMessageBox(_T("没找到执行程序，自动运行失败"));

		exit(0);
	}
	return ;
}


void CMyTomatoDlg::OnMenuExit()
{
	// TODO:  在此添加命令处理程序代码
	::PostQuitMessage(0);
}


void CAboutDlg::OnMenuShow()
{
	// TODO:  在此添加命令处理程序代码
	 
	if (IsWindowVisible())
		ShowWindow(SW_HIDE);
	else
		ShowWindow(SW_SHOWNORMAL);
}


void CAboutDlg::OnMuneTop()
{
	// TODO:  在此添加命令处理程序代码
}


void CMyTomatoDlg::OnMuneTop()
{
	// TODO:  在此添加命令处理程序代码 
	
}


void CMyTomatoDlg::OnMenuShow()
{
	// TODO:  在此添加命令处理程序代码
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
	GetCurrentDirectoryW(256, strBuff);  //获取当前路径
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
	// TODO:  在此添加控件通知处理程序代码
	//CDialog dlg(IDD_DIALOG_ALERT);
	//dlg.SetWindowTextW(_T(""));
	//dlg.DoModal();
	
	CDialogAlert  *pDlg = new CDialogAlert;
	pDlg->Create(IDD_DIALOG_ALERT, this);
	pDlg->ShowWindow(SW_SHOW);
}

 