
// MyTomato.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyTomatoApp: 
// �йش����ʵ�֣������ MyTomato.cpp
//

class CMyTomatoApp : public CWinApp
{
public:
	CMyTomatoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyTomatoApp theApp;