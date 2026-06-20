# 🎮 Controle Mapper

Um programa desenvolvido em C++ que transforma qualquer controle de videogame (Xbox, PlayStation, genéricos) em uma ferramenta que emula funções de teclado e mouse. 

O projeto lê os inputs físicos do hardware utilizando a biblioteca **SDL2** e injeta os comandos diretamente na API do Windows (apenas por enquanto), permitindo navegação completa pelo computador, uso de atalhos e rolagem de páginas de forma nativa e sem engasgos.

## Funcionalidades e Mapeamento

O programa fica executando em segundo plano e mapeia o controle da seguinte forma:

| Ação no Controle | Ação no Sistema Operacional |
| :--- | :--- |
| **Analógico Esquerdo** | Movimenta o cursor do Mouse |
| **Analógico Direito** | Scroll (Rolagem vertical e horizontal) |
| **Gatilho LT** | Clique Esquerdo do Mouse |
| **Gatilho RT** | Clique Direito do Mouse |
| **D-Pad (Setinhas)** | Setas do Teclado (Cima, Baixo, Esquerda, Direita) |
| **Botão RB** | Abre o menu `ALT + TAB` (Navegue e confirme com A ou B, no windows) |
| **START + B** | Encerra o programa com segurança |

*Nota: Os analógicos contam com uma configuração interna de Zona Morta (Deadzone) para evitar que o mouse ou a tela se movam sozinhos devido ao desgaste físico do controle (drift).*

## Arquitetura do Projeto

O código foi construído com foco em modularidade, separando a lógica de leitura de hardware da injeção de software:

* `/controller`: Gerencia a conexão com o SDL2, eventos de hardware e mapeamento bruto dos botões.
* `/mouse`: Lida com a injeção nativa de movimento, scroll e cliques (via `SendInput` no Windows).
* `/keyboard`: Gerencia a injeção de teclas virtuais e atalhos de sistema.

## ⚙️ Pré-requisitos para Compilação

Para compilar este projeto a partir do código-fonte, você precisará de:

1.  **Compilador C++**: Suporte a C++17 (Recomendado: GCC via MSYS2/UCRT64 no Windows).
2.  **CMake**: Versão 3.14 ou superior. 

*A biblioteca SDL2 é baixada e linkada automaticamente pelo CMake no momento da compilação, não sendo necessária instalação manual.*

## 🛠️ Como Compilar e Executar (Windows)

1. Clone o repositório ou baixe os arquivos fonte.
2. Abra a pasta raiz do projeto no seu terminal ou VS Code.
3. Crie a pasta de build e acesse-a:
```bash
mkdir build
cd build
```

4. Gere os arquivos de compilação com o CMake:
```bash
cmake ..
```

5. Compile o executável:
```bash
cmake --build .
```

6. Execute o programa gerado (`ControleMapper.exe`).

> **Aviso de Permissões:** Para que o controle consiga clicar em janelas executadas como Administrador (como Gerenciador de Tarefas ou instaladores), é necessário iniciar o `ControleMapper.exe` também como Administrador.

## 🗺️ Roadmap (Próximos Passos)

* [x] Leitura de hardware via Polling (Zero lag).
* [x] Injeção de estado contínuo (Cliques e Scroll).
* [x] Modularização do código (Orientação a Objetos).
* [ ] Adicionar suporte multiplataforma para injeção de inputs no Linux (X11 / uinput).
