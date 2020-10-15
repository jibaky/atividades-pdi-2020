#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "PGM.h"
#include "PPM.h"

void PPMdecompose(struct PPMimagem* PointColor, struct PGMimagem** pointR, struct PGMimagem** pointG, struct PGMimagem** pointB){
    printf("\nTENTANDO DECOMPOR A IMAGEM PPM\n");
    int nPixels = PointColor->largura * PointColor->altura;
    struct PGMimagem *imR=(struct PGMimagem*)malloc(sizeof(struct PGMimagem));
    if( imR == NULL){
        printf("\nerro de alocacao strR\n");
        return;
    }
    struct PGMimagem *imG=(struct PGMimagem*)malloc(sizeof(struct PGMimagem));
    if( imG == NULL){
        printf("\nerro de alocacao strG\n");
        return;
    }
    struct PGMimagem *imB=(struct PGMimagem*)malloc(sizeof(struct PGMimagem));
    if( imB == NULL){
        printf("\nerro de alocacao strB\n");
        return;
    }
    struct no* imC= PointColor->pixels->first;
    imR->altura = PointColor->altura;
    imR->largura = PointColor->largura;
    imR->magic = 2;
    imR->cor = PointColor->cor;
    inicializaLista(&imR->pixels);
    imG->altura = PointColor->altura;
    imG->largura = PointColor->largura;
    imG->magic = 2;
    imG->cor = PointColor->cor;
    inicializaLista(&imG->pixels);
    imB->altura = PointColor->altura;
    imB->largura = PointColor->largura;
    imB->magic = 2;
    imB->cor = PointColor->cor;
    inicializaLista(&imB->pixels);
    for(int i=0; i<nPixels; i++){
        insereLista(&imR->pixels, imC->red, 0, 0, 0);
        insereLista(&imG->pixels, imC->green, 0, 0, 0);
        insereLista(&imB->pixels, imC->blue, 0, 0, 0);
        imC = imC->next;
    }
    *pointR = imR;
    *pointG = imG;
    *pointB = imB;
    printf("IMAGEM DECOMPOSTA COM SUCESSO\n");
}

void PGMrecompose(struct PPMimagem** pointColor, struct PGMimagem* pointR, struct PGMimagem* pointG, struct PGMimagem* pointB){
    printf("\nTENTANDO RECOMPOR OS PGMs EM UMA IMAGEM PPM\n");
    int nPixels = pointR->largura * pointR->altura;
    struct PPMimagem* imC = (struct PPMimagem*)malloc(sizeof(struct PPMimagem));
    if(imC == NULL){
        printf("\nerro de alocacao imC\n");
        return;
    }
    struct no* imR = pointR->pixels->first;
    struct no* imG = pointG->pixels->first;
    struct no* imB = pointB->pixels->first;
    imC->altura = pointR->altura;
    imC->largura = pointR->largura;
    imC->magic = 3;
    imC->cor = pointR->cor;
    inicializaLista(&imC->pixels);
    for(int i=0; i<nPixels; i++){
        insereLista(&imC->pixels, 0, imR->grey, imG->grey, imB->grey);
        imR = imR->next;
        imG = imG->next;
        imB = imB->next;
    }
    *pointColor = imC;
    printf("IMAGEM RECOMPOSTA COM SUCESSO\n");
}
