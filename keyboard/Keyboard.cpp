#include "Keyboard.h"

#ifdef _WIN32
    #include <windows.h>
#endif

void Keyboard::apertaTecla(int vkCode, bool pressionada){
    #ifdef _WIN32
        INPUT input = { 0 };
        input.type = INPUT_KEYBOARD;

        // Define a tecla que vai ser clicada
        input.ki.wVk = vkCode;

        if(!pressionada){
            input.ki.dwFlags = KEYEVENTF_KEYUP;
        }

        SendInput(1, &input, sizeof(INPUT));
    #endif
}