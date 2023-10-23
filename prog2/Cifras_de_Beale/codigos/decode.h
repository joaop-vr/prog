#ifndef DECODE_H_
#define DECODE_H_

#include "beale.h"

/* Decodifica a mensagem codificada a partir do arquivo de chaves */
void Decodificar_com_ArqChaves(FILE* mensagemCodificada, FILE* mensagemDecodificada, FILE* ArqChaves);

/* Busca no arquivo de chaves o caracter que corresponde a chave que foi passada como parametro */
int Busca_ArqChaves(FILE* ArqChaves, char* chave);

/* Decodifica a mensagem codificada a partir do LivroCifra */
void Decodificar_com_LivroCifra(FILE* mensagemCodificada, FILE* mensagemDecodificada, FILE* livroCifra);

/* Calcula a quantidade de palavras em um arquivo*/
int Contador_palavras (FILE* livroCifra);

/* Preenche de forma ordenada o vetor contendo structs nodo_caracteres */
void Preencher_vetor (struct nodo_caracter Vet[], FILE* livroCifra);

/* Busca no vetor de caracteres o caracter que corresponde a chave que foi passada como parametro */
int Busca_livroCifra(struct nodo_caracter Vet[], int chave, int num_palavras);

/* Busca binaria no vetor ordenado formado pelas primeiras letras das palavras do livroCifra */
int Busca_Binaria(struct nodo_caracter Vet[], int a, int b, int chave);

#endif