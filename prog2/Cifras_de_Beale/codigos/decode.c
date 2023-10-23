#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <math.h>

#include "decode.h"

int Busca_ArqChaves(FILE* ArqChaves, char* chave) {

    char space[5] = "-1";
    char interrogacao[5] = "-2";
    char quebraLinha[5] = "-3";
    char linha[10];
    char caracter;
    

    /* Tratando dos caracteres que não possuem chaves 
    (todos são representados por "-2" e posteriomente escritos como "?") */
    if (strcmp(interrogacao, chave) == 0) {
        return 63;
    }

    /* O space é registrado como -1 */
    if (strcmp(space, chave) == 0) {
        return 32;
    }

    /* Cuidando das quebras de linha */
    if (strcmp(quebraLinha, chave) == 0) {
        return 10;
    }
    
    /* Lendo a primeira palavra */
    fscanf(ArqChaves, "%s", linha);

    /* Caracter guarda a primeira letra da palavra lida */
    caracter = linha[0];

    /* lendo o ':' */
    fscanf(ArqChaves, "%s", linha); 

    while (! feof(ArqChaves)) {
        
        /* Percorre as chaves do caracter em quetao */
        while (linha[1] != ':' && (strcmp(linha, chave) != 0))
            fscanf(ArqChaves, "%s", linha);

        /* Achou o caracter*/
        if (strcmp(linha, chave) == 0) {
            rewind(ArqChaves);
            return caracter;
        }

        /* Caracter guarda a primeira letra da palavra lida */
        caracter = linha[0];

        /* Lendo a proxima palavra */
        fscanf(ArqChaves, "%s", linha);
    }

    /* Caso nao tenha encontrado */
    return -1;
}

void Decodificar_com_ArqChaves(FILE* mensagemCodificada, FILE* mensagemDecodificada, FILE* ArqChaves) {

    char chave[35];
    char caracter;

    /* Lendo o primeiro codigo*/
    fscanf(mensagemCodificada, "%s", chave);

    /* Busca a chave dentro do ArqChaves, caso nao encontre retorna -1 */
    caracter = Busca_ArqChaves(ArqChaves, chave);
    if (caracter == -1) {
        printf("Erro: Busca_ArqChaves nao encontrou.\n");
        exit(1);
    }


    /* Escrevendo o primeiro caracter decodificado */
    fprintf(mensagemDecodificada, "%c", caracter);


    while (! feof(mensagemCodificada)) {

        /* Lendo o proximo codigo */
        fscanf(mensagemCodificada, "%s", chave);

        if (! feof(mensagemCodificada)) {

            /* Busca a chave dentro do ArqChaves, caso nao encontre retorna -1 */
            caracter = Busca_ArqChaves(ArqChaves, chave);
            if (caracter == -1) {
                printf("Erro: Busca_ArqChaves nao encontrou.\n");
                exit(1);
            }
            
            /* Escrevendo o proximo caracter decodificado */
            fprintf(mensagemDecodificada, "%c", caracter);
        }
    }
}

int Contador_palavras (FILE* livroCifra) {

    int cont = 1; //conta a quantidade de palavras
    char palavra[100];

    fscanf(livroCifra, "%s", palavra);
    while (! feof(livroCifra)) {

        if (! feof(livroCifra)) {
            fscanf(livroCifra, "%s", palavra);
            cont++;
        }
    }

    return cont;
}

void Preencher_vetor (struct nodo_caracter Vet[], FILE* livroCifra) {

    int j = 0; //contador de posicao
    char palavra[100];
    char caracter;

    /* Lendo a primeira palavra */
    fscanf(livroCifra, "%s", palavra);
    
    /* Caracter guarda a primeira letra da palavra lida */
    caracter = palavra[0];

    /* Transformando maiscula em minuscula */
    if (65 <= caracter && caracter <= 90)
        caracter += 32;

    /* Atribuindo o caracter e sua posicao ao Vet de indice j */
    Vet[j].caracter = caracter;
    Vet[j].posicao = j;

    while (! feof(livroCifra)) {

        if (! feof(livroCifra)) {
            
            /* Lendo a proxima palavra */
            fscanf(livroCifra, "%s", palavra);

            /* Incrementando o indice do vetor */
            j++;

            /* Caracter guarda a primeira letra da palavra lida */
            caracter = palavra[0];

            /* Transformando maiscula em minuscula */
            if (65 <= caracter && caracter <= 90)
                caracter += 32;

            /* Atribuindo o caracter e sua posicao ao Vet de indice j */
            Vet[j].caracter = caracter;
            Vet[j].posicao = j;
        }
    }
}

int Busca_Binaria(struct nodo_caracter Vet[], int a, int b, int chave) {

    if(a > b)
		return -1;

	int m = floor((a+b)/2);

	if(chave == Vet[m].posicao) {
		return m;                                 
	}
	else if(chave < Vet[m].posicao) {
		return Busca_Binaria(Vet, a, m-1, chave);
	}
	
	return Busca_Binaria(Vet, m+1, b, chave);
}

int Busca_livroCifra(struct nodo_caracter Vet[], int chave, int num_palavras) {

    /* Tratando dos caracteres que não possuem chaves 
    (todos são representados por "-2" e posteriomente escritos como "?") */
    if (chave == -2) {
        return -2;
    }

    /* O space é registrado como -1 */
    if (chave == -1) {
        return -1;
    }

    /* Cuidando das quebras de linha registrado como -3*/
    if (chave == -3) {
        return -3;
    }

    int a = 0;
    int b = num_palavras-1;
    int output = Busca_Binaria(Vet, a, b, chave);

    return output;
}

void Decodificar_com_LivroCifra(FILE* mensagemCodificada, FILE* mensagemDecodificada, FILE* livroCifra) {

    int chave, indice;
    char caracter;

    /* Contando o numero de palavras do livroCifra */
    int num_palavras = Contador_palavras(livroCifra);
    
    /* Alocando um vetor para guardar cada primeira letra das palavras*/
    struct nodo_caracter Vet_caracteres[num_palavras];

    rewind(livroCifra);

    /* Preenche o vetor Vet_caracteres com cada primeira letra das palavras*/
    Preencher_vetor(Vet_caracteres, livroCifra);

    /* Lendo o primeiro codigo*/
    fscanf(mensagemCodificada, "%i", &chave);

    /* Busca a chave dentro do vetor de caracteres, caso nao encontre retorna -1 */
    indice = Busca_livroCifra(Vet_caracteres, chave, num_palavras);
    switch (indice) {
        
        /* Caso de space */
        case -1: {
            caracter = 32;
            break;}

        /* Caso de caracter sem chave*/
        case -2: {
            caracter = 63;
            break;}

        /* Caso de quebra de linha */
        case -3: {
            caracter = 10;
            break;}
        
        /* Caso que utliza o resultado da Busca no livroCifra */
        default:
            caracter = Vet_caracteres[indice].caracter;
            break;
        }

    /* Escrevendo o primeiro caracter decodificado */
    fprintf(mensagemDecodificada, "%c", caracter);


    while (! feof(mensagemCodificada)) {

        /* Lendo o proximo codigo */
        fscanf(mensagemCodificada, "%i", &chave);

        if (! feof(mensagemCodificada)) {

            indice = Busca_livroCifra(Vet_caracteres, chave, num_palavras);
            switch (indice) {
        
                /* Caso de space */
                case -1: {
                    caracter = 32;
                    break;}

                /* Caso de caracter sem chave*/
                case -2: {
                    caracter = 63;
                    break;}

                /* Caso de quebra de linha */
                case -3: {
                    caracter = 10;
                    break;}
                
                /* Caso que utliza o resultado da Busca no livroCifra */
                default:
                    caracter = Vet_caracteres[indice].caracter;
                    break;
            }

            /* Escrevendo o proximo caracter decodificado */
            fprintf(mensagemDecodificada, "%c", caracter);
        }
    }

    fflush(mensagemDecodificada);

}