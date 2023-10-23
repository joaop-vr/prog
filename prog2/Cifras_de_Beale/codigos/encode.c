#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "arq_chave.h"
#include "encode.h"

void Codificar (FILE* mensagemOriginal, FILE* mensagemCodificada, struct lista_caracteres* L_caracteres) {

    wchar_t caracter;
    int sorteado;
    int i, k;
    struct nodo_caracter* aux_caracter;
    struct nodo_chaves* aux_chave;
    struct nodo_caracter* aux_percorre;
    srand(time(NULL));

    /* Lendo o primeiro caracter */
    fscanf(mensagemOriginal, "%lc", &caracter);

    while (! feof(mensagemOriginal)) {

        /* Imprimindo space (representado por -1) */
        if (caracter == 32) {
            fprintf(mensagemCodificada, "-1 ");
        }
        
        /* Quebrando linha (representado por -3)*/
        else if (caracter == 10) {
            fprintf(mensagemCodificada, "-3 ");
        }
        else {

            /* Percorre a lista ate encontrar o caracter em questao, se nao encontrar retorna NULL*/
            aux_caracter = Buscar_lista (L_caracteres, caracter);

            /* Trata letras maiusculas como minusculas */
            if (65 <= caracter && caracter <= 90) { 
                k = 0;
                for (aux_percorre = aux_caracter; k < 32; aux_percorre = aux_percorre->prox)
                    k++;
                aux_caracter = aux_percorre;
            }

            if (aux_caracter == NULL) {
                printf("Erro: tentou procurar o caracter: %lc, que não consta na lista de caracteres de ASCII extendida", caracter);
                exit(1);
            }
            else {

                i = 1;

                /* Imprime apenas os caracteres que possuem chaves */
                if (aux_caracter->chaves->num_chaves != 0) {

                    /* Sortando uma chave para ser utilizada */
                    sorteado = (rand() % (aux_caracter->chaves->num_chaves))+1;
                    for (aux_chave = aux_caracter->chaves->inicio; i < sorteado; aux_chave = aux_chave->prox)
                        i++;

                    /* Escrevendo a chave sorteada */
                    fprintf(mensagemCodificada, "%i ", aux_chave->valor);

                }

                /* Tratando dos caracteres que não possuem chaves
                (todos são representados por "-2" e posteriomente escritos como "?") */
                else if ((caracter != '.') && (caracter != ',') && (caracter != ';')){
                    fprintf(mensagemCodificada, "-2 ");
                }

            }
        }

        /* Lendo o proximo caracter */
        fscanf(mensagemOriginal, "%lc", &caracter);
    }
}