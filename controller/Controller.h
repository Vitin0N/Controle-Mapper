#pragma once
#include <SDL2/SDL.h>

class Controller {
    private:
        SDL_GameController *controle;

    public:
        // CONTRUTOR DO CONTROLLER
        Controller();

        // Funçõs publicas
        bool conectar();
        void atualizarEventos();

        // Funções especificas
        bool isBotaoPressionado(SDL_GameControllerButton botao);
        int getEixos(SDL_GameControllerAxis eixo);

        // Função de limpeza
        void desconectar();
};  