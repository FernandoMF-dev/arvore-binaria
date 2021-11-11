#include <stdio.h>

#include "headers/Aluno.h"
#include "headers/ArvoreBinaria.h"
#include "headers/ControleArquivoAluno.h"

int menu() {
    int choice = 0;

    printf("\n\n=============== MENU ===============\n");
    printf("\n1 - Inserir");
    printf("\n2 - Busca");
    printf("\n3 - Remover");
    printf("\n4 - Estatística");
    printf("\n0 - Sair");

    printf("\nESCOLHA: ");
    scanf(" %d", &choice);

    return choice;
}

int main() {
    ArvoreBinaria *arvoreBinaria = readAlunoFromFile(newArvoreBinaria("ArvoreBinaria"));
    char *key = (char *) malloc(64 * sizeof(char));
    int repeat = 1;

    while (repeat) {
        switch (menu()) {
            case 0:
                writeArvoreBinariaOnFile(arvoreBinaria);
                repeat = 0;
                break;
            case 1:
                insertArvoreBinaria(arvoreBinaria, readAluno());
                break;
            case 2:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                printf("\nSAÍDA: ");
                findAndPrintArvoreBinaria(arvoreBinaria, key);
                break;
            case 3:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                removeArvoreBinaria(arvoreBinaria, key);
                break;
            case 4:
                printStatisticsArvoreBinaria(arvoreBinaria);
                break;
            default:
                break;
        }
    }

    clearArvoreBinaria(arvoreBinaria);
    free(arvoreBinaria);
    return 0;
}
