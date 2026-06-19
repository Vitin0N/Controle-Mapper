#include <iostream>
#include <SDL2/SDL.h>
#include "controller/Controller.h"
#include "controller/Controller_Map.h"
#include "mouse/Mouse.h"
#include "keyboard/Keyboard.h"


// Importa o windows.h caso estejamos em sistemas windows
#ifdef _WIN32
    #include <windows.h>
#endif

// Variaveis globais

// Zona morta do analogico do controle
#define ZONA_MORTA 5000
#define VELOCIDADE_SCROLL 350

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

    // Criando um teclado virtual
    Keyboard meuTeclado;
    
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

    // Define se botões padrão estão apertados
    bool botao_UP_apertado = false;
    bool botao_DOWN_apertado = false;
    bool botao_LEFT_apertado = false;
    bool botao_RIGHT_apertado = false;

    // Roda até o usuário pedir para parar
    while(rodando){

        SDL_Event lixo;
        while(SDL_PollEvent(&lixo)){
            // Tirar os itens antigos da fila para não travar
        }

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

        int eixoRX = meuControle.getEixos(ControllerMap::RIGHT_X);
        int eixoRY = meuControle.getEixos(ControllerMap::RIGHT_Y);

        int scrollX = 0;
        int scrollY = 0;

        if(abs(eixoRY) > ZONA_MORTA){
            scrollY = (eixoRY / VELOCIDADE_SCROLL) * -1; // Deixa invertido
        }

        if(abs(eixoRX) > ZONA_MORTA){
            scrollY = (eixoRX / VELOCIDADE_SCROLL);
        }

        if(scrollX != 0 || scrollY != 0){
            meuMouse.scroll(scrollX, scrollY);
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

        // Funções de teclado
        bool botaoUP = meuControle.isBotaoPressionado(ControllerMap::DPAD_UP);
        bool botaoDOWN = meuControle.isBotaoPressionado(ControllerMap::DPAD_DOWN);
        bool botaoLEFT = meuControle.isBotaoPressionado(ControllerMap::DPAD_LEFT);
        bool botaoRIGHT = meuControle.isBotaoPressionado(ControllerMap::DPAD_RIGHT);

        // Botão UP pressionada pela setinha do controle
        if(botaoUP){
            meuTeclado.apertaTecla(VK_UP, true);
        } else {
            meuTeclado.apertaTecla(VK_UP, false);
        }

        // Botão DOWN pressionada pela setinha do controle
        if(botaoDOWN){
            meuTeclado.apertaTecla(VK_DOWN, true);
        } else {
            meuTeclado.apertaTecla(VK_DOWN, false);
        }

        // Botão LEFT pressionada pela setinha do controle
        if(botaoLEFT){
            meuTeclado.apertaTecla(VK_LEFT, true);
        } else {
            meuTeclado.apertaTecla(VK_LEFT, false);
        }

        // Botão RIGHT pressionada pela setinha do controle
        if(botaoRIGHT){
            meuTeclado.apertaTecla(VK_RIGHT, true);
        } else {
            meuTeclado.apertaTecla(VK_RIGHT, false);
        }

        SDL_Delay(50); // Espera 50ms antes de ler uma nova entrada
    }

    // Libera o controle
    meuControle.desconectar();
    // Fecha o SDL corretamente antes de sair
    SDL_Quit();
    return 0;
}