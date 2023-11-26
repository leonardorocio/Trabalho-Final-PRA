#include "AVL.h"

int contadorAVL = 0;

ArvoreAVL* criarAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
  
    return arvore;
}

int vaziaAVL(ArvoreAVL* arvore) {
    return arvore->raiz == NULL;
}

NoAVL* criarNoAVL(int valor) {
    NoAVL* no = malloc(sizeof(NoAVL));
    no->valor = valor;
    no->pai = NULL;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

NoAVL* adicionarNoAVL(NoAVL* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == NULL) {
            // printf("Adicionando %d\n",valor);
            NoAVL* novo = criarNoAVL(valor);
            novo->pai = no;
            no->direita = novo;
				
            return novo;
        } else {
            return adicionarNoAVL(no->direita, valor);
        }
    } else {
        if (no->esquerda == NULL) {
            // printf("Adicionando %d\n",valor);
            NoAVL* novo = criarNoAVL(valor);
			novo->pai = no;
			no->esquerda = novo;
			
            return novo;
        } else {
            return adicionarNoAVL(no->esquerda, valor);
        }
    }
}

NoAVL* adicionarAVL(ArvoreAVL* arvore, int valor) {
    if (arvore->raiz == NULL) {
        // printf("Adicionando %d\n",valor);
        NoAVL* novo = criarNoAVL(valor);
        arvore->raiz = novo;
        arvore->raiz->pai = NULL;
        return novo;
    } else {
        NoAVL* no = adicionarNoAVL(arvore->raiz, valor);
        balanceamento(arvore, no);
        return no;
    }
}

void balanceamento(ArvoreAVL* a, NoAVL* no) {
    while (no != NULL) {
        int fator = fb(no);

        if (fator > 1) { //arvore mais profunda a esquerda
            //rotacao a direita
            if (fb(no->esquerda) > 0) {
                // printf("RSD(%d)\n", no->valor);
                rsd(a, no);
            } else {
                // printf("RDD(%d)\n", no->valor);
                rdd(a, no);
            }
        } else if (fator < -1) {
            //rotacao a esquerda
            if (fb(no->direita) < 0) {
                // printf("RSE(%d)\n", no->valor);
                rse(a, no);
            } else {
                // printf("RDE(%d)\n", no->valor);
                rde(a, no);
            }
        }

        no = no->pai;
    }
}

void removerSimples(ArvoreAVL* arvore, NoAVL* no) {
    if (no->esquerda != NULL)
        removerSimples(arvore, no->esquerda);  
  
    if (no->direita != NULL)
        removerSimples(arvore, no->direita);
  
    if (no->pai == NULL) {
        arvore->raiz = no->esquerda != NULL ? no->esquerda : no->direita;
    } else {
        if (no->pai->esquerda == no) {
            no->pai->esquerda = NULL;
            balanceamento(arvore, no->pai->direita ? no->pai->direita : no->pai);
        }
        else {
            no->pai->direita = NULL;
            balanceamento(arvore, no->pai->esquerda ? no->pai->esquerda : no->pai);
        }
    }
    
    free(no);
}

void removerAVL(ArvoreAVL* arvore, int chave) {
    NoAVL *no = localizar(arvore->raiz, chave);
    if (no != NULL) {
        if (no->direita != NULL && no->esquerda != NULL) {
            NoAVL* sucessor = sucessorInOrder(no->direita);
            no->valor = sucessor->valor; 
            no = sucessor;
        }
    }

    removerSimples(arvore, no);
}

NoAVL* localizar(NoAVL* no, int valor) {
    if (no->valor == valor) {
        return no;
    } else {
        if (valor < no->valor) {
            if (no->esquerda != NULL) {
                return localizar(no->esquerda, valor);
            }
        } else {
            if (no->direita != NULL) {
                return localizar(no->direita, valor);
            }
        }
    }

    return NULL;
}

NoAVL* sucessorInOrder(NoAVL* no) {
    while(no->esquerda != NULL) {
        no = no->esquerda;
    }
    return no;
}

void percorrerAVL(NoAVL* no) {
    if (no != NULL) {
        percorrerAVL(no->esquerda);
        printf("%d ", no->valor);
        percorrerAVL(no->direita);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

int altura(NoAVL* no){
    int esquerda = 0,direita = 0;

    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb(NoAVL* no) {
    int esquerda = 0,direita = 0;
  
    if (no->esquerda != NULL) {
        esquerda = altura(no->esquerda) + 1;
    }

    if (no->direita != NULL) {
        direita = altura(no->direita) + 1;
    }
  
    return esquerda - direita;
}

NoAVL* rse(ArvoreAVL* arvore, NoAVL* no) {
    NoAVL* pai = no->pai;
    NoAVL* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    return direita;
}

NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no) {
    NoAVL* pai = no->pai;
    NoAVL* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    return esquerda;
}

NoAVL* rde(ArvoreAVL* arvore, NoAVL* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}



    // ArvoreAVL* a = criar();
    /*
    adicionar(a, 4);
    adicionar(a, 2);
    adicionar(a, 8);
    adicionar(a, 1);
    adicionar(a, 3);
    adicionar(a, 6);
    adicionar(a, 9);
    adicionar(a, 5);
    adicionar(a, 7);
    */
    // int i;
    // for (i = 1; i <= 9; i++) {
    //     adicionar(a, i);
    // }

    // printf("Altura: %d\n", altura(a->raiz) + 1);
    // printf("In-order: ");
    // percorrer(a->raiz,visitar);
    // printf("\n");