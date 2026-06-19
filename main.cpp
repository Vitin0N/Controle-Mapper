#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    // Tenta inicializar o subsistema de controle do SDL
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
        std::cerr << "Erro ao inicializar o SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Flags de execução
    bool rodando = true;
    SDL_Event evento;

    // Ponteiro vazio para o controle
    SDL_GameController* controle = nullptr;

    // Verifica quantos controles estão conectados
    for(int i = 0; i < SDL_NumJoysticks(); i++){ // Passa por todos os dispositivos conectados
        // Verifica se o dispositivo é um controle 
        if(SDL_IsGameController(i)){
            // Se é um controle então o controle 'mestre' será o primeiro
            controle = SDL_GameControllerOpen(i);
            std::cout << "Controle encontrado " << SDL_GameControllerName(controle);
            break;
        }
    }

    if(controle){
        SDL_GameControllerClose(controle);
    }

    // Fecha o SDL corretamente antes de sair
    SDL_Quit();
    return 0;
}