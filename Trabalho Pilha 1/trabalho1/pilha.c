#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>


Pilha *create (int tam){
    Pilha *p = NULL;

    if(tam>0){
        p = malloc(sizeof(Pilha));      
        p->tamanho = tam;
        p->topo1 = -1;
        p->topo2 = tam;
        p->vetorP = malloc(sizeof(int)*tam);
    }
    return p;
}

void destroy(Pilha **p){
    free((*p)->vetorP);
    free(*p);
    *p = NULL;
}

int empty(int num, Pilha *p) {
    if (num == 1) {
        if (p->topo1 == -1) {
            printf("\nPilha Vazia! Sem objetos para Desempilhar\n");
            return 1;
        }
    }
    if (num == 2) {
        if (p->topo2 == p->tamanho) {
            printf("\nPilha Vazia! Sem objetos para Desempilhar\n");
            return 1;
        }
    }
    return 0;
}


int full(Pilha *p){
    return (p->topo1)+1 == p->topo2;
}

void restart(Pilha *p, int num){
    if(num == 1){
        p->topo1 = -1;
    }

    if(num == 2){
        p->topo2 = p->tamanho;
    }
    printf("\nPilha reiniciada com sucesso\n");
}

int empilha (Pilha *p, int num, int novo){
    if(full(p)){
        printf("\nCapacidade Máxima da Pilha atingida\n");
        return 0;
    }

    if(num == 1){
        p->topo1++;
        p->vetorP[p->topo1] = novo;
        return 1;
    }

    if(num == 2){
        p->topo2--;
        p->vetorP[p->topo2] = novo;
        return 1;
    }
    
}

int desempilha(Pilha *p, int num) {
    int valor;
    switch (num) {
        case 1:
            if (empty(1, p)) {
                return 0;
            }
            valor = p->vetorP[p->topo1];
            p->topo1--;
            return valor;
            break;
        case 2:
            if (empty(2, p)) {
                return 0;
            }
            valor = p->vetorP[p->topo2];
            p->topo2++;
            return valor;
            break;
        default:
            break;
    }
    return 0;
}

int busca(int num, Pilha *p){
    switch(num){
        case 1:
            if(empty(1,p))
                return 0;
            return p->vetorP[p->topo1];
            break;
        case 2:
            if(empty(2, p))
                return 0;
            return p->vetorP[p->topo2];
            break;
    }
}

int count(int num, Pilha *p){
    int cont = 0;
    switch(num){
        case 1:
            return p->topo1 + 1;
        break;
        case 2:
            return p->tamanho - p->topo2;
        break;
    }
}

