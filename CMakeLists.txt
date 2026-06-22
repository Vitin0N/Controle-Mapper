cmake_minimum_required(VERSION 3.14)
project(ControleMapper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Módulo nativo do CMake para baixar dependências da internet
include(FetchContent)

# Declara onde está o SDL2 e qual versão queremos
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.2 
)

# Executa o download e a configuração do SDL2 nos bastidores
FetchContent_MakeAvailable(SDL2)

# Adiciona o seu executável
add_executable(${PROJECT_NAME} 
    main.cpp 
    controller/Controller.cpp 
    mouse/Mouse.cpp 
    keyboard/Keyboard.cpp 
    keyboard/AtalhoTeclasMapper.h
    keyboard/VirtualKeyboard.cpp
)

# Linka a biblioteca do SDL2 ao seu projeto
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static) 