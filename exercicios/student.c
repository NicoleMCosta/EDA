#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>


struct curso{
    char nome[20];
    float tempo;
}curso;


struct estudante {
    char matricula[10];
    char nome[20];
    struct curso *cursando;
}est;


void imprimeEstudante( struct estudante *e);

int main(){
    // Corrigindo a alocação de memória
    struct estudante *est = (struct estudante *) malloc(sizeof(struct estudante));
    struct curso *curso = (struct curso *) malloc(sizeof(struct curso));


    strcpy(est->matricula, "12345");
    strcpy(est->nome, "nicole");
    strcpy(curso->nome, "BCC");

    curso->tempo = 2;
    est->cursando = curso;

    // Chamando a função imprimeEstudante
    imprimeEstudante(est);
    free(curso);
    free(est);

    return 0;
}

void imprimeEstudante(struct estudante *e){
    printf("\nEstudante: %s", e->nome);
    printf("\nMatricula: %s", e->matricula);
    printf("\nCurso: %s", e->cursando->nome);
    printf("\nTempo de curso: %.2f anos\n", e->cursando->tempo);
}