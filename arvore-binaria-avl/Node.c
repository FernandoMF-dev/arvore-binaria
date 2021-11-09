#include "headers/Node.h"

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

    node->chargeFactor = 0;
    node->value = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node *readNode(Aluno *value) {
    Node *node = newNode();

    node->value = value;

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

int getHeight(Node *node) {
    if (node == NULL) {
        return -1;
    }

    return getMaxInt(getHeight(node->left), getHeight(node->right)) + 1;
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