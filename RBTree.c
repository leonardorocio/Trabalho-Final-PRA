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
    if (valor > no->valor) {
        if (no->direita == arvore->nulo) {
            no->direita = criarNoRB(arvore, no, valor);     
            no->direita->cor = Vermelho;       
        		
            return no->direita;
        } else {
            return adicionarNoRB(arvore, no->direita, valor);
        }
    } else {
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
    while (no->esquerda != arvore->nulo) {
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
    if (u->pai == arvore->nulo) {
        arvore->raiz = v;
    } else if (u == u->pai->esquerda) {
        u->pai->esquerda = v;
    } else if (u == u->pai->direita) {
        u->pai->direita = v;
    } 
    v->pai = u->pai;
}

void balancearRemocao(ArvoreRB* arvore, NoRB* no, NoRB* irmao) {
    while (no != arvore->raiz && no->cor == Preto) {
        if (no == no->pai->esquerda) {
            irmao = no->pai->direita;
            if (irmao->cor == Vermelho) {
                irmao->cor = Preto;
                no->pai->cor = Vermelho;
                rotacionarEsquerda(arvore, no->pai);
                irmao = no->pai->direita;
            }
            else if (irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
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
            if (irmao->cor == Vermelho) {
                irmao->cor = Preto;
                no->pai->cor = Vermelho;
                rotacionarDireita(arvore, no->pai);
                irmao = no->pai->esquerda;
            }
            else if (irmao->esquerda->cor == Preto && irmao->direita->cor == Preto) {
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

void removerRB(ArvoreRB* arvore, NoRB* no, int chave) {
    NoRB *subs = no;
    NoRB *x = no;
    Cor subsCorOriginal = subs->cor;
    if (no->esquerda == arvore->nulo) {
        x = no->direita;
        transplant(arvore, no, no->direita);
    } else if (no->direita == arvore->nulo) {
        x = no->esquerda;
        transplant(arvore, no, no->esquerda);
    } else {
        subs = sucessorInOrderRb(arvore, no->direita);
        subsCorOriginal = subs->cor;
        x = subs->direita;
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

    if (subsCorOriginal == Preto) {
        balancearRemocao(arvore, x, x);
    }

    free(no);

}

void balancear(ArvoreRB* arvore, NoRB* no) {
    while (no->pai->cor == Vermelho) {
        if (no->pai == no->pai->pai->esquerda) {
            NoRB *tio = no->pai->pai->direita;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; 
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; 
                no = no->pai->pai; 
            } else {
                if (no == no->pai->direita) {
                    no = no->pai; 
                    rotacionarEsquerda(arvore, no); 
                } 
                no->pai->cor = Preto; 
                no->pai->pai->cor = Vermelho; 
                rotacionarDireita(arvore, no->pai->pai); 
            }
        } else {
            NoRB *tio = no->pai->pai->esquerda;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto; 
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho; 
                no = no->pai->pai; 
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai; 
                    rotacionarDireita(arvore, no); 
                }
                no->pai->cor = Preto; 
                no->pai->pai->cor = Vermelho; 
                rotacionarEsquerda(arvore, no->pai->pai); 
            }
        }
    }
    arvore->raiz->cor = Preto;
}

NoRB* localizarRB(ArvoreRB* arvore, int valor) {
    if (!vaziaRB(arvore)) {
        NoRB* no = arvore->raiz;

        while (no != arvore->nulo) {
            if (no->valor == valor) {
                return no;
            } else {
                no = valor < no->valor ? no->esquerda : no->direita;
            }
        }
    }

    return NULL;
}

void percorrerProfundidadeInOrder(ArvoreRB* arvore, NoRB* no) {
    if (no != arvore->nulo) {
        
        
        percorrerProfundidadeInOrder(arvore, no->esquerda);
        printf("%d ", (no->valor));
        percorrerProfundidadeInOrder(arvore, no->direita);
    }
}

void percorrerProfundidadePreOrder(ArvoreRB* arvore, NoRB* no, void (*callback)(int)) {
    if (no != arvore->nulo) {
        callback(no->valor);
        percorrerProfundidadePreOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePreOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePosOrder(ArvoreRB* arvore, NoRB* no, void (callback)(int)) {
    if (no != arvore->nulo) {
        percorrerProfundidadePosOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePosOrder(arvore, no->direita,callback);
        callback(no->valor);
    }
}

NoRB* rotacionarEsquerda(ArvoreRB* arvore, NoRB* no) {
    NoRB* direita = no->direita;
    no->direita = direita->esquerda; 

    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
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
    
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }
    
    esquerda->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
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