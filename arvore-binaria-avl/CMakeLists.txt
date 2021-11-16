cmake_minimum_required(VERSION 3.20)
project(arvore_binaria_avl C)

set(CMAKE_C_STANDARD 99)

add_executable(arvore_binaria_avl main.c Aluno.c headers/Aluno.h ArvoreBinaria.c headers/ArvoreBinaria.h Node.c headers/Node.h FuncaoUtils.c headers/FuncaoUtils.h ControleArquivoAluno.c headers/ControleArquivoAluno.h ArvoreAvl.c headers/ArvoreAvl.h)

target_link_libraries(arvore_binaria_avl m)