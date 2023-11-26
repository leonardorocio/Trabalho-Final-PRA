#include "AVL.h"
#include "BTree.h"
#include "RBTree.h"
#include "time.h"

int* geraVetor(int n) {
    int* v = malloc(sizeof(int) * n);
    int i;

    for (i = 0; i < n; i++) {
        v[i] = rand() % n;
    }

    return v;
}

int arvoreAVL(int *valores, int tamanho) {
    ArvoreAVL *avl = criarAVL();
    int i;
    NoAVL* nosAdicionados[tamanho];
    for (i = 0; i < tamanho; i++) {
        NoAVL* no = adicionarAVL(avl, valores[i]);
        nosAdicionados[i] = no;
    }
    // removerAVL(avl, valores[0]);
    return 0;
}

int arvoreRB(int *valores, int tamanho) {
    ArvoreRB *rbtree = criar();
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
    srand(time(0));
    int n = 10000;
    int *valores = geraVetor(n);
    int i, valor, repeticoes = 1;

    int mediaAVL = 0;
    int mediaRubroNegra = 0;
    int mediaBtreeOne = 0;
    int mediaBtreeFive = 0;
    int mediaBtreeTen = 0;

    for (i = 0; i < repeticoes; i++) {
        mediaAVL += arvoreAVL(valores, n);
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
