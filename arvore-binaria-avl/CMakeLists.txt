cmake_minimum_required(VERSION 3.20)
project(arvore_binaria_avl C)

set(CMAKE_C_STANDARD 99)

add_executable(arvore_binaria_avl main.c Aluno.c headers/Aluno.h)

target_link_libraries(arvore_binaria_avl m)