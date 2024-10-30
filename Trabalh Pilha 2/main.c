#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arq.h"


int main(int argc, char *argv[]){
    FILE *fp;
    char texto[50] = "";
    int dentroTag = TRUE;
    int foraTag= FALSE;
    int c;
    int linha = 0;
    tag *tags;
    tag *aux;
    
    struct pilha *pil = NULL;
 
    pil = cria();
    tags = iniciaTag();
    aux = iniciaTag();

    for (int i = 1; i < argc; i++){
        fp = fopen(argv[i], "r");
        if (fp == NULL){
            printf("\nErro na abertura do arquivo.\n");
            fclose(fp);
            break;
        }

        while ((c = fgetc(fp)) != EOF){
            if (c == '<')
                dentroTag = TRUE;
            if (c == '\n')
                linha++;
            

            if (dentroTag){

                if (c == '>' || c == ' '){
                    strcat(texto, ">");

                    if (texto[1] == '/'){
                        removeChar(texto, '/');
                        if (strcmp(texto, pil->topo->info) == 0 && !vazia(pil))
                            desempilha(tags, pil);
                        else{
                            printf("ERRO de 'aninhamento' da tag %s na linha %i\n", texto, linha);
                            return 0;
                        }
                    } else{
                        if (!excessao(texto)){
                            strcpy(tags->info, texto);
                            tags->linha = linha;
                            empilha(tags, pil);
                        }
                    }

                    dentroTag = FALSE;
                    memset(texto, 0, sizeof(texto));
                } else
                    texto[strlen(texto)] = c;
            }
        }
        if(!vazia(pil) && !foraTag){
            aux = pil->topo;
            while(aux->abaixo != NULL){
                printf("ERRO: No arquivo %s, %s não foi fechado\n", argv[i], aux->info);
                aux = aux->abaixo;
            }
            continue;
        }
        if (!foraTag)
            printf("\nTags corretamente aninhadas!\n");
        
        reinicia(pil);
    }
    fclose(fp);
    destroi(pil);
}