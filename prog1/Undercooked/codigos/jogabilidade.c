#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define ANSI_COLOR_RED      "\x1b[31m" //cores em ANSI utilizadas 
#define ANSI_COLOR_RESET     "\e[0;37m"

#include "fila.h"
#include "lista.h"
#include "pilha.h" 
#include "jogabilidade.h"

void Layout() {                         
    char mapa[17][118] = {{'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','='},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ','#','#',' ',' ',' ','#','#',' ','#','#','#','#',' ',' ','#','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ','#','#','#',' ',' ','#','#',' ','#','#',' ','#','#',' ','#','#',' ',' ',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ','#','#','#','#',' ','#','#',' ','#','#',' ','#','#',' ','#','#','#','#',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ','#','#',' ','#','#','#','#',' ','#','#',' ','#','#',' ','#','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ','#','#',' ',' ','#','#','#',' ','#','#',' ','#','#',' ','#','#',' ',' ',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#',' ',' ','#','#',' ',' ',' ','#','#',' ','#','#','#','#',' ',' ','#','#','#','#',' ','#','#',' ',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ','#','#','#','#',' ',' ',' ','#','#','#','#',' ',' ','#','#',' ',' ','#','#',' ','#','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ','#','#',' ',' ','#','#',' ','#','#',' ',' ','#','#',' ','#','#',' ','#','#',' ',' ','#','#',' ',' ',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ','#','#',' ',' ','#','#',' ','#','#','#','#',' ',' ',' ','#','#','#','#',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ','#','#',' ',' ','#','#',' ','#','#','#','#',' ',' ',' ','#','#','#','#',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ','#','#',' ','#','#',' ',' ','#','#',' ','#','#',' ',' ','#','#',' ','#','#',' ','#','#',' ',' ','#','#',' ',' ',' ','#','#',' ','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ','#','#','#','#',' ',' ',' ','#','#','#','#',' ',' ','#','#',' ',' ','#','#',' ','#','#','#','#',' ','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
                         {'=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','='}};     
    
    /*38 colunas de vazio, 38 colunas de letra, 38 colunas de vazio*/ 
    
    int row;
    int column;
    
    
    int i = 0;
    int cont_column_min = 0;
    int cont_column_max = 25;
    while (i <= 57) {
        for (row = 0; row < 17; row++) {
            for (column = cont_column_min; column < cont_column_max; column++) {
                printf(ANSI_COLOR_RED"%c ", mapa[row][column]);
                printf(ANSI_COLOR_RESET);
            }
            printf("\n");
        }
        cont_column_min++;
        cont_column_max++;
        i++;
        usleep(100000);
        system("clear");
    }
}

int Game_mode () {

    char output;
    printf("\n----------------------------------------------------------\n");
    printf("    Voce deseja o modo infinito? [Y/N] ");
    scanf("%c", &output);
    switch (output) {
    case 'n':
        return 0;
        break;
    case 'N':
        return 0;
        break; 
    case 'y':
        return 1;
        break;
    case 'Y':
        return 1;
        break;   
    default:
        printf("\nErro: esposta invalida");
        int saida = Game_mode();
        return saida;
    }
}

int Sortear_pedido () {
    int x = rand() % 6;
    printf("Sorteado: %d\n",x);

    return x;
}

void Preencher_pedido (struct nodo_dupla *pedido, int sorteado, int i) {

    switch (sorteado) {
        case 0:
            pedido->num_cliente = i;    // <-- posição do cliente na fila
            pedido->nome = "X-Burger";  // <-- qual foi o pedido
            pedido->codigo = 1;  // <-- codigo do pedido (menu)
            break;
        case 1:
            pedido->num_cliente = i;
            pedido->nome = "X-Salada";
            pedido->codigo = 2;
            break;
        case 2:
            pedido->num_cliente = i;
            pedido->nome = "Combo 1 ";
            pedido->codigo = 3;
            break;
        case 3:
            pedido->num_cliente = i;
            pedido->nome = "Combo 2";
            pedido->codigo = 4;
            break;
        case 4:
            pedido->num_cliente = i;
            pedido->nome =  "Vegetariano";
            pedido->codigo = 5;
            break;
        case 5:
            pedido->num_cliente = i;
            pedido->nome = "Vegano";
            pedido->codigo = 6;
            break;
    }
}
void Criar_pedidos (int *num_pedidos, struct lista_dupla *Fila_pedidos, int mode) {
    
    if (mode == 0) {
        int novo_num_pedidos;
        printf("\n----------------------------------------------------------\n");
        printf("    Informe o numero de pedidos a serem processados: ");
        scanf("%i", &novo_num_pedidos);
        *num_pedidos = novo_num_pedidos;
    }

    int i;
    srand(time(NULL));
    for (i = 1; i <= *num_pedidos; i++) {
        struct nodo_dupla *pedido = malloc(sizeof(struct nodo_dupla));
        Criar_nodo_fila(Fila_pedidos, pedido);
        int sorteado = Sortear_pedido();      // <-- sorteia um numero de 1 a 6 (menu de opções de lanches)
        Preencher_pedido(pedido, sorteado, i);
    }
}

void Reabastecer_pedido (int *num_pedidos, struct lista_dupla *Fila_pedidos) {
    srand(time(NULL));
    struct nodo_dupla *pedido = malloc(sizeof(struct nodo_dupla));
    Criar_nodo_fila(Fila_pedidos, pedido);
    int sorteado = Sortear_pedido();      // <-- sorteia um numero de 1 a 6 (menu de opções de lanches)
    Fila_pedidos->tam = Fila_pedidos->tam + 1;
    Preencher_pedido(pedido, sorteado, Fila_pedidos->tam);
}

int Verificar_fim (struct desempenho Status) {
    if ((Status.num_pedidos == Status.num_erros + Status.num_exito) && Status.num_erros < 3 && Status.num_lixo < 5) {
        system("clear");
        printf("-------------------------\n");
        printf("    ***FIM DE JOGO***\n");
        printf("       Parabens!!\n");
        printf("-------------------------\n");
        return 1;
    }
    else if (Status.num_erros == 3) {
        system("clear");
        printf("-------------------------\n");
        printf("    ***FIM DE JOGO***\n");
        printf("    Pedidos errados: %d\n", Status.num_erros);
        printf("-------------------------\n");
        return -1;
    }
    else if (Status.num_lixo == 5) {
        system("clear");
        printf("-------------------------\n");
        printf("    ***FIM DE JOGO***\n");
        printf("    Pedidos jogados no lixo: %d\n", Status.num_lixo);
        printf("-------------------------\n");
        return -1;
    }
    else 
        return 0;
}

void Criando_mapa(char mapa[7][23], struct localizacao *Posicao) {
    int column, row;
    for (row = 0; row < 7; row++) {
        for (column = 0; column < 23; column++) {
            if (row == 3 && column == 11) {
                mapa[row][column] = '&';
                Posicao->row = row;
                Posicao->column = column;
            }
            else if (row == 0 && column == 11) 
                mapa[row][column] = '@';
            else if (row == 3 && column == 21)
                mapa[row][column] = 'o';
            else if (row == 2 && column == 4)
                mapa[row][column] = '[';
            else if (row == 2 && column == 5)
                mapa[row][column] = 'R';
            else if (row == 2 && column == 6)
                mapa[row][column] = ']';
            else if (row == 3 && column == 4)
                mapa[row][column] = '[';
            else if (row == 3 && column == 5)
                mapa[row][column] = 'F';
            else if (row == 3 && column == 6)
                mapa[row][column] = ']';
            else if ((row == 5 && column == 2) || (row == 5 && column == 6) || (row == 5 && column == 10) || (row == 5 && column == 14) || (row == 5 && column == 18))
                mapa[row][column] = '[';
            else if ((row == 5 && column == 4) || (row == 5 && column == 8) || (row == 5 && column == 12) || (row == 5 && column == 16) || (row == 5 && column == 20))
                mapa[row][column] = ']';
            else if (row == 5 && column == 3)
                mapa[row][column] = 'p';
            else if (row == 5 && column == 7)
                mapa[row][column] = 'H';
            else if (row == 5 && column == 11)
                mapa[row][column] = 'Q';
            else if (row == 5 && column == 15)
                mapa[row][column] = 'S';
            else if (row == 5 && column == 19)
                mapa[row][column] = 'P';
            else if ((row == 0 && column == 10) || (row == 0 && column == 12))
                mapa[row][column] = '|';
            else if ((row == 0 && column == 0) || (row == 0 && column == 22) || (row == 6 && column == 0) || (row == 6 && column == 22))
                mapa[row][column] = '#';
            else if (column == 0 || (column == 22 && (row != 0 && row != 22)))
                mapa[row][column] = '|';
            else if (row == 0 || (row == 6 && (column != 0 && column != 22)))
                mapa[row][column] = '-';
            else
                mapa[row][column] = ' ';
            
        }
        
    }
}

void Imprimir_fila (struct lista_dupla P) {
    if (P.cabeca == NULL) {
        printf("    Lista sem pedidos\n");
    }
    else {
        struct nodo_dupla *aux;
        if (P.tam > 5) {                                                       //garante que só 5 pedidos sejam impressos
            int cont = 1;
            for (aux = P.cabeca; cont <= 5; aux = aux->prox) {
                if (cont != 5)
                    printf(" [Cliente %d | %s] ->", aux->num_cliente, aux->nome);
                else
                    printf(" [Cliente %d | %s]\n", aux->num_cliente, aux->nome);
                cont ++;
            }
            printf("\n");
        }
        else {
            for (aux = P.cabeca; aux != NULL; aux = aux->prox ) {
                if (aux != P.fim)
                    printf(" [Cliente %d | %s] ->", aux->num_cliente, aux->nome);
                else
                    printf(" [Cliente %d | %s]\n", aux->num_cliente, aux->nome);
            }
            printf("\n");
        }
    }
}

void Imprimir(char mapa[7][23], struct lista_dupla Fila_pedidos, struct desempenho Status, struct topo Pilha_igredientes) {
    system("clear");
    int row, column;
    for (row = 0; row < 7; row++) {
        printf("                     ");
        for (column = 0; column < 23; column++) {
                printf("%c", mapa[row][column]);
        }
        if (row == 6) {
            Imprimir_fila(Fila_pedidos);
            printf("Num_exito: %d  Num_lixo: %d   Num_erro: %d\n", Status.num_exito, Status.num_lixo, Status.num_erros);
            struct nodo_simples *aux; 
            if (Pilha_igredientes.tam != 0){
            printf("\nIgredientes: ");
            for (aux = Pilha_igredientes.cabeca; aux != NULL; aux = aux->prox)
                printf("%c  ", aux->igrediente);
            printf("\n");
        }
        }
        else
            printf("\n");
    }
}

int Checar_troca (char mapa [7][23], char mov, struct localizacao *Posicao) {
    if (mov == 'a' || mov == 'D') {                    //<-- MOVE P/ ESQUERDA
        if (mapa[Posicao->row][Posicao->column-1] == '|')       
            return -1;                                      
        else if (mapa[Posicao->row][Posicao->column-1] == ']')  
            return 1;                                       
        else 
            return 0;                                             
    }
    else if (mov == 'd' || mov == 'C') {               //<-- MOVE P/ DIREITA
        if(mapa[Posicao->row][Posicao->column+1] == '|')        
            return -1;
        else if(mapa[Posicao->row][Posicao->column+1] == '[')   
            return 1;    
        else if(mapa[Posicao->row][Posicao->column+1] == 'o')
            return 3;
        else 
            return 0;
    }
    else if (mov == 'w' || mov == 'A') {               //<-- MOVE P/ CIMA
        if(mapa[Posicao->row-1][Posicao->column] == 'F')         
            return 1;
        else if(mapa[Posicao->row-1][Posicao->column] == 'o')
            return 3;
        else if(mapa[Posicao->row-1][Posicao->column] == '@')
            return 2;
        else if(mapa[Posicao->row-1][Posicao->column] == ' ')   
            return 0;    
        else 
            return -1;                                       
    }
    else if (mov == 's' || mov == 'B') {               //<-- MOVE P/ BAIXO
        if((mapa[Posicao->row+1][Posicao->column] == '[') || (mapa[Posicao->row+1][Posicao->column] == ']') || (mapa[Posicao->row+1][Posicao->column] == '-'))        
            return -1;
        else if(mapa[Posicao->row+1][Posicao->column] == ' ')   
            return 0;  
        else if(mapa[Posicao->row+1][Posicao->column] == 'o')
            return 3;  
        else 
            return 1;                                       
    }
    else {
        printf("\nErro: tecla invalida\n");
        return 2;
    }
}

void Troca (char mapa [7][23], char mov, struct localizacao *Posicao) {

    if (mov == 'a' || mov == 'D') {                    //<-- MOVE P/ ESQUERDA
        char aux = mapa[Posicao->row][Posicao->column];
        mapa[Posicao->row][Posicao->column] = mapa[Posicao->row][Posicao->column-1];
        mapa[Posicao->row][Posicao->column-1] = aux;
        Posicao->row = Posicao->row;
        Posicao->column = Posicao->column-1;
    }
    else if (mov == 'd' || mov == 'C') {               //<-- MOVE P/ DIREITA
        char aux = mapa[Posicao->row][Posicao->column];
        mapa[Posicao->row][Posicao->column] = mapa[Posicao->row][Posicao->column+1];
        mapa[Posicao->row][Posicao->column+1] = aux;
        Posicao->row = Posicao->row;
        Posicao->column = Posicao->column+1;
    }
    else if (mov == 'w' || mov == 'A') {               //<-- MOVE P/ CIMA
        char aux = mapa[Posicao->row][Posicao->column];
        mapa[Posicao->row][Posicao->column] = mapa[Posicao->row-1][Posicao->column];
        mapa[Posicao->row-1][Posicao->column] = aux;      
        Posicao->row = Posicao->row-1;
        Posicao->column = Posicao->column;                       
    }
    else if (mov == 's' || mov == 'B') {               //<-- MOVE P/ BAIXO
        char aux = mapa[Posicao->row][Posicao->column];
        mapa[Posicao->row][Posicao->column] = mapa[Posicao->row+1][Posicao->column];
        mapa[Posicao->row+1][Posicao->column] = aux;      
        Posicao->row = Posicao->row+1;
        Posicao->column = Posicao->column;                         
    }
}

void Empilhar (struct topo *Pilha_igredientes, char mapa [7][23], struct localizacao *Posicao, char mov) {
    switch (mov) {
    case 'a':
        Push(Pilha_igredientes, mapa[Posicao->row][Posicao->column-2]);
        break;
    case 'D':
        Push(Pilha_igredientes, mapa[Posicao->row][Posicao->column-2]);
        break;
    case 'd':
        Push(Pilha_igredientes, mapa[Posicao->row][Posicao->column+2]);
        break;
    case 'C':
        Push(Pilha_igredientes, mapa[Posicao->row][Posicao->column+2]);
        break;
    case 'w':
        Push(Pilha_igredientes, mapa[Posicao->row-1][Posicao->column]);
        break;
    case 'A':
        Push(Pilha_igredientes, mapa[Posicao->row-1][Posicao->column]);
        break;
    case 's':
        Push(Pilha_igredientes, mapa[Posicao->row+1][Posicao->column]);
        break;
    case 'B':
        Push(Pilha_igredientes, mapa[Posicao->row+1][Posicao->column]);
        break;
    }
}

void destroiRefeicao (struct topo *Pilha_igredientes) {
    int i = 1;
    while ( i <= Pilha_igredientes->tam) 
        Pop(Pilha_igredientes);
    
}

int verificaPedido(struct topo *Pilha_igredientes, struct lista_dupla *Fila_pedidos) {
    printf("\nCodigo: %i\n",Fila_pedidos->cabeca->codigo);
    switch (Fila_pedidos->cabeca->codigo) {

        case 1: {      //X-Burguer
            char igredientes[4] = {"pHQP"};
            int i;
            struct nodo_simples *aux = Pilha_igredientes->cabeca;
            for (i = 0; i < 4; i++) {
                if (igredientes[i] != aux->igrediente)
                    return -1;
                aux = aux->prox;
            }
            break;
        }
        case 2: {      //X-Salada
            char igredientes[5] = {"pHQSP"};
            int i;
            struct nodo_simples *aux = Pilha_igredientes->cabeca;
            for (i = 0; i < 5; i++) {
                if (igredientes[i] != aux->igrediente)
                    return -1;
                aux = aux->prox;
            }
            break;
        }
        case 3: {      //Combo 1
            char igredientes[6] = {"pHQPFR"};
            int i;
            struct nodo_simples *aux = Pilha_igredientes->cabeca;
            for (i = 0; i < 6; i++) {
                if (igredientes[i] != aux->igrediente)
                    return -1;
                aux = aux->prox;
            }
            break;
        }
        case 4: {      //Combo 2
            char igredientes[7] = {"pHQSPFR"};
            int i;
            struct nodo_simples *aux = Pilha_igredientes->cabeca;
            for (i = 0; i < 7; i++) {
                if (igredientes[i] != aux->igrediente)
                    return -1;
                aux = aux->prox;
            }
            break;
        }
        case 5: {      //Vegetariano
            char igredientes[5] = {"pQPFR"};
            int i;
            struct nodo_simples *aux = Pilha_igredientes->cabeca;
            for (i = 0; i < 5; i++) {
                if (igredientes[i] != aux->igrediente)
                    return -1;
                aux = aux->prox;
            }
            break;
        }
        case 6: {      //Vegano
            char igredientes[3] = {"SFR"};
            int i;
            struct nodo_simples *aux = Pilha_igredientes->cabeca;
            for (i = 0; i < 3; i++) {
                if (igredientes[i] != aux->igrediente)
                    return -1;
                aux = aux->prox;
            }
            break;
        }
    }
    return 0;
}

int Andar (char mapa[7][23], struct desempenho *Status, struct localizacao *Posicao, struct topo *Pilha_igredientes, struct lista_dupla *Fila_pedidos) {
    
    printf("\nMovimento [a,s,d,w ou setas]: ");
    char string_mov[10];
    char mov;
    scanf("%s", string_mov);

    if (string_mov[0] == 'a' || (string_mov[0] == 'w' || (string_mov[0] == 's' || string_mov[0] == 'd')))
        mov = string_mov[0];
    else {
        mov = string_mov[2];
    }
                 
    int operacao = Checar_troca(mapa, mov, Posicao);
    if (operacao == 4) {
        while (operacao == 4) {
            printf("Movimento [a,s,d,w ou setas]:");
            scanf("%s", &mov);
            operacao = Checar_troca(mapa, mov, Posicao);
        }
    }
    switch (Checar_troca(mapa, mov, Posicao)) {
        case -1:                                            //encontrou uma parede, não há troca
            break;
        case 0:                                             //espaco vazio, pode trocar
            Troca(mapa, mov, Posicao);
            break;
        case 1:                                             //pegar igrediente
            Empilhar(Pilha_igredientes, mapa, Posicao, mov);
            break;
        case 2:                                             //entregar pedido
            if (Pilha_igredientes->tam != 0){
                if (verificaPedido(Pilha_igredientes, Fila_pedidos) == 0) 
                    Status->num_exito = Status->num_exito + 1;
                else
                    Status->num_erros = Status->num_erros + 1;
                Excluir_nodo_fila(Fila_pedidos);
                destroiRefeicao(Pilha_igredientes);
                return 1;
            }
            break;
        case 3:                                             //descartar pedido
            if (Pilha_igredientes->tam != 0) {
                Status->num_lixo = Status->num_lixo + 1;
                destroiRefeicao(Pilha_igredientes);
                printf("\nIGREDIENTE FOI DE AMERICANAS\n");
            }
            break;
        case 4:                                             //tecla invalida
            break;

    }
    return 0;
}