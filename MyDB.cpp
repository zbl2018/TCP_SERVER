#include<iostream>
#include<cstdlib>
#include "stdio.h"
#include "./include/MyDB.h"
using namespace std;

MyDB::MyDB()
{
	connection = mysql_init(NULL); // 初始化数据库连接变量
	if(connection == NULL)
	{
		cout << "Error:" << mysql_error(connection);
		exit(1);
	}
	 result=NULL;
     row=NULL;
}

MyDB::~MyDB()
{
	if(connection != NULL)  // 关闭数据库连接
	{
		mysql_close(connection);
	}
}

bool MyDB::initDB(string host, string user, string pwd, string db_name)
{
	// 函数mysql_real_connect建立一个数据库连接
	// 成功返回MYSQL*连接句柄，失败返回NULL
	connection = mysql_real_connect(connection, host.c_str(),
			user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
			//cout<<"111"<<endl;
	if(connection == NULL)
	{
		cout << "Error:" <<mysql_error(connection)<<endl;
		return false;
		//exit(1);
	}
	else {
		printf("connect database successfully!\n");
		return true;
	}
	//return true;
}

bool MyDB::exeSQL(string sql,int option,MYSQL_RES *&result)
{
	if(mysql_real_query(connection, sql.c_str(),sql.length()+1))
	{
		cout << "Query Error:" << mysql_error(connection);
		return false;
		//exit(1);
	}
	//根据 option参数返回结果
	//cout<<"2"<<endl;
	switch(option)
	{
		case INSERT :{
						printf("insert sucessfully!\n");
						return true;
					}
		case SELECT :{
						result = mysql_use_result(connection); // 获取结果集
						int num_fields = mysql_num_fields(result);
						// while(row=mysql_fetch_row(result))
						// {
						// 	//mysql_fetch_field(My_db.row)
						// 	for(int i=0;i<num_fields;i++)
						// 	{
						// 		cout<<row[i]<<" ";
						// 	}
						// 	cout<<endl;
						// }
						//cout<<"row00:"<<result->row_count<<endl;
						if(num_fields>0){
							//cout<<"true"<<endl;
							cout<<"1111:"<<num_fields<<endl;
							return true;
						}
						else {
							mysql_free_result(result);
							cout<<"row:"<<num_fields<<endl;
							return false;
							}
		}
		case UPDATE :{
						printf("update sucessfully!\n");
						return true;
		}
	}
}
	// // mysql_query()执行成功返回0，失败返回非0值。与PHP中不一样
	
		
	// 	// mysql_field_count()返回connection查询的列数
	// 	for(int i=0; i < mysql_field_count(connection); ++i)
	// 	{
	// 		// 获取下一行
	// 		row = mysql_fetch_row(result);
	// 		if(row <= 0)
	// 		{
	// 			break;
	// 		}
	// 		// mysql_num_fields()返回结果集中的字段数
	// 		for(int j=0; j < mysql_num_fields(result); ++j)
	// 		{
	// 			cout << row[j] << " ";
	// 		}
	// 		cout << endl;
	// 	}
	// 	// 释放结果集的内存
	// 	mysql_free_result(result);
	// }
	// return true;

  
// int main()  
// {  
//     MyDB db;
// 	char sql[200];
// 	db.initDB("localhost", "root", "4817", "server");
// 	sprintf(sql,"insert into user_info(account,password,address,phone_number) values('%s','%s','%s','%s')","zbl2018","1234","汕头","18826054817");
// 	printf("sql:%s\n",sql);
// 	db.exeSQL(sql);

// 	//db.exeSQL( "INSERT INTO 表名 VALUES ("hyq","M")");  
// 	//db.exeSQL("select * from user_info");  
//     return 0;  
// }  