#include "headers/Node.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

int getChargeFactor(Node *node);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

/*
 * Retorna o fator de carga de um Node.
 * Caso o Node seja nulo, retorna 0.
 * */
int getChargeFactor(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->chargeFactor;
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

/*
 * Inicializa e retorna uma nova instância de Node.
 * */
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

/*
 * Inicializa e retorna uma nova instância de Node preenchido com o valor passado por parâmetro.
 * */
Node *readNode(Aluno *value) {
    Node *node = newNode();

    if (node != NULL) {
        node->value = value;
    }

    return node;
}

/*
 * Compara dois nodes.
 *
 * Se forem iguais, retorna 0.
 * Se node1 for o maior, retorna um inteiro maior que 0.
 * Se node2 for o menor, retorna um inteiro menor que 0.
 * */
int compareNode(Node *node1, Node *node2) {
    return compareAluno(node1->value, node2->value);
}

/*
 * Compara se um valor (value) corresponde a ao registro em um node.
 *
 * Se sim, retorna 0.
 * Se o valor for maior, retorna um inteiro maior que 0.
 * Se o valor for menor, retorna um inteiro menor que 0.
 * */
int compareNodeByValue(Node *node, Aluno *value) {
    return compareAluno(node->value, value);
}

/*
 * Compara se uma chave (key) corresponde a ao registro em um node.
 *
 * Se sim, retorna 0.
 * Se a chave for maior, retorna um inteiro maior que 0.
 * Se a chave for menor, retorna um inteiro menor que 0.
 * */
int compareNodeByKey(Node *node, char *key) {
    return compareAlunoByKey(node->value, key);
}

/*
 * Imprime um Node
 * */
void printNode(Node *node) {
    printAluno(node->value);
}

/*
 * Calcula e retorna a altura de um Node com base no seus filho.
 * O valor inicial é 0, então um Node sem filhos retornará 0.
 * Caso o Node seja nulo, retorna -1
 * */
int getHeightNode(Node *node) {
    if (node == NULL) {
        return -1;
    }

    return getMaxInt(getHeightNode(node->left), getHeightNode(node->right)) + 1;
}

/*
 * Calcula e retorna a quantidade de nodes que caracterizam um Node.
 * Esse calculo incluí o pŕoprio Node, então um Node sem filhos retorna 1.
 * Caso o Node seja nulo, retorna 0
 * */
int getSizeNode(Node *node) {
    int size = 0;

    if (node != NULL) {
        size += getSizeNode(node->left);
        size += getSizeNode(node->right);
        size++;
    }

    return size;
}

/*
 * Atualiza o fator carga de um node e seus filhos
 * */
void updateChargeFactor(Node *node) {
    if (node->left != NULL) {
        updateChargeFactor(node->left);
    }
    if (node->right != NULL) {
        updateChargeFactor(node->right);
    }

    node->chargeFactor = getChargeFactor(node->left) - getChargeFactor(node->right);
}

/*
 * Apaga todos os filhos de um node e então si mesmo.
 * */
void clearNode(Node *node) {
    if (node->left != NULL) {
        clearNode(node->left);
    }
    if (node->right != NULL) {
        clearNode(node->right);
    }
    free(node);
}