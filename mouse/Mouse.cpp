#include "Mouse.h"

// Caso o sistema seja windows inclui a biblioteca dele
#ifdef _WIN32
    #include <windows.h>
#endif

void Mouse::mover(int dx, int dy){
    #ifdef _WIN32
        // Cria uma estrutura de entrada vazia
        INPUT input = { 0 };

        // Define como um input de mouse
        input.type = INPUT_MOUSE;

        // Define o quanto o mouse vai mover
        input.mi.dx = dx;
        input.mi.dy = dy;

        // Avisa para o windows movimentar o mouse
        input.mi.dwFlags = MOUSEEVENTF_MOVE;

        // Dispara a injeção do evento
        SendInput(1, &input, sizeof(INPUT));

    #endif
}

void Mouse::cliqueEsquerdo(bool clicado){
    #ifdef _WIN32
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;

        if(clicado){
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        } else {
            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        }

        SendInput(1, &input, sizeof(INPUT));
    #endif
}


void Mouse::cliqueDireito(bool clicado){
    #ifdef _WIN32
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;

        if(clicado){
            input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        } else {
            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        }

        SendInput(1, &input, sizeof(INPUT));
    #endif
}