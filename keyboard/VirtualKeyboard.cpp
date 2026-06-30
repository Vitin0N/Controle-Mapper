#include "VirtualKeyboard.h"
#include <cmath> // Para std::abs

namespace {
    const int MARGEM = 4; // Padding entre as teclas

    // Se for compilar no Linux depois, troque para o caminho de uma fonte do sistema,
    // ou melhor ainda: coloque a fonte na mesma pasta do executável.
    // const char* CAMINHO_FONTE = "assets/motiva-sans/MotivaSansMedium.ttf";
    const char* CAMINHO_FONTE = "C:\\Windows\\Fonts\\arial.ttf";
    
    const int TAMANHO_FONTE = 24;
}

VirtualKeyboard::VirtualKeyboard(int screenW, int screenH) {
    if(TTF_WasInit() == 0){
        TTF_Init();
    }
    fonte = TTF_OpenFont(CAMINHO_FONTE, TAMANHO_FONTE);

    // Definindo a área total que o teclado vai ocupar (parte inferior da tela)
    tecladoLargura = screenW;
    tecladoAltura = screenH;
    tecladoYOffset = screenH - tecladoAltura; // Posiciona embaixo

    exibirSimbolos = false;

    // Inicializando o layout com os pesos (Estilo Steam Big Picture)
    layoutPrincipal = {
        // LINHA 0
        { {"`", "", 0.6f, NORMAL}, {"1", "", 1.0f, NORMAL}, {"2", "", 1.0f, NORMAL}, {"3", "", 1.0f, NORMAL}, 
          {"4", "", 1.0f, NORMAL}, {"5", "", 1.0f, NORMAL}, {"6", "", 1.0f, NORMAL}, {"7", "", 1.0f, NORMAL}, 
          {"8", "", 1.0f, NORMAL}, {"9", "", 1.0f, NORMAL}, {"0", "", 1.0f, NORMAL}, {"-", "", 1.0f, NORMAL}, 
          {"=", "", 1.0f, NORMAL}, {"Backspace", "X", 2.0f, ESPECIAL} },
        // LINHA 1
        { {"Tab", "", 1.5f, ESPECIAL}, {"q", "", 1.0f, NORMAL}, {"w", "", 1.0f, NORMAL}, {"e", "", 1.0f, NORMAL}, 
          {"r", "", 1.0f, NORMAL}, {"t", "", 1.0f, NORMAL}, {"y", "", 1.0f, NORMAL}, {"u", "", 1.0f, NORMAL}, 
          {"i", "", 1.0f, NORMAL}, {"o", "", 1.0f, NORMAL}, {"p", "", 1.0f, NORMAL}, {"[", "", 1.0f, NORMAL}, 
          {"]", "", 1.0f, NORMAL}, {"\\", "", 1.0f, NORMAL} },
        // LINHA 2
        { {"Caps", "L3", 1.8f, ESPECIAL}, {"a", "", 1.0f, NORMAL}, {"s", "", 1.0f, NORMAL}, {"d", "", 1.0f, NORMAL}, 
          {"f", "", 1.0f, NORMAL}, {"g", "", 1.0f, NORMAL}, {"h", "", 1.0f, NORMAL}, {"j", "", 1.0f, NORMAL}, 
          {"k", "", 1.0f, NORMAL}, {"l", "", 1.0f, NORMAL}, {"ç", "", 1.0f, NORMAL}, {"'", "", 1.0f, NORMAL}, 
          {"Enter", "R2", 2.2f, ESPECIAL} },
        // LINHA 3
        { {"Shift", "L2", 2.2f, ESPECIAL}, {"z", "", 1.0f, NORMAL}, {"x", "", 1.0f, NORMAL}, {"c", "", 1.0f, NORMAL}, 
          {"v", "", 1.0f, NORMAL}, {"b", "", 1.0f, NORMAL}, {"n", "", 1.0f, NORMAL}, {"m", "", 1.0f, NORMAL}, 
          {",", "", 1.0f, NORMAL}, {".", "", 1.0f, NORMAL}, {"/", "", 1.0f, NORMAL}, {"Shift", "L2", 2.5f, ESPECIAL} },
        // LINHA 4
        { {":)", "", 1.0f, ESPECIAL}, {"Ctrl", "", 1.5f, ESPECIAL}, {"Espaço", "Y", 8.0f, NORMAL}, 
          {"<", "", 1.0f, ESPECIAL}, {">", "", 1.0f, ESPECIAL}, {"Paste", "L2", 1.2f, ESPECIAL}, {"Move", "", 1.2f, ESPECIAL} }
    };

    layoutSecundario = {
        // LINHA 0
        {
            {"~", "", 0.6f, NORMAL}, {"!", "", 1.0f, NORMAL}, {"@", "", 1.0f, NORMAL},
            {"#", "", 1.0f, NORMAL}, {"$", "", 1.0f, NORMAL}, {"%", "", 1.0f, NORMAL},
            {"^", "", 1.0f, NORMAL}, {"&", "", 1.0f, NORMAL}, {"*", "", 1.0f, NORMAL},
            {"(", "", 1.0f, NORMAL}, {")", "", 1.0f, NORMAL}, {"_", "", 1.0f, NORMAL},
            {"+", "", 1.0f, NORMAL}, {"Backspace", "X", 2.0f, ESPECIAL}
        },

        // LINHA 1
        {
            {"Tab", "", 1.5f, ESPECIAL}, {"Q", "", 1.0f, NORMAL}, {"W", "", 1.0f, NORMAL},
            {"E", "", 1.0f, NORMAL}, {"R", "", 1.0f, NORMAL}, {"T", "", 1.0f, NORMAL},
            {"Y", "", 1.0f, NORMAL}, {"U", "", 1.0f, NORMAL}, {"I", "", 1.0f, NORMAL},
            {"O", "", 1.0f, NORMAL}, {"P", "", 1.0f, NORMAL}, {"{", "", 1.0f, NORMAL},
            {"}", "", 1.0f, NORMAL}, {"|", "", 1.0f, NORMAL}
        },

        // LINHA 2
        {
            {"Caps", "L3", 1.8f, ESPECIAL}, {"A", "", 1.0f, NORMAL}, {"S", "", 1.0f, NORMAL},
            {"D", "", 1.0f, NORMAL}, {"F", "", 1.0f, NORMAL}, {"G", "", 1.0f, NORMAL},
            {"H", "", 1.0f, NORMAL}, {"J", "", 1.0f, NORMAL}, {"K", "", 1.0f, NORMAL},
            {"L", "", 1.0f, NORMAL}, {"Ç", "", 1.0f, NORMAL}, {"\"", "", 1.0f, NORMAL},
            {"Enter", "R2", 2.2f, ESPECIAL}
        },

        // LINHA 3
        {
            {"Shift", "L2", 2.2f, ESPECIAL}, {"Z", "", 1.0f, NORMAL}, {"X", "", 1.0f, NORMAL},
            {"C", "", 1.0f, NORMAL}, {"V", "", 1.0f, NORMAL}, {"B", "", 1.0f, NORMAL},
            {"N", "", 1.0f, NORMAL}, {"M", "", 1.0f, NORMAL}, {"<", "", 1.0f, NORMAL},
            {">", "", 1.0f, NORMAL}, {"?", "", 1.0f, NORMAL},
            {"Shift", "L2", 2.5f, ESPECIAL}
        },

        // LINHA 4
        {
            {":)", "", 1.0f, ESPECIAL}, {"Ctrl", "", 1.5f, ESPECIAL},
            {"Espaço", "Y", 8.0f, NORMAL},
            {"<", "", 1.0f, ESPECIAL}, {">", "", 1.0f, ESPECIAL},
            {"Paste", "L2", 1.2f, ESPECIAL}, {"Move", "", 1.2f, ESPECIAL}
        }
    };

    layout = layoutPrincipal;

    calculaLayout();

    // Começa na tecla 'g' (Linha 2, Coluna 5)
    linhaAtual = 2;
    colunaAtual = 5;
}

VirtualKeyboard::~VirtualKeyboard() {
    if(fonte) {
        TTF_CloseFont(fonte);
        fonte = nullptr;
    }
}

void VirtualKeyboard::calculaLayout() {
    int numLinhas = layout.size();
    int alturaLinha = tecladoAltura / numLinhas;

    for (int l = 0; l < numLinhas; ++l) {
        float pesoTotal = 0;
        for (const auto& tecla : layout[l]) {
            pesoTotal += tecla.peso;
        }

        int xAtual = 0;
        for (auto& tecla : layout[l]) {
            int larguraTecla = (tecladoLargura / pesoTotal) * tecla.peso;

            tecla.bounds.x = xAtual + MARGEM;
            tecla.bounds.y = tecladoYOffset + (l * alturaLinha) + MARGEM;
            tecla.bounds.w = larguraTecla - (MARGEM * 2);
            tecla.bounds.h = alturaLinha - (MARGEM * 2);

            xAtual += larguraTecla;
        }
    }
}

void VirtualKeyboard::redimencionarLayout(int novoW, int novoH){
    tecladoLargura = novoW;
    tecladoAltura = novoH;
    tecladoYOffset = novoH - tecladoAltura;

    // Calcula novamente o layout
    calculaLayout();

}

TeclaDef VirtualKeyboard::getTeclaAtual() {
    return layout[linhaAtual][colunaAtual];
}

void VirtualKeyboard::desenhaTeclado(SDL_Renderer *render) {
    for(size_t l = 0; l < layout.size(); ++l) {
        for(size_t c = 0; c < layout[l].size(); ++c) {
            const TeclaDef& tecla = layout[l][c];
            bool selecionada = (l == linhaAtual && c == colunaAtual);

            if(tecla.tipo == INVISIVEL && !selecionada) continue;

            // --- Fundo da tecla ---
            if(selecionada) {
                SDL_SetRenderDrawColor(render, 255, 255, 255, 255); // Branco
            } else if(tecla.tipo == ESPECIAL) {
                SDL_SetRenderDrawColor(render, 1, 1, 2, 255); // Escuro
            } else {
                SDL_SetRenderDrawColor(render, 13, 20, 27, 255); // Cinza azulado
            }
            SDL_RenderFillRect(render, &tecla.bounds);

            // --- Texto Principal ---
            if(fonte && !tecla.label.empty()) {
                SDL_Color corTexto = selecionada ? SDL_Color{0, 0, 0, 255} : SDL_Color{255, 255, 255, 255};
                SDL_Surface* surf = TTF_RenderUTF8_Blended(fonte, tecla.label.c_str(), corTexto);
                if(surf) {
                    SDL_Texture* tex = SDL_CreateTextureFromSurface(render, surf);
                    if(tex) {
                        SDL_Rect destino;
                        destino.w = surf->w;
                        destino.h = surf->h;
                        destino.x = tecla.bounds.x + (tecla.bounds.w - destino.w) / 2;
                        destino.y = tecla.bounds.y + (tecla.bounds.h - destino.h) / 2;
                        SDL_RenderCopy(render, tex, NULL, &destino);
                        SDL_DestroyTexture(tex);
                    }
                    SDL_FreeSurface(surf);
                }
            }
            
            // TODO: adicionar o código para rederizar o gamepadICon
        }
    }
}

// =============================
// Funções de movimentações
// =============================

void VirtualKeyboard::moverDireita() {
    do {
        colunaAtual = (colunaAtual + 1) % layout[linhaAtual].size();
    } while (layout[linhaAtual][colunaAtual].tipo == INVISIVEL);
}

void VirtualKeyboard::moverEsquerda() {
    do {
        colunaAtual = (colunaAtual - 1 + layout[linhaAtual].size()) % layout[linhaAtual].size();
    } while (layout[linhaAtual][colunaAtual].tipo == INVISIVEL);
}

void VirtualKeyboard::moverBaixo() {
    int xCentroAtual = layout[linhaAtual][colunaAtual].bounds.x + (layout[linhaAtual][colunaAtual].bounds.w / 2);
    int proximaLinha = (linhaAtual + 1) % layout.size();
    
    int melhorDistancia = 999999;
    int melhorColuna = 0;

    for (size_t c = 0; c < layout[proximaLinha].size(); ++c) {
        if (layout[proximaLinha][c].tipo == INVISIVEL) continue;
        
        int xCentroCandidato = layout[proximaLinha][c].bounds.x + (layout[proximaLinha][c].bounds.w / 2);
        int distancia = std::abs(xCentroAtual - xCentroCandidato);
        
        if (distancia < melhorDistancia) {
            melhorDistancia = distancia;
            melhorColuna = c;
        }
    }

    linhaAtual = proximaLinha;
    colunaAtual = melhorColuna;
}

void VirtualKeyboard::moverCima() {
    int xCentroAtual = layout[linhaAtual][colunaAtual].bounds.x + (layout[linhaAtual][colunaAtual].bounds.w / 2);
    int proximaLinha = (linhaAtual - 1 + layout.size()) % layout.size();
    
    int melhorDistancia = 999999;
    int melhorColuna = 0;

    for (size_t c = 0; c < layout[proximaLinha].size(); ++c) {
        if (layout[proximaLinha][c].tipo == INVISIVEL) continue;
        
        int xCentroCandidato = layout[proximaLinha][c].bounds.x + (layout[proximaLinha][c].bounds.w / 2);
        int distancia = std::abs(xCentroAtual - xCentroCandidato);
        
        if (distancia < melhorDistancia) {
            melhorDistancia = distancia;
            melhorColuna = c;
        }
    }

    linhaAtual = proximaLinha;
    colunaAtual = melhorColuna;
}

void VirtualKeyboard::alterarLayout() {
    exibirSimbolos = !exibirSimbolos;

    if (exibirSimbolos) {
        layout = layoutSecundario;
    } else {
        layout = layoutPrincipal;
    }

    // Muda o teclado porque os simbolos mudaram
    calculaLayout();
}