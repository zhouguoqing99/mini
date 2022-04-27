#ifndef STRUTURE_H_INCLUDE
#define STRUTURE_H_INCLUDE

#define M_MSG_KEY 1627455490
#define SQL_LEN 1024
#define BUF_LEN 1024
#define MYSQL_CONFIG_PATH "./mysql.conf"
#define HEI_MING_DAN_PATH "./heimingdan.tmp"
#define IP_SIZE 20
#define HEI_MING_DAN_BUFFER_SIZE 20 * 1000

#include <unistd.h>
#include <string>
#include <string.h>
#include <event2/bufferevent.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

struct address
{
    int port;
    char ip[20];
    char token[10];
    address()
    {
        bzero(ip, sizeof(ip));
        bzero(token, sizeof(token));
    }
};

struct message
{
    long msg_type;
    int port;
    char ip[20];
    int process_id;
    message() { bzero(ip, sizeof(ip)); }
};

//消息类型
enum OPTION_TYPE_E
{
    EN_LOGIN = 1,    //登录
    EN_REGISTER = 2, //注册
    EN_EXIT = 3,     //退出
    EN_INQUIRY = 4,  //查询
    EN_SCRAMBLE = 5, //抢票
    EN_CREATE = 6    //新建抢票任务
};

struct Head
{
    //OPTION_TYPE_E type;
    int length;
};

struct client_information
{
    bufferevent *bev;
    int count = 0;
    std::string ip;
    bool close_flag = false;
};

struct Hhei_Ming_Dan
{
    pthread_rwlock_t m_lock;
    int count;
    char buffer[HEI_MING_DAN_BUFFER_SIZE];
    bool accept_flag;
    pthread_mutex_t accpet_mutex;
    void init_shm()
    {
        count = 0;
        accept_flag = true;
        //初始化黑名单锁
        pthread_rwlockattr_t attr;
        pthread_rwlockattr_init(&attr);
        pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);            //进程共享
        pthread_rwlock_init(&m_lock, &attr);     //初始化读写锁
        bzero(buffer, HEI_MING_DAN_BUFFER_SIZE); //初始化黑名单

        //初始化accept锁
        pthread_mutexattr_t mutex_attr;
        pthread_mutexattr_init(&mutex_attr);
        pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED); //进程共享
        pthread_mutex_init(&accpet_mutex, &mutex_attr);
    }
};

#endif // STRUTURE_H-INCLUDE