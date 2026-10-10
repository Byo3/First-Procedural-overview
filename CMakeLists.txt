cmake_minimum_required(VERSION 3.16)

project(Grids LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Grids main.cpp)

set(SFML_DIR "~/DevProjects/C++/Libraries/SFML-3.1.0/lib/cmake/SFML/")

find_package(SFML 3.1 REQUIRED COMPONENTS Graphics Window System Audio Network)

# Faz a compilador aplicar as funcao da biblitecas
target_link_libraries(Grids
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    SFML::Network)

target_compile_options(Grids PRIVATE -lsfml-graphics -lsfml-window -lsfml-system)

include(GNUInstallDirs)
install(TARGETS Grids
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
