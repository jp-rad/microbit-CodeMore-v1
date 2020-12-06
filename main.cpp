/*
MIT License

Copyright (c) 2020 jp-rad

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
#include "MbitCodeMore.h"

// 
// Microbit uBit
// https://lancaster-university.github.io/microbit-docs/
// 
// ManagedString
// https://lancaster-university.github.io/microbit-docs/data-types/string/
// 
// uBit.display
// https://lancaster-university.github.io/microbit-docs/ubit/display/
// 

const ManagedString MY_CMD("@cmd");

// This handler, onDisplayTextCommmand is called, If the display text starts with '@'.
int onDisplayTextCommand(MicroBit &uBit, ManagedString &text)
{
    if (text==MY_CMD)
    {
        uBit.display.stopAnimation();
        // scroll your smiley across the screen, without waiting for it to finish...
        MicroBitImage smiley("0,255,0,255, 0\n0,255,0,255,0\n0,0,0,0,0\n255,0,0,0,255\n0,255,255,255,0\n");
        uBit.display.scrollAsync(smiley);
        // Handled, return zero.
        return 0;
    }
    ManagedString err("Err:");
    text = err + text;
    // Unhandled, retrun not zero.
    return 1;
}

int main()
{
    // Start Service
    //MbitMore::startMbitMoreService();
    MbitMore::startMbitMoreService(onDisplayTextCommand);
}

