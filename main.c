#include "AVL.h"
#include "RBTree.h"
#include "time.h"
#include "btree.h"


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

    if (keyA < keyB) {
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

    while (low < high) {
        unsigned int mid = low + (high - low) / 2;
        const struct test_item *midItem = (const struct test_item *)base[mid];

        // Compare the key with the middle item
        int cmp = compareTestItem(key, midItem);

        if (cmp < 0) {
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
    printf("%s", avl->raiz == NULL ? "Finalizado AVL com sucesso\n" : "Erro!");
    return 0;
}

int arvoreRB(int *valores, int tamanho) {
    contadorRBTree = 0;
    ArvoreRB *rbtree = criar();
    int i;
    for (i = 0; i < tamanho; i++) {
        NoRB* no = adicionarRB(rbtree, valores[i]);
    }
    contadorRBTree = 0;
    for (i = 0; i < tamanho; i++) {
        removerRB(rbtree, valores[i]);
    }
    printf("%s", rbtree->raiz == rbtree->nulo ? "Finalizado RB com sucesso\n" : "Erro!");
    return 0;
}

int arvoreBOrdemUm(int *valores, int tamanho) {
    max_items = 2;
    int i;
    struct test_item chave_valor[tamanho];
    struct btree *tree = btree_new(binarySearchTestItem);
    // Copiando os valores gerados aleatoriamente pra dentro do array de struct chave valor
    for (i = 0; i < tamanho; chave_valor[i].key = valores[i], chave_valor[i].value = valores[i], i++);
    
    for (i = 0; i < tamanho; i++) {
        btree_insert(tree, &chave_valor[i]);
        void *test = btree_lookup(tree, &chave_valor[i].key);
        if (test != NULL) {
            // printf("Adicionado com sucesso!\n");
        }
    }

    for (i = 0; i < tamanho; i++) {
        bool removed = btree_remove(tree, &chave_valor[i].key);
        if (removed) {
            // printf("Removido com sucesso!\n");
        }
    }
    printf("Finalizado com sucesso BTree 1\n");
}

int arvoreBOrdemCinco(int *valores, int tamanho) {
    // Pra usar com ordem 5, dado que max_items / 2 = ordem = mínimo 
    max_items = 10;
    int i;
    struct test_item chave_valor[tamanho];
    struct btree *tree = btree_new(binarySearchTestItem);
    // Copiando os valores gerados aleatoriamente pra dentro do array de struct chave valor
    for (i = 0; i < tamanho; chave_valor[i].key = valores[i], chave_valor[i].value = valores[i], i++);
    
    for (i = 0; i < tamanho; i++) {
        btree_insert(tree, &chave_valor[i]);
        void *test = btree_lookup(tree, &chave_valor[i].key);
        // if (test != NULL) {
        //     printf("Adicionado com sucesso!\n");
        // }
    }

    for (i = 0; i < tamanho; i++) {
        bool removed = btree_remove(tree, &chave_valor[i].key);
        // if (removed) {
        //     printf("Removido com sucesso!\n");
        // }
    }
    printf("Finalizado com sucesso BTree 5\n");
}

int arvoreBOrdemDez(int *valores, int tamanho) {
    // Pra usar com ordem 10, dado que max_items / 2 = ordem = mínimo 
    max_items = 20;
    int i;
    // Cada item tem uma chave e um valor
    struct test_item chave_valor[tamanho];
    struct btree *tree = btree_new(binarySearchTestItem);
    // Copiando os valores gerados aleatoriamente pra dentro do array de struct chave valor
    for (i = 0; i < tamanho; chave_valor[i].key = valores[i], chave_valor[i].value = valores[i], i++);
    
    for (i = 0; i < tamanho; i++) {
        btree_insert(tree, &chave_valor[i]);
        void *test = btree_lookup(tree, &chave_valor[i].key);
        // if (test != NULL) {
        //     printf("Adicionado com sucesso!\n");
        // }
    }

    for (i = 0; i < tamanho; i++) {
        bool removed = btree_remove(tree, &chave_valor[i].key);
        // if (removed) {
        //     printf("Removido com sucesso!\n");
        // }
    }
    printf("Finalizado com sucesso BTree 10\n");
}

int main(int argc, char const *argv[]) {
    int n = 10000;
    
    int i, valor, repeticoes = 10;

    int mediaAVL = 0;
    int mediaRubroNegra = 0;
    int mediaBtreeOne = 0;
    int mediaBtreeFive = 0;
    int mediaBtreeTen = 0;

    for (i = 0; i < repeticoes; i++) {
        int *valores = geraVetor(n);
        // mediaAVL += arvoreAVL(valores, n);
        mediaRubroNegra += arvoreRB(valores, n);
        // mediaBtreeOne += arvoreBOrdemUm(valores, n);
        // mediaBtreeFive += arvoreBOrdemCinco(valores, n);
        // mediaBtreeTen += arvoreBOrdemDez(valores, n);    
    }

    mediaAVL /= repeticoes;
    mediaRubroNegra /= repeticoes;
    mediaBtreeOne /= repeticoes;
    mediaBtreeFive /= repeticoes;
    mediaBtreeTen /= repeticoes;
    return 0;
}
