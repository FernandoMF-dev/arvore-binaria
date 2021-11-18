CC = gcc
flags = -c -Wall
CFLAGS = -lm
ARQUIVOS = *.o
OBJS = ControleArquivoAluno.o ArvoreBinaria.o ArvoreAvl.o Node.o Aluno.o FuncaoUtils.o main.o
EXE = main
MAIN = main.c

all: main.o
	$(CC) $(OBJS) -o $(EXE) -lm
	./main

main.o: main.c ArvoreBinaria.o ArvoreAvl.o ControleArquivoAluno.o Aluno.o
	$(CC) $(flags) $(MAIN) $(CLFLAGS)

ControleArquivoAluno.o: ControleArquivoAluno.c ArvoreBinaria.o ArvoreAvl.o Node.o Aluno.o
	$(CC) $(flags) ControleArquivoAluno.c

ArvoreBinaria.o: ArvoreBinaria.c Node.o Aluno.o
	$(CC) $(flags) ArvoreBinaria.c

ArvoreAvl.o: ArvoreAvl.c Node.o Aluno.o
	$(CC) $(flags) ArvoreAvl.c

Node.o: Node.c FuncaoUtils.o Aluno.o
	$(CC) $(flags) Node.c

Aluno.o: Aluno.c
	$(CC) $(flags) Aluno.c

FuncaoUtils.o: FuncaoUtils.c
	$(CC) $(flags) FuncaoUtils.c

passos: main.c
	gcc -E main.c -o main.i
	gcc -S main.i -o main.s
	gcc -c main.s -o main.o
	gcc main.o ControleArquivoAluno.o ArvoreBinaria.o ArvoreAvl.o Node.o Aluno.o FuncaoUtils.o -o -lm main

run:
	./main

listar:
	ls $(ARQUIVOS)

clean:
	rm -f *.o *.i *.s
	rm -f $(EXE)