#include "headers/ArvoreBinaria.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_ARVORE_VAZIA "\n\tERRO: A ArvoreBinaria está vazia!\n"
#define ERROR_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado!\n"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

void insertRoot(ArvoreBinaria *arvoreBinaria, Aluno *value);

Node *insertNode(Node *node, Aluno *value);

Node *insertNewNode(Node *node, Aluno *value);

Aluno *searchNode(Node *node, char *key);

void findAndPrintNode(Node *node, char *key, int counter);

Node *removeNode(Node *node, char *key);

Node *removeNodeZeroChildren(Node *node);

Node *removeNodeOneChildren(Node *node);

Node *removeNodeTwoChildren(Node *node, char *key);

Aluno *getMaxNode(Node *node);

Aluno *getMinNode(Node *node);

void cloneNodeIntoArvoreBinaria(ArvoreBinaria *target, Node *source);

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

    if (compare > 0) {
        node->left = insertNewNode(node->left, value);
    } else if (compare < 0) {
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

    if (compare > 0) {
        return searchNode(node->left, key);
    } else if (compare < 0) {
        return searchNode(node->right, key);
    }
    return node->value;
}

void findAndPrintNode(Node *node, char *key, int counter) {
    if (node != NULL) {
        int compare = compareNodeByKey(node, key);

        if (compare > 0) {
            return findAndPrintNode(node->left, key, counter + 1);
        } else if (compare < 0) {
            return findAndPrintNode(node->right, key, counter + 1);
        } else {
            printNode(node);
        }
    } else {
        printf(ERROR_REGISTRO_NAO_ENCONTRADO);
    }
    printf("\nForam comparados %d registros antes de encontrar esse resultado", counter);
}

Node *removeNode(Node *node, char *key) {
    if (node == NULL) {
        printf(ERROR_REGISTRO_NAO_ENCONTRADO);
        return NULL;
    }

    int compare = compareNodeByKey(node, key);

    if (compare > 0) {
        node->left = removeNode(node->left, key);
    } else if (compare < 0) {
        node->right = removeNode(node->right, key);
    } else {
        if (node->left == NULL && node->right == NULL) {
            node = removeNodeZeroChildren(node);
        } else if (node->left == NULL || node->right == NULL) {
            node = removeNodeOneChildren(node);
        } else {
            node = removeNodeTwoChildren(node, key);
        }
    }
    return node;
}

Node *removeNodeZeroChildren(Node *node) {
    free(node);
    return NULL;
}

Node *removeNodeOneChildren(Node *node) {
    Node *aux = node->left != NULL ? node->left : node->right;

    free(node);

    return aux;
}

Node *removeNodeTwoChildren(Node *node, char *key) {
    Node *aux = node->left;
    Aluno *value = node->value;

    while (aux->right != NULL) {
        aux = aux->right;
    }

    node->value = aux->value;
    aux->value = value;
    node->left = removeNode(node->left, key);

    return node;
}

Aluno *getMaxNode(Node *node) {
    if (node->right == NULL) {
        return node->value;
    }
    return getMaxNode(node->right);
}

Aluno *getMinNode(Node *node) {
    if (node->left == NULL) {
        return node->value;
    }
    return getMinNode(node->left);
}

void cloneNodeIntoArvoreBinaria(ArvoreBinaria *target, Node *source) {
    if (source == NULL) {
        return;
    }

    insertArvoreBinaria(target, source->value);
    cloneNodeIntoArvoreBinaria(target, source->left);
    cloneNodeIntoArvoreBinaria(target, source->right);
}

void printNodeInOrderAsc(Node *node) {
    if (node == NULL) {
        return;
    }

    printNodeInOrderAsc(node->left);
    printNode(node);
    printf("\n");
    printNodeInOrderAsc(node->right);
}

void printNodeInOrderDesc(Node *node) {
    if (node == NULL) {
        return;
    }

    printNodeInOrderDesc(node->right);
    printNode(node);
    printf("\n");
    printNodeInOrderDesc(node->left);
}

void printNodePreOrder(Node *node) {
    if (node == NULL) {
        return;
    }

    printNode(node);
    printf("\n");
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
    printf("\n");
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

ArvoreBinaria *newArvoreBinaria(char *label) {
    ArvoreBinaria *arvoreBinaria = (ArvoreBinaria *) malloc(sizeof(ArvoreBinaria));

    if (arvoreBinaria == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

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

Aluno *searchArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return NULL;
    }
    return searchNode(arvoreBinaria->root, key);
}

void findAndPrintArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return;
    }
    findAndPrintNode(arvoreBinaria->root, key, 0);
}

void removeArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return;
    }
    arvoreBinaria->root = removeNode(arvoreBinaria->root, key);
}

int getHeightArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
    }
    return getHeightNode(arvoreBinaria->root);
}

int getSizeArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
    }
    return getSizeNode(arvoreBinaria->root);
}

Aluno *getMaxArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return NULL;
    }
    return getMaxNode(arvoreBinaria->root);
}

Aluno *getMinArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return NULL;
    }
    return getMinNode(arvoreBinaria->root);
}

void clearArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        return;
    }

    clearNode(arvoreBinaria->root);
    arvoreBinaria->root = NULL;
}

void cloneArvoreBinaria(ArvoreBinaria *target, ArvoreBinaria *source) {
    cloneNodeIntoArvoreBinaria(target, source->root);
}

void printArvoreBinariaInOrderAsc(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s\n", arvoreBinaria->label);
    printNodeInOrderAsc(arvoreBinaria->root);
}

void printArvoreBinariaInOrderDesc(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s\n", arvoreBinaria->label);
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

void printStatisticsArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s", arvoreBinaria->label);
    printf("\nAltura: %d", getHeightArvoreBinaria(arvoreBinaria));
    printf("\nTamanho: %d", getSizeArvoreBinaria(arvoreBinaria));
}