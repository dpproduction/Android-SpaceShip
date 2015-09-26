#include "EventLoop.hpp"
#include "Log.hpp"

namespace packt {
    EventLoop::EventLoop(android_app * mApplication) :
            mApplication(mApplication)
    {}

    void EventLoop::run() {
        int32_t lResult;
        int32_t lEvents;


        app_dummy();

        packt::Log::info("Starting event loop");
        while(true){
            struct android_poll_source * lSource;
            while ((lResult = ALooper_pollAll(-1, NULL, &lEvents, (void**) &lSource)) >=0 ){
                if(lSource != NULL){
                    packt::Log::info("Processing an event");
                    lSource->process(mApplication, lSource);
                }
                if(mApplication->destroyRequested){
                    packt::Log::info("Exiting event loop");
                    return;
                }
            }
        }
    }
}