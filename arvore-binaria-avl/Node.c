#include "headers/Node.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado!\n"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

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
 * Se o node for maior, retorna um inteiro maior que 0.
 * Se o node for menor, retorna um inteiro menor que 0.
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
 * Busca um valor em um Node e nos seus filhos de acordo com uma chave (key).
 *
 * Se encontrar, retorna os dados do valor.
 * Se não, retorna NULL.
 * */
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

/*
 * Busca um registro em um node e nos seus filhos e imprime:
 *
 * - Os dados do registro;
 * - O número de registros que foram verificados antes de o alvo ser encontrado.
 * */
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

/*
 * Imprime um Node
 * */
void printNode(Node *node) {
    printf("[%d]", node->chargeFactor);
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
 * Busca e retorna o maior valor numa sub árvore
 * */
Aluno *getMaxNode(Node *node) {
    if (node->right == NULL) {
        return node->value;
    }
    return getMaxNode(node->right);
}

/*
 * Busca e retorna o menor valor numa sub árvore
 * */
Aluno *getMinNode(Node *node) {
    if (node->left == NULL) {
        return node->value;
    }
    return getMinNode(node->left);
}

/*
 * Atualiza o fator carga de um node e seus filhos
 * */
void updateAllChargeFactor(Node *node) {
    if (node == NULL) {
        return;
    }
    if (node->left != NULL) {
        updateAllChargeFactor(node->left);
    }
    if (node->right != NULL) {
        updateAllChargeFactor(node->right);
    }

    updateChargeFactor(node);
}

/*
 * Atualiza o fator carga de um node
 * */
void updateChargeFactor(Node *node) {
    if (node == NULL) {
        return;
    }

    if (node->left == NULL && node->right == NULL) {
        node->chargeFactor = 0;
        return;
    }

    if (node->left != NULL && node->right == NULL) {
        node->chargeFactor = node->left->chargeFactor + 1;
        return;
    }

    if (node->left == NULL && node->right != NULL) {
        node->chargeFactor = node->right->chargeFactor - 1;
        return;
    }

    node->chargeFactor = node->left->chargeFactor - node->right->chargeFactor;
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

/*
 * Imprime o valor de um Node e de seus filhos
 * Segue a ordenação "Em-Ordem Crescente"
 * */
void printNodeInOrderAsc(Node *node) {
    if (node == NULL) {
        return;
    }

    printNodeInOrderAsc(node->left);
    printNode(node);
    printf("\n");
    printNodeInOrderAsc(node->right);
}

/*
 * Imprime o valor de um Node e de seus filhos
 * Segue a ordenação "Em-Ordem Decrescente"
 * */
void printNodeInOrderDesc(Node *node) {
    if (node == NULL) {
        return;
    }

    printNodeInOrderDesc(node->right);
    printNode(node);
    printf("\n");
    printNodeInOrderDesc(node->left);
}

/*
 * Imprime o valor de um Node e de seus filhos
 * Segue a ordenação "Pré-Ordem"
 * */
void printNodePreOrder(Node *node) {
    if (node == NULL) {
        return;
    }

    printNode(node);
    printf("\n");
    printNodePreOrder(node->left);
    printNodePreOrder(node->right);
}

/*
 * Imprime o valor de um Node e de seus filhos
 * Segue a ordenação "Pós-Ordem"
 * */
void printNodePostOrder(Node *node) {
    if (node == NULL) {
        return;
    }

    printNodePostOrder(node->left);
    printNodePostOrder(node->right);
    printNode(node);
    printf("\n");
}
