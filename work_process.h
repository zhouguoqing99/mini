#ifndef WORK_PROCESS_H_INCLUDE
#define WORK_PROCESS_H_INCLUDE

#include <sched.h>
class process  //工作进程
{
   public:
    process() : m_pid(-1){};

   public:
    pid_t m_pid;
    int m_piped[2];  //主进程与工作进程之间通信的管道
};

#endif  // WORK_PROCESS_H_INCLUDE