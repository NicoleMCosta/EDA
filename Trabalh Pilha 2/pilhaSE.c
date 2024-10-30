#include "arq.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int vazia(struct pilha *pil){
  return pil->topo == NULL;
}

int empilha(tag *item, struct pilha *pil){
    tag *aux=NULL;
    aux= (tag *) malloc(sizeof(tag));

    if (aux!=NULL){
        memcpy(&(aux->info), item, sizeof(tag)); //<<<<<<<<<<
	    aux->abaixo=pil->topo;
     	pil->topo=aux;
	    (pil->tam)++;
        return TRUE;
    }
    else
        return FALSE;
}

int desempilha(tag *reg, struct pilha *pil){
    struct tag *aux=NULL;	  
    if (!vazia(pil)){
        memcpy(reg, &(pil->topo->info),sizeof(tag)); //<<<<<<<
	    aux=pil->topo->abaixo;
	    free(pil->topo);
	    pil->topo=aux;
        (pil->tam)--;
        return TRUE;
    }
    else
        return FALSE;
}


struct pilha *cria(){
    struct pilha *p=NULL;
    p = (struct pilha *) malloc(sizeof(struct pilha));
    if (p){
	    p->topo=NULL;
        p->tam=0;
    }
    return p;
}


void reinicia(struct pilha *pil){
    struct tag *aux=NULL;	  
    if (vazia(pil)==FALSE){	 
        aux=pil->topo->abaixo;
        while(aux!=NULL){
            free(pil->topo);
            pil->topo=aux;
            aux=aux->abaixo;
        }
        free(pil->topo);
        pil->topo=NULL;
        pil->tam=0;
    }
 	
}

struct pilha *destroi(struct pilha *pil){
	reinicia(pil);
	free(pil);
  	return NULL;	
}	

void removeChar(char *str, char removed) {
    char *source, *destine;
    for (source = destine = str; *source != '\0'; source++) {
        *destine = *source;
        if (*destine != removed) 
            destine++;
    }
    *destine = '\0';
}
int excessao(char texto[]){
    char excessoes[][50] = {"<!DOCTYPE>","<input>","<frame>","<br>","<img>","<option>","<meta>"};
    if (strncmp(texto, "<!--", 4) == 0)
        return TRUE;
    for (int i = 0; i < (sizeof(excessoes) / sizeof(excessoes[0])); i++){
        if(strcmp(excessoes[i], texto) == 0)
            return TRUE;
    }
    return FALSE;
}

tag *iniciaTag(){
    tag *t=NULL;
    t = (tag *) malloc(sizeof(tag));
    if (t){
	    t->abaixo = NULL;
        t->linha = 0;
        strcpy(t->info," ");
    }
    return t;
    
}