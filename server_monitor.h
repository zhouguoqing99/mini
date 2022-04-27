#ifndef SERVER_MONITOR_H_INCLUDE
#define SERVER_MONITOR_H_INCLUDE

#include <json/json.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <pthread.h>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "structure.h"
#include <string>
#include <event2/util.h>
#include "work_process.h"
#include <arpa/inet.h>
#include <vector>

class ServerMonitor {
   public:
    ServerMonitor();
    ServerMonitor(int interval, int maxfails, std::string type, int process_num, process* sub_process
                  ,void* shm_address);
    ~ServerMonitor();

    int StartActiveDetect();
    int StartPassiveDetect();
    void StopServerMonitor();
    static int ConnectServer(evutil_socket_t& sockfd, char* ip, int port);
    static int SetServerDown(const char* ip, const int& port);
    static int SetServerUp(const char* ip, const int& port);
    static int LoginServer(const char* ip, const int& port);
    static int LogoutServer(const char* ip, const int& port);
    static int LoadServerList(Json::Value& server_up, Json::Value& server_down);
    static int UpdateServerList(Json::Value& server_up, Json::Value& server_down);

   public:
    static int m_maxfails;
    static int m_interval;
    static std::string m_type;
    static bool m_running;
    static int m_process_num;
    static process* m_sub_process;
    static void* m_shm_address;
};

#endif  // SERVER_MONITOR_H_INCLUDE