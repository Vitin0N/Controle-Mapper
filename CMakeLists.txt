cmake_minimum_required(VERSION 3.14)
project(ControleMapper)

# Compila com UTF8
add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)

# Define o padrão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# BUSCA DAS BIBLIOTECAS

# Busca o motor principal do SDL2
find_package(SDL2 REQUIRED)

# Ativa o radar do pkg-config para achar a extensão SDL_ttf
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# ARQUIVOS DO PROJETO
add_executable(${PROJECT_NAME} 
    main.cpp 
    controller/Controller.cpp 
    mouse/Mouse.cpp 
    keyboard/Keyboard.cpp 
    keyboard/VirtualKeyboard.cpp
)

# LINKAGEM E DIRETÓRIOS

# Força o compilador a achar a pasta dos arquivos .h (Headers)
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Conecta tudo no executável final (.a e .dll)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SDL2::SDL2 
    SDL2::SDL2main 
    ${SDL2_TTF_LIBRARIES}
)

# -------- Configuração de Testes --------

# Cria um executável separado para o teste
add_executable(ver_teclado 
    test/visualizar_teclado.cpp 
    keyboard/VirtualKeyboard.cpp
)

# Dá acesso aos headers do SDL2 para o target de teste
target_include_directories(ver_teclado PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Linka as bibliotecas do SDL2 no target de teste
target_link_libraries(ver_teclado PRIVATE 
    SDL2::SDL2 
    SDL2::SDL2main 
    ${SDL2_TTF_LIBRARIES}
)