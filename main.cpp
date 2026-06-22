#include <iostream>
#include <SDL2/SDL.h>

#include "controller/Controller.h"
#include "controller/Controller_Map.h"
#include "mouse/Mouse.h"
#include "keyboard/Keyboard.h"
#include "keyboard/AtalhoTeclasMapper.h"
#include "keyboard/VirtualKeyboard.h"


// Importa o windows.h caso estejamos em sistemas windows
#ifdef _WIN32
    #include <windows.h>
#endif

// Variaveis globais

// Zona morta do analogico do controle
#define ZONA_MORTA 5000
#define VELOCIDADE_SCROLL 350

int main(int argc, char* argv[]) {

    // Força o SDL a escutar o controle mesmo com a janela escondida ou sem foco
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

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
    VirtualKeyboard meuTecladoVirtual;

    // Cria a tela do teclado virtual
    SDL_Window *janelaTeclado = SDL_CreateWindow(
        "Teclado Virtual (Aperte SELECT pra sair)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        710, 290, 
        SDL_WINDOW_HIDDEN
    );

    SDL_Renderer *renderizador = SDL_CreateRenderer(janelaTeclado, -1, SDL_RENDERER_ACCELERATED);

    // Criando estados possiveis do programa
    enum ModoPrograma {
        MODO_NORMAL,
        MODO_TECLADO_VIRTUAL
    };

    ModoPrograma modoAtual = MODO_NORMAL;
    
    // Verifica se há algum conectado
    if(!meuControle.conectar()){
        SDL_Quit();
        return -1;
    }

    // Flags de execução
    bool rodando = true;

    std::cout << "\nLendo o controle 1. Precione START + B para encerrar o programa\n";

    // Define os triggers como não clicados ainda
    bool LT_pressionado = false;
    bool RT_pressionado = false;

    // Define se botões padrão estão apertados
    bool RB_pressionado = false;
    bool BACK_pressionado = false;
    bool A_pressionado = false;
    bool UP_pressionado = false;
    bool DOWN_pressionado = false;
    bool LEFT_pressionado = false;
    bool RIGHT_pressionado = false;

    // Define se as teclas estão sendo seguradas
    bool ALT_pressionado = false;


    // Roda até o usuário pedir para parar
    while(rodando){

        SDL_Event lixo;
        while(SDL_PollEvent(&lixo)){
            if(lixo.type == SDL_QUIT){
                rodando = false;
            }
            // Tirar os itens antigos da fila para não travar
        }
        
        // Recebe os eventos de entrada dos dispositivos conectados
        meuControle.atualizarEventos();
        
        // ========================
        // Encerramento do programa
        // ========================
        
        // START + B programa encerra
        if(meuControle.isBotaoPressionado(ControllerMap::START) &&
        meuControle.isBotaoPressionado(ControllerMap::BTN_B)
    ) {
        rodando = false;
    }

    // Lógica de mudança de estado do programa
    bool botaoBack = meuControle.isBotaoPressionado(ControllerMap::BACK);
    if(!BACK_pressionado && botaoBack){
        if(modoAtual == MODO_NORMAL){
            modoAtual = MODO_TECLADO_VIRTUAL;
            SDL_ShowWindow(janelaTeclado);
            std::cout << "\n--- MODO TECLADO ATIVADO ---\n";
        } else {
            modoAtual = MODO_NORMAL;
            SDL_HideWindow(janelaTeclado);
            std::cout << "\n--- MODO NORMAL ATIVADO ---\n";
        }
        BACK_pressionado = true;
    } else if(BACK_pressionado && !botaoBack){
        BACK_pressionado = false;
    }
    
        // Verifica modo de programa
        if(modoAtual == MODO_NORMAL){
            // ================
            // Função de mouse
            // =================
            
            // Pega as coordenadas da alavanca esquerda
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

            // Pega as coordenadas da alavanca direita
            int eixoRX = meuControle.getEixos(ControllerMap::RIGHT_X);
            int eixoRY = meuControle.getEixos(ControllerMap::RIGHT_Y);
            
            int scrollX = 0;
            int scrollY = 0;
            
            if(abs(eixoRY) > ZONA_MORTA){
                scrollY = (eixoRY / VELOCIDADE_SCROLL) * -1; // Deixa invertido
            }
            
            if(abs(eixoRX) > ZONA_MORTA){
                scrollX = (eixoRX / VELOCIDADE_SCROLL);
            }
            
            if(scrollX != 0 || scrollY != 0){
                meuMouse.scroll(scrollX, scrollY);
            }
            
            // Verifica se os gatilhos forma precionado mais da metade
            bool deveClicarLT = meuControle.getEixos(ControllerMap::LT) > 1600;
            bool deveClicarRT = meuControle.getEixos(ControllerMap::RT) > 1600;
            
            // Verifica se o LT esta pressionado para executar o clique no botão esquerdo do mouse
            if(deveClicarLT && !LT_pressionado){
                meuMouse.cliqueEsquerdo(true);
                LT_pressionado = true;
            } else if(!deveClicarLT && LT_pressionado){
                meuMouse.cliqueEsquerdo(false);
                LT_pressionado = false;
            }
            
            // Verifica se o RT esta pressionado para executar o clique no botão direito do mouse
            if(deveClicarRT && !RT_pressionado){
                meuMouse.cliqueDireito(true);
                RT_pressionado = true;
            } else if(!deveClicarRT && RT_pressionado){
                meuMouse.cliqueDireito(false);
                RT_pressionado = false;
            }
            
            // ==================
            // Funções de teclado
            // ==================
            
            // Verifica se as setinhas do teclados estão sendo pressionadas
            bool botaoUP = meuControle.isBotaoPressionado(ControllerMap::DPAD_UP);
            bool botaoDOWN = meuControle.isBotaoPressionado(ControllerMap::DPAD_DOWN);
            bool botaoLEFT = meuControle.isBotaoPressionado(ControllerMap::DPAD_LEFT);
            bool botaoRIGHT = meuControle.isBotaoPressionado(ControllerMap::DPAD_RIGHT);
            
            // Botão UP pressionada pela setinha do controle
            if(botaoUP){
                meuTeclado.apertaTecla(VK_UP, true);
                std::cout << "Tecla Atual: " << meuTecladoVirtual.getTeclaAtual() << "\n";
            } else {
                meuTeclado.apertaTecla(VK_UP, false);
            }
            
            // Botão DOWN pressionada pela setinha do controle
            if(botaoDOWN){
                meuTeclado.apertaTecla(VK_DOWN, true);
                std::cout << "Tecla Atual: " << meuTecladoVirtual.getTeclaAtual() << "\n";
            } else {
                meuTeclado.apertaTecla(VK_DOWN, false);
            }
            
            // Botão LEFT pressionada pela setinha do controle
            if(botaoLEFT){
                meuTeclado.apertaTecla(VK_LEFT, true);
                std::cout << "Tecla Atual: " << meuTecladoVirtual.getTeclaAtual() << "\n";
            } else {
                meuTeclado.apertaTecla(VK_LEFT, false);
            }
            
            // Botão RIGHT pressionada pela setinha do controle
            if(botaoRIGHT){
                meuTeclado.apertaTecla(VK_RIGHT, true);
                std::cout << "Tecla Atual: " << meuTecladoVirtual.getTeclaAtual() << "\n";
            } else {
                meuTeclado.apertaTecla(VK_RIGHT, false);
            }
            
            // =================
            // Funções de atalho
            // =================
            
            // RB -> ALT + TAB (ativar)
            if(meuControle.isBotaoPressionado(ControllerMap::RB) && 
                !RB_pressionado && !ALT_pressionado)
            {
                meuTeclado.apertaAltTab();
                ALT_pressionado = true;
                RB_pressionado = true;

                
                // Bloqueia as outras funções até ele sair do ALT + TAB
                while(ALT_pressionado){
                    // Pega os botões no estado atual
                    bool botaoA = meuControle.isBotaoPressionado(ControllerMap::BTN_A);
                    bool botaoB = meuControle.isBotaoPressionado(ControllerMap::BTN_B);
                    
                    // Busca os inputs do controle
                    meuControle.atualizarEventos();

                    // Caso ele confirme ou saia do ALT + TAB então o while é encerrado.
                    if(botaoA || botaoB) {
                            ALT_pressionado = false;
                    }

                    SDL_Delay(30);
                }

                RB_pressionado = false;
                meuTeclado.soltaAltTab();

            } 
        } else if(modoAtual == MODO_TECLADO_VIRTUAL){
            // ==========================
            // Funções de Teclado Virtual
            // ==========================

            // Move para cima
            if(!UP_pressionado && meuControle.isBotaoPressionado(ControllerMap::DPAD_UP)){
                meuTecladoVirtual.moverCima();
                UP_pressionado = true;
            }else if(UP_pressionado && !meuControle.isBotaoPressionado(ControllerMap::DPAD_UP)){
                UP_pressionado = false;
            }
            
            // Move para baixo
            if(!DOWN_pressionado && meuControle.isBotaoPressionado(ControllerMap::DPAD_DOWN)){
                meuTecladoVirtual.moverBaixo();
                DOWN_pressionado = true;
            }else if(DOWN_pressionado && !meuControle.isBotaoPressionado(ControllerMap::DPAD_DOWN)){
                DOWN_pressionado = false;
            }
            
            // Move para esquerda
            if(!LEFT_pressionado && meuControle.isBotaoPressionado(ControllerMap::DPAD_LEFT)){
                meuTecladoVirtual.moverEsquerda();
                LEFT_pressionado = true;
            }else if(LEFT_pressionado && !meuControle.isBotaoPressionado(ControllerMap::DPAD_LEFT)){
                LEFT_pressionado = false;
            }
            
            // Move para direita
            if(!RIGHT_pressionado && meuControle.isBotaoPressionado(ControllerMap::DPAD_RIGHT)){
                meuTecladoVirtual.moverDireita();
                RIGHT_pressionado = true;
            }else if(RIGHT_pressionado && !meuControle.isBotaoPressionado(ControllerMap::DPAD_RIGHT)){
                RIGHT_pressionado = false;
            }

            // Confirmou a tecla pressionada
            bool botaoA = meuControle.isBotaoPressionado(ControllerMap::BTN_A);
            if(!A_pressionado && botaoA){
                std::cout << meuTecladoVirtual.getTeclaAtual();
                A_pressionado = true;
            } else if(A_pressionado && !botaoA){
                A_pressionado = false;
            }

            meuTecladoVirtual.desenhaTeclado(renderizador);
        }

        SDL_Delay(30); // Espera 50ms antes de ler uma nova entrada
    }
    
    // Libera o controle
    meuControle.desconectar();
    // Fecha o SDL corretamente antes de sair
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janelaTeclado);
    SDL_Quit();
    return 0;
}