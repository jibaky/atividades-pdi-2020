#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "PGM.h"
#include "PPM.h"
#include "AT2.h"
#include "AT3.h"

#define SIZE 55

int main(){
    setlocale(LC_ALL,"portuguese");
    printf("\n** Os caminhos de abertura de arquivo devem ter no maximo 50 caracteres, ou o codigo pode nao funcionar normalmente **\n");
    int choice, tipo;
    FILE *arq1, *arq2;
    char abrir[SIZE], gravar[SIZE], ext[4];
    char copiaAbrir[SIZE];
    struct PGMimagem *im1 = NULL;
    struct PGMimagem *im2 = NULL;
    struct PPMimagem *im3 = NULL;
    struct PPMimagem *im4 = NULL;

    while(1){
        printf("Introduza um numero entre 0 e 4 para escolher a operacao.");
        printf("\n0 - Sair.\n1 - Clarear.\n2 - Escurecer.\n3 - Copiar.");
        printf("\n4 - Rotacionar 90 graus no sentido horario.\n5 - Negativo");
        printf("\n6 - Decompor PPM em PGM.");
        printf("\n7 - Recompor PPM.\n8 - Fatiamento de Niveis de Intensidade.");
        printf("\n9 - Transformacao Gama.\n10 - Flip Horizontal.");
        printf("\nNumero ");
        scanf("%d", &choice);
        if((choice>=0) && (choice <11)) break;
    }
    if(choice != 0){
        if((choice == 6) || (choice == 7)){
            FILE  *arqR, *arqG, *arqB;
            char strR[SIZE],strG[SIZE],strB[SIZE];
            struct PGMimagem *imR = NULL;
            struct PGMimagem *imG = NULL;
            struct PGMimagem *imB = NULL;
            if(choice == 6){
                printf("\narquivo a ser aberto\n");
                printf("*nao colocar arquivos com espaco ou a extensao do arquivo*\n");
                scanf("%s", &abrir);
                strcpy(strR, abrir);
                strcat(strR, "5R.pgm");
                strcpy(strG, abrir);
                strcat(strG, "5G.pgm");
                strcpy(strB, abrir);
                strcat(strB, "5B.pgm");
                strcat(abrir, ".ppm");
                arq1 = fopen(abrir, "r");
                if(arq1 == NULL){
                    printf("\nERRO NA ABERTURA DO ARQ1\n");
                    return 0;
                }
                PPMabreMat(arq1, &im3);
                arqR = fopen(strR, "w");
                if(arqR == NULL){
                    printf("\nERRO NA ABERTURA DO ARQR\n");
                    return 0;
                }
                arqG = fopen(strG, "w");
                if(arqG == NULL){
                    printf("\nERRO NA ABERTURA DO ARQG\n");
                    return 0;
                }
                arqB = fopen(strB, "w");
                if(arqG == NULL){
                    printf("\nERRO NA ABERTURA DO ARQG\n");
                    return 0;
                }

                PPMdecompose(im3, &imR, &imG, &imB);
                PGMgravaMat(arqR, imR);
                PGMgravaMat(arqG, imG);
                PGMgravaMat(arqB, imB);
                fclose(arq1);
                fclose(arqR);
                fclose(arqG);
                fclose(arqB);
                system("pause");
                return 0;
            }
            else if(choice == 7){
                printf("*nao colocar arquivos com espaco ou a extensao do arquivo*\n");
                printf("\narquivo a ser aberto no canal vermelho\n");
                scanf("%s", &strR);
                printf("\narquivo a ser aberto no canal verde\n");
                scanf("%s", &strG);
                printf("\narquivo a ser aberto no canal azul\n");
                scanf("%s", &strB);
                printf("\narquivo a ser salvo o .ppm\n");
                scanf("%s", &gravar);
                strcat(strR, ".pgm");
                strcat(strG, ".pgm");
                strcat(strB, ".pgm");
                strcat(gravar, "6.ppm");
                arqR = fopen(strR, "r");
                if(arqR == NULL){
                    printf("\nERRO NA ABERTURA DO ARQR\n");
                    return 0;
                }
                arqG = fopen(strG, "r");
                if(arqG == NULL){
                    printf("\nERRO NA ABERTURA DO ARQG\n");
                    return 0;
                }
                arqB = fopen(strB, "r");
                if(arqB == NULL){
                    printf("\nERRO NA ABERTURA DO ARQB\n");
                    return 0;
                }
                arq2 = fopen(gravar, "w");
                if(arq2 == NULL){
                    printf("\nERRO NA ABERTURA DO ARQ2\n");
                    return 0;
                }
                PGMabreMat(arqR, &imR);
                PGMabreMat(arqG, &imG);
                PGMabreMat(arqB, &imB);
                PGMrecompose(&im4, imR, imG, imB);
                PPMgravaMat(arq2, im4);
                fclose(arq2);
                fclose(arqR);
                fclose(arqG);
                fclose(arqB);
                system("pause");
                return 0;
            }
        }
        while(1){
            printf("\nQual a extensao da imagem?\n 0 - .pgm\n 1 - .ppm\n");
            scanf("%d", &tipo);
            if((tipo==0) || (tipo==1)) break;
        }

        printf("\narquivo a ser aberto\n");
        printf("*nao colocar arquivos com espaco ou a extensao do arquivo*\n");

        scanf("%s", &abrir);
        strcpy(copiaAbrir, abrir);
        if(tipo)strcat(abrir, ".ppm");
        else strcat(abrir, ".pgm");
        arq1 = fopen(abrir, "r");
        if(arq1 == NULL){
            printf("\nERRO NA ABERTURA DO ARQ1\n");
            return 0;
        }
        if(tipo)PPMabreMat(arq1, &im3);
        else PGMabreMat(arq1, &im1);
        fclose(arq1);
        strcpy(gravar, copiaAbrir);
        char to_char = (char)(48 + choice);
        strcat(gravar,&to_char);
        if(tipo)strcat(gravar, ".ppm");
        else strcat(gravar, ".pgm");
        printf("\n%s\n", gravar);
        if(choice == 1){
            arq2 = fopen(gravar, "w");
            if(arq2 == NULL){
                printf("\nERRO NA ABERTURA DO ARQ2\n");
                return 0;
            }
            if(tipo){
                PPMclarearImagem(im3, &im4, 50);
                PPMgravaMat(arq2, im4);
            }
            else{
                PGMclarearImagem(im1, &im2, 50);
                PGMgravaMat(arq2, im2);
            }
            fclose(arq2);
        }
        else if(choice == 2){
            arq2 = fopen(gravar, "w");
            if(arq2 == NULL){
                printf("\nERRO NA ABERTURA DO ARQ2\n");
                return 0;
            }
            if(tipo){
                PPMescureceImagem(im3, &im4, 50);
                PPMgravaMat(arq2, im4);
            }
            else{
                PGMescureceImagem(im1, &im2, 50);
                PGMgravaMat(arq2, im2);
            }
            fclose(arq2);
        }
        else if(choice == 3){
            arq2 = fopen(gravar, "w");
            if(arq2 == NULL){
                printf("\nERRO NA ABERTURA DO ARQ2\n");
                return 0;
            }
            if(tipo){
                PPMcopiaImagem(im3, &im4);
                PPMgravaMat(arq2, im4);
            }
            else{
                PGMcopiaImagem(im1, &im2);
                PGMgravaMat(arq2, im2);
            }
            fclose(arq2);
        }
        else if(choice == 4){
            arq2 = fopen(gravar, "w");
            if(arq2 == NULL){
                printf("\nERRO NA ABERTURA DO ARQ2\n");
                return 0;
            }
            if(tipo){
                PPMrotate(im3, &im4);
                PPMgravaMat(arq2, im4);
            }
            else{
                PGMrotate(im1, &im2);
                PGMgravaMat(arq2, im2);
            }
            fclose(arq2);
        }
        else if(choice == 5){
            arq2 = fopen(gravar, "w");
            if(arq2 == NULL){
                printf("\nERRO NA ABERTURA DO ARQ2\n");
                return 0;
            }
            if(tipo){
                PPMnegative(im3, &im4);
                PPMgravaMat(arq2, im4);
            }
            else{
                PGMnegative(im1, &im2);
                PGMgravaMat(arq2, im2);
            }
            fclose(arq2);
        }
        else if(choice == 8){
            arq2 = fopen(gravar, "w");
            if(arq2 == NULL){
                printf("\nERRO NA ABERTURA DO ARQ2\n");
                return 0;
            }
            if(tipo){
                printf("\nainda nao foi implementado\n");
                return 0;
            }
            else{
                PGMfatiamento(im1, &im2, 50, 0, 50);
                PGMgravaMat(arq2, im2);
            }
        }
        else if(choice == 9){
            arq2 = fopen(gravar, "w");
            if(arq2 == NULL){
                printf("\nERRO NA ABERTURA DO ARQ2\n");
                return 0;
            }
            if(tipo){
                printf("\nainda nao foi implementado\n");
                return 0;
            }
            else{
                PGMgamma(im1, &im2, 1, 5, 0, 255);
                PGMgravaMat(arq2, im2);
            }
        }
        else if(choice == 10){
            arq2 = fopen(gravar, "w");
            if(arq2 == NULL){
                printf("\nERRO NA ABERTURA DO ARQ2\n");
                return 0;
            }
            if(tipo){
                PPMflipHorizontal(im3, &im4);
                PPMgravaMat(arq2, im4);
            }
            else{
                PGMflipHorizontal(im1, &im2);
                PGMgravaMat(arq2, im2);
            }
        }
    }
    system("pause");
}
