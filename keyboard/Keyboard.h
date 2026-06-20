#pragma once
#include "AtalhoTeclasMapper.h"

class Keyboard{
    public:
        // vk = Virtual Key (que é o código usado pelo o Windows)
        void apertaTecla(int vkCode, bool precionada);
        void apertaAtalho(const Atalho& atalho);
        
        // ===================
        // Funções Especificas
        // ===================

        //Alt + Tab
        void apertaAltTab();
        void soltaAltTab();

};