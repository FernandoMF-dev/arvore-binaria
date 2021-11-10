#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aluno.h"
#include "ArvoreBinaria.h"

#ifndef ARVORE_BINARIA_AVL_CONTROLEARQUIVOALUNO_H
#define ARVORE_BINARIA_AVL_CONTROLEARQUIVOALUNO_H

ArvoreBinaria *readAlunoFromFile(ArvoreBinaria *hash);

void writeArvoreBinariaOnFile(ArvoreBinaria *hash);

#endif //ARVORE_BINARIA_AVL_CONTROLEARQUIVOALUNO_H
