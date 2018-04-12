#include"include/ev_tcpServer.h"
#include<iostream>
using namespace std;
int main(){
    //声明一个服务器对象，并初始化数据库链接
    ev_tcpServer Tcp_server("127.0.0.1","root","4817","web");
    //开始指定监听本机指定的端口号
   // MyDB *ev_tcpServer::My_db=new MyDB();
    //ev_tcpServer::server_log("./log/server_log.txt",ios::app);//记录日志，追加的方式 
    cout<<"sysytem time :"<<ev_tcpServer::GetTime()<<endl;
    Tcp_server.start_server(/*"127.0.0.1"*/22222);
    
    return 1;

}