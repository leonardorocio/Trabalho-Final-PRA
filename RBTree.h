#ifndef RBTREE_STDIO_H
#define RBTREE_STDIO_H

#include <stdlib.h>
#include <stdio.h>

enum coloracao
{
    Vermelho,
    Preto
};
typedef enum coloracao Cor;

typedef struct no
{
    struct no *pai;
    struct no *esquerda;
    struct no *direita;
    Cor cor;
    int valor;
} NoRB;

typedef struct arvore
{
    struct no *raiz;
    struct no *nulo;
} ArvoreRB;

NoRB *criarNoRB(ArvoreRB *, NoRB *, int);
void balancear(ArvoreRB *, NoRB *);
NoRB* rotacionarEsquerda(ArvoreRB *, NoRB *);
NoRB* rotacionarDireita(ArvoreRB *, NoRB *);
ArvoreRB *criar();
int vaziaRB(ArvoreRB *);
// void removerRB(ArvoreRB*, NoRB*, int);
void removerBalanceado(ArvoreRB* arvore, int chave);
void removerRB(ArvoreRB*, int);
NoRB* resolveCasosBalanceamento(ArvoreRB*, NoRB*);
NoRB* adicionarRB(ArvoreRB *, int);
void percorrerProfundidadeInOrder(ArvoreRB* arvore, NoRB* no);
NoRB* localizarRB(ArvoreRB *arvore, int valor);
#endif