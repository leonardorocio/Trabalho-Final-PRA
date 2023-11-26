#ifndef BTREE_STDIO_H
#define BTREE_STDIO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct noB
{
    int total;
    int *chaves;
    struct noB **filhos;
    struct noB *pai;
} NoB;

typedef struct arvoreB
{
    NoB *raiz;
    int ordem;
} ArvoreB;

ArvoreB *criaArvore(int);
NoB *criaNoB(ArvoreB *);
void percorreArvore(NoB *);
int pesquisaBinaria(NoB *, int);
int localizaChave(ArvoreB *, int);
NoB *localizaNoB(ArvoreB *, int);
void adicionaChaveNoB(NoB *, NoB *, int);
int transbordo(ArvoreB *, NoB *);
NoB *divideNoB(ArvoreB *, NoB *);
void adicionaChaveRecursivo(ArvoreB *, NoB *, NoB *, int);
void adicionaChave(ArvoreB *, int);
#endif