//
// Created by neroyang on 2017/10/18.
//

#include <iostream>
#include <sstream>
#include "System.h"

namespace OpenIP {
    System::System() {
        int no_os_flag = 1;

#ifdef linux

        no_os_flag=0;
        sysarch = SYSARCH::LINUX;

#endif

#ifdef _UNIX

        no_os_flag=0;

        sysarch = SYSARCH::UNIX;
#endif

#ifdef __WINDOWS_

        no_os_flag=0;

        sysarch = SYSARCH::WIN;

#endif

#ifdef _WIN32

        no_os_flag=0;

        sysarch = SYSARCH::WIN32;

#endif

        if (1 == no_os_flag) {

            sysarch = SYSARCH::OTHER;

        }
    }


    const char *System::get_items(const char *buffer, unsigned int item) {

        const char *p = buffer;

        int len = strlen(buffer);
        int count = 0;

        for (int i = 0; i < len; i++) {
            if (' ' == *p) {
                count++;
                if (count == item - 1) {
                    p++;
                    break;
                }
            }
            p++;
        }

        return p;
    }

    unsigned long System::get_cpu_total_occupy() {

        FILE *fd;
        char buff[1024] = {0};
        Total_Cpu_Occupy_t t;

        fd = fopen("/proc/stat", "r");
        if (nullptr == fd) {
            return 0;
        }

        fgets(buff, sizeof(buff), fd);
        char name[64] = {0};
        sscanf(buff, "%s %ld %ld %ld %ld", name, &t.user, &t.nice, &t.system, &t.idle);
        fclose(fd);

        return (t.user + t.nice + t.system + t.idle);
    }

    unsigned long System::get_cpu_proc_occupy(unsigned int pid) {
        char file_name[64] = {0};
        Proc_Cpu_Occupy_t t;
        FILE *fd;
        char line_buff[1024] = {0};
        sprintf(file_name, "/proc/%d/stat", pid);

        fd = fopen(file_name, "r");
        if (nullptr == fd) {
            return 0;
        }

        fgets(line_buff, sizeof(line_buff), fd);

        sscanf(line_buff, "%u", &t.pid);
        const char *q = get_items(line_buff, PROCESS_ITEM);
        sscanf(q, "%ld %ld %ld %ld", &t.utime, &t.stime, &t.cutime, &t.cstime);
        fclose(fd);

        return (t.utime + t.stime + t.cutime + t.cstime);
    }

    const char *System::get_proc_cpu(unsigned int pid) {
        if (sysarch == SYSARCH::LINUX) {
            unsigned long totalcputime1, totalcputime2;
            unsigned long procputime1, procputime2;

            totalcputime1 = get_cpu_total_occupy();
            procputime1 = get_cpu_proc_occupy(pid);

            usleep(200000);

            totalcputime2 = get_cpu_total_occupy();
            procputime2 = get_cpu_proc_occupy(pid);

            float pcpu = 0.0;
            if (0 != totalcputime2 - totalcputime1) {
                pcpu = 100.0 * (procputime2 - procputime1) / (totalcputime2 - totalcputime1);
            }

            std::ostringstream buffer_mem;
            buffer_mem << pcpu;
            std::string str_mem = buffer_mem.str();
            const char *ff_mem = str_mem.c_str();
            return ff_mem;
        } else {
            return ErrorMsg(sysarch);
        }

    }

    const char *System::get_proc_mem(unsigned int pid) {
        if (sysarch == SYSARCH::LINUX) {
            char file_name[64] = {0};
            FILE *fd;
            char line_buff[512] = {0};
            sprintf(file_name, "/proc/%d/status", pid);

            fd = fopen(file_name, "r");
            if (nullptr == fd) {
                return 0;
            }

            char name[64];
            int vmrss;
            for (int i = 0; i < VMRSS_LINE - 1; i++) {
                fgets(line_buff, sizeof(line_buff), fd);
            }

            fgets(line_buff, sizeof(line_buff), fd);
            sscanf(line_buff, "%s %d", name, &vmrss);
            fclose(fd);

            std::ostringstream buffer_mem;
            buffer_mem << vmrss;
            std::string str_mem = buffer_mem.str();
            const char *ff_mem = str_mem.c_str();
            return ff_mem;
        } else {
            return ErrorMsg(sysarch);
        }
    }

    unsigned int System::get_proc_virtualmem(unsigned int pid) {
        char file_name[64] = {0};
        FILE *fd;
        char line_buff[512] = {0};
        sprintf(file_name, "/proc/%d/status", pid);

        fd = fopen(file_name, "r");
        if (nullptr == fd) {
            return 0;
        }

        char name[64];
        int vmsize;
        for (int i = 0; i < VMSIZE_LINE - 1; i++) {
            fgets(line_buff, sizeof(line_buff), fd);
        }

        fgets(line_buff, sizeof(line_buff), fd);
        sscanf(line_buff, "%s %d", name, &vmsize);
        fclose(fd);

        return vmsize;
    }

    int System::get_pid(const char *process_name, const char *user) {
        if (user == nullptr) {
            user = getlogin();
        }

        char cmd[512];
        if (user) {
            sprintf(cmd, "pgrep %s -u %s", process_name, user);
        }

        FILE *pstr = popen(cmd, "r");

        if (pstr == nullptr) {
            return 0;
        }

        char buff[512];
        ::memset(buff, 0, sizeof(buff));
        if (NULL == fgets(buff, 512, pstr)) {
            return 0;
        }

        return atoi(buff);
    }
    const char* System::ErrorMsg(SYSARCH arch){

        switch (sysarch){
            case SYSARCH::WIN:
                return "Unavailable on Windows";
                break;
            case SYSARCH::WIN32:
                return "Unavailable on WIN32";
                break;
            case SYSARCH::LINUX:
                return "Unavailable on Linux";
                break;
            case SYSARCH::UNIX:
                return "Unavailable on Unix";
                break;
            case SYSARCH::OTHER:
                return "Unavailable on Unknown System";
                break;

        }
    }
}
