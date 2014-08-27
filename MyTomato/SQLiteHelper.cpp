#include "stdafx.h"
#include "SQLiteHelper.h"


#include "../sqlite3/sqlite3.h"
#pragma comment(lib, "../sqlite3/sqlite3.lib")

SQLiteHelper::SQLiteHelper()
{
}


SQLiteHelper::~SQLiteHelper()
{

}

int SQLiteHelper::InitDB()
{
	const char * sSQL3 = "select * from users;";
	sqlite3 * db	= 0;
	int ret			= 0;
	ret = sqlite3_open("./test.db", &db);

	if (ret != SQLITE_OK)
	{ 
		AfxMessageBox(_T("�޷������ݿ�: "));
		return 0;
	}

	const char * sSQL1 = "create table users(userid varchar(20) PRIMARY KEY, age int, birthday datetime);";

	return 1;
}



int SQLiteHelper::TestSQL()
{
	const char * sSQL1 = "create table users(userid varchar(20) PRIMARY KEY, age int, birthday datetime);";
	const char * sSQL2 = "insert into users values('wang',20,'1989-5-4');";
	const char * sSQL3 = "select * from users;";
	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;

	// �������ݿ�
	ret = sqlite3_open("./test.db", &db);

	if (ret != SQLITE_OK)
	{

		AfxMessageBox(_T("�޷������ݿ�: "));
		return 1;
	}
	AfxMessageBox(_T("���ݿ����ӳɹ�!\n"));

	// ִ�н���SQL

	sqlite3_exec(db, sSQL1, 0, 0, &pErrMsg);
	if (ret != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", pErrMsg);
		sqlite3_free(pErrMsg);
	}

	// ִ�в����¼SQL
	sqlite3_exec(db, sSQL2, 0, 0, &pErrMsg);

	// ��ѯ���ݱ�
	sqlite3_exec(db, sSQL3, _sql_callback, 0, &pErrMsg);

	// �ر����ݿ�
	sqlite3_close(db);
	db = 0;

	return 0;
}
