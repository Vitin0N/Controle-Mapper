#include <iostream>
#include <SDL2/SDL.h>
#include "controller/Controller.h"
#include "controller/Controller_Map.h"

int main(int argc, char* argv[]) {

    // Tenta inicializar o subsistema de controle do SDL
    if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao inicializar o SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Criando controle
    Controller meuControle;
    
    // Verifica se há algum conectado
    if(!meuControle.conectar()){
        SDL_Quit();
        return -1;
    }

    // Flags de execução
    bool rodando = true;

    std::cout << "\nLendo o controle 1. Precione START + B para encerrar o programa\n";

    // Roda até o usuário pedir para parar
    while(rodando){
        // Recebe os eventos de entrada dos dispositivos conectados
        meuControle.atualizarEventos();

        // START + B programa encerra
        if(meuControle.isBotaoPressionado(ControllerMap::START) &&
            meuControle.isBotaoPressionado(ControllerMap::BTN_B)
        ) {
            rodando = false;
        }



        SDL_Delay(50); // Espera 50ms antes de ler uma nova entrada
    }

    // Libera o controle
    meuControle.desconectar();
    // Fecha o SDL corretamente antes de sair
    SDL_Quit();
    return 0;
}