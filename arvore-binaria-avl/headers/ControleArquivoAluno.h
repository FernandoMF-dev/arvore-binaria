#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Aluno.h"
#include "Node.h"
#include "ArvoreBinaria.h"
#include "ArvoreAvl.h"

#ifndef ARVORE_BINARIA_AVL_CONTROLEARQUIVOALUNO_H
#define ARVORE_BINARIA_AVL_CONTROLEARQUIVOALUNO_H

ArvoreBinaria *readAlunoFromFile(ArvoreBinaria *arvoreBinaria, ArvoreAvl *arvoreAvl);

void writeArvoreBinariaOnFile(ArvoreBinaria *arvoreBinaria);

void writeArvoreAvlOnFile(ArvoreAvl *arvoreAvl);

#endif //ARVORE_BINARIA_AVL_CONTROLEARQUIVOALUNO_H
