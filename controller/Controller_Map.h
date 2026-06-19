#ifndef CONTROLLER_MAP_H
#define CONTROLLER_MAP_H

#include <SDL2/SDL.h>

namespace ControllerMap
{
    // BOTÕES (UNIVERSAIS)
    constexpr SDL_GameControllerButton BTN_A = SDL_CONTROLLER_BUTTON_A;
    constexpr SDL_GameControllerButton BTN_B = SDL_CONTROLLER_BUTTON_B;
    constexpr SDL_GameControllerButton BTN_X = SDL_CONTROLLER_BUTTON_X;
    constexpr SDL_GameControllerButton BTN_Y = SDL_CONTROLLER_BUTTON_Y;

    constexpr SDL_GameControllerButton BACK = SDL_CONTROLLER_BUTTON_BACK;
    constexpr SDL_GameControllerButton GUIDE = SDL_CONTROLLER_BUTTON_GUIDE;
    constexpr SDL_GameControllerButton START = SDL_CONTROLLER_BUTTON_START;

    constexpr SDL_GameControllerButton LEFT_STICK = SDL_CONTROLLER_BUTTON_LEFTSTICK;
    constexpr SDL_GameControllerButton RIGHT_STICK = SDL_CONTROLLER_BUTTON_RIGHTSTICK;

    constexpr SDL_GameControllerButton LB = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
    constexpr SDL_GameControllerAxis LT = SDL_CONTROLLER_AXIS_TRIGGERLEFT;

    constexpr SDL_GameControllerButton RB = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
    constexpr SDL_GameControllerAxis RT = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;

    // D-PAD
    constexpr SDL_GameControllerButton DPAD_UP = SDL_CONTROLLER_BUTTON_DPAD_UP;
    constexpr SDL_GameControllerButton DPAD_DOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
    constexpr SDL_GameControllerButton DPAD_LEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
    constexpr SDL_GameControllerButton DPAD_RIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;

    // Extras modernos
    constexpr SDL_GameControllerButton MISC1 = SDL_CONTROLLER_BUTTON_MISC1;

    constexpr SDL_GameControllerButton PADDLE1 = SDL_CONTROLLER_BUTTON_PADDLE1;
    constexpr SDL_GameControllerButton PADDLE2 = SDL_CONTROLLER_BUTTON_PADDLE2;
    constexpr SDL_GameControllerButton PADDLE3 = SDL_CONTROLLER_BUTTON_PADDLE3;
    constexpr SDL_GameControllerButton PADDLE4 = SDL_CONTROLLER_BUTTON_PADDLE4;

    constexpr SDL_GameControllerButton TOUCHPAD = SDL_CONTROLLER_BUTTON_TOUCHPAD;

    // EIXOS ANALÓGICOS
    constexpr SDL_GameControllerAxis LEFT_X = SDL_CONTROLLER_AXIS_LEFTX;
    constexpr SDL_GameControllerAxis LEFT_Y = SDL_CONTROLLER_AXIS_LEFTY;

    constexpr SDL_GameControllerAxis TRIGGER_LEFT = SDL_CONTROLLER_AXIS_TRIGGERLEFT;
    constexpr SDL_GameControllerAxis TRIGGER_RIGHT = SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
    constexpr SDL_GameControllerAxis RIGHT_X = SDL_CONTROLLER_AXIS_RIGHTX;
    constexpr SDL_GameControllerAxis RIGHT_Y = SDL_CONTROLLER_AXIS_RIGHTY;


    // FUNÇÃO AUXILIAR: Retorna o nome do botão precionado
    inline const char* ButtonName(SDL_GameControllerButton btn)
    {
        switch (btn)
        {
            case SDL_CONTROLLER_BUTTON_A: return "A";
            case SDL_CONTROLLER_BUTTON_B: return "B";
            case SDL_CONTROLLER_BUTTON_X: return "X";
            case SDL_CONTROLLER_BUTTON_Y: return "Y";
            case SDL_CONTROLLER_BUTTON_BACK: return "BACK";
            case SDL_CONTROLLER_BUTTON_GUIDE: return "GUIDE";
            case SDL_CONTROLLER_BUTTON_START: return "START";
            case SDL_CONTROLLER_BUTTON_LEFTSTICK: return "LEFT_STICK";
            case SDL_CONTROLLER_BUTTON_RIGHTSTICK: return "RIGHT_STICK";
            case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: return "LB";
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: return "RB";
            case SDL_CONTROLLER_BUTTON_DPAD_UP: return "DPAD_UP";
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN: return "DPAD_DOWN";
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT: return "DPAD_LEFT";
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: return "DPAD_RIGHT";
            case SDL_CONTROLLER_BUTTON_TOUCHPAD: return "TOUCHPAD";
            default: return "UNKNOWN";
        }
    }

}

#endif