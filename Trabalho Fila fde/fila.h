#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FRACASSO 0
#define SUCESSO 1  

#define MAIOR 1
#define IGUAL 0
#define MENOR -1

typedef struct registros{ //struct para guardar dados dos arquivo csv
    char nome[50];
    int matricula;
    int ranking;
    char curso[50];
}registros;

typedef struct noFila{ //nó de dados
    registros dados;
    struct noFila *defronte;
    struct noFila *atras;
}noFila;


typedef struct descritor{ //desctritor para FDDEP com referêncial móvel
    int tamInfo;
    noFila *defronte;
    noFila *atras;
    noFila *refMovel;
}descritor;

descritor *create(int tamInfo);
descritor *destroi(descritor *ds);
int insere(registros *novo,descritor *p, int(*compara)(registros *novo,registros *visitado), int *loops);
int insereMovel(descritor *ds, registros *novo, int *loops);
int remover(registros *old, descritor *ds);
int buscaCauda(registros *node, descritor *ds);
int buscaFrente(registros *node, descritor *ds);
int reinicia(descritor *ds);
int isEmpty(descritor *ds);

int compara(registros *dado1, registros *dado2);
