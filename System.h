//
// Created by neroyang on 2017/10/18.
//

#ifndef GP_HW_02_SYSTEM_H
#define GP_HW_02_SYSTEM_H

#include <cstring>
#include <cstdio>
#include <zconf.h>
#include <cstdlib>
#define VMRSS_LINE 17
#define VMSIZE_LINE 13
#define PROCESS_ITEM 14

namespace OpenIP {

    typedef struct {
        unsigned long user;
        unsigned long nice;
        unsigned long system;
        unsigned long idle;
    }Total_Cpu_Occupy_t;

    typedef struct {
        unsigned int pid;
        unsigned long utime;
        unsigned long stime;
        unsigned long cutime;
        unsigned long cstime;
    }Proc_Cpu_Occupy_t;

    enum SYSARCH{
        WIN,WIN32,LINUX,UNIX,OTHER
    };

    class System {
    private:
        SYSARCH  sysarch;
        float cpu;
        int processor_num;
        float mem;

    public:
        System();

        //获取第N项开始的指针
        const char* get_items(const char*buffer ,unsigned int item);


        //获取总的CPU时间
        unsigned long get_cpu_total_occupy();


        //获取进程的CPU时间
        unsigned long get_cpu_proc_occupy(unsigned int pid);


        //获取CPU占用率
        const char* get_proc_cpu(unsigned int pid);

        //获取进程占用内存
        const char* get_proc_mem(unsigned int pid);


        //获取进程占用虚拟内存
        unsigned int get_proc_virtualmem(unsigned int pid);


        //进程本身
        int get_pid(const char* process_name, const char* user = nullptr);

        const char* ErrorMsg(SYSARCH arch);
    };
}


#endif //GP_HW_02_SYSTEM_H
