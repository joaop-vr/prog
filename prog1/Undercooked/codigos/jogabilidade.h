#ifndef MAIN_H
#define MAIN_H

#include "lista.h"

struct desempenho {
    int num_erros;
    int num_lixo;
    int num_exito;
    int num_pedidos;
};

struct localizacao {
    int row;
    int column;
};

void Layout(); 

int Game_mode ();

void Criando_mapa(char mapa[7][23], struct localizacao *Posicao);

void Imprimir(char mapa[7][23], struct lista_dupla Fila_pedidos, struct desempenho Status, struct topo Pilha_igredientes);

void Criar_pedidos (int *num_pedidos, struct lista_dupla *Fila_pedidos, int mode);

void Reabastecer_pedido (int *num_pedidos, struct lista_dupla *Fila_pedidos);

void Preencher_pedido (struct nodo_dupla *pedido, int sorteado, int i) ;

int Verificar_fim (struct desempenho Status);

void Imprimir_fila (struct lista_dupla P);

int Andar (char mapa[7][23], struct desempenho *Status, struct localizacao *Posicao, struct topo *Pilha_igredientes, struct lista_dupla *Fila_pedidos);

int Checar_troca (char mapa [7][23], char mov, struct localizacao *Posicao);

void Troca (char mapa [7][23], char mov, struct localizacao *Posicao);

void Empilhar (struct topo *Pilha_igredientes, char mapa [7][23], struct localizacao *Posicao, char mov);

int verificaPedido(struct topo *Pilha_igredientes, struct lista_dupla *Fila_pedidos);

void destroiRefeicao (struct topo *Pilha_igredientes);

#endif