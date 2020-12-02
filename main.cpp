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

MicroBit uBit;

#include "MbitMoreService.h"

#define UPDATE_PERIOD 11
#define NOTIFY_PERIOD 101

enum SharedDataIndex {
    //% block="data0"
    DATA0 = 0,
    //% block="data1"
    DATA1 = 1,
    //% block="data2"
    DATA2 = 2,
    //% block="data3"
    DATA3 = 3,
};

//% color=#FF9900 weight=95 icon="\uf1b0"
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

    /**
    * Starts a Scratch extension service.
    */
    //%
    void startMbitMoreService() {
        if (NULL != _pService) return;

        _pService = new MbitMoreService(uBit);
        create_fiber(update);
        create_fiber(notifyScratch);
    }

    /**
    * Set shared data value.
    */
    //%
    void setMbitMoreSharedData(SharedDataIndex index, int value) {
        if (NULL == _pService) return;

        _pService->setSharedData((int)index, value);
    }

    /**
     * Get shared data value. 
     */
    //%
    int getMbitMoreSharedData(SharedDataIndex index) {
        if (NULL == _pService) return 0;

        return _pService->getSharedData((int)index);
    }    
}

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    
    // Insert your code here!
    MbitMore::startMbitMoreService();

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();
}

