#include "stdafx.h"
#include "LogFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CLogFile::CLogFile()
{
}


CLogFile::~CLogFile()
{
}


//获取文件名称
CString CLogFile::GetFileName()
{
	CString m_sFileName;
	CTime t = CTime::GetCurrentTime(); 
	m_sFileName = t.Format("%Y-%m-%d.log"); 
	return m_sFileName;
}
//获取应用程序所在路径
CString CLogFile::GetFilePath()
{
	CString m_FilePath;

	GetModuleFileName(NULL, m_FilePath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);

	m_FilePath.ReleaseBuffer();

	int m_iPosIndex;

	m_iPosIndex = m_FilePath.ReverseFind('\\');

	m_FilePath = m_FilePath.Left(m_iPosIndex);
	m_FilePath.Append(_T("\\Log"));
	return m_FilePath;
}

BOOL CLogFile::WriteLog(CString LogText)
{
	try
	{
		CFile m_File;
		CStdioFile m_SFile;
		CFileFind m_FileFind;
		CString m_sErrorMessage;
		CString m_sFileName = GetFileName();
		CString m_sFilePath = GetFilePath();
		CString m_sCurrentTime = CTime::GetCurrentTime().Format("%Y-%m-%d %X");
		
		//m_sErrorMessage = _T("*******************") + m_sCurrentTime + _T("*******************") + _T("\r");
		m_sErrorMessage = "";
		m_sErrorMessage += LogText + L"\r";
		//m_sErrorMessage += _T("*******************") + m_sCurrentTime + _T("*******************") + _T("\r");

		if (!m_FileFind.FindFile(m_sFilePath))
		{
			CreateDirectory(m_sFilePath, NULL);
		}

		if (!m_SFile.Open(m_sFilePath + "\\" + m_sFileName, CFile::modeReadWrite))
		{
			m_SFile.Open(m_sFilePath + "\\" + m_sFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText);
		} 
		m_SFile.SeekToEnd();

		char* m_szMessage; 
		m_szMessage = (char*)(LPCTSTR)m_sErrorMessage;
		//m_SFile.Write(m_szMessage, strlen(m_szMessage));
		m_SFile.WriteString(m_sErrorMessage);
		m_SFile.Close();
	}
	catch (CFileException fileException)
	{
		return false;
	}

	return true;
}