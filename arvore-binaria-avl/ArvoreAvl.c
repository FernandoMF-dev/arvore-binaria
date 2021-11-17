#include "headers/ArvoreAvl.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERROR_ARVORE_VAZIA "\n\tERRO: A ArvoreAvl está vazia!\n"
#define ERROR_REGISTRO_NAO_ENCONTRADO "\n\tERRO: Registro não encontrado!\n"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

Node *rotateLeft(Node *node);

Node *rotateRight(Node *node);

Node *rotateLeftRight(Node *node);

Node *rotateRightLeft(Node *node);

Node *insertBalanceAvlLeft(Node *node, Aluno *value);

Node *insertBalanceAvlRight(Node *node, Aluno *value);

Node *removeBalanceAvlLeft(Node *node);

Node *removeBalanceAvlRight(Node *node);

void insertRootArvoreAvl(ArvoreAvl *arvoreAvl, Aluno *value);

Node *insertNodeArvoreAvl(Node *node, Aluno *value);

Node *insertNewNodeArvoreAvl(Node *node, Aluno *value);

Node *removeNodeArvoreAvl(Node *node, char *key);

Node *removeNodeZeroChildrenArvoreAvl(Node *node);

Node *removeNodeOneChildrenArvoreAvl(Node *node);

Node *removeNodeTwoChildrenArvoreAvl(Node *node, char *key);

void cloneNodeIntoArvoreAvl(ArvoreAvl *target, Node *source);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

Node *rotateLeft(Node *node) {
    Node *aux = node->left;

    node->left = aux->right;
    aux->right = node;

    return aux;
}

Node *rotateRight(Node *node) {
    Node *aux = node->right;

    node->right = aux->left;
    aux->left = node;

    return aux;
}

Node *rotateLeftRight(Node *node) {
    node->left = rotateRight(node->left);
    return rotateLeft(node);
}

Node *rotateRightLeft(Node *node) {
    node->right = rotateLeft(node->right);
    return rotateRight(node);
}

Node *insertBalanceAvlLeft(Node *node, Aluno *value) {
    if (node->chargeFactor > 1) {
        if (compareNodeByValue(node, value) > 0) {
            node = rotateLeft(node);
        } else {
            node = rotateLeftRight(node);
        }
        updateAllChargeFactor(node);
    }

    return node;
}

Node *insertBalanceAvlRight(Node *node, Aluno *value) {
    if (node->chargeFactor < -1) {
        if (compareNodeByValue(node, value) < 0) {
            node = rotateRight(node);
        } else {
            node = rotateRightLeft(node);
        }
        updateAllChargeFactor(node);
    }

    return node;
}

Node *removeBalanceAvlLeft(Node *node) {
    if (node->chargeFactor > 1) {
        if (getHeightNode(node->right->right) < getHeightNode(node->right->left)) {
            node = rotateRightLeft(node);
        } else {
            node = rotateRight(node);
        }
        updateAllChargeFactor(node);
    }

    return node;
}

Node *removeBalanceAvlRight(Node *node) {
    if (node->chargeFactor < 1) {
        if (getHeightNode(node->left->left) < getHeightNode(node->left->right)) {
            node = rotateLeftRight(node);
        } else {
            node = rotateLeft(node);
        }
        updateAllChargeFactor(node);
    }

    return node;
}

/*
 * Insere um registro na raiz de uma ArvoreAvl
 * */
void insertRootArvoreAvl(ArvoreAvl *arvoreAvl, Aluno *value) {
    arvoreAvl->root = readNode(value);
}

/*
 * Verifica se um valor deve ser inserido a esquerda ou a direita de um Node
 * */
Node *insertNodeArvoreAvl(Node *node, Aluno *value) {
    int compare = compareNodeByValue(node, value);

    if (compare > 0) {
        node->left = insertNewNodeArvoreAvl(node->left, value);
        updateChargeFactor(node);
        node = insertBalanceAvlLeft(node, value);
    } else if (compare < 0) {
        node->right = insertNewNodeArvoreAvl(node->right, value);
        updateChargeFactor(node);
        node = insertBalanceAvlRight(node, value);
    }

    return node;
}

/*
 * Cria e retorna um Node com o valor passado para ser substituído por um Node nulo
 * */
Node *insertNewNodeArvoreAvl(Node *node, Aluno *value) {
    if (node != NULL) {
        node = insertNodeArvoreAvl(node, value);
    } else {
        node = readNode(value);
    }

    return node;
}

/*
 * Apaga um Node de acordo com uma chave (key).
 * */
Node *removeNodeArvoreAvl(Node *node, char *key) {
    if (node == NULL) {
        printf(ERROR_REGISTRO_NAO_ENCONTRADO);
        return NULL;
    }

    int compare = compareNodeByKey(node, key);

    if (compare > 0) {
        node->left = removeNodeArvoreAvl(node->left, key);
        updateChargeFactor(node);
        removeBalanceAvlLeft(node);
    } else if (compare < 0) {
        node->right = removeNodeArvoreAvl(node->right, key);
        updateChargeFactor(node);
        removeBalanceAvlRight(node);
    } else {
        if (node->left == NULL && node->right == NULL) {
            node = removeNodeZeroChildrenArvoreAvl(node);
        } else if (node->left == NULL || node->right == NULL) {
            node = removeNodeOneChildrenArvoreAvl(node);
        } else {
            node = removeNodeTwoChildrenArvoreAvl(node, key);
        }
        updateAllChargeFactor(node);
    }

    return node;
}

/*
 * Apaga um Node que não possua qualquer filho
 * */
Node *removeNodeZeroChildrenArvoreAvl(Node *node) {
    free(node);
    return NULL;
}

/*
 * Apaga um Node que possua um e apenas um filho
 * */
Node *removeNodeOneChildrenArvoreAvl(Node *node) {
    Node *aux = node->left != NULL ? node->left : node->right;

    free(node);

    return aux;
}

/*
 * Apaga um Node que possua dois filhos
 * */
Node *removeNodeTwoChildrenArvoreAvl(Node *node, char *key) {
    Node *aux = node->left;
    Aluno *value = node->value;

    while (aux->right != NULL) {
        aux = aux->right;
    }

    node->value = aux->value;
    aux->value = value;
    node->left = removeNodeArvoreAvl(node->left, key);

    return node;
}

/*
 * Insere o valor de um Node e de seus filhos numa ArvoreAvl.
 * */
void cloneNodeIntoArvoreAvl(ArvoreAvl *target, Node *source) {
    if (source == NULL) {
        return;
    }

    insertArvoreAvl(target, source->value);
    cloneNodeIntoArvoreAvl(target, source->left);
    cloneNodeIntoArvoreAvl(target, source->right);
}

// =-=-=-=-= METODOS PUBLICOS =-=-=-=-=

/*
 * Inicializa e retorna uma nova instância de ArvoreAvl.
 * */
ArvoreAvl *newArvoreAvl(char *label) {
    ArvoreAvl *arvoreAvl = (ArvoreAvl *) malloc(sizeof(ArvoreAvl));

    if (arvoreAvl == NULL) {
        printf(ERROR_FALHA_ALOCACAO);
        return NULL;
    }

    arvoreAvl->label = label;
    arvoreAvl->root = NULL;

    return arvoreAvl;
}

/*
 * Insere um novo registro numa ArvoreAvl.
 * */
void insertArvoreAvl(ArvoreAvl *arvoreAvl, Aluno *value) {
    if (arvoreAvl->root == NULL) {
        return insertRootArvoreAvl(arvoreAvl, value);
    }
    arvoreAvl->root = insertNodeArvoreAvl(arvoreAvl->root, value);
}

/*
 * Busca um registro na ArvoreAvl de acordo com uma chave (key).
 *
 * Se encontrar, retorna os dados do registro.
 * Se não, retorna NULL.
 * */
Aluno *searchArvoreAvl(ArvoreAvl *arvoreAvl, char *key) {
    if (arvoreAvl->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return NULL;
    }
    return searchNode(arvoreAvl->root, key);
}

/*
 * Busca um registro na ArvoreAvl e imprime os seguintes dados sobre ele:
 *
 * - Os dados do registro;
 * - O número de registros que foram veríficados antes do alvo ser encontrado.
 * */
void findAndPrintArvoreAvl(ArvoreAvl *arvoreAvl, char *key) {
    if (arvoreAvl->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return;
    }
    findAndPrintNode(arvoreAvl->root, key, 0);
}

/*
 * Remove um registro da ArvoreAvl de acordo com uma chave (key).
 * */
void removeArvoreAvl(ArvoreAvl *arvoreAvl, char *key) {
    if (arvoreAvl->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return;
    }
    arvoreAvl->root = removeNodeArvoreAvl(arvoreAvl->root, key);
}

/*
 * Calcula e retorna a altura de uma ArvoreAvl com base no seus filho.
 * O valor inicial é 0, então uma ArvoreAvl com apenas um Node retornará 0.
 * Caso a ArvoreAvl não possua qualquer registro, retorna -1
 * */
int getHeightArvoreAvl(ArvoreAvl *arvoreAvl) {
    if (arvoreAvl->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
    }
    return getHeightNode(arvoreAvl->root);
}

/*
 * Calcula e retorna a quantidade de registros numa ArvoreAvl.
 * */
int getSizeArvoreAvl(ArvoreAvl *arvoreAvl) {
    if (arvoreAvl->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
    }
    return getSizeNode(arvoreAvl->root);
}

/*
 * Retorna o maior registro numa ArvoreAvl.
 * */
Aluno *getMaxArvoreAvl(ArvoreAvl *arvoreAvl) {
    if (arvoreAvl->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return NULL;
    }
    return getMaxNode(arvoreAvl->root);
}

/*
 * Retorna o menor registro numa ArvoreAvl.
 * */
Aluno *getMinArvoreAvl(ArvoreAvl *arvoreAvl) {
    if (arvoreAvl->root == NULL) {
        printf(ERROR_ARVORE_VAZIA);
        return NULL;
    }
    return getMinNode(arvoreAvl->root);
}

/*
 * Remove todos os registros numa ArvoreAvl
 * */
void clearArvoreAvl(ArvoreAvl *arvoreAvl) {
    if (arvoreAvl->root == NULL) {
        return;
    }

    clearNode(arvoreAvl->root);
    arvoreAvl->root = NULL;
}

/*
 * Lê todos os registros da ArvoreAvl 'source' e os insere na ArvoreAvl 'target'.
 * */
void cloneArvoreAvl(ArvoreAvl *target, ArvoreAvl *source) {
    cloneNodeIntoArvoreAvl(target, source->root);
}

/*
 * Imprime uma ArvoreAvl.
 * Imprime os registros dela com ordenação "Em-Ordem Crescente"
 * */
void printArvoreAvlInOrderAsc(ArvoreAvl *arvoreAvl) {
    printf("\n%s\n", arvoreAvl->label);
    printNodeInOrderAsc(arvoreAvl->root);
}

/*
 * Imprime uma ArvoreAvl.
 * Imprime os registros dela com ordenação "Em-Ordem Decrescente"
 * */
void printArvoreAvlInOrderDesc(ArvoreAvl *arvoreAvl) {
    printf("\n%s\n", arvoreAvl->label);
    printNodeInOrderDesc(arvoreAvl->root);
}

/*
 * Imprime uma ArvoreAvl.
 * Imprime os registros dela com ordenação "Pré-Ordem"
 * */
void printArvoreAvlPreOrder(ArvoreAvl *arvoreAvl) {
    printf("\n%s\n", arvoreAvl->label);
    printNodePreOrder(arvoreAvl->root);
}

/*
 * Imprime uma ArvoreAvl.
 * Imprime os registros dela com ordenação "Pós-Ordem"
 * */
void printArvoreAvlPostOrder(ArvoreAvl *arvoreAvl) {
    printf("\n%s\n", arvoreAvl->label);
    printNodePostOrder(arvoreAvl->root);
}

/*
 * Imprime os seguintes dados de uma ArvoreAvl:
 *
 * - Nome;
 * - Altura;
 * - Número de registros.
 * */
void printStatisticsArvoreAvl(ArvoreAvl *arvoreAvl) {
    printf("\n%s", arvoreAvl->label);
    printf("\nAltura: %d", getHeightArvoreAvl(arvoreAvl));
    printf("\nTamanho: %d", getSizeArvoreAvl(arvoreAvl));
}
