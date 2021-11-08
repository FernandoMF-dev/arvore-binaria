#include <stdio.h>
#include <stdlib.h>

#include "Aluno.h"

#ifndef ARVORE_BINARIA_AVL_NODE_H
#define ARVORE_BINARIA_AVL_NODE_H

typedef struct Node {
    int heigth;
    Aluno *value;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode();

Node *readNode(Aluno *value);

int compareNode(Node *node, Aluno *value);

int compareNodeByKey(char *key);

void printNode(Node *node);

#endif //ARVORE_BINARIA_AVL_NODE_H
