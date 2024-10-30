#include<stdio.h>
#include<stdlib.h>

int main(){

  float altura;
  char sexo;

  FILE *p ;

  p =  fopen("home//vscode//EDA//dados.txt","rt");
  if (p==NULL){
     printf("\nNao deu certo");
     return -1;
  } 
  
  printf("\n Leu arquivo");

  while ( !feof(p)){
      fscanf(p, "%c %f", &sexo, &altura);
      printf("\n Pessoa : sexo = %c altura=%f", sexo, altura );
   }

 
   return 0;  
}
