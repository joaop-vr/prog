#ifndef ARQ_CHAVE_H_
#define ARQ_CHAVE_H_

#include "beale.h"

/* Insere o novo caracter na lista de caracteres */
void Inserir_caracter(struct lista_caracteres* L, wchar_t x);

/* Insere a nova chave na lista de chaves */
void Inserir_chave(struct lista_chaves* L, int posicao);

/* Busca pela lista de caracteres*/
struct nodo_caracter* Buscar_lista (struct lista_caracteres* L, wchar_t caracter);

/* Cria a lista que contem os caracteres */
struct lista_caracteres* Criar_lista (FILE* livroCifra, struct lista_caracteres* L_caracteres);

/* Cria a lista que contem as chaves */
void Criar_chaves (struct lista_caracteres* L_caracteres, FILE* livroCifra);

/* Cria o arquivo de caracteres */
void Criar_ArqChaves (FILE* ArqChaves, struct lista_caracteres* L_caracteres);

/* Faz um loop de Pop ate liberar toda a memoria da lista */
void Limpeza (struct lista_caracteres* L);

/* Pop em nodo chave */
void Pop_chave (struct lista_chaves* L_chaves);

/* Pop em nodo caracter */
void Pop_caracter (struct lista_caracteres* L_caracteres);

#endif