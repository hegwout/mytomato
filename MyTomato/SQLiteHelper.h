#pragma once
#include <string>
#include <ctime>
#include <vector>

static int _sql_callback(void * notused, int argc, char ** argv, char ** szColName)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", szColName[i], argv[i] == 0 ? "NUL" : argv[i]);
	}

	return 0;
}

class SQLiteHelper
{
public:
	SQLiteHelper();
	~SQLiteHelper();
	int TestSQL();
	int InitDB();
	int NewTomato(const wchar_t*);
private:
	const char* db_name = "tomato.db";

public:
	std::vector<std::wstring> GetList();
};

