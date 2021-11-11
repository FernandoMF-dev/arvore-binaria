#include <stdio.h>
#include <stdlib.h>

#include "Aluno.h"
#include "FuncaoUtils.h"

#ifndef ARVORE_BINARIA_AVL_NODE_H
#define ARVORE_BINARIA_AVL_NODE_H

typedef struct Node {
    int chargeFactor;
    Aluno *value;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode();

Node *readNode(Aluno *value);

int compareNode(Node *node1, Node *node2);

int compareNodeByValue(Node *node, Aluno *value);

int compareNodeByKey(Node *node, char *key);

void printNode(Node *node);

int getHeightNode(Node *node);

int getSizeNode(Node *node);

void updateChargeFactor(Node *node);

void clearNode(Node *node);

#endif //ARVORE_BINARIA_AVL_NODE_H
