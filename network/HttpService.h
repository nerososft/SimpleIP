//
// Created by neroyang on 2017/11/8.
//

#ifndef GP_HW_02_HTTPSERVICE_H
#define GP_HW_02_HTTPSERVICE_H

namespace OpenIP {
    class HttpService {
    private:
        int port;
        bool isRuning = false;

    public:

        void init();
        void child_thread();
        void start();
        void stop();
    };
}


#endif //GP_HW_02_HTTPSERVICE_H
