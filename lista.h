#pragma once
#include <stdio.h>
#include <stdlib.h>

struct no{
    int grey;
    int red;
    int green;
    int blue;
    int indice;
    struct no* next;
    struct no* prev;
};

struct lista{
    struct no* first;
    struct no* last;
};

void inicializaLista(struct lista** point){
    struct lista* novo = (struct lista*)malloc(sizeof(struct lista));
    if(novo == NULL){
        printf("\nERRO DE ALOCACAO\n");
        return;
    }
    novo->first = NULL;
    novo->last = NULL;
    *point = novo;
}

void insereLista(struct lista** point, int cinza, int vermelho, int verde, int azul){
    struct no *novo = (struct no*)malloc(sizeof(struct no));
    if(novo == NULL){
        printf("\nERRO DE ALOCACAO\n");
        return;
    }
    novo->next = NULL;
    novo->prev = NULL;
    novo->grey = cinza;
    novo->red = vermelho;
    novo->green = verde;
    novo->blue = azul;
    novo->indice = 0;
    struct lista *ptr = *point;
    if( ptr->first == NULL){
        ptr->first = novo;
        ptr->last = novo;
        return;
    }
    else{
        struct no* ultimo = ptr->last;
        ultimo->next = novo;
        novo->prev = ultimo;
        ptr->last = novo;
    }
    return;
}

void insereListaOrdenada(struct lista **point, int indice, int cinza, int vermelho, int verde, int azul){
	struct no *novo = (struct no*)malloc(sizeof(struct no));
	if(novo == NULL){
		printf("\nERRO DE ALOCAÇÃO\n");
		return;
	}
	novo->next = NULL;
	novo->prev = NULL;
	novo->grey = cinza;
	novo->red = vermelho;
	novo->green = verde;
	novo->blue = azul;
	novo->indice = indice;
	struct lista *ptr = *point;
	if(ptr->first == NULL){
		//printf("\nprimeira inserção");
		ptr->first = novo;
		ptr->last = novo;
		return;
	}
	if((novo->indice < ptr->first->indice)&&(ptr->first->prev == NULL)){
        //printf("\ninserção antes do primeiro");
        novo->next = ptr->first;
        ptr->first->prev = novo;
        ptr->first = novo;
        return;
	}
	struct no *ultimo = ptr->last;
	if(novo->indice > ultimo->indice){
		//printf("\ninserção do %d depois do %d", novo->indice, ultimo->indice);
		ultimo->next = novo;
		novo->prev = ultimo;
		ptr->last = novo;
		return;
	}
	struct no* penultimo = ultimo->prev;
	if((novo->indice < ultimo->indice)&&(novo->indice > penultimo->indice)){
	    //printf("\ninserindo o %d entre o %d e o %d", novo->indice, penultimo->indice, ultimo->indice);
		penultimo->next = novo;
		novo->prev = penultimo;
		novo->next = ultimo;
		ultimo->prev = novo;
		return;
	}
	//)printf("\ntek2");
	struct no* busca = ptr->first;
	while(busca->next != NULL){
		if(busca->indice > novo->indice){
            if(busca->prev == NULL){
                //printf("\ninserindo o %d antes do %d", novo->indice, busca->indice);
                busca->prev = novo;
                novo->next = busca;
                ptr->first = novo;
                return;
            }
            else{
                //printf("\ninserindo o %d entre o %d e o %d", novo->indice, busca->prev->indice, busca->indice);
                novo->prev = busca->prev;
                busca->prev->next = novo;
                novo->next = busca;
                busca->prev = novo;
                return;
            }
        }
		busca = busca->next;
	}
}

void zerarIndice(struct lista **point){
    if(point == NULL) {
        printf("\nLISTA NAO EXISTE\n");
        return;
    }
    struct lista *ptr = *point;
    struct no *busca = ptr->first;
    if(busca == NULL){
        printf("\nLISTA NAO EXISTE\n");
        return;
    }
    while(busca != NULL){
        busca->indice = 0;
        busca = busca->next;;
    }
    return;
}

void indexarLista(struct lista **point){
    if(point == NULL) {
        printf("\nLISTA NAO EXISTE\n");
        return;
    }
    struct lista *ptr = *point;
    struct no *busca = ptr->first;
    if(busca == NULL){
        printf("\nLISTA NAO EXISTE\n");
        return;
    }
    int cont=0;
    while(busca != NULL){
        busca->indice = cont;
        busca = busca->next;
        cont++;
    }
    return;
}


