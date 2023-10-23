#include <stdio.h>
#include <stdlib.h>



#include "fila.h"


int Sortear_pedido ();

void Criar_nodo_fila (struct lista_dupla *P, struct nodo_dupla *novo) {

    /*fila vazia*/
    if ( P->cabeca == NULL) {
        novo->ant = NULL;
        novo->prox = P->cabeca;
        P->cabeca = novo;
        P->inicio = novo;
        P->fim = novo;
        P->tam++;
    }   
    else {
        /*Inserindo no fim*/
        novo->ant = P->fim;
        P->fim->prox = novo;
        P->fim = novo;
        novo->prox = NULL;
        P->tam++;
    }

    
}

void Excluir_nodo_fila (struct lista_dupla *P) {
    if (P->cabeca == NULL) {
        printf("\n----------------------------------------------------------\n\n");
        printf("    Erro: fila esta vazia\n");
    }
    /*Excluindo o ultimo nodo restante*/
    else if (P->tam == 1) {
        free(P->inicio);
        P->cabeca = NULL;
        P->tam--;
    }
    /*Excluindo primeiro nodo*/
    else {
        P->inicio->prox->ant = NULL;
        P->inicio = P->inicio->prox;
        P->cabeca = P->inicio;
        P->tam--;
    }
}