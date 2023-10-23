#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "beale.h"
#include "encode.h"
#include "decode.h"
#include "arq_chave.h"

int main (int argc, char *argv[]) {

    setlocale(LC_ALL, "");
    setlocale (LC_CTYPE, "pt_BR.UTF-8"); // por via das dúvidas

    /*Linha de execucao para codificar*/
    if ((argc == 10) && (strcmp(argv[1], "-e") == 0)) {
        if((strcmp(argv[2], "-b") == 0) && (strcmp(argv[4], "-m") == 0) && (strcmp(argv[6], "-o") == 0) && (strcmp(argv[8], "-c") == 0)) {
            
            FILE* livroCifra = fopen(argv[3], "r");
            if (! livroCifra) {
                printf("Erro: nao foi possivel abrir o arquivo.\n");
                exit (1);
            }

            struct lista_caracteres* L_caracteres = malloc(sizeof(struct lista_caracteres));
            L_caracteres = Criar_lista(livroCifra, L_caracteres);
            Criar_chaves(L_caracteres, livroCifra);
            fclose(livroCifra);

            FILE* ArqChaves = fopen(argv[9], "w+");
            if (! ArqChaves) {
                printf("Erro: nao foi possivel abrir o arquivo.\n");
                exit (1);
            }

            Criar_ArqChaves(ArqChaves, L_caracteres);
            fclose(ArqChaves);

            FILE* mensagemOriginal = fopen(argv[5], "r");
            FILE* mensagemCodificada = fopen(argv[7], "w+");
            if (! (mensagemOriginal && mensagemCodificada)) {
                printf("Erro: nao foi possivel abrir o arquivo.\n");
                exit (1);
            }

            Codificar(mensagemOriginal, mensagemCodificada, L_caracteres);

            Limpeza(L_caracteres);
            
            fclose(mensagemOriginal);
            fclose(mensagemCodificada);
        }
        else {
            printf("\nErro: linha de comando incorreta. Opcoes disponiveis: \n");
            printf("1) ./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves\n");
            printf("2) ./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada\n");
            printf("3) ./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada \n\n");
        }
    }
    /*Liha de execucao para decodificar*/
    else if ((argc == 8) && (strcmp(argv[1], "-d") == 0)) {
        if ((strcmp(argv[2], "-i") == 0) && (strcmp(argv[6], "-o") == 0)) {

            /* Decodificar usando um arq de codigos*/
            if (strcmp(argv[4], "-c") == 0) {

                FILE* mensagemCodificada = fopen(argv[3], "r");
                FILE* ArqChaves = fopen(argv[5], "r");
                FILE* mensagemDecodificada = fopen(argv[7], "w+");
                if (! (mensagemCodificada && mensagemDecodificada)) {
                    printf("Erro: nao foi possivel abrir o arquivo.\n");
                    exit (1);
                }

                Decodificar_com_ArqChaves(mensagemCodificada, mensagemDecodificada, ArqChaves);

                fclose(mensagemCodificada);
                fclose(ArqChaves);
                fclose(mensagemDecodificada);
            }

            /* Decodificar usando o livro cifra*/
            else if (strcmp(argv[4], "-b") == 0) {
                
                FILE* mensagemCodificada = fopen(argv[3], "r");
                FILE* livroCifra = fopen(argv[5], "r");
                FILE* mensagemDecodificada = fopen(argv[7], "w+");
                if (! (mensagemCodificada && mensagemDecodificada)) {
                    printf("Erro: nao foi possivel abrir o arquivo.\n");
                    exit (1);
                }

                Decodificar_com_LivroCifra(mensagemCodificada, mensagemDecodificada, livroCifra);

                fclose(mensagemCodificada);
                fclose(livroCifra);
                fclose(mensagemDecodificada);
            }
        }
        else {
            printf("\nErro: linha de comando incorreta. Opcoes disponiveis: \n");
            printf("1) ./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves\n");
            printf("2) ./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada\n");
            printf("3) ./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada \n\n");
        }
    }
    /*Linha de execucao invalida*/
    else {
        printf("\nErro: linha de comando incorreta. Opcoes disponiveis: \n");
        printf("1) ./beale  -e  -b LivroCifra -m MensagemOriginal -o MensagemCodificada -c ArquivoDeChaves\n");
        printf("2) ./beale  -d  -i MensagemCodificada  -c ArquivoDeChaves  -o MensagemDecodificada\n");
        printf("3) ./beale -d -i MensagemCodificada -b LivroCifra -o MensagemDecodificada \n\n");
    }
        
    return 0;
}