#include "Controller.h"
#include <iostream>

// Construtor: inicializa o ponteiro como nulo
Controller::Controller(){
    controle = nullptr;
}

bool Controller::conectar(){
    // Passa por todos os aparelhos conectado
    for(int i = 0; i < SDL_NumJoysticks(); i++){
        // Caso encontre um que seja o controle o primeiro será o que terá
        // poder de controlar as coisas
        if(SDL_IsGameController(i)){
            controle = SDL_GameControllerOpen(i);
            if(controle){
                std::cout << "Controle encontrado! " << SDL_GameControllerName(controle);
                return true;
            }
        }
    }
    // Não foi encontrado nenhum controle
    std::cout << "Controle nao encontrado\n";
    return false;
}

void Controller::atualizarEventos(){
    // Razoavelmente perigoso, mas funcionou melhor que o SDL_PollEvent
    SDL_PumpEvents();
}

bool Controller::isBotaoPressionado(SDL_GameControllerButton botao){
    if (!controle) return false;

    return SDL_GameControllerGetButton(controle, botao) == 1;
}

int Controller::getEixos(SDL_GameControllerAxis eixo){
    if(!controle) return 0;

    return SDL_GameControllerGetAxis(controle, eixo);
}

void Controller::desconectar(){
    if(controle){
        SDL_GameControllerClose(controle);
        controle = nullptr;
        std::cout << "Controle desconectado!\n";
    }
}