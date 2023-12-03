#include "AVL.h"
#include "BTree.h"
#include "RBTree.h"
#include "time.h"

#define TAM_CONJUNTOS 10000
#define QTDE_DE_CONJUNTOS 10
#define QTDE_TIPOS_DE_ARVORES 5

#define AVL 0
#define RB 1
#define B_ONE 2
#define B_FIVE 3
#define B_TEN 4

struct test_item {
	int key;
	int value;
};

// Essa variável serve pra passar pro arquivo btree.c quanto que vai ser o máximo de chaves por nó
// Pra iniciar com ordem 1, dado que max_items / 2 = ordem = mínimo
int max_items = 2;
extern unsigned long contadorAVL;
extern unsigned long contadorRBTree;
extern unsigned long contadorBTree;

// Função de comparação para a struct test_item
int compareTestItem(const void *a, const void *b) {
    int keyA = ((const struct test_item *)a)->key;
    int keyB = ((const struct test_item *)b)->key;

    contadorBTree += 2;
    if (keyA < keyB) {
        contadorBTree--;
        return -1;
    } else if (keyA > keyB) {
        return 1;
    } else {
        return 0;
    }
}

// A BTree utilizada precisa de uma função de busca binária com essa assinatura para funcionar
unsigned int binarySearchTestItem(
    const void *key,
    const void * const *base,
    unsigned int count,
    int lr,
    int *found
) {
    unsigned int low = 0;
    unsigned int high = count;

    contadorBTree++;
    while (low < high) {
        unsigned int mid = low + (high - low) / 2;
        const struct test_item *midItem = (const struct test_item *)base[mid];

        // Compare the key with the middle item
        int cmp = compareTestItem(key, midItem);

        contadorBTree += 2;
        if (cmp < 0) {
            contadorBTree--;
            high = mid; // Key is in the left half
            lr = -1;    // Indicate left search
        } else if (cmp > 0) {
            low = mid + 1; // Key is in the right half
            lr = 1;        // Indicate right search
        } else {
            *found = 1; // Key found at position mid
            return mid;
        }
    }

    // Key not found, return the position where it should be inserted
    *found = 0;
    return low;
}

int compare(const void *a, const void *b, void* udata) {
    return *((int*) a) - *((int*) b);
}

int dadosAdicao[TAM_CONJUNTOS][QTDE_TIPOS_DE_ARVORES];
int dadosRemocao[TAM_CONJUNTOS][QTDE_TIPOS_DE_ARVORES];

void criarCsv(int matrizArvores[TAM_CONJUNTOS][QTDE_TIPOS_DE_ARVORES], int tam, char *nomeRelatorio) {

    FILE *arquivo;
    arquivo = fopen(nomeRelatorio, "w"); // Abre o arquivo para escrita

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
    }

    fprintf(arquivo, "AVL,RB,B ONE,B FIVE,B TEN\n");

    int linha;
    for (linha = 0; linha < TAM_CONJUNTOS; linha++) {
        fprintf(arquivo, "%ul,%ul,%ul,%ul,%ul\n", matrizArvores[linha][AVL], matrizArvores[linha][RB], matrizArvores[linha][B_ONE], matrizArvores[linha][B_FIVE], matrizArvores[linha][B_TEN]);
    }

    fclose(arquivo);

    printf("Arquivo CSV criado com sucesso\n");
}

int* geraVetor(int n) {
    srand(time(0));
    int* v = malloc(sizeof(int) * n);
    int i;

    for (i = 0; i < n; i++) {
        v[i] = rand();
    }

    return v;
}

void arvoreAVL(int *valores, int tamanho) {
    contadorAVL = 0;
    ArvoreAVL *avl = criarAVL();
    int i;
    for (i = 0; i < tamanho; i++) {
        NoAVL* no = adicionarAVL(avl, valores[i]);
        dadosAdicao[i][AVL] += contadorAVL;
        contadorAVL = 0;
    }
    contadorAVL = 0;
    for (i = 0; i < tamanho; i++) {
        removerAVLChave(avl, avl->raiz, valores[i]);
        dadosRemocao[i][AVL] += contadorAVL;
        contadorAVL = 0;
    }
}

void arvoreRB(int *valores, int tamanho) {
    contadorRBTree = 0;
    ArvoreRB *rbtree = criar();
    int i;
    for (i = 0; i < tamanho; i++) {
        NoRB* no = adicionarRB(rbtree, valores[i]);
        dadosAdicao[i][RB] += contadorRBTree;
        contadorRBTree = 0;
    }
    contadorRBTree = 0;
    for (i = 0; i < tamanho; i++) {
        removerRB(rbtree, valores[i]);
        dadosRemocao[i][RB] += contadorRBTree;
        contadorRBTree = 0;
    }
}

void arvoreBOrdemUm(int *valores, int tamanho) {
    contadorBTree = 0;
    int i;
    struct test_item chave_valor[tamanho];
    struct btree *tree = btree_new(binarySearchTestItem);
    // Copiando os valores gerados aleatoriamente pra dentro do array de struct chave valor
    for (i = 0; i < tamanho; chave_valor[i].key = valores[i], chave_valor[i].value = valores[i], i++);
    for (i = 0; i < tamanho; i++) {
        btree_insert(tree, &chave_valor[i]);
        dadosAdicao[i][B_ONE] += contadorBTree;
        contadorBTree = 0;
    }
    contadorBTree = 0;
    for (i = 0; i < tamanho; i++) {
        btree_remove(tree, &chave_valor[i].key);
        dadosRemocao[i][B_ONE] += contadorBTree;
        contadorBTree = 0;
    }

}

void arvoreBOrdemCinco(int *valores, int tamanho) {
    contadorBTree = 0;
    // Pra usar com ordem 5, dado que max_items / 2 = ordem = mínimo
    max_items = 10;
    int i;
    struct test_item chave_valor[tamanho];
    struct btree *tree = btree_new(binarySearchTestItem);
    // Copiando os valores gerados aleatoriamente pra dentro do array de struct chave valor
    for (i = 0; i < tamanho; chave_valor[i].key = valores[i], chave_valor[i].value = valores[i], i++);

    for (i = 0; i < tamanho; i++) {
        btree_insert(tree, &chave_valor[i]);
        dadosAdicao[i][B_FIVE] += contadorBTree;
        contadorBTree = 0;
    }

    contadorBTree = 0;
    for (i = 0; i < tamanho; i++) {
        btree_remove(tree, &chave_valor[i].key);
        dadosRemocao[i][B_FIVE] += contadorBTree;
        contadorBTree = 0;
    }
}

void arvoreBOrdemDez(int *valores, int tamanho) {
    contadorBTree = 0;
    // Pra usar com ordem 10, dado que max_items / 2 = ordem = mínimo
    max_items = 20;
    int i;
    struct test_item chave_valor[tamanho];
    struct btree *tree = btree_new(binarySearchTestItem);
    // Copiando os valores gerados aleatoriamente pra dentro do array de struct chave valor
    for (i = 0; i < tamanho; chave_valor[i].key = valores[i], chave_valor[i].value = valores[i], i++);

    for (i = 0; i < tamanho; i++) {
        btree_insert(tree, &chave_valor[i]);
        dadosAdicao[i][B_TEN] += contadorBTree;
        contadorBTree = 0;
    }

    contadorBTree = 0;
    for (i = 0; i < tamanho; i++) {
        btree_remove(tree, &chave_valor[i].key);
        dadosRemocao[i][B_TEN] += contadorBTree;
        contadorBTree = 0;
    }
}

int main(int argc, char const *argv[]) {

    int i, valor;

    int lin, col;
    for (lin = 0; lin < TAM_CONJUNTOS; lin++) {
        for (col = 0; col < QTDE_TIPOS_DE_ARVORES; col++) {
            dadosAdicao[lin][col] = 0;
            dadosRemocao[lin][col] = 0;
        }
    }

    for (i = 0; i < QTDE_DE_CONJUNTOS; i++) {
        int *valores = geraVetor(TAM_CONJUNTOS);
        arvoreAVL(valores, TAM_CONJUNTOS);
        arvoreRB(valores, TAM_CONJUNTOS);
        arvoreBOrdemUm(valores, TAM_CONJUNTOS);
        arvoreBOrdemCinco(valores, TAM_CONJUNTOS);
        arvoreBOrdemDez(valores, TAM_CONJUNTOS);
    }

    for (i = 0; i < TAM_CONJUNTOS; i++) {
        dadosAdicao[i][AVL] = dadosAdicao[i][AVL] / QTDE_DE_CONJUNTOS;
        dadosAdicao[i][RB] = dadosAdicao[i][RB] / QTDE_DE_CONJUNTOS;
        dadosAdicao[i][B_ONE] = dadosAdicao[i][B_ONE] / QTDE_DE_CONJUNTOS;
        dadosAdicao[i][B_FIVE] = dadosAdicao[i][B_FIVE] / QTDE_DE_CONJUNTOS;
        dadosAdicao[i][B_TEN] = dadosAdicao[i][B_TEN] / QTDE_DE_CONJUNTOS;

        dadosRemocao[i][AVL] = dadosRemocao[i][AVL] / QTDE_DE_CONJUNTOS;
        dadosRemocao[i][RB] = dadosRemocao[i][RB] / QTDE_DE_CONJUNTOS;
        dadosRemocao[i][B_ONE] = dadosRemocao[i][B_ONE] / QTDE_DE_CONJUNTOS;
        dadosRemocao[i][B_FIVE] = dadosRemocao[i][B_FIVE] / QTDE_DE_CONJUNTOS;
        dadosRemocao[i][B_TEN] = dadosRemocao[i][B_TEN] / QTDE_DE_CONJUNTOS;
    }

    criarCsv(dadosAdicao, TAM_CONJUNTOS, "Relatório Adições.csv");
    criarCsv(dadosRemocao, TAM_CONJUNTOS, "Relatório Remoções.csv");

    return 0;
}
