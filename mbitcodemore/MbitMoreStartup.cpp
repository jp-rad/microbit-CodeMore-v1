/*
MIT License

Copyright (c) 2020 jp-rad
Copyright (c) 2020 Koji Yokokawa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MicroBit.h"
#include "MbitMoreStartup.h"
#include "MbitMoreService.h"

MicroBit uBit;

namespace MbitMore {
    MbitMoreService* _pService = NULL;

    void update() {
        while (NULL != _pService) {
            _pService->update();
            fiber_sleep(UPDATE_PERIOD);
        }
    }

    void notifyScratch() {
        while (NULL != _pService) {
            // notyfy data to Scratch
            _pService->notify();
            fiber_sleep(NOTIFY_PERIOD);
        }
    }

    void startMbitMoreService(p_displayTextCommand displayTextCommand) {
        if (NULL != _pService) return;

        // Initialise the micro:bit runtime.
        uBit.init();
        
        // Setup
        _pService = new MbitMoreService(uBit);
        if (displayTextCommand!=NULL)
        {
            _pService->assigneCallbackDisplayTextCommand(displayTextCommand);
        }
        create_fiber(update);
        create_fiber(notifyScratch);
        
        // If main exits, there may still be other fibers running or registered event handlers etc.
        // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
        // sit in the idle task forever, in a power efficient sleep.
        release_fiber();
    }

}
