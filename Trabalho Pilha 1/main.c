#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main(){
    setlocale(LC_ALL, "pt_BR.UTF-8");

    Pilha *pilha = create(1);
    int escolha=-1;
    int tamvet;
    int add;
    int numP;
    int confirma;

    while(escolha !=0){
        printf("\n\nMenu de Ações\n");
        printf("1- Criar Pilha\n");
        printf("2- Empilhamento em Pilha Alvo\n");
        printf("3- Desempilha em Pilha Alvo\n");
        printf("4- Reinicia Pilha Alvo\n");
        printf("5- Destruir Pilha\n");
        printf("6- Buscar Topo Alvo\n");
        printf("7- Contar Pilha Alvo\n");
        printf("0- Sair\n");

        printf("\nDigite o número da ação: ");
        scanf("%i", &escolha);

        switch (escolha)
        {
        case 1:
            if(pilha == NULL){
                printf("Informe tamanho total das Pilhas: ");
                scanf("%i", &tamvet);
                pilha = create(tamvet);
            }else{
                printf("Caso você crie uma nova está existente será apagada, tem certeza que quer continuar?\n1 - Sim\n0- Não\n");
                scanf("%i", &confirma);
                if(confirma==0){
                    break;
                }
                destroy(&pilha);
                printf("Informe tamanho total das Pilhas: ");
                scanf("%i", &tamvet);
                pilha = create(tamvet);
            }
            break;
        case 2:
            printf("Informe a Pilha que deseja alterar: ");
            scanf("%i", &numP);
            printf("O que deseja empilhar: ");
            scanf("%i", &add);
            empilha(pilha, numP, add);
            printf("\nEmpilhado com Sucesso\n");
            break;
        case 3:
            printf("Informe a Pilha que deseja alterar: ");
            scanf("%i", &numP);
            desempilha(pilha, numP);
            printf("\nDesempilhado com Sucesso\n");
            break;
        case 4: 
            printf("Informe a Pilha que deseja reiniciar: ");
            scanf("%i", &numP);
            restart(pilha, numP);

            break;
        case 5:
            printf("A ação de Destruir as pilhas é irreversível,\ntem certeza que deseja continuar?\n1- Sim\t0- Não\n");
            scanf("%i", &confirma);
            if (confirma==0)
                break;

            printf("As Pilhas serão destruídas\n\n");
            destroy(&pilha);
            printf("Pilha Destruída com Sucesso\n");
            break;
        case 6:
            printf("Informe a Pilha que deseja Buscar: ");
            scanf("%i", &numP);
            printf("\nEncontrado no Topo %i : %i\n",numP, busca(numP, pilha));
            break;
        case 7:
            printf("Informe a Pilha que deseja contar: ");
            scanf("%i", &numP);
            printf("Tamanho da pilha de Topo %i : %i",numP, count(numP, pilha));
            break;
        }
    }
    printf("\nPrograma Encerrado\n");
    destroy(&pilha);
}
