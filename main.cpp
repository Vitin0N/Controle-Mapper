#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    // Tenta inicializar o subsistema de controle do SDL
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) {
        std::cerr << "Erro ao inicializar o SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "SDL2 importado e inicializado com sucesso!" << std::endl;

    // Fecha o SDL corretamente antes de sair
    SDL_Quit();
    return 0;
}