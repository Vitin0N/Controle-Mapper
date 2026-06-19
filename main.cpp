#include <iostream>
#include <SDL2/SDL.h>
#include "controller/Controller.h"
#include "controller/Controller_Map.h"
#include "mouse/Mouse.h"

// Variaveis globais

// Zona morta do analogico do controle
#define ZONA_MORTA 5000

int main(int argc, char* argv[]) {

    // Tenta inicializar o subsistema de controle do SDL
    if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erro ao inicializar o SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Criando controle
    Controller meuControle;

    // Criando um mouse virtual
    Mouse meuMouse;
    
    // Verifica se há algum conectado
    if(!meuControle.conectar()){
        SDL_Quit();
        return -1;
    }

    // Flags de execução
    bool rodando = true;

    std::cout << "\nLendo o controle 1. Precione START + B para encerrar o programa\n";

    // Define os triggers como não clicados ainda
    bool lt_pressionado = false;
    bool rt_pressionado = false;

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

        // Função de mouse
        int eixoLX = meuControle.getEixos(ControllerMap::LEFT_X);
        int eixoLY = meuControle.getEixos(ControllerMap::LEFT_Y);

        int velocidadeLX = 0;
        int velocidadeLY = 0;

        // Verifica a velocidade de movimento do mouse
        if(abs(eixoLX) > ZONA_MORTA){
            velocidadeLX = (eixoLX / 2000);
        }

        if(abs(eixoLY) > ZONA_MORTA){
            velocidadeLY = (eixoLY / 2000);
        }

        // Caso exista alguma velocidade então o mouse é movido
        if(velocidadeLX != 0 || velocidadeLY != 0){
            meuMouse.mover(velocidadeLX, velocidadeLY);
        }

        // Verifica se os gatilhos forma precionado mais da metade
        bool deveClicarLT = meuControle.getEixos(ControllerMap::LT) > 1600;
        bool deveClicarRT = meuControle.getEixos(ControllerMap::RT) > 1600;

        // Verifica se o LT esta pressionado para executar o clique no botão esquerdo do mouse
        if(deveClicarLT && !lt_pressionado){
            meuMouse.cliqueEsquerdo(true);
            lt_pressionado = true;
        } else if(!deveClicarLT && lt_pressionado){
            meuMouse.cliqueEsquerdo(false);
            lt_pressionado = false;
        }

        // Verifica se o RT esta pressionado para executar o clique no botão direito do mouse
        if(deveClicarRT && !rt_pressionado){
            meuMouse.cliqueDireito(true);
            rt_pressionado = true;
        } else if(!deveClicarRT && rt_pressionado){
            meuMouse.cliqueDireito(false);
            rt_pressionado = false;
        }

        SDL_Delay(50); // Espera 50ms antes de ler uma nova entrada
    }

    // Libera o controle
    meuControle.desconectar();
    // Fecha o SDL corretamente antes de sair
    SDL_Quit();
    return 0;
}