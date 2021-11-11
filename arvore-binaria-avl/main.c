#include <stdio.h>

#include "headers/Aluno.h"
#include "headers/ArvoreBinaria.h"
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
//    ArvoreBinaria *arvoreBinaria = readAlunoFromFile(newArvoreBinaria("ArvoreBinaria"));
    ArvoreBinaria *arvoreBinaria = newArvoreBinaria("ArvoreBinaria");
    ArvoreBinaria *clone = newArvoreBinaria("Clone");
    char *key = (char *) malloc(64 * sizeof(char));
    int repeat = 1;

    while (repeat) {
        switch (menu()) {
            case 0:
                writeArvoreBinariaOnFile(arvoreBinaria);
                writeArvoreBinariaOnFile(clone);
                repeat = 0;
                break;
            case 1:
                insertArvoreBinaria(arvoreBinaria, readAluno());
                break;
            case 2:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                printf("\nSAÍDA: ");
                printAluno(searchArvoreBinaria(arvoreBinaria, key));
                break;
            case 3:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                printf("\nSAÍDA: ");
                findAndPrintArvoreBinaria(arvoreBinaria, key);
                break;
            case 4:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                removeArvoreBinaria(arvoreBinaria, key);
                break;
            case 5:
                printf("SAÍDA: %d", getHeightArvoreBinaria(arvoreBinaria));
                break;
            case 6:
                printf("SAÍDA: %d", getSizeArvoreBinaria(arvoreBinaria));
                break;
            case 7:
                printf("\nSAÍDA: ");
                printAluno(getMaxArvoreBinaria(arvoreBinaria));
                break;
            case 8:
                printf("\nSAÍDA: ");
                printAluno(getMinArvoreBinaria(arvoreBinaria));
                break;
            case 9:
                clearArvoreBinaria(arvoreBinaria);
                break;
            case 10:
                printStatisticsArvoreBinaria(arvoreBinaria);
                printStatisticsArvoreBinaria(clone);
                break;
            case 11:
                printArvoreBinariaInOrderAsc(arvoreBinaria);
                printArvoreBinariaInOrderAsc(clone);
                break;
            case 12:
                printArvoreBinariaInOrderDesc(arvoreBinaria);
                printArvoreBinariaInOrderDesc(clone);
                break;
            case 13:
                printArvoreBinariaPreOrder(arvoreBinaria);
                printArvoreBinariaPreOrder(clone);
                break;
            case 14:
                printArvoreBinariaPostOrder(arvoreBinaria);
                printArvoreBinariaPostOrder(clone);
                break;
            case 15:
                cloneArvoreBinaria(clone, arvoreBinaria);
                break;
            default:
                break;
        }
    }

    clearArvoreBinaria(arvoreBinaria);
    free(arvoreBinaria);
    return 0;
}
