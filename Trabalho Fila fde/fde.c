#include "fila.h"

descritor *create(int tamInfo){
    descritor *desc= (descritor*) malloc(sizeof(descritor));
    if(desc != NULL){
        desc->atras = NULL;
        desc->defronte = NULL;
	    desc->tamInfo = tamInfo;
        desc->refMovel = NULL;
    }
    return desc;
}


int insere(registros *novo,descritor *p, int(*compara)(registros *novo,registros *visitado), int *loops){ 
    int result;
    noFila *novoNoFila=NULL, *visitado=NULL;
    loops++;

    if ((novoNoFila = (noFila *) malloc(sizeof(noFila))) != NULL){ 
	    memcpy(&(novoNoFila->dados),novo, p->tamInfo);
  	    if(isEmpty(p)){
            novoNoFila->atras = novoNoFila->defronte = NULL;
    	    p->defronte = p->atras = novoNoFila;	
    	}
        else{ 
    	    result = (*compara)(novo,&(p->atras->dados));
            if(result == MENOR) /*novo elemento é o de menor prioridade */
    	 	{ 	novoNoFila->atras=NULL;
    	 		novoNoFila->defronte=p->atras;
    	 		p->atras->atras=novoNoFila;
    	 		p->atras=novoNoFila;

    	 	}
    	 	else{
                visitado = p->defronte; /*maior prioridade na frente */
                while(visitado->atras != NULL && (*compara)(novo,&(visitado->dados)) != MAIOR ){ 
                        visitado= visitado->atras; /*comparou(A,B) e A < B ou A == B*/
                        loops++;
                }
                
                result = (*compara)(novo,&(visitado->dados));
                if(result == MAIOR)   /* novo item fica a frente do visitado */{   	
					novoNoFila->atras = visitado;
      				if (visitado->defronte != NULL)
      				{       novoNoFila->defronte = visitado->defronte;
      				        visitado->defronte->atras = novoNoFila;
      				} 
      				else{  // novo item é o de maior prioridade de todos na fila, sendo a nova frente
                        novoNoFila->defronte = NULL;      
                        p->defronte = novoNoFila;
			        }	   
					
                    visitado->defronte = novoNoFila;  
					novoNoFila->atras = visitado;       						
				}
		}	
	}
		return SUCESSO;
    }
    
	return FRACASSO;

}


int remover(registros *old, descritor *ds){

    noFila *aux = ds->atras;
    if(!isEmpty(ds)){
        memcpy(old,&(ds->defronte->dados),ds->tamInfo);
        if(aux == ds->defronte){//cauda = topo da lista, implicando um UNICO elemento na Lista
            free(ds->defronte);
            ds->atras = ds->defronte = NULL;
        }else{
            ds->defronte = ds->defronte->atras;
            free(ds->defronte->defronte);
            ds->defronte->defronte= NULL;
        }
        return SUCESSO;
    }
    return FRACASSO;
}

int buscaCauda(registros *node, descritor *ds){
    if(isEmpty(ds))
        return FRACASSO;
    
    memcpy(node,&(ds->atras->dados),ds->tamInfo);
    return SUCESSO;
}

int buscaFrente(registros *node, descritor *ds){
    if(isEmpty(ds))
        return FRACASSO;
    memcpy(node, &(ds->defronte->dados),ds->tamInfo);
    return SUCESSO;
}

int reinicia(descritor *ds){
    if(isEmpty(ds))
        return FRACASSO;
    
    noFila *aux = NULL;

    while(aux!=NULL){
        free(ds->atras);
        ds->atras= aux;
        aux = aux->defronte;
    }

    free(ds->atras);
    ds->atras= NULL;
    ds->defronte = NULL;

    return SUCESSO;
}
 
int isEmpty(descritor *p){
    return (p->defronte == NULL && p->atras == NULL && p->refMovel == NULL);
}

descritor *destroi(descritor *ds){
    if (ds != NULL) {
        reinicia(ds);
        free(ds);
    }
    return NULL;
}

int insereMovel(descritor *ds, registros *novo, int *loops){
    noFila *novoNo = NULL, *visitado = NULL;
    int result1 = 0;
    
    *loops++;
    memcpy(&(novoNo->dados),novo, ds->tamInfo);

    if(isEmpty(ds)){ //para o caso de lista VAZIA
        novoNo->atras = novoNo->defronte = NULL;
        ds->refMovel = ds->defronte = ds->atras = novoNo;
        return SUCESSO;
    }


    //if para definir o valor de result
    if(ds->atras->dados.ranking < novoNo->dados.ranking <= ds->refMovel->dados.ranking)
        result1 = 3;//cauda < novo <= refMovel
    else{
        if(ds->refMovel->dados.ranking < novoNo->dados.ranking <= ds->defronte->dados.ranking)
            result1 = 4;//refMovel < novo <= frente
        else{
            if(novoNo->dados.ranking <= ds->atras->dados.ranking){//menor ou igual a cauda
                result1 = 1;
            }else{
                if(novoNo->dados.ranking>= ds->defronte->dados.ranking)//maior ou igual ao topo
                    result1 = 2;
            }
        }
    }

    //inserção dependendo do caso/valor de result1
    switch (result1){
        case 1:
            //MENOR ou IGUAL a cauda
            novoNo->atras=NULL;
    	 	novoNo->defronte=ds->atras;
    	 	ds->atras->atras=novoNo;
    	 	ds->atras=novoNo;
            break;
        case 2: 
            //MAIOR que a frente
            novoNo->defronte = ds->defronte;
            novoNo->defronte = NULL;
            ds->defronte->defronte = novoNo;
            ds->defronte = novoNo;
            break;
        case 3:
            //ENTRE CAUDA E REF
            int a = abs(ds->atras->dados.ranking - novo->ranking);
            int b = abs(ds->refMovel->dados.ranking - novo ->ranking);   
            if(a <= b){
                //pela cauda
                visitado = ds->atras;

                    while(visitado->defronte != NULL && visitado->dados.ranking < novoNo->dados.ranking) {
                        visitado = visitado->defronte;
                        *loops++;
                    }
                    novoNo->defronte = visitado;
                    novoNo->atras = visitado->atras;
                    if (visitado->atras != NULL)
                        visitado->atras->defronte = novoNo;
                    visitado->atras = novoNo;
            }else{
                //pelo ref.móvel
                visitado = ds->refMovel;

                while(visitado->atras != NULL && visitado->dados.ranking >= novoNo->dados.ranking) {
                    visitado = visitado->atras;
                    *loops++;
                }
                novoNo->atras = visitado;
                novoNo->defronte = visitado->defronte;
                if (visitado->defronte != NULL)
                    visitado->defronte->atras = novoNo;
                visitado->defronte = novoNo;
                
            }
            break;
        case 4:
            //ENTRE REF E FRENTE
            int c = abs(ds->defronte->dados.ranking - novo->ranking);
            int d = abs(ds->refMovel->dados.ranking - novo->ranking);
            if(c <= d){
                //pelo ref.Móvel
                 visitado = ds->refMovel;

                while(visitado->defronte != NULL && visitado->dados.ranking < novoNo->dados.ranking) {
                    visitado = visitado->defronte;
                    *loops += 1;
                }
                novoNo->defronte = visitado;
                novoNo->atras = visitado->atras;
                if (visitado->atras != NULL)
                    visitado->atras->defronte = novoNo;
                visitado->atras = novoNo;

            }else{
                //pela frente
                visitado = ds->defronte;
                while(visitado->atras != ds->refMovel && (*compara)(novo,&(visitado->dados)) != MAIOR ){
                        visitado= visitado->atras;
                        loops++;
                }
            }
            break;
        default:
            return FRACASSO;
            break;
    }
    return SUCESSO;
}

//FUNÇÃO COMPARATIVA FILA DE PRIORIDADEdado1->ranking < dado2->ranking
int compara(registros *dado1, registros *dado2){
    if (dado1->ranking < dado2->ranking)
        return MENOR;
    if(dado1->ranking > dado2->ranking)
        return MAIOR;
    return IGUAL;
}

