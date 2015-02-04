#include "stdafx.h"
#include "SQLiteHelper.h"
#include <string>
#include <time.h>
#include <vector>
#include "LogFile.h"

#include "../sqlite3/sqlite3.h"
#pragma comment(lib, "../sqlite3/sqlite3.lib")

using namespace std;

SQLiteHelper::SQLiteHelper()
{
 
	InitDB();
}


SQLiteHelper::~SQLiteHelper()
{
	
}

int SQLiteHelper::InitDB()
{
	const char * sSQL3 = "select 1 from users;";
	sqlite3 * db	= 0;
	int ret			= 0;
	char * pErrMsg = 0;
	ret = sqlite3_open(db_name, &db);

	if (ret != SQLITE_OK)
	{ 
		AfxMessageBox(_T("无法打开数据库: "));
		return 1;
	} 

	const char * create_table = "create table t_list( id INTEGER PRIMARY KEY autoincrement, title TEXT(32) ,begin_time TEXT ,end_time TEXT);";
	sqlite3_exec(db, create_table, 0, 0, &pErrMsg);
	if (ret != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", pErrMsg);
		sqlite3_free(pErrMsg);
	}

	sqlite3_close(db);

	return 0;
}



int SQLiteHelper::TestSQL()
{
	const char * sSQL1 = "create table users(userid varchar(20) PRIMARY KEY, age int, birthday datetime);";
	const char * sSQL2 = "insert into users values('wang',20,'1989-5-4');";
	const char * sSQL3 = "select * from users;";
	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;

	// 连接数据库
	ret = sqlite3_open("./test.db", &db);

	if (ret != SQLITE_OK)
	{

		AfxMessageBox(_T("无法打开数据库: "));
		return 1;
	}
	AfxMessageBox(_T("数据库连接成功!\n"));

	// 执行建表SQL

	sqlite3_exec(db, sSQL1, 0, 0, &pErrMsg);
	if (ret != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", pErrMsg);
		sqlite3_free(pErrMsg);
	}

	// 执行插入记录SQL
	sqlite3_exec(db, sSQL2, 0, 0, &pErrMsg);

	// 查询数据表
	sqlite3_exec(db, sSQL3, _sql_callback, 0, &pErrMsg);

	// 关闭数据库
	sqlite3_close(db);
	db = 0;

	return 0;
}



int SQLiteHelper::NewTomato(const wchar_t* title)
{
	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;
	//wchar_t sql = L"insert into t_list(title) values('第一条');";
	 
	// 连接数据库
	ret = sqlite3_open(db_name, &db);
	if (ret != SQLITE_OK)
	{ 
		AfxMessageBox(_T("无法打开数据库: "));
		return 1;
	}
	

	//当前时间
	struct tm  t ;
	time_t ti = time(NULL);
	char begin[50];
	localtime_s(&t, &ti);
	strftime(begin, sizeof(begin), "%Y-%m-%d %H:%M:%S",&t );

	wchar_t* sql = new wchar_t[100];
	wsprintf(sql, _T("insert into t_list(title,begin_time) values('%s','%s');"), title, CA2W(begin));
	 
	// 执行插入记录SQL
	int result = sqlite3_exec(db, CW2A(sql,CP_UTF8), 0, 0, &pErrMsg);

	return result;
}




std::vector<std::wstring> SQLiteHelper::GetList()
{
	std::vector<wstring> list;
	std::vector<wstring>::iterator it;
	
	sqlite3 * db = 0;
	char * pErrMsg = 0;
	int ret = 0;
 
	// 连接数据库
	ret = sqlite3_open(db_name, &db);
	if (ret != SQLITE_OK)
	{
		AfxMessageBox(_T("无法打开数据库: ")); 
	}
	else{
		//string sql = CW2A(_T("select * from t_list;"), CP_UTF8); 
		char **pazResult;
		int nRow, nCol;
		/*
		id,title,begin_time,end_time
		1, 'Title1',   '',    ''
		2, 'Title2',   '',    ''    
		*/
		ret = sqlite3_get_table(db, "SELECT * FROM t_list ORDER BY id DESC LIMIT 1000 OFFSET 0", &pazResult, &nRow, &nCol, 0);
		if (SQLITE_OK == ret){
			for (int i = 0; i < nRow; i++){
				int j = (i + 1) * nCol + 1; //title的列值
				wstring title = CA2W(pazResult[j], CP_UTF8)   ;
				title.append(L" (");
				title.append(CA2W(pazResult[j + 1], CP_UTF8));
				title.append(L")");
				list.push_back(title);
		 
				//char *a = new char[10];
				//_itoa_s(i, a, 5, 10);
				//string s("This is item ");
				//s.append(a);
				//list.push_back(s);
				//delete a;
			}
		}
		sqlite3_free_table(pazResult); 
	}

	
	return list;
}
 