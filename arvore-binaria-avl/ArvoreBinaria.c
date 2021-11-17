#include "headers/ArvoreBinaria.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_ARVORE_VAZIA "\n\tERRO: A ArvoreBinaria está vazia!\n"
#define ERROR_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado!\n"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

void insertRootArvoreBinaria(ArvoreBinaria *arvoreBinaria, Aluno *value);

Node *insertNodeArvoreBinaria(Node *node, Aluno *value);

Node *insertNewNodeArvoreBinaria(Node *node, Aluno *value);

Node *removeNodeArvoreBinaria(Node *node, char *key);

Node *removeNodeZeroChildrenArvoreBinaria(Node *node);

Node *removeNodeOneChildrenArvoreBinaria(Node *node);

Node *removeNodeTwoChildrenArvoreBinaria(Node *node, char *key);

void cloneNodeIntoArvoreBinaria(ArvoreBinaria *target, Node *source);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

/*
 * Insere um registro na raiz de uma ArvoreBinaria
 * */
void insertRootArvoreBinaria(ArvoreBinaria *arvoreBinaria, Aluno *value) {
    arvoreBinaria->root = readNode(value);
}

/*
 * Verifica se um valor deve ser inserido a esquerda ou a direita de um Node
 * */
Node *insertNodeArvoreBinaria(Node *node, Aluno *value) {
    int compare = compareNodeByValue(node, value);

    if (compare > 0) {
        node->left = insertNewNodeArvoreBinaria(node->left, value);
    } else if (compare < 0) {
        node->right = insertNewNodeArvoreBinaria(node->right, value);
    }

    return node;
}

/*
 * Cria e retorna um Node com o valor passado para ser substituído por um Node nulo
 * */
Node *insertNewNodeArvoreBinaria(Node *node, Aluno *value) {
    if (node != NULL) {
        node = insertNodeArvoreBinaria(node, value);
    } else {
        node = readNode(value);
    }

    return node;
}

/*
 * Apaga um Node de acordo com uma chave (key).
 * */
Node *removeNodeArvoreBinaria(Node *node, char *key) {
    if (node == NULL) {
        printf(ERROR_REGISTRO_NAO_ENCONTRADO);
        return NULL;
    }

    int compare = compareNodeByKey(node, key);

    if (compare > 0) {
        node->left = removeNodeArvoreBinaria(node->left, key);
    } else if (compare < 0) {
        node->right = removeNodeArvoreBinaria(node->right, key);
    } else {
        if (node->left == NULL && node->right == NULL) {
            node = removeNodeZeroChildrenArvoreBinaria(node);
        } else if (node->left == NULL || node->right == NULL) {
            node = removeNodeOneChildrenArvoreBinaria(node);
        } else {
            node = removeNodeTwoChildrenArvoreBinaria(node, key);
        }
    }
    return node;
}

/*
 * Apaga um Node que não possua qualquer filho
 * */
Node *removeNodeZeroChildrenArvoreBinaria(Node *node) {
    free(node);
    return NULL;
}

/*
 * Apaga um Node que possua um e apenas um filho
 * */
Node *removeNodeOneChildrenArvoreBinaria(Node *node) {
    Node *aux = node->left != NULL ? node->left : node->right;

    free(node);

    return aux;
}

/*
 * Apaga um Node que possua dois filhos
 * */
Node *removeNodeTwoChildrenArvoreBinaria(Node *node, char *key) {
    Node *aux = node->left;
    Aluno *value = node->value;

    while (aux->right != NULL) {
        aux = aux->right;
    }

    node->value = aux->value;
    aux->value = value;
    node->left = removeNodeArvoreBinaria(node->left, key);

    return node;
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
        return insertRootArvoreBinaria(arvoreBinaria, value);
    }
    arvoreBinaria->root = insertNodeArvoreBinaria(arvoreBinaria->root, value);
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
    arvoreBinaria->root = removeNodeArvoreBinaria(arvoreBinaria->root, key);
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
    return findHeightNode(arvoreBinaria->root);
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
    printf("\n%s\n", arvoreBinaria->label);
    printNodePreOrder(arvoreBinaria->root);
}

/*
 * Imprime uma ArvoreBinaria.
 * Imprime os registros dela com ordenação "Pós-Ordem"
 * */
void printArvoreBinariaPostOrder(ArvoreBinaria *arvoreBinaria) {
    printf("\n%s\n", arvoreBinaria->label);
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
