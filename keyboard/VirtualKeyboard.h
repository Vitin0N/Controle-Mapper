#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

enum TeclaTipo {
    NORMAL,
    ESPECIAL,
    INVISIVEL
};

struct TeclaDef {
    std::string label;
    std::string gamepadIcon;
    float peso; // Em vez de largura fixa, usamos o peso relativo
    TeclaTipo tipo;
    
    SDL_Rect bounds; // Calculado dinamicamente
};

class VirtualKeyboard {
private:
    std::vector<std::vector<TeclaDef>> layout;
    std::vector<std::vector<TeclaDef>> layoutPrincipal;
    std::vector<std::vector<TeclaDef>> layoutSecundario;
    bool exibirSimbolos;
    
    int linhaAtual;
    int colunaAtual;
    
    int tecladoLargura;
    int tecladoAltura;
    int tecladoYOffset; // Distância do topo da tela
    
    TTF_Font* fonte;

public:
    VirtualKeyboard(int screenW, int screenH);
    ~VirtualKeyboard();

    // Calculo do tamanho da janela
    void calculaLayout();
    void redimencionarLayout(int novoW, int novoH);

    void moverCima();
    void moverBaixo();
    void moverEsquerda();
    void moverDireita();

    void alterarLayout();

    TeclaDef getTeclaAtual();

    void desenhaTeclado(SDL_Renderer *render);
};