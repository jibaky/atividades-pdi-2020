#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct PGMimagem{
    short magic;
    short largura;
    short altura;
    short cor;
    struct lista *pixels;
};

void PGMabreMat(FILE *dat, struct PGMimagem **pic){
    printf("\nTENTANDO ABRIR MATRIZ PGM\n");
    struct PGMimagem *mat=(struct PGMimagem*)malloc(sizeof(struct PGMimagem));
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
        int current;
        fscanf(dat, "%d\n", &current);
        insereLista(&mat->pixels, current, 0, 0, 0);
    }
    *pic = mat;
    printf("MATRIZ ABERTA COM SUCESSO\n");
    indexarLista(&mat->pixels);
}

void PGMgravaMat(FILE *dat, struct PGMimagem *mat){
    printf("\nTENTANDO GRAVAR MATRIZ PGM\n");
    fprintf(dat, "P%d\n", mat->magic);
    fprintf(dat, "%d %d\n", mat->largura, mat->altura);
    fprintf(dat, "%d\n", mat->cor);
    struct no *busca = mat->pixels->first;
    while(busca != NULL){
        fprintf(dat, "%d\n", busca->grey);
        busca = busca->next;
    }
    printf("MATRIZ PGM GRAVADA COM SUCESSO\n");
}

void PGMimprimeImagem(struct PGMimagem *mat){
    int cont=0;
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
        if((cont % 6 == 0)&&(cont != 0)) printf("\n");
        printf("linha %5d = |%3d| ", point->indice, point->grey);
        point = point->next;
        cont++;
    }
    printf("\n");
    return;
}

void PGMcopiaImagem(struct PGMimagem *picOrig, struct PGMimagem **picNova){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    printf("\nINICIANDO COPIA MATRIZ PGM\n");
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
        int current = busca->grey;
        insereLista(&mat->pixels, current, 0, 0, 0);
        busca = busca->next;
    }
    *picNova = mat;
    printf("COPIA FEITA COM SUCESSO\n");
}

void PGMclarearImagem(struct PGMimagem *picOrig, struct PGMimagem **picNova, int fator){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    printf("\nINICIANDO CLAREAMENTO DA MATRIZ PGM\n");
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
        int soma = busca->grey + fator;
        if( soma > cor )insereLista(&mat->pixels, cor, 0, 0, 0);
        else insereLista(&mat->pixels, soma, 0, 0, 0);
        busca = busca->next;
    }
    *picNova = mat;
    printf("MATRIZ CLAREADA COM SUCESSO\n");
}

void PGMescureceImagem(struct PGMimagem *picOrig, struct PGMimagem **picNova, int fator){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    printf("\nINICIANDO ESCURECIMENTO DA MATRIZ PGM\n");
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
        int diferenca = busca->grey - fator;
        if( diferenca < 0 )insereLista(&mat->pixels, 0, 0, 0, 0);
        else insereLista(&mat->pixels, diferenca, 0, 0, 0);
        busca = busca->next;
    }
    *picNova = mat;
    printf("MATRIZ ESCURECIDA COM SUCESSO\n");
}

void PGMrotacionarImagem(struct PGMimagem *picOrig, struct PGMimagem **picNova, int check){
    if(check)
        printf("\nINICIANDO ROTACAO QUADRADA\n");
    else
        printf("\nINICIANDO ROTACAO RETANGULAR\n");
    struct PGMimagem *mat = (struct PGMimagem*) malloc(sizeof(struct PGMimagem*));
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
        insereListaOrdenada(&mat->pixels, atual->indice, atual->grey, 0, 0, 0);
        atual = atual->next;
    }
    *picNova = mat;
}

void PGMrotate(struct PGMimagem *picOrig, struct PGMimagem **picNova){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    if(picOrig->largura == picOrig->altura)PGMrotacionarImagem(picOrig, picNova, 1);
    else PGMrotacionarImagem(picOrig, picNova, 0);
    printf("ROTACAO CONCLUIDA\n");
}

void PGMnegative(struct PGMimagem *picOrig, struct PGMimagem **picNova){
    if( picOrig == NULL){
        printf("\nA IMAGEM NAO EXISTE\n");
        return;
    }
    printf("\nINICIANDO NEGATIVAÇÃO DE MATRIZ PGM\n");
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
        int current = (cor-1) - busca->grey;
        insereLista(&mat->pixels, current, 0, 0, 0);
        busca = busca->next;
    }
    *picNova = mat;
    printf("NEGATIVAÇÃO FEITA COM SUCESSO\n");
}
