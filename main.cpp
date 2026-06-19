#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    // Força a leitura do controle mesmo sem jogos
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1"); 

    // Tenta inicializar o subsistema de controle do SDL
    if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao inicializar o SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Flags de execução
    bool rodando = true;

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

    std::cout << "\nLendo o controle 1. Precione 'START' + 'X' para encerrar o programa\n";

    // 
    while(rodando){
        // Atualiza o estado do controle atual
        SDL_PumpEvents();

        // Lê o botão 'A' do controle e printa
        if (SDL_GameControllerGetButton(controle, SDL_CONTROLLER_BUTTON_A)){
            std::cout << "Botao A apertado\n";
        }

        // Caso o botão 'START' + 'X' for apertado então o while se fecha
        if(SDL_GameControllerGetButton(controle, SDL_CONTROLLER_BUTTON_START) && 
            SDL_GameControllerGetButton(controle, SDL_CONTROLLER_BUTTON_X)){
            std::cout << "Encerrando programa\n";
            rodando = false;
        }

        int eixoX = SDL_GameControllerGetAxis(controle, SDL_CONTROLLER_AXIS_LEFTX);
        
        if (abs(eixoX) > 5000) { // 8000 é a zona morta (estado parado) então se passar disso ele printa
            std::cout << "Analogico preciosando " << eixoX << std::endl;
        }
        

        SDL_Delay(50); // Espera 50ms antes de ler uma nova entrada
    }

    // Libera o controle
    SDL_GameControllerClose(controle);
    // Fecha o SDL corretamente antes de sair
    SDL_Quit();
    return 0;
}