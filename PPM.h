#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct PPMimagem{
    short magic;
    short largura;
    short altura;
    short cor;
    struct lista *pixels;
};

void PPMabreMat(FILE *dat, struct PPMimagem **pic){
    printf("\nTENTANDO ABRIR MATRIZ PPM\n");
    struct PPMimagem *mat=(struct PPMimagem*)malloc(sizeof(struct PPMimagem));
    if( mat == NULL){
        printf("\nerro de alocacao\n");
        return;
    }
    int largura, altura, cor, magic;
    fscanf(dat, "P%d\n", &magic);
    fscanf(dat, "%d %d\n", &largura, &altura);
    fscanf(dat, "%d\n", &cor);
    int nPixels = largura * altura;
    mat->magic = magic;
    mat->largura = largura;
    mat->altura = altura;
    mat->cor = cor;
    inicializaLista(&mat->pixels);
    for(int i=0; i<nPixels; i++){
            int red;
            int green;
            int blue;
            fscanf(dat, "%d\n%d\n%d\n", &red, &green, &blue);
            insereLista(&mat->pixels, 0, red, green, blue);
    }
    *pic = mat;
    printf("MATRIZ ABERTA COM SUCESSO\n");
    indexarLista(&mat->pixels);
}

void PPMgravaMat(FILE *dat, struct PPMimagem *mat){
    printf("\nTENTANDO GRAVAR MATRIZ PPM\n");
    fprintf(dat, "P%d\n", mat->magic);
    fprintf(dat, "%d %d\n", mat->largura, mat->altura);
    fprintf(dat, "%d\n", mat->cor);
    struct no *busca = mat->pixels->first;
    while(busca != NULL){
        fprintf(dat, "%d\n", busca->red);
        fprintf(dat, "%d\n", busca->green);
        fprintf(dat, "%d\n", busca->blue);
        busca = busca->next;
    }
    printf("MATRIZ PPM GRAVADA COM SUCESSO\n");
}

void PPMimprimeImagem(struct PPMimagem *mat){
    if( mat == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    struct no *point = mat->pixels->first;
    if(point == NULL) {
        printf("\nLISTA NAO EXISTE\n");
        return;
    }
    while(point != NULL){
        if(point->indice % 4 == 0) printf("\n");
        printf("linha %5d = |%3d %3d %3d|\n", point->indice, point->red, point->green, point->blue);
        point = point->next;
    }
    printf("\n");
    return;
}

void PPMcopiaImagem(struct PPMimagem *picOrig, struct PPMimagem **picNova){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    printf("\nINICIANDO COPIA MATRIZ PPM\n");
    struct PPMimagem *mat = (struct PPMimagem*) malloc(sizeof(struct PPMimagem*));
    int altura = picOrig->altura, largura = picOrig->largura;
    int cor = picOrig->cor, magic = picOrig->magic;
    mat->altura = altura;
    mat->largura = largura;
    mat->cor = cor;
    mat->magic = magic;
    inicializaLista(&mat->pixels);
    struct no *busca = picOrig->pixels->first;
    while(busca != NULL){
        int red = busca->red;
        int green = busca->green;
        int blue = busca->blue;
        insereLista(&mat->pixels, 0, red, green, blue);
        busca = busca->next;
    }
    *picNova = mat;
    printf("COPIA FEITA COM SUCESSO\n");
}

void PPMclarearImagem(struct PPMimagem *picOrig, struct PPMimagem **picNova, int fator){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    printf("\nINICIANDO CLAREAMENTO DA MATRIZ PPM\n");
    struct PPMimagem *mat = (struct PPMimagem*) malloc(sizeof(struct PPMimagem*));
    int altura = picOrig->altura, largura = picOrig->largura;
    int cor = picOrig->cor, magic = picOrig->magic;
    mat->altura = altura;
    mat->largura = largura;
    mat->cor = cor;
    mat->magic = magic;
    inicializaLista(&mat->pixels);
    struct no *busca = picOrig->pixels->first;
    while(busca != NULL){
        int soma1 = busca->red + fator;
        int soma2 = busca->green + fator;
        int soma3 = busca->blue + fator;
        if( soma1 > cor ) soma1 = cor;
        if( soma2 > cor ) soma2 = cor;
        if( soma3 > cor ) soma3 = cor;
        insereLista(&mat->pixels, 0, soma1, soma2, soma3);
        busca = busca->next;
    }
    *picNova = mat;
    printf("MATRIZ CLAREADA COM SUCESSO\n");
}

void PPMescureceImagem(struct PPMimagem *picOrig, struct PPMimagem **picNova, int fator){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    printf("\nINICIANDO ESCURECIMENTO DA MATRIZ PPM\n");
    struct PPMimagem *mat = (struct PPMimagem*) malloc(sizeof(struct PPMimagem*));
    int altura = picOrig->altura, largura = picOrig->largura;
    int cor = picOrig->cor, magic = picOrig->magic;
    mat->altura = altura;
    mat->largura = largura;
    mat->cor = cor;
    mat->magic = magic;
    inicializaLista(&mat->pixels);
    struct no *busca = picOrig->pixels->first;
    while(busca != NULL){
        int dif1 = busca->red - fator;
        int dif2 = busca->green - fator;
        int dif3 = busca->blue - fator;
        if( dif1 < 0 ) dif1 = 0;
        if( dif2 < 0 ) dif2 = 0;
        if( dif3 < 0 ) dif3 = 0;
        insereLista(&mat->pixels, 0, dif1, dif2, dif3);
        busca = busca->next;
    }
    *picNova = mat;
    printf("MATRIZ ESCURECIDA COM SUCESSO\n");
}

void PPMrotacionarImagem(struct PPMimagem *picOrig, struct PPMimagem **picNova, int check){
    if(check)
        printf("\nINICIANDO ROTACAO QUADRADA\n");
    else
        printf("\nINICIANDO ROTACAO RETANGULAR\n");
    struct PPMimagem *mat = (struct PPMimagem*) malloc(sizeof(struct PPMimagem*));
    int altura = picOrig->altura, largura = picOrig->largura;
    int cor = picOrig->cor, magic = picOrig->magic;
    int nPixels = largura * altura;
    if(check){
        mat->altura = altura;
        mat->largura = largura;
    }
    else{
        mat->altura = largura;
        mat->largura = altura;
    }
    mat->cor = cor;
    mat->magic = magic;
    inicializaLista(&mat->pixels);
    struct no *busca = picOrig->pixels->first;
    for(int i=0; i<nPixels; i++){
        busca->indice = (busca->indice % largura)*altura+(altura-(busca->indice/largura)-1);
        busca = busca->next;
    }
    struct no *atual = picOrig->pixels->first;
    while(atual != NULL){
        insereListaOrdenada(&mat->pixels, atual->indice, atual->grey, atual->red, atual->green, atual->blue);
        atual = atual->next;
    }
    *picNova = mat;
}

void PPMrotate(struct PPMimagem *picOrig, struct PPMimagem **picNova){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    if(picOrig->largura == picOrig->altura)PPMrotacionarImagem(picOrig, picNova, 1);
    else PPMrotacionarImagem(picOrig, picNova, 0);
    printf("ROTACAO CONCLUIDA\n");
}

void PPMnegative(struct PPMimagem *picOrig, struct PPMimagem **picNova){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    printf("\nINICIANDO NEGATIVAÇÃO DE MATRIZ PPM\n");
    struct PPMimagem *mat = (struct PPMimagem*) malloc(sizeof(struct PPMimagem*));
    int altura = picOrig->altura, largura = picOrig->largura;
    int cor = picOrig->cor, magic = picOrig->magic;
    mat->altura = altura;
    mat->largura = largura;
    mat->cor = cor;
    mat->magic = magic;
    inicializaLista(&mat->pixels);
    struct no *busca = picOrig->pixels->first;
    while(busca != NULL){
        int red = (cor-1) - busca->red;
        int green = (cor-1) - busca->green;
        int blue = (cor-1) - busca->blue;
        insereLista(&mat->pixels, 0, red, green, blue);
        busca = busca->next;
    }
    *picNova = mat;
    printf("NEGATIVAÇÃO FEITA COM SUCESSO\n");
}
