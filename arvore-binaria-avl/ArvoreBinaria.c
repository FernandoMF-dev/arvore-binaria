#include "headers/ArvoreBinaria.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

void insertRoot(ArvoreBinaria *arvoreBinaria, Aluno *value);

Node *insertNode(Node *node, Aluno *value);

Node *insertNewNode(Node *node, Aluno *value);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

void insertRoot(ArvoreBinaria *arvoreBinaria, Aluno *value) {
    arvoreBinaria->root = readNode(value);
}

Node *insertNode(Node *node, Aluno *value) {
    int compare = compareNodeByValue(node, value);

    if (compare < 0) {
        node->left = insertNewNode(node->left, value);
    } else if (compare > 0) {
        node->right = insertNewNode(node->right, value);
    }

    return node;
}

Node *insertNewNode(Node *node, Aluno *value) {
    if (node != NULL) {
        node = insertNode(node, value);
    } else {
        node = readNode(value);
    }

    return node;
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

ArvoreBinaria *newArvoreBinaria(char *label) {
    ArvoreBinaria *arvoreBinaria = (ArvoreBinaria *) malloc(sizeof(ArvoreBinaria));

    arvoreBinaria->label = label;
    arvoreBinaria->root = NULL;

    return arvoreBinaria;
}

void insertArvoreBinaria(ArvoreBinaria *arvoreBinaria, Aluno *value) {
    if (arvoreBinaria->root == NULL) {
        return insertRoot(arvoreBinaria, value);
    }
    arvoreBinaria->root = insertNode(arvoreBinaria->root, value);
}

int getHeightArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    return getHeightNode(arvoreBinaria->root);
}