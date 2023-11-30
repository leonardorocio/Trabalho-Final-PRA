#include "AVL.h"
#include "BTree.h"
#include "RBTree.h"
#include "time.h"

extern int contadorAVL;
extern int contadorRBTree;
extern int contadorBTree;

int* geraVetor(int n) {
    srand(time(0));
    int* v = malloc(sizeof(int) * n);
    int i;

    for (i = 0; i < n; i++) {
        v[i] = rand();
    }

    return v;
}

int arvoreAVL(int *valores, int tamanho) {
    contadorAVL = 0;
    ArvoreAVL *avl = criarAVL();
    int i;
    for (i = 0; i < tamanho; i++) {
        NoAVL* no = adicionarAVL(avl, valores[i]);
    }
    contadorAVL = 0;
    for (i = 0; i < tamanho; i++) {
        removerAVLChave(avl, avl->raiz, valores[i]);
    }
    return 0;
}

int arvoreRB(int *valores, int tamanho) {
    contadorRBTree = 0;
    ArvoreRB *rbtree = criar();
    int i;
    NoRB* nosAdicionados[tamanho];
    for (i = 0; i < tamanho; i++) {
        NoRB* no = adicionarRB(rbtree, valores[i]);
    }
    contadorRBTree = 0;
    for (i = 0; i < tamanho; i++) {
        removerRB(rbtree, rbtree->raiz,valores[i]);
    }
    return 0;
}

int arvoreBOrdemUm(int *valores, int tamanho) {
    ArvoreB *btreeOne = criaArvore(1);
}

int arvoreBOrdemCinco(int *valores, int tamanho) {
    ArvoreB *btreeFive = criaArvore(5);
}

int arvoreBOrdemDez(int *valores, int tamanho) {
    ArvoreB *btreeTen = criaArvore(10);
}

int main(int argc, char const *argv[]) {
    int n = 10000;
    
    int i, valor, repeticoes = 1;

    int mediaAVL = 0;
    int mediaRubroNegra = 0;
    int mediaBtreeOne = 0;
    int mediaBtreeFive = 0;
    int mediaBtreeTen = 0;

    for (i = 0; i < repeticoes; i++) {
        int *valores = geraVetor(n);
        // mediaAVL += arvoreAVL(valores, n);
        mediaRubroNegra += arvoreRB(valores, n);
        mediaBtreeOne += arvoreBOrdemUm(valores, n);
        mediaBtreeFive += arvoreBOrdemCinco(valores, n);
        mediaBtreeTen += arvoreBOrdemDez(valores, n);    
    }

    mediaAVL /= repeticoes;
    mediaRubroNegra /= repeticoes;
    mediaBtreeOne /= repeticoes;
    mediaBtreeFive /= repeticoes;
    mediaBtreeTen /= repeticoes;
    return 0;
}
