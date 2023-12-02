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
    contadorAVL++;
    if (arvore->raiz == NULL) {
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
                no = rsd(a, no);
            } else {
                // printf("RDD(%d)\n", no->valor);
                no = rdd(a, no);
            }
        } else if (fator < -1) {
            //rotacao a esquerda
            if (fb(no->direita) < 0) {
                // printf("RSE(%d)\n", no->valor);
                no = rse(a, no);
            } else {
                // printf("RDE(%d)\n", no->valor);
                no = rde(a, no);
            }
        }

        no = no->pai;
    }
}

NoAVL* removerAVLChave(ArvoreAVL* arvore, NoAVL* no, int chave) {
    if (no == NULL) {
        return no;
    }

    if (chave < no->valor) {
        no->esquerda = removerAVLChave(arvore, no->esquerda, chave);
    } else if (chave > no->valor) {
        no->direita = removerAVLChave(arvore, no->direita, chave);
    } else {
        if (no->direita != NULL && no->esquerda != NULL) {
            NoAVL* sucessor = sucessorInOrder(no->direita);
            no->valor = sucessor->valor;
            no->direita = removerAVLChave(arvore, no->direita, sucessor->valor);
        } else {
            if (no == arvore->raiz) {
                if (no->esquerda != NULL) {
                    arvore->raiz = no->esquerda;
                } else {
                    arvore->raiz = no->direita;
                }
            } else {
                NoAVL *temp = no->direita ? no->esquerda : no->direita;
                if (temp == NULL) {
                    temp = no;
                    no = NULL;
                } else {
                    *no = *temp;
                }

                free(temp);
            }
        }
    }

    if (no == NULL) {
        return no;
    }

    // Tá feio mas funciona, o negócio é que como a função vai reconstruindo os ancestrais, ela precisa desse retorno das rotações.
    int fator = fb(no);
    if (fator > 1) { 
        if (fb(no->esquerda) > 0) {
            return rsd(arvore, no);
        } else {
            return rdd(arvore, no);
        }
    } else if (fator < -1) {
        if (fb(no->direita) < 0) {
            return rse(arvore, no);
        } else {
            return rde(arvore, no);
        }
    }

    return no;
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
    NoAVL* atual = no;
    while(atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
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
