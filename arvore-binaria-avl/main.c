#include <stdio.h>

#include "headers/Aluno.h"
#include "headers/ArvoreAvl.h"
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
    ArvoreAvl *arvoreAvl = newArvoreAvl("ArvoreAvl");
    ArvoreBinaria *arvoreBinaria = newArvoreBinaria("ArvoreBinaria");
    Aluno *aluno;
    char *key = (char *) malloc(64 * sizeof(char));
    int repeat = 1;

    if (arvoreAvl == NULL || arvoreBinaria == NULL || key == NULL) {
        return 0;
    }

    readAlunoFromFile(arvoreBinaria, arvoreAvl);

    while (repeat) {
        switch (menu()) {
            case 0:
                writeArvoreAvlOnFile(arvoreAvl);
                writeArvoreBinariaOnFile(arvoreBinaria);
                repeat = 0;
                break;
            case 1:
                aluno = readAluno();
                insertArvoreAvl(arvoreAvl, aluno);
                insertArvoreBinaria(arvoreBinaria, aluno);
                break;
            case 2:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                printf("\nSAÍDA: ");
                findAndPrintArvoreAvl(arvoreAvl, key);
                printf("\n");
                findAndPrintArvoreBinaria(arvoreBinaria, key);
                break;
            case 3:
                printf("\nENTRADA: ");
                scanf(" %[^\n]s", key);
                removeArvoreAvl(arvoreAvl, key);
                removeArvoreBinaria(arvoreBinaria, key);
                break;
            case 4:
                printStatisticsArvoreAvl(arvoreAvl);
                printf("\n");
                printStatisticsArvoreBinaria(arvoreBinaria);
                break;
            default:
                break;
        }
    }

    clearArvoreAvl(arvoreAvl);
    clearArvoreBinaria(arvoreBinaria);
    free(arvoreAvl);
    free(arvoreBinaria);
    return 0;
}
