#include "headers/Node.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

int getChargeFactor(Node *node);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

int getChargeFactor(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->chargeFactor;
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

Node *newNode() {
    Node *node = (Node *) malloc(sizeof(Node));

    if (node == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

    node->chargeFactor = 0;
    node->value = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node *readNode(Aluno *value) {
    Node *node = newNode();

    if (node != NULL) {
        node->value = value;
    }

    return node;
}

int compareNode(Node *node1, Node *node2) {
    return compareAluno(node1->value, node2->value);
}

int compareNodeByValue(Node *node, Aluno *value) {
    return compareAluno(node->value, value);
}

int compareNodeByKey(Node *node, char *key) {
    return compareAlunoByKey(node->value, key);
}

void printNode(Node *node) {
    printAluno(node->value);
}

int getHeightNode(Node *node) {
    if (node == NULL) {
        return -1;
    }

    return getMaxInt(getHeightNode(node->left), getHeightNode(node->right)) + 1;
}

int getSizeNode(Node *node) {
    int size = 0;

    if (node != NULL) {
        size += getSizeNode(node->left);
        size += getSizeNode(node->right);
        size++;
    }

    return size;
}

void updateChargeFactor(Node *node) {
    if (node->left != NULL) {
        updateChargeFactor(node->left);
    }
    if (node->right != NULL) {
        updateChargeFactor(node->right);
    }

    node->chargeFactor = getChargeFactor(node->left) - getChargeFactor(node->right);
}

void clearNode(Node *node) {
    if (node->left != NULL) {
        clearNode(node->left);
    }
    if (node->right != NULL) {
        clearNode(node->right);
    }
    free(node);
}