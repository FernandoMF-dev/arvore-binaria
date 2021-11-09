#include "headers/Node.h"

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