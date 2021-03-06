#include <stdio.h>
#include <stdlib.h>

#include "Aluno.h"
#include "FuncaoUtils.h"

#ifndef ARVORE_BINARIA_AVL_NODE_H
#define ARVORE_BINARIA_AVL_NODE_H

typedef struct Node {
    int height;
    Aluno *value;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode();

Node *readNode(Aluno *value);

int compareNode(Node *node1, Node *node2);

int compareNodeByValue(Node *node, Aluno *value);

int compareNodeByKey(Node *node, char *key);

Aluno *searchNode(Node *node, char *key);

void findAndPrintNode(Node *node, char *key, int counter);

void printNode(Node *node);

int findHeightNode(Node *node);

int getSizeNode(Node *node);

Aluno *getMaxNode(Node *node);

Aluno *getMinNode(Node *node);

int getChargeFactorNode(Node *node);

void updateAllHeightNode(Node *node);

void updateChildrenHeightNode(Node *node);

void updateHeightNode(Node *node);

void clearNode(Node *node);

void printNodeInOrderAsc(Node *node);

void printNodeInOrderDesc(Node *node);

void printNodePreOrder(Node *node);

void printNodePostOrder(Node *node);

#endif //ARVORE_BINARIA_AVL_NODE_H
