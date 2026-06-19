#pragma once

class Mouse {
    public:
        // Função responsável por mover o mouse
        void mover(int dx, int dy);

        // Função de clique de botão
        void cliqueEsquerdo(bool clicado);
        void cliqueDireito(bool clicado);
};