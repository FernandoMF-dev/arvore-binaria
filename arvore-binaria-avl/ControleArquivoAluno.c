#include "headers/ControleArquivoAluno.h"

// =-=-=-=-= CONSTANTES =-=-=-=-=

#define ERROR_FALHA_ALOCACAO "\n\tERRO: Erro durante alocação de memória!\n"
#define ERRO_ABRIR_ARQUIVO "\n\tERRO: Erro na abertura do arquivo!\n"

#define MENSSAGE_LENDO_ARQUIVO "\n\tAVISO: Lendo arquivo, por favor aguarde...\n"
#define MENSSAGE_SALVANDO_ARQUIVO "\n\tAVISO: Salvando arquivo, por favor aguarde...\n"

#define DIRETORIO_ARQUIVO_ENTRADA "../../Entrada/forcado700000.txt"
#define DIRETORIO_ARQUIVO_SAIDA "../saida/"

#define LINE_MAX_LENGTH 255
#define FILE_NAME_MAX_LENGTH 31
#define DELIMITER ";"

// =-=-=-=-= METODOS PRIVADOS | DECLARAÇÃO =-=-=-=-=

Aluno *readNextAluno(FILE *fp);

void writeAlunosOnFile(FILE *fp, Node *node);

void writeCurrentAlunoOnFile(FILE *fp, Node *node);

// =-=-=-=-= METODOS PRIVADOS | IMPLEMENTAÇÃO =-=-=-=-=

/*
 * Lê a próxima linha do arquivo e preencha dados de Aluno
 * */
Aluno *readNextAluno(FILE *fp) {
    Aluno *aluno = newAluno();
    char *line = (char *) malloc((LINE_MAX_LENGTH + 1) * sizeof(char));
    char *ptr;

    fscanf(fp, " %[^\n]%*c", line);
    ptr = strtok(line, DELIMITER);
    strcpy(aluno->matricula, ptr);

    ptr = strtok(NULL, DELIMITER);
    strcpy(aluno->nome, ptr);

    ptr = strtok(NULL, DELIMITER);
    aluno->nota = (float) atof(ptr);

    free(line);

    return aluno;
}

/*
 * Escreve todos os alunos de uma ArvoreBinaria num arquivo
 * */
void writeAlunosOnFile(FILE *fp, Node *node) {
    if (node == NULL) {
        return;
    }

    writeAlunosOnFile(fp, node->left);
    writeCurrentAlunoOnFile(fp, node);
    writeAlunosOnFile(fp, node->right);
}

/*
 * Escreve um aluno num arquivo
 * */
void writeCurrentAlunoOnFile(FILE *fp, Node *node) {
    Aluno *value = node->value;
    fprintf(fp, "%s;%s;%.0f\n", value->matricula, value->nome, value->nota);
}

// =-=-=-=-= METODOS PÚBLICOS =-=-=-=-=

/*
 * Lê o arquivo na URL específicada e preenche as hash de acordo com seu o conteúdo
 * */
ArvoreBinaria *readAlunoFromFile(ArvoreBinaria *arvoreBinaria) {
    FILE *fp = fopen(DIRETORIO_ARQUIVO_ENTRADA, "r");
    int contador = 0;
    int registros;

    if (!fp) {
        printf(ERRO_ABRIR_ARQUIVO);
        return arvoreBinaria;
    }

    printf(MENSSAGE_LENDO_ARQUIVO);
    fscanf(fp, " %d", &registros);
    while (!feof(fp) && contador < registros) {
        Aluno *aluno = readNextAluno(fp);
        insertArvoreBinaria(arvoreBinaria, aluno);
        contador++;
    }

    fclose(fp);
    return arvoreBinaria;
}

/*
 * Cria um arquivo com os registros de uma hash
 * */
void writeArvoreBinariaOnFile(ArvoreBinaria *arvoreBinaria) {
    int nomeArquivoSaidaLength = strlen(DIRETORIO_ARQUIVO_SAIDA) + FILE_NAME_MAX_LENGTH + 1;
    char *nomeArquivoSaida = (char *) malloc(nomeArquivoSaidaLength * sizeof(char));
    FILE *fp;

    sprintf(nomeArquivoSaida, "%ssaida-%s.txt", DIRETORIO_ARQUIVO_SAIDA, arvoreBinaria->label);
    fp = fopen(nomeArquivoSaida, "w");
    if (!fp) {
        printf(ERRO_ABRIR_ARQUIVO);
        return;
    }

    printf(MENSSAGE_SALVANDO_ARQUIVO);
    writeAlunosOnFile(fp, arvoreBinaria->root);

    fclose(fp);
}