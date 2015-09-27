#ifndef _PACKT_EVENTLOOP_HPP_
#define _PACKT_EVENTLOOP_HPP_

#include "EventHandler.hpp"
#include "Types.hpp"
#include "native_app_glue/android_native_app_glue.h"

namespace packt {
    class EventLoop {
    public:
        EventLoop(android_app* application);

        void run(EventHandler* eventHandler);

    protected:
        void activate();
        void deactivate();

        void processActivityEvent(int32_t pCommand);
    private :
        static void activityCallback(android_app* pApplication, int32_t pCommand);
    private:
        bool mEnabled; bool mQuit;
        EventHandler* mEventHandler;
        android_app* mApplication;
    };
}

#endif