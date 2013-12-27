#pragma once

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
};

