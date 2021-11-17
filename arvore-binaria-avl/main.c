#include <stdio.h>

#include "headers/Aluno.h"
#include "headers/ArvoreAvl.h"
#include "headers/ControleArquivoAluno.h"

int menu() {
    int choice = 0;

    printf("\n\n=============== MENU ===============\n");
    printf("\n1 - Inserir");
    printf("\n2 - Recuperar");
    printf("\n3 - Busca e Imprimir");
    printf("\n4 - Remover");
    printf("\n5 - Altura");
    printf("\n6 - Tamanho");
    printf("\n7 - Maior");
    printf("\n8 - Menor");
    printf("\n9 - Limpar");
    printf("\n10 - Estatística");
    printf("\n11 - Listar Em Ordem ASC");
    printf("\n12 - Listar Em Ordem DES");
    printf("\n13 - Listar Pré-Ordem");
    printf("\n14 - Listar Pós-Ordem");
    printf("\n15 - Clone");
    printf("\n0 - Sair");

    printf("\nESCOLHA: ");
    scanf(" %d", &choice);

    return choice;
}

int main() {
    ArvoreAvl *arvoreAvl = newArvoreAvl("ArvoreAvl");
    ArvoreAvl *clone = newArvoreAvl("Clone");
    char *key = (char *) malloc(64 * sizeof(char));
    int repeat = 1;

    while (repeat) {
        switch (menu()) {
            case 0:
                repeat = 0;
                break;
            case 1:
                insertArvoreAvl(arvoreAvl, readAluno());
                break;
            case 2:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                printf("\nSAÍDA: ");
                printAluno(searchArvoreAvl(arvoreAvl, key));
                break;
            case 3:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                printf("\nSAÍDA: ");
                findAndPrintArvoreAvl(arvoreAvl, key);
                break;
            case 4:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                removeArvoreAvl(arvoreAvl, key);
                break;
            case 5:
                printf("SAÍDA: %d", getHeightArvoreAvl(arvoreAvl));
                break;
            case 6:
                printf("SAÍDA: %d", getSizeArvoreAvl(arvoreAvl));
                break;
            case 7:
                printf("\nSAÍDA: ");
                printAluno(getMaxArvoreAvl(arvoreAvl));
                break;
            case 8:
                printf("\nSAÍDA: ");
                printAluno(getMinArvoreAvl(arvoreAvl));
                break;
            case 9:
                clearArvoreAvl(arvoreAvl);
                break;
            case 10:
                printStatisticsArvoreAvl(arvoreAvl);
                printStatisticsArvoreAvl(clone);
                break;
            case 11:
                printArvoreAvlInOrderAsc(arvoreAvl);
                printArvoreAvlInOrderAsc(clone);
                break;
            case 12:
                printArvoreAvlInOrderDesc(arvoreAvl);
                printArvoreAvlInOrderDesc(clone);
                break;
            case 13:
                printArvoreAvlPreOrder(arvoreAvl);
                printArvoreAvlPreOrder(clone);
                break;
            case 14:
                printArvoreAvlPostOrder(arvoreAvl);
                printArvoreAvlPostOrder(clone);
                break;
            case 15:
                cloneArvoreAvl(clone, arvoreAvl);
                break;
            default:
                break;
        }
    }

    clearArvoreAvl(arvoreAvl);
    free(arvoreAvl);
    return 0;
}
