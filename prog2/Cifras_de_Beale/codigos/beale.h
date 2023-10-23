#ifndef BEALE_H_
#define BEALE_H_

#include <stdio.h>
#include <stddef.h>
#include <wchar.h>


/* Lista simplesmente encadeada que armazena todos os caracteres obtidos do livro cifra*/
struct lista_caracteres {
    size_t tam;
    struct nodo_caracter* inicio;
    struct nodo_caracter* fim;
};

/* nodo que contem o caracter e a lista de suas chaves*/
struct nodo_caracter {
    wchar_t caracter;
    int posicao;
    struct lista_chaves* chaves;
    struct nodo_caracter* prox;
};

/* Lista simplesmente encadeada que armazena todos as chaves de um caracter */
struct lista_chaves {
    size_t num_chaves;
    struct nodo_chaves* inicio;
    struct nodo_chaves* fim;
};

/* nodo da lista de chaves, contem uma chave do caracter*/
struct nodo_chaves {
    int valor;
    struct nodo_chaves* prox;
};

#endif