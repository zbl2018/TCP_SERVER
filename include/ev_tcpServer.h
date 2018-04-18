#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ev.h>
#include<fstream>
#include <string>
#include<time.h>
#include "MyDB.h"
#include"json/json.h"
#include"control_car.h"
#include"MyJson.h"
#define MAX_BUF_LEN  1024
#define HEAD_LEN  6 //每个报文头部长度
#define PORT_EXIST 1000
//#define JSON_NULL "_NULL"
#define byte unsigned char
/*暂时默认ws_server的TCP连接id是6*/
#define WS_TCP_CON_ID 6
#define RES_UNEXIST 2001
// #define RES_FAIL 2002
// #define RES_SUCC 2003
using namespace std;

typedef struct watcher_data{
        int client_port;
        char data_buf[200];
        bool first_flag = false;
};

class ev_tcpServer{
    public:
            static ofstream server_log;
            ev_tcpServer(string db_ip,string db_user_name,string db_pwd,string db_name);  
            ~ev_tcpServer();
            int start_server(int port);  
            int create_socket(int port);
            //以下是io回调函数 
            static void accept_socket_cb(struct ev_loop *loop,ev_io *w, int revents);
            static void recv_socket_cb_hardware(struct ev_loop *loop,ev_io *w, int revents);
            static void recv_socket_cb_net(struct ev_loop *loop,ev_io *w, int revents);
            static void recv_socket_cb_local(struct ev_loop *loop,ev_io *w, int revents);
            static void write_socket_cb(struct ev_loop *loop,ev_io *w, int revents);
            //used in cb function            
            static int deal_recv_info_hardware(ev_io *w,string data_buff);
            static int deal_recv_info_net(ev_io *w,string data_buff,byte head[]);
            int deal_send_info(ev_io *w,string data_buff);
            //used in deal function
            //static int pre


            //tool
            static byte* intToBytes(int value,int byte_len);
            //获得当前小车对应的web端ws连接id
            static int GetWs_connectID(int this_car_tcpId);
            static int bytesToInt(byte* des, int byte_len);
            static string GetTime();
            
    private:
            static MyDB *My_db;
            static car *CarObject;
            static MyJson *my_json;

};
