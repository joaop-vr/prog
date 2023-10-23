#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stddef.h>

#include "arq_chave.h"

void Inserir_caracter(struct lista_caracteres* L, wchar_t x) {

    /* Alocando nodo do caracter*/
    struct nodo_caracter *novo = malloc(sizeof(struct nodo_caracter));

    /* Alocando lista de chaves do caracter*/
    struct lista_chaves* L_chaves = malloc(sizeof(struct lista_chaves));

    /* Inserindo o primeiro nodo*/
    if (L->inicio == NULL) {
        L->inicio = novo;
        L->fim = novo;
        novo->prox = NULL;
        novo->caracter = x;
        novo->chaves = NULL;        
        L->tam++;
        
        novo->chaves = L_chaves;
        novo->chaves->inicio = NULL;
        novo->chaves->fim = NULL;
        novo->chaves->num_chaves = 0;

    }
    else {
        L->fim->prox = novo;
        L->fim = novo;
        novo->prox = NULL;
        novo->caracter = x;
        novo->chaves = NULL;  
        L->tam++;

        novo->chaves = L_chaves;
        novo->chaves->inicio = NULL;
        novo->chaves->fim = NULL;
        novo->chaves->num_chaves = 0;
    }
}

void Inserir_chave(struct lista_chaves* L, int posicao) {

    /* Alocando novo nodo */
    struct nodo_chaves *novo = malloc(sizeof(struct nodo_chaves));

    /* Inserindo o primeiro nodo*/
    if (L->inicio == NULL) {
        L->inicio = novo;
        L->fim = novo;
        novo->prox = NULL;
        novo->valor = posicao;
        L->num_chaves++;
    }
    else {
        L->fim->prox = novo;
        L->fim = novo;
        novo->prox = NULL;
        novo->valor = posicao;
        L->num_chaves++;
    }
}

struct nodo_caracter* Buscar_lista (struct lista_caracteres* L, wchar_t caracter) {

    int i = 0;
    for (struct nodo_caracter* aux = L->inicio; i < 256; aux = aux->prox) {
        if (aux->caracter == caracter)
            return aux;
        i++;
    }

    /* Caso nao encontre*/
    return NULL;

}

struct lista_caracteres* Criar_lista (FILE* livroCifra, struct lista_caracteres* L_caracteres) {

    /* Inicializando a lista de caracteres*/
    L_caracteres->tam = 0;
    L_caracteres->inicio = NULL;
    L_caracteres->fim = NULL;

    /* Preenchendo a lista com os caracteres da tabela ASCII*/
    for (int a = 0; a < 256; a++) {
        Inserir_caracter(L_caracteres, a);
    }

    return L_caracteres;
}

void Criar_chaves (struct lista_caracteres* L_caracteres, FILE* livroCifra) {

    wchar_t caracter;
    struct nodo_caracter* aux;
    struct nodo_caracter* aux_percorre;

    int j, k;
    
    j = 0; //int j: contador de posicao
    
    /* Lendo o primeiro caracter do arquivo*/
    fscanf(livroCifra, "%lc", &caracter);

    /* Percorre a lista ate encontrar o caracter em questao, se nao encontrar retorna NULL*/
    aux = Buscar_lista (L_caracteres, caracter);

    if (aux == NULL) {
        printf("Erro: tentou procurar o caracter: %lc|%i, que não consta na lista de caracteres de ASCII extendida", caracter, caracter);
        exit(1);
        }
    else {

        /* Trata letras maiusculas como minusculas */
        if (65 <= caracter && caracter <= 90) {
            k = 0;
            for (aux_percorre = aux; k < 32; aux_percorre = aux_percorre->prox)  //avanca 32 nodos na lista de caracteres
                k++;

            Inserir_chave(aux_percorre->chaves, j);
        }
        else
            Inserir_chave(aux->chaves, j);
    }
    
    while (! feof(livroCifra)) {

        /* Percorrendo ate encontrar ou um space ou um \n */
        while (caracter != 32 && caracter != 10 && (! feof(livroCifra))) 
            fscanf(livroCifra, "%lc", &caracter);

        /* Garantindo que ele nao guarde o final do arq*/
        if (! feof(livroCifra)) {

            /* Lendo o proximo caracter */
            fscanf(livroCifra, "%lc", &caracter);

            if (caracter == 0x0D)  //Tratamdo os casos de carriage return (tive problema com isso para certos casos)
                continue;
            else if (caracter != 32 && caracter != 10) {     //Cuidando para os casos de duplo \n ou espace seguido de \n
                
                /* Incrementa a posicao */
                j++;

                /* Percorre a lista ate encontrar o caracter em questao, se nao encontrar retorna NULL*/
                aux = Buscar_lista (L_caracteres, caracter);

                if (aux == NULL) {
                    printf("Erro: tentou procurar o caracter: %lc|%i, que não consta na lista de caracteres de ASCII extendida", caracter, caracter);
                    exit(1);
                }
                else {
                    if (65 <= caracter && caracter <= 90) { //Trata letras maiusculas como minusculas
                        k = 0;
                        for (aux_percorre = aux; k < 32; aux_percorre = aux_percorre->prox) //avança 32 nodos na lista de caracteres
                            k++;

                        Inserir_chave(aux_percorre->chaves, j);
                    }
                    else
                        Inserir_chave(aux->chaves, j);
                }
            }
        }
    }
}

void Criar_ArqChaves (FILE* ArqChaves, struct lista_caracteres* L_caracteres) {

    int j;  //contador para percorrer a lista de caracteres
    int x;  //contador para percorrer a lista de chaves
    
    struct nodo_caracter* aux_caracteres;
    struct nodo_chaves* aux_chaves;

    j = 0;
    for (aux_caracteres = L_caracteres->inicio; j < 256; aux_caracteres = aux_caracteres->prox) {

        /* Printa somente os caracteres que possuem chaves */
        if (aux_caracteres->chaves->num_chaves != 0) {

            /* Escreve o caracter da vez */
            fprintf(ArqChaves, "%lc:", aux_caracteres->caracter);

            /* Escreve chave por chave */
            x = 0;
            for (aux_chaves = aux_caracteres->chaves->inicio; x < aux_caracteres->chaves->num_chaves; aux_chaves = aux_chaves->prox) {
                fprintf(ArqChaves, " %i", aux_chaves->valor);
                x++;
            }

            /* Pula a linha */
            fprintf(ArqChaves, "\n");
        }
        j++;
    }
}

void Pop_chave (struct lista_chaves* L_chaves) {

    struct nodo_chaves* apagar = L_chaves->inicio;
    L_chaves->inicio = L_chaves->inicio->prox;
    free(apagar);
}

void Pop_caracter (struct lista_caracteres* L_caracteres) {

    struct nodo_caracter* apagar = L_caracteres->inicio;
    L_caracteres->inicio = L_caracteres->inicio->prox;
    free(apagar);
}

void Limpeza (struct lista_caracteres* L) {

    int i, j;
    struct nodo_caracter* aux_caracter;

    i = 0;
    for(aux_caracter = L->inicio; i < L->tam; aux_caracter = aux_caracter->prox) {
        if (aux_caracter->chaves->num_chaves != 0) {
            j = aux_caracter->chaves->num_chaves;
            while (j > 0) {
                Pop_chave(aux_caracter->chaves);
                j--;
            }
            aux_caracter->chaves->num_chaves = 0;
        }
        free(aux_caracter->chaves);
        i++;
    }

    i = L->tam;
    while (i > 0) {
        Pop_caracter(L);
        i--;
    }

    free(L);

}
