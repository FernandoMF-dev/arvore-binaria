#include "headers/ArvoreBinaria.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado!\n"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

void insertRoot(ArvoreBinaria *arvoreBinaria, Aluno *value);

Node *insertNode(Node *node, Aluno *value);

Node *insertNewNode(Node *node, Aluno *value);

Aluno *searchNode(Node *node, char *key);

void findAndPrintNode(Node *node, char *key, int counter);

void printNodeInOrderAsc(Node *node);

void printNodeInOrderDesc(Node *node);

void printNodePreOrder(Node *node);

void printNodePostOrder(Node *node);

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

Aluno *searchNode(Node *node, char *key) {
    if (node == NULL) {
        printf(ERROR_REGISTRO_NAO_ENCONTRADO);
        return NULL;
    }

    int compare = compareNodeByKey(node, key);

    if (compare < 0) {
        return searchNode(node->left, key);
    } else if (compare > 0) {
        return searchNode(node->right, key);
    }
    return node->value;
}

void findAndPrintNode(Node *node, char *key, int counter) {
    if (node != NULL) {
        int compare = compareNodeByKey(node, key);

        if (compare < 0) {
            return findAndPrintNode(node->left, key, counter + 1);
        } else if (compare > 0) {
            return findAndPrintNode(node->right, key, counter + 1);
        }
    } else {
        printf(ERROR_REGISTRO_NAO_ENCONTRADO);
    }
    printf("\nForam comparados %d registros antes de encontrar esse resultado", counter);
}

void printNodeInOrderAsc(Node *node) {
    if (node == NULL) {
        return;
    }

    printNodeInOrderAsc(node->left);
    printNode(node);
    printNodeInOrderAsc(node->right);
}

void printNodeInOrderDesc(Node *node) {
    if (node == NULL) {
        return;
    }

    printNodeInOrderDesc(node->right);
    printNode(node);
    printNodeInOrderDesc(node->left);
}

void printNodePreOrder(Node *node) {
    if (node == NULL) {
        return;
    }

    printNode(node);
    printNodePreOrder(node->left);
    printNodePreOrder(node->right);
}

void printNodePostOrder(Node *node) {
    if (node == NULL) {
        return;
    }

    printNodePostOrder(node->left);
    printNodePostOrder(node->right);
    printNode(node);
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

Aluno *searchArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key) {
    return searchNode(arvoreBinaria->root, key);
}

void findAndPrintArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key) {
    findAndPrintNode(arvoreBinaria->root, key, 0);
}

void printArvoreBinariaInOrderAsc(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s", arvoreBinaria->label);
    printNodeInOrderAsc(arvoreBinaria->root);
}

void printArvoreBinariaInOrderDesc(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s", arvoreBinaria->label);
    printNodeInOrderDesc(arvoreBinaria->root);
}

void printArvoreBinariaPreOrder(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s", arvoreBinaria->label);
    printNodePreOrder(arvoreBinaria->root);
}

void printArvoreBinariaPostOrder(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s", arvoreBinaria->label);
    printNodePostOrder(arvoreBinaria->root);
}