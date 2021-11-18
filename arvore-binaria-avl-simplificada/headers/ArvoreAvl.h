#include <stdio.h>
#include <stdlib.h>

#include "Node.h"
#include "Aluno.h"

#ifndef ARVORE_BINARIA_AVL_ARVOREAVL_H
#define ARVORE_BINARIA_AVL_ARVOREAVL_H

typedef struct ArvoreAvl {
    char *label;
    Node *root;
} ArvoreAvl;

ArvoreAvl *newArvoreAvl(char *label);

void insertArvoreAvl(ArvoreAvl *arvoreAvl, Aluno *value);

Aluno *searchArvoreAvl(ArvoreAvl *arvoreAvl, char *key);

void findAndPrintArvoreAvl(ArvoreAvl *arvoreAvl, char *key);

void removeArvoreAvl(ArvoreAvl *arvoreAvl, char *key);

int getHeightArvoreAvl(ArvoreAvl *arvoreAvl);

int getSizeArvoreAvl(ArvoreAvl *arvoreAvl);

Aluno *getMaxArvoreAvl(ArvoreAvl *arvoreAvl);

Aluno *getMinArvoreAvl(ArvoreAvl *arvoreAvl);

void clearArvoreAvl(ArvoreAvl *arvoreAvl);

void cloneArvoreAvl(ArvoreAvl *target, ArvoreAvl *source);

void printArvoreAvlInOrderAsc(ArvoreAvl *arvoreAvl);

void printArvoreAvlInOrderDesc(ArvoreAvl *arvoreAvl);

void printArvoreAvlPreOrder(ArvoreAvl *arvoreAvl);

void printArvoreAvlPostOrder(ArvoreAvl *arvoreAvl);

void printStatisticsArvoreAvl(ArvoreAvl *arvoreAvl);

#endif //ARVORE_BINARIA_AVL_ARVOREAVL_H
