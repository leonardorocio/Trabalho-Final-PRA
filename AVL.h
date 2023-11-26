#ifndef AVL_STDIO_H
#define AVL_STDIO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct noAVL {
    struct noAVL* pai;
    struct noAVL* esquerda;
    struct noAVL* direita;
    int valor;
} NoAVL;

typedef struct arvoreAVL {
    struct noAVL* raiz;
} ArvoreAVL;

void balanceamento(ArvoreAVL*, NoAVL*);
int altura(NoAVL*);
int fb(NoAVL*);
void removerAVL(ArvoreAVL*, int);
ArvoreAVL* criarAVL();
NoAVL* localizar(NoAVL*, int);
NoAVL* sucessorInOrder(NoAVL*);
void percorrerAVL(NoAVL*);
NoAVL* adicionarAVL(ArvoreAVL*, int);
NoAVL* rsd(ArvoreAVL*, NoAVL*);
NoAVL* rse(ArvoreAVL*, NoAVL*);
NoAVL* rdd(ArvoreAVL*, NoAVL*);
NoAVL* rde(ArvoreAVL*, NoAVL*);

#endif