#ifndef _PACKT_EVENTLOOP_HPP_
#define _PACKT_EVENTLOOP_HPP_

#include "Types.hpp"
#include "native_app_glue/android_native_app_glue.h"

namespace packt {
    class EventLoop {
    public:
        EventLoop(android_app* application);

        void run();

    private:
        android_app* mApplication;
    };
}

#endif