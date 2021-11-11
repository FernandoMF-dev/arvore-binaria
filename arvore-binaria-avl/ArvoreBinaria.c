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

/*
 * Insere um registro na raiz de uma ArvoreBinaria
 * */
void insertRoot(ArvoreBinaria *arvoreBinaria, Aluno *value) {
    arvoreBinaria->root = readNode(value);
}

/*
 * Verifica se um valor deve ser inserido a esquerda ou a direita de um Node
 * */
Node *insertNode(Node *node, Aluno *value) {
    int compare = compareNodeByValue(node, value);

    if (compare > 0) {
        node->left = insertNewNode(node->left, value);
    } else if (compare < 0) {
        node->right = insertNewNode(node->right, value);
    }

    return node;
}

/*
 * Cria e retorna um Node com o valor passado para ser substituído por um Node nulo
 * */
Node *insertNewNode(Node *node, Aluno *value) {
    if (node != NULL) {
        node = insertNode(node, value);
    } else {
        node = readNode(value);
    }

    return node;
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
 * Apaga um Node de acordo com uma chave (key).
 * */
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

/*
 * Apaga um Node que não possua qualquer filho
 * */
Node *removeNodeZeroChildren(Node *node) {
    free(node);
    return NULL;
}

/*
 * Apaga um Node que possua um e apenas um filho
 * */
Node *removeNodeOneChildren(Node *node) {
    Node *aux = node->left != NULL ? node->left : node->right;

    free(node);

    return aux;
}

/*
 * Apaga um Node que possua dois filhos
 * */
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
 * Insere o valor de um Node e de seus filhos numa ArvoreBinaria.
 * */
void cloneNodeIntoArvoreBinaria(ArvoreBinaria *target, Node *source) {
    if (source == NULL) {
        return;
    }

    insertArvoreBinaria(target, source->value);
    cloneNodeIntoArvoreBinaria(target, source->left);
    cloneNodeIntoArvoreBinaria(target, source->right);
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

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

/*
 * Inicializa e retorna uma nova instância de ArvoreBinaria.
 * */
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

/*
 * Insere um novo registro numa ArvoreBinaria.
 * */
void insertArvoreBinaria(ArvoreBinaria *arvoreBinaria, Aluno *value) {
    if (arvoreBinaria->root == NULL) {
        return insertRoot(arvoreBinaria, value);
    }
    arvoreBinaria->root = insertNode(arvoreBinaria->root, value);
}

/*
 * Busca um registro na ArvoreBinaria de acordo com uma chave (key).
 *
 * Se encontrar, retorna os dados do registro.
 * Se não, retorna NULL.
 * */
Aluno *searchArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return NULL;
    }
    return searchNode(arvoreBinaria->root, key);
}

/*
 * Busca um registro na ArvoreBinaria e imprime os seguintes dados sobre ele:
 *
 * - Os dados do registro;
 * - O número de registros que foram veríficados antes do alvo ser encontrado.
 * */
void findAndPrintArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return;
    }
    findAndPrintNode(arvoreBinaria->root, key, 0);
}

/*
 * Remove um registro da ArvoreBinaria de acordo com uma chave (key).
 * */
void removeArvoreBinaria(ArvoreBinaria *arvoreBinaria, char *key) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return;
    }
    arvoreBinaria->root = removeNode(arvoreBinaria->root, key);
}

/*
 * Calcula e retorna a altura de uma ArvoreBinaria com base no seus filho.
 * O valor inicial é 0, então uma ArvoreBinaria com apenas um Node retornará 0.
 * Caso a ArvoreBinaria não possua qualquer registro, retorna -1
 * */
int getHeightArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
    }
    return getHeightNode(arvoreBinaria->root);
}

/*
 * Calcula e retorna a quantidade de registros numa ArvoreBinaria.
 * */
int getSizeArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
    }
    return getSizeNode(arvoreBinaria->root);
}

/*
 * Retorna o maior registro numa ArvoreBinaria.
 * */
Aluno *getMaxArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return NULL;
    }
    return getMaxNode(arvoreBinaria->root);
}

/*
 * Retorna o menor registro numa ArvoreBinaria.
 * */
Aluno *getMinArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return NULL;
    }
    return getMinNode(arvoreBinaria->root);
}

/*
 * Remove todos os registros numa ArvoreBinaria
 * */
void clearArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    if (arvoreBinaria->root == NULL) {
        return;
    }

    clearNode(arvoreBinaria->root);
    arvoreBinaria->root = NULL;
}

/*
 * Lê todos os registros da ArvoreBinaria 'source' e os insere na ArvoreBinaria 'target'.
 * */
void cloneArvoreBinaria(ArvoreBinaria *target, ArvoreBinaria *source) {
    cloneNodeIntoArvoreBinaria(target, source->root);
}

/*
 * Imprime uma ArvoreBinaria.
 * Imprime os registros dela com ordenação "Em-Ordem Crescente"
 * */
void printArvoreBinariaInOrderAsc(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s\n", arvoreBinaria->label);
    printNodeInOrderAsc(arvoreBinaria->root);
}

/*
 * Imprime uma ArvoreBinaria.
 * Imprime os registros dela com ordenação "Em-Ordem Decrescente"
 * */
void printArvoreBinariaInOrderDesc(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s\n", arvoreBinaria->label);
    printNodeInOrderDesc(arvoreBinaria->root);
}

/*
 * Imprime uma ArvoreBinaria.
 * Imprime os registros dela com ordenação "Pré-Ordem"
 * */
void printArvoreBinariaPreOrder(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s", arvoreBinaria->label);
    printNodePreOrder(arvoreBinaria->root);
}

/*
 * Imprime uma ArvoreBinaria.
 * Imprime os registros dela com ordenação "Pós-Ordem"
 * */
void printArvoreBinariaPostOrder(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s", arvoreBinaria->label);
    printNodePostOrder(arvoreBinaria->root);
}

/*
 * Imprime os seguintes dados de uma ArvoreBinaria:
 *
 * - Nome;
 * - Altura;
 * - Número de registros.
 * */
void printStatisticsArvoreBinaria(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s", arvoreBinaria->label);
    printf("\nAltura: %d", getHeightArvoreBinaria(arvoreBinaria));
    printf("\nTamanho: %d", getSizeArvoreBinaria(arvoreBinaria));
}