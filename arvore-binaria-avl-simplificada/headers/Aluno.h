#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ARVORE_BINARIA_AVL_ALUNO_H
#define ARVORE_BINARIA_AVL_ALUNO_H

typedef struct Aluno {
    char *matricula;
    char *nome;
    float nota;
} Aluno;

Aluno *newAluno();

Aluno *readAluno();

int compareAlunoByKey(Aluno *aluno, char *key);

int compareAluno(Aluno *aluno1, Aluno *aluno2);

void printAluno(Aluno *aluno);

#endif //ARVORE_BINARIA_AVL_ALUNO_H
