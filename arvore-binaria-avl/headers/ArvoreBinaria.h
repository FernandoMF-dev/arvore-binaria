#include <stdio.h>
#include <stdlib.h>

#include "Node.h"
#include "Aluno.h"

#ifndef ARVORE_BINARIA_AVL_ARVOREBINARIA_H
#define ARVORE_BINARIA_AVL_ARVOREBINARIA_H

typedef struct ArvoreBinaria {
    char *label;
    Node *root;
} ArvoreBinaria;

ArvoreBinaria *newArvoreBinaria(char *label);

void insertArvoreBinaria(ArvoreBinaria *arvoreBinaria, Aluno *value);

Aluno *searchArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key);

void findAndPrintArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key);

void removeArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key);

int getHeightArvoreBinaria(ArvoreBinaria *arvoreBinaria);

void clearArvoreBinaria(ArvoreBinaria *arvoreBinaria);

void cloneArvoreBinaria(ArvoreBinaria *target, ArvoreBinaria *source);

void printArvoreBinariaInOrderAsc(ArvoreBinaria *arvoreBinaria);

void printArvoreBinariaInOrderDesc(ArvoreBinaria *arvoreBinaria);

void printArvoreBinariaPreOrder(ArvoreBinaria *arvoreBinaria);

void printArvoreBinariaPostOrder(ArvoreBinaria *arvoreBinaria);

#endif //ARVORE_BINARIA_AVL_ARVOREBINARIA_H
