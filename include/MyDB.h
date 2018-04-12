#include<iostream>
#include<string>
#include<mysql/mysql.h>
using namespace std;

#define INSERT 1
#define SELECT 2
#define UPDATE 3
class MyDB
{
public:
	MyDB();
	~MyDB();
	bool initDB(string host, string user, string pwd, string db_name);
	//执行数据库操作 option传递操作类型, result返回select查询结果
	bool exeSQL(string sql,int option,MYSQL_RES *&result);

	MYSQL_RES *result;
	MYSQL_ROW row;
private:
	MYSQL *connection;

};
