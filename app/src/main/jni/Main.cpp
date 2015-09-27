//
// Created by gabber on 26.09.15.
//

#include "EventLoop.hpp"
#include "DroidBlaster.hpp"

void android_main(android_app* pApplication){
    packt::EventLoop lEventLoop(pApplication);
    dbs::DroidBlaster lDroidBlaster;
    lEventLoop.run(&lDroidBlaster);
}
