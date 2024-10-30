#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <string.h>
 
typedef struct {
    int codigo;
    char nome[200];
    float nota;
} Aluno;
 
Aluno aluno_especial[5];
int posicao;
char nome[200];

int main() {

int i = 0;
setlocale(LC_ALL,"portuguese");
 
//cria 5 alunos NULL 
for(i=0; i<5; i++) {
    aluno_especial[i].codigo = 0;
    strcpy(aluno_especial[i].nome, "NULL");
    aluno_especial[i].nota = 0.0;
}
 

printf("\nINSERÇÃO DE ALUNOS\n");

for(i=0; i<5; i++) {
    printf(" Digite o código do aluno especial: ");
    scanf("%d", &aluno_especial[i].codigo);
    printf(" Digite o nome do aluno especial: ");
    scanf("%s", aluno_especial[i].nome);
    printf(" Digite a nota do aluno especial: ");
    scanf("%f", &aluno_especial[i].nota);
    printf(" \n ------------------------------\n");
}

printf("\n\nMOSTRANDO ALUNOS\n");

for(i=0; i<5; i++) {
    printf(" \n O código do aluno especial é: %d ", aluno_especial[i].codigo);
    printf(" \n O nome do aluno especial é: %s ", aluno_especial[i].nome);
    printf(" \n A nota do aluno especial é: %.2f ", aluno_especial[i].nota);
    printf(" \n ---------------------------");
}
 
printf(" \n \n");


printf(" \n Digite um nome: ");
scanf("%s", nome);
for(i=0; i<5; i++) {
    if(strcmp(nome, aluno_especial[i].nome)== 0) {
        printf("\n Registro encontrado! ");
        posicao = i;
    } else {
        posicao = -1;
    }
}
 
if(posicao = -1) {
    printf(" \n Registro não encontrado! ");
}

return 0;
}