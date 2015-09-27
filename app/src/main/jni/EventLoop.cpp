#include "EventLoop.hpp"
#include "Log.hpp"

namespace packt {
    EventLoop::EventLoop(android_app * mApplication) :
            mEnabled(false), mQuit(false),
            mApplication(mApplication),
            mEventHandler(NULL){
        mApplication->onAppCmd = activityCallback;
        mApplication->userData = this;
    }

    void EventLoop::run(EventHandler* pEventHandler) {
        int32_t lResult;
        int32_t lEvents;

        app_dummy();
        mEventHandler = pEventHandler;
        packt::Log::info("Starting event loop");
        while(true){
            struct android_poll_source * lSource;
            while ((lResult = ALooper_pollAll(mEnabled ? 0 : -1, NULL, &lEvents, (void**) &lSource)) >=0 ){
                if(lSource != NULL){
                    packt::Log::info("Processing an event");
                    lSource->process(mApplication, lSource);
                }
                if(mApplication->destroyRequested){
                    packt::Log::info("Exiting event loop");
                    return;
                }
            }
            if((mEnabled) && (!mQuit)){
                packt::Log::info("Step");

                if(mEventHandler->onStep() != STATUS_OK){
                    mQuit = true;
                    ANativeActivity_finish(mApplication->activity);
                }
            }
        }
    }

    void EventLoop::activate(){
        if((!mEnabled) && (mApplication->window != NULL)){
            mQuit = false; mEnabled = true;
            if(mEventHandler->onActivate() != STATUS_OK){
                mQuit = true;
                ANativeActivity_finish(mApplication->activity);
            }
        }
    }

    void EventLoop::deactivate(){
        if(mEnabled){
            mEventHandler->onDeactivate();
            mEnabled = false;
        }
    }

    void EventLoop::processActivityEvent(int32_t pCommand){
        switch(pCommand){
            case APP_CMD_CONFIG_CHANGED:
                mEventHandler->onConfigurationChanged();
                break;
            case APP_CMD_INIT_WINDOW:
                mEventHandler->onCreateWindow();
                break;
            case APP_CMD_DESTROY:
                mEventHandler->onDestroy();
                break;
            case APP_CMD_GAINED_FOCUS:
                activate();
                mEventHandler->onGainFocus();
                break;
            case APP_CMD_LOST_FOCUS:
                mEventHandler->onLostFocus();
                deactivate();
                break;
            case APP_CMD_LOW_MEMORY:
                mEventHandler->onLowMemory();
                break;
            case APP_CMD_PAUSE:
                mEventHandler->onPause();
                deactivate();
                break;
            case APP_CMD_RESUME:
                mEventHandler->onResume();
                break;
            case APP_CMD_SAVE_STATE:
                mEventHandler->onSaveState(&mApplication->savedState, &mApplication->savedStateSize);
                break;
            case APP_CMD_START:
                mEventHandler->onStart();
                break;
            case APP_CMD_STOP:
                mEventHandler->onStop();
                break;
            case APP_CMD_TERM_WINDOW:
                mEventHandler->onDestroyWindow();
                deactivate();
                break;
            default:
                break;
        }
    }

    void EventLoop::activityCallback(android_app* pApplication, int32_t pCommand){
        EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
        lEventLoop.processActivityEvent(pCommand);
    }
}