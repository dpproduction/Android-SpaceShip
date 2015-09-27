#ifndef _PACKT_DROIDBLASTER_HPP_
#define _PACKT_DROIDBLASTER_HPP_

#include "EventHandler.hpp"
#include "Types.hpp"

namespace dbs{
    class DroidBlaster : public packt::EventHandler{
        public:
            DroidBlaster();
            virtual ~DroidBlaster();

        protected:
            status onActivate();
            void onDeactivate();
            status onStep();

            void onStart();
            void onResume();
            void onPause();
            void onStop();
            void onDestroy();

            void onSaveState(void** pData, size_t * pSize);
            void onConfigurationChanged();
            void onLowMemory();

            void onCreateWindow();
            void onDestroyWindow();
            void onGainFocus();
            void onLostFocus();

    };
}

#endif