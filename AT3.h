#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista.h"
#include "PGM.h"
#include "PPM.h"

void PGMfatiamento(struct PGMimagem *picOrig, struct PGMimagem **picNova, double c, int boundA, int boundB){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    struct PGMimagem *mat = (struct PGMimagem*) malloc(sizeof(struct PGMimagem*));
    int altura = picOrig->altura, largura = picOrig->largura;
    int cor = picOrig->cor, magic = picOrig->magic;
    mat->altura = altura;
    mat->largura = largura;
    mat->cor = cor;
    mat->magic = magic;
    inicializaLista(&mat->pixels);
    struct no *busca = picOrig->pixels->first;
    int i=0;
    while(busca != NULL){
        if((busca->grey > boundA) && (busca->grey < boundB)){
            double r = busca->grey/255.0;
            //printf("\nB4 busca->grey = %d ,r = %d", busca->grey, r);
            r = 255 * c * log2(1+r);
            if(r>255) busca->grey = 255;
            else busca->grey = (int)r;
            //printf("\nAF busca->grey = %d ,r = %d", busca->grey, r);
        }
        insereLista(&mat->pixels, busca->grey, 0, 0, 0);
        busca = busca->next;
        i++;
    }
    *picNova = mat;
}

void PGMgamma(struct PGMimagem *picOrig, struct PGMimagem **picNova, double c, double gamma, int boundA, int boundB){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    struct PGMimagem *mat = (struct PGMimagem*) malloc(sizeof(struct PGMimagem*));
    int altura = picOrig->altura, largura = picOrig->largura;
    int cor = picOrig->cor, magic = picOrig->magic;
    mat->altura = altura;
    mat->largura = largura;
    mat->cor = cor;
    mat->magic = magic;
    inicializaLista(&mat->pixels);
    struct no *busca = picOrig->pixels->first;
    while(busca != NULL){
        if((busca->grey > boundA) && (busca->grey <boundB)){
            double valor = busca->grey/255.0;
            valor = (c*pow(valor, gamma));
            busca->grey = 255*(int)valor ;
        }
        insereLista(&mat->pixels, busca->grey, 0, 0, 0);
        busca = busca->next;
    }
    *picNova = mat;
}

void PGMflipHorizontal(struct PGMimagem *picOrig, struct PGMimagem **picNova){
    int debug = 0;
    struct PGMimagem *mat = (struct PGMimagem*) malloc(sizeof(struct PGMimagem*));
    int altura = picOrig->altura, largura = picOrig->largura;
    int cor = picOrig->cor, magic = picOrig->magic;
    int nPixels = largura * altura;
    mat->altura = altura;
    mat->largura = largura;
    mat->cor = cor;
    mat->magic = magic;
    inicializaLista(&mat->pixels);
    struct no *busca = picOrig->pixels->first;
    for(int i=0; i<altura; i++){
        int mod = largura-1;
        for(int j=0; j<largura; j++){
            busca->indice = busca->indice+mod;
            mod = mod-2;
            busca = busca->next;
        }
    }
    struct no *atual = picOrig->pixels->first;
    while(atual != NULL){
        if(debug)printf("\ntesteBeg");
        insereListaOrdenada(&mat->pixels, atual->indice, atual->grey,0,0,0);
        atual = atual->next;
        if(debug)printf("\ntesteEnd");
    }
    if(debug)printf("\nd\n");
    *picNova = mat;
}

void PPMflipHorizontal(struct PPMimagem *picOrig, struct PPMimagem **picNova){
    int debug = 0;
    struct PPMimagem *mat = (struct PPMimagem*) malloc(sizeof(struct PPMimagem*));
    int altura = picOrig->altura, largura = picOrig->largura;
    int cor = picOrig->cor, magic = picOrig->magic;
    int nPixels = largura * altura;
    mat->altura = altura;
    mat->largura = largura;
    mat->cor = cor;
    mat->magic = magic;
    inicializaLista(&mat->pixels);
    struct no *busca = picOrig->pixels->first;
    for(int i=0; i<altura; i++){
        int mod = largura-1;
        for(int j=0; j<largura; j++){
            busca->indice = busca->indice+mod;
            mod = mod-2;
            busca = busca->next;
        }
    }
    struct no *atual = picOrig->pixels->first;
    while(atual != NULL){
        if(debug)printf("\ntesteBeg");
        insereListaOrdenada(&mat->pixels, atual->indice, 0, atual->red, atual->green, atual->blue);
        atual = atual->next;
        if(debug)printf("\ntesteEnd");
    }
    if(debug)printf("\nd\n");
    *picNova = mat;
}
