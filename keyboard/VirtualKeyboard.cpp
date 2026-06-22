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


char VirtualKeyboard::getTeclaAtual(){
    // Retorna a tecla que o cursor atual está
    return layout[linhaAtual][colunaAtual];
}
