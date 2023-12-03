#include "RBTree.h"

unsigned long contadorRBTree = 0;

ArvoreRB* criar() {
    ArvoreRB *arvore = malloc(sizeof(ArvoreRB));
    arvore->nulo = NULL;
    arvore->raiz = NULL;

    arvore->nulo = criarNoRB(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    return arvore;
}

int vaziaRB(ArvoreRB* arvore) {
    contadorRBTree++;
    return arvore->raiz == NULL;
}

NoRB* criarNoRB(ArvoreRB* arvore, NoRB* pai, int valor) {
    NoRB* no = malloc(sizeof(NoRB));

    no->pai = pai;
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

NoRB* adicionarNoRB(ArvoreRB* arvore, NoRB* no, int valor) {
    contadorRBTree++;
    if (valor > no->valor) {
        contadorRBTree++;
        if (no->direita == arvore->nulo) {
            no->direita = criarNoRB(arvore, no, valor);
            no->direita->cor = Vermelho;

            return no->direita;
        } else {
            return adicionarNoRB(arvore, no->direita, valor);
        }
    } else {
        contadorRBTree++;
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNoRB(arvore, no, valor);
            no->esquerda->cor = Vermelho;

            return no->esquerda;
        } else {
            return adicionarNoRB(arvore, no->esquerda, valor);
        }
    }
}

NoRB* adicionarRB(ArvoreRB* arvore, int valor) {
    contadorRBTree++;
    if (vaziaRB(arvore)) {
        arvore->raiz = criarNoRB(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;

        return arvore->raiz;
    } else {
        NoRB* no = adicionarNoRB(arvore, arvore->raiz, valor);
        balancear(arvore, no);

        return no;
    }
}

NoRB* sucessorInOrderRb(ArvoreRB* arvore, NoRB* no) {
    contadorRBTree++;
    while (no->esquerda != arvore->nulo) {
        contadorRBTree++;
        no = no->esquerda;
    }

    return no;
}

void trocaValores(NoRB* a, NoRB* b) {
    int x = a->valor;
    a->valor = b->valor;
    b->valor = x;
}

void transplant(ArvoreRB* arvore, NoRB* u, NoRB* v) {
    contadorRBTree+=3;
    if (u->pai == arvore->nulo) {
        contadorRBTree-=2;
        arvore->raiz = v;
    } else if (u == u->pai->esquerda) {
        contadorRBTree--;
        u->pai->esquerda = v;
    } else if (u == u->pai->direita) {
        u->pai->direita = v;
    }
    v->pai = u->pai;
}

void balancearRemocao(ArvoreRB* arvore, NoRB* no, NoRB* irmao) {
    contadorRBTree+=2;
    while (no != arvore->raiz && no->cor == Preto) {
        contadorRBTree++;
        if (no == no->pai->esquerda) {
            irmao = no->pai->direita;
            contadorRBTree+=4;
            if (irmao->cor == Vermelho) {
                contadorRBTree-=3;
                irmao->cor = Preto;
                no->pai->cor = Vermelho;
                rotacionarEsquerda(arvore, no->pai);
                irmao = no->pai->direita;
            } else if (irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
                contadorRBTree-=1;
                irmao->cor = Vermelho;
                no = no->pai;
            } else if (irmao->direita->cor == Preto) {
                irmao->esquerda->cor = Preto;
                irmao->cor = Vermelho;
                rotacionarDireita(arvore, irmao);
                irmao = no->pai->direita;
            } else {
                irmao->cor = no->pai->cor;
                no->pai->cor = Preto;
                irmao->direita->cor = Preto;
                rotacionarEsquerda(arvore, no->pai);
                no = arvore->raiz;
            }
        } else {
            irmao = no->pai->esquerda;
            contadorRBTree+=4;
            if (irmao->cor == Vermelho) {
                contadorRBTree-=3;
                irmao->cor = Preto;
                no->pai->cor = Vermelho;
                rotacionarDireita(arvore, no->pai);
                irmao = no->pai->esquerda;
            } else if (irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
                contadorRBTree--;
                irmao->cor = Vermelho;
                no = no->pai;
            } else if (irmao->esquerda->cor == Preto) {
                irmao->direita->cor = Preto;
                irmao->cor = Vermelho;
                rotacionarEsquerda(arvore, irmao);
                irmao = no->pai->esquerda;
            } else {
                irmao->cor = no->pai->cor;
                no->pai->cor = Preto;
                irmao->esquerda->cor = Preto;
                rotacionarDireita(arvore, no->pai);
                no = arvore->raiz;
            }
        }
    }
    no->cor = Preto;

}



void removerRB(ArvoreRB* arvore, int chave) {
    NoRB* no = localizarRB(arvore, chave);
    NoRB *subs = no;
    NoRB *x = no;
    Cor subsCorOriginal = subs->cor;
    contadorRBTree+=2;
    if (no->esquerda == arvore->nulo) {
        contadorRBTree--;
        x = no->direita;
        transplant(arvore, no, no->direita);
    } else if (no->direita == arvore->nulo) {
        x = no->esquerda;
        transplant(arvore, no, no->esquerda);
    } else {
        subs = sucessorInOrderRb(arvore, no->direita);
        subsCorOriginal = subs->cor;
        x = subs->direita;
        contadorRBTree++;
        if (subs->pai == no) {
            x->pai = subs;
        } else {
            transplant(arvore, subs, subs->direita);
            subs->direita = no->direita;
            subs->direita->pai = subs;
        }
        transplant(arvore, no, subs);
        subs->esquerda = no->esquerda;
        subs->esquerda->pai = subs;
        subs->cor = no->cor;
    }

    contadorRBTree++;
    if (subsCorOriginal == Preto) {
        balancearRemocao(arvore, x, x);
    }

    free(no);

}

void balancear(ArvoreRB* arvore, NoRB* no) {
    contadorRBTree++;
    while (no->pai->cor == Vermelho) {
        contadorRBTree++;
        contadorRBTree++;
        if (no->pai == no->pai->pai->esquerda) {
            NoRB *tio = no->pai->pai->direita;

            contadorRBTree++;
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto;

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                contadorRBTree++;
                if (no == no->pai->direita) {
                    no = no->pai; //Caso 2
                    rotacionarEsquerda(arvore, no); //Caso 2
                }
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho; //Caso 3
                rotacionarDireita(arvore, no->pai->pai); //Caso 3
            }
        } else {
            NoRB *tio = no->pai->pai->esquerda;

            contadorRBTree++;
            if (tio->cor == Vermelho) {
                tio->cor = Preto; //Caso 1
                no->pai->cor = Preto;

                no->pai->pai->cor = Vermelho; //Caso 1
                no = no->pai->pai; //Caso 1
            } else {
                contadorRBTree++;
                if (no == no->pai->esquerda) {
                    no = no->pai; //Caso 2
                    rotacionarDireita(arvore, no); //Caso 2
                }
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho; //Caso 3
                rotacionarEsquerda(arvore, no->pai->pai); //Caso 3
            }
        }
    }
    arvore->raiz->cor = Preto; //Conserta possível quebra regra 2
}

NoRB* localizarRB(ArvoreRB* arvore, int valor) {
    contadorRBTree++;
    if (!vaziaRB(arvore)) {
        NoRB* no = arvore->raiz;

        contadorRBTree++;
        while (no != arvore->nulo) {
            contadorRBTree++;
            contadorRBTree++;
            if (no->valor == valor) {
                return no;
            } else {
                contadorRBTree++;
                no = valor < no->valor ? no->esquerda : no->direita;
            }
        }
    }

    printf("Nó não existe!\n");
    return NULL;
}

void percorrerProfundidadeInOrder(ArvoreRB* arvore, NoRB* no) {
    contadorRBTree++;
    if (no != arvore->nulo) {


        percorrerProfundidadeInOrder(arvore, no->esquerda);
        printf("%d ", (no->valor));
        percorrerProfundidadeInOrder(arvore, no->direita);
    }
}

void percorrerProfundidadePreOrder(ArvoreRB* arvore, NoRB* no, void (*callback)(int)) {
    contadorRBTree++;
    if (no != arvore->nulo) {
        callback(no->valor);
        percorrerProfundidadePreOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePreOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePosOrder(ArvoreRB* arvore, NoRB* no, void (callback)(int)) {
    contadorRBTree++;
    if (no != arvore->nulo) {
        percorrerProfundidadePosOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePosOrder(arvore, no->direita,callback);
        callback(no->valor);
    }
}

NoRB* rotacionarEsquerda(ArvoreRB* arvore, NoRB* no) {
    NoRB* direita = no->direita;
    no->direita = direita->esquerda;

    contadorRBTree++;
    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;

    contadorRBTree+=2;
    if (no->pai == arvore->nulo) {
        contadorRBTree--;
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita;
    } else {
        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;

    return direita;
}

NoRB* rotacionarDireita(ArvoreRB* arvore, NoRB* no) {
    NoRB* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;

    contadorRBTree++;
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }

    esquerda->pai = no->pai;

    contadorRBTree+=2;
    if (no->pai == arvore->nulo) {
        contadorRBTree--;
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda;
    } else {
        no->pai->direita = esquerda;
    }

    esquerda->direita = no;
    no->pai = esquerda;

    return esquerda;
}
