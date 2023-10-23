#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"


void Push (struct topo *P, char x) {
    struct nodo_simples *novo = malloc(sizeof(struct nodo_simples));
    if (P->cabeca == NULL) {
        P->inicio = novo;
        P->fim = novo;
        novo->igrediente = x;
        novo->prox = P->cabeca;
        P->cabeca = novo;
        P->tam++;
    }
    else {
        novo->igrediente = x;
        P->tam++;
        novo->prox = P->fim->prox;
        P->fim->prox = novo;
        P->fim = novo;
    }
}

void Pop (struct topo *P) {

        struct nodo_simples *aux = P->inicio;
        P->cabeca = P->inicio->prox;
        P->inicio = P->inicio->prox;
        P->tam--;
        free(aux);

}
