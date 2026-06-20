#include "Keyboard.h"
#include "AtalhoTeclasMapper.h"

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

void Keyboard::apertaAtalho(const Atalho& atalho){
    #ifdef _WIN32
        // Pressiona todas as teclas
        for(int i = 0; i < atalho.tamanho; i++){
            apertaTecla(atalho.teclas[i], true);
        }

        // Depois solta todas as teclas
        for(int i = atalho.tamanho - 1; i >= 0; i--){
            apertaTecla(atalho.teclas[i], false);
        }
    #endif
}

void Keyboard::apertaAltTab(){
    #ifdef _WIN32
        // Pressiona ALT + TAB
        apertaTecla(VK_MENU, true);
        apertaTecla(VK_TAB, true);

        // Libera apenas o TAB
        apertaTecla(VK_TAB, false);
    #endif
}

void Keyboard::soltaAltTab(){
    #ifdef _WIN32
        // Solta o ALT 
        apertaTecla(VK_MENU, false);
    #endif
}