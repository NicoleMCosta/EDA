/*#include <stdio.h>


typedef struct  pessoa{
    char nome[100];
    int peso;
    float altura;
}Pessoa;

int main(){
    Pessoa p1, p2, p3;
    size_t tnome, tpeso, taltura,tam;
    
    tnome = 100*sizeof(char);

    printf("\nnome tem size = %li\n", tnome);
    tpeso = sizeof(int);
    printf("peso tem size = %li\n", tpeso);
    taltura = sizeof(float);
    printf("altura tem size = %li", taltura);
    tam = sizeof(p1);
    printf("\nTamanho de uma struct Pessoa: %li\n", tam);

}*/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct pf{
   char nome[200];
   char cpf[12];
   int idade;
   struct pf* conjuge;
} Pessoa;


void imprimeDadosPessoa( Pessoa p);


int main(){
   Pessoa pma, pjo;

   strcpy(pma.nome , "Maria");
   strcpy(pma.cpf , "02395907930");
   pma.idade = 40;
   pma.conjuge=NULL;

   strcpy(pjo.nome , "Joao");
   strcpy(pjo.cpf , "01366909301");
   pjo.idade = 34;
   pjo.conjuge=NULL;

   pma.conjuge= &pjo;
   pjo.conjuge= &pma;
   imprimeDadosPessoa(pma);
    return 0;
}



void imprimeDadosPessoa( Pessoa p){
   printf("\nNome: %s\ncpf %s\n%i anos\n", p.nome, p.cpf, p.idade) ;
   if ( p.conjuge->nome != NULL)
       printf("E\nCONJUGE\nConjuge: %s\nCpf: %s\n%i anos\n", p.conjuge->nome, p.conjuge->cpf, p.conjuge->idade);
    else   
        printf("Solteiro(a)");           
}