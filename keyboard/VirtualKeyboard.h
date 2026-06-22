#pragma once
#include <SDL2/SDL.h>

class VirtualKeyboard{

    private:
    // Tamanho do teclado virtual
    static const int LINHAS = 4;
    static const int COLUNAS = 10;

    // Matriz que guarda os caracteres
    char layout[LINHAS][COLUNAS];

    // Coordenadas atuais
    int linhaAtual;
    int colunaAtual;

    public:
    // Construtor
    VirtualKeyboard();

    // Funções de navegação;
    void moverCima();
    void moverBaixo();
    void moverEsquerda();
    void moverDireita();

    // Função que sabe a tecla atual
    char getTeclaAtual();

    // Desenha o teclado na tela
    void desenhaTeclado(SDL_Renderer *render);
};