#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define SIZE 10000

void mostrarMenu();
registros *lerCSV(const char *filename, int qnt) ;

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "pt-BR");

    int choice = -1;
    int ctz = 0;
    int loops = 0;
    descritor *fila = create(sizeof(registros));
    registros reg;
    registros tempReg;
    
    while(choice != 0){
        mostrarMenu();
        scanf("%d", &choice);
        switch (choice){
            case 0:
                destroi(fila);  
                break;
            case 1:
                if(fila != NULL){
                    printf("\nJá existe uma fila, certeza que deseja criar outra?\nIsso destruirá a Fila Anterior\nDigite 1 para SIM e 0 para NÃO: ");
                    scanf("%i", &ctz);
                    if(ctz = 1){
                        destroi(fila);
                        fila = create(sizeof(registros));
                        printf("\nSucesso\n");
                    }else{
                        break;
                    }
                }
                break;
            case 2:
                if (fila == NULL) {
                            printf("Crie uma fila primeiro.\n");
                        } else {
                            printf("Informe nome, matrícula, ranking e curso: ");
                            scanf("%s %d %d %s", reg.nome, &reg.matricula, &reg.ranking, reg.curso);
                            if (insere(&reg, fila, compara, &loops) == SUCESSO) {
                                printf("Sucesso ao inserir na Fila\n");
                            } else {
                                printf("Não foi possível fazer a inserção\n");
                            }
                        }
                break;
            case 3:
                if (fila == NULL) {
                            printf("Crie uma fila primeiro.\n");
                        } else {
                            if (remover(&tempReg, fila) == SUCESSO) {
                                printf("Elemento removido: %s, %d, %d, %s\n", tempReg.nome, tempReg.matricula, tempReg.ranking, tempReg.curso);
                            } else {
                                printf("Erro ao remover o elemento.\n");
                            }
                        }if (fila != NULL) {
                            destroi(fila);
                        }
                break;
            case 4:
                if (fila == NULL) {
                        printf("Crie uma fila primeiro.\n");
                    } else {
                        if (buscaCauda(&tempReg, fila) == SUCESSO) {
                            printf("Elemento na cauda: %s, %d, %d, %s\n", tempReg.nome, tempReg.matricula, tempReg.ranking, tempReg.curso);
                        } else {
                            printf("Erro ao buscar na cauda.\n");
                        }
                    }
                break;
            case 5:
                if (fila == NULL) {
                    printf("Crie uma fila primeiro.\n");
                } else {
                    if (buscaFrente(&tempReg, fila) == SUCESSO) {
                        printf("Elemento na frente: %s, %d, %d, %s\n", tempReg.nome, tempReg.matricula, tempReg.ranking, tempReg.curso);
                    } else {
                        printf("Erro ao buscar na frente.\n");
                    }
                }
                break;
            case 6:
                if (fila == NULL) {
                    printf("Crie uma fila primeiro.\n");
                } else {
                    if (reinicia(fila) == SUCESSO) {
                        printf("Fila reiniciada com sucesso.\n");
                    } else {
                        printf("Erro ao reiniciar a fila.\n");
                    }
                }
                break;
            case 7:
                if (fila == NULL) {
                    printf("Crie uma fila primeiro.\n");
                } else {
                    if (isEmpty(fila)) {
                        printf("A fila está vazia.\n");
                    } else {
                        printf("A fila não está vazia.\n");
                    }
                }
                break;
            case 8:
                int tamanhos[] = {500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000};
                descritor *filaRefMovel = create(sizeof(registros));
                descritor *filaComum = create(sizeof(registros));
                for (int i = 0; i < 18; i++){//18 situações de teste
                    int numRepA = 0;
                    int numRepB = 0;
                    registros *p = lerCSV(argv[1],tamanhos[i]);
                    for (int j = 0; j < tamanhos[i]; j++){
                        insereMovel(filaRefMovel, &(p[j]), &numRepA);//fila com refMovel
                        insere( &(p[j]), filaComum, compara,&numRepB);//fila sem refMovel
                    }
                    printf("Media com %i dados:\nCom refMovel: %i\nSem refMovel: %d\n", tamanhos[i], numRepA, numRepB);
                    destroi(filaRefMovel);
                    destroi(filaComum);
                }
                

                break;
            default:
                    printf("\nOpção Inválida\nTente Novamente\n\n");
                break;
        }
    }
    return 0;
}


void mostrarMenu(){
    printf("\nMENU\n");
    printf("1- Criar Fila\n");
    printf("2- Inserir\n");
    printf("3- Remover\n");
    printf("4- Buscar Cauda\n");
    printf("5- Buscar Frente\n");
    printf("6- Reiniciar\n");
    printf("7- Verificar se está vazia\n");
    printf("8- Teste LOOPs\n");
    printf("0- Sair\n");
    printf("Informe a ação: ");
}

registros *lerCSV(const char *filename, int qnt) {
    FILE *file = fopen("dataset_v1.csv", "r");
    srand(time(NULL));
    
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[256];
    int contador = 0;
    registros *pessoa = malloc(qnt * sizeof(registros));

    int* randomLines = malloc(qnt * sizeof(int));
    for (int i = 0; i < qnt; i++) {
        randomLines[i] = rand() % qnt;
    }
    while (fgets(linha, sizeof(linha), file)) {
            registros p;
            sscanf(linha, "%49[^,],%d,%d,%49[^\n]", p.nome, &p.matricula, &p.ranking, p.curso);
            pessoa[contador] = p;
            contador++;
    }

    fclose(file);
}
