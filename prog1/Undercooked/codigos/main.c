#include <stdio.h>
#include <stdlib.h>


#include "jogabilidade.h"


int main() {

    int num_pedidos = 10;                   // <--- default

    char mapa[7][23];
    struct localizacao Posicao;             // <-- STRUCT PARA GUARDAR A POSICAO DO CHAPEIRO
    Criando_mapa(mapa, &Posicao);

    struct lista_dupla Fila_pedidos;
    Fila_pedidos.tam = 0;
    Fila_pedidos.cabeca = NULL;

    struct desempenho Status;
    Status.num_erros = 0;                   //numero de pedidos errados
    Status.num_lixo = 0;                    //numero de pedidos descartados no lixo
    Status.num_exito = 0;                   //numero de pedidos corretos

    struct topo Pilha_ingredientes;
    Pilha_ingredientes.cabeca = NULL;
    Pilha_ingredientes.tam = 0;   

    Layout(); 
        
    int mode = Game_mode();     //[0: finito; 1:infinito]

    if (mode == 0) {

        Criar_pedidos(&num_pedidos, &Fila_pedidos, mode);
        Status.num_pedidos = num_pedidos;       //numero de pedidos no total

        while (Verificar_fim(Status) == 0) {
            Imprimir(mapa, Fila_pedidos, Status, Pilha_ingredientes);
            Verificar_fim(Status);      
            Andar(mapa, &Status, &Posicao, &Pilha_ingredientes, &Fila_pedidos);
        }
    
        return 0;
    }
    else {

        Criar_pedidos(&num_pedidos, &Fila_pedidos, mode);
        Status.num_pedidos = num_pedidos;       //numero de pedidos no total

        while (Verificar_fim(Status) == 0) {
            Imprimir(mapa, Fila_pedidos, Status, Pilha_ingredientes);
            Verificar_fim(Status);  
            int reabastecer = Andar(mapa, &Status, &Posicao, &Pilha_ingredientes, &Fila_pedidos);
            if (reabastecer == 1) 
                Reabastecer_pedido(&num_pedidos, &Fila_pedidos);
        }
    
        return 0;
    }
}