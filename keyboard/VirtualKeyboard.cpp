#include "VirtualKeyboard.h"

VirtualKeyboard::VirtualKeyboard(){
    char inicializador[LINHAS][COLUNAS] = {
        {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
        {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'C'}, // Usando 'C' no lugar do 'Ç' para simplificar por enquanto
        {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '?'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}  // A última linha inteira é o Espaço
    };

    // Copia o teclado atual para o layout
    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            layout[i][j] = inicializador[i][j];
        }
    }

    // Inicializa o cursor do teclado
    linhaAtual = 0;
    colunaAtual = 0;
}

// Funções de movimentações
void VirtualKeyboard::moverBaixo(){
    linhaAtual = (linhaAtual + 1) % LINHAS;
}

void VirtualKeyboard::moverCima(){
    linhaAtual = (linhaAtual - 1 + LINHAS) % LINHAS;
}

void VirtualKeyboard::moverEsquerda(){
    colunaAtual = (colunaAtual - 1 + COLUNAS) % COLUNAS;
}

void VirtualKeyboard::moverDireita(){
    colunaAtual = (colunaAtual + 1) % COLUNAS;
}

// Funções de mostrar a tecla atual
char VirtualKeyboard::getTeclaAtual(){
    // Retorna a tecla que o cursor atual está
    return layout[linhaAtual][colunaAtual];
}

// Cria um teclado virtual
void VirtualKeyboard::desenhaTeclado(SDL_Renderer *render){
    // Limpa fundo e pinta de preto
    SDL_SetRenderDrawColor(render, 30, 30, 30, 255);
    SDL_RenderClear(render);

    // Configurações do desenho da tecla
    int larguraTecla = 60;
    int alturaTecla = 60;
    int margemTecla = 10;

    // Percorre a matriz e cria as teclas na janela
    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){

            SDL_Rect tecla;
            tecla.x = margemTecla + j * (larguraTecla + margemTecla);
            tecla.y = margemTecla + i * (alturaTecla + margemTecla);
            tecla.w = larguraTecla;
            tecla.h = alturaTecla;

            // Lógica de colisão para mostrar qual tecla está sendo selecionada
            if(i == linhaAtual && j == colunaAtual) {
                SDL_SetRenderDrawColor(render, 100, 150, 255, 255);
            } else {
                SDL_SetRenderDrawColor(render, 80, 80, 80, 255);
            }

            // Preenche a tecla com a cor atual
            SDL_RenderFillRect(render, &tecla);
        }
    }

    SDL_RenderPresent(render);
}
