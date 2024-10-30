#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ESTUDANTES 50

typedef struct disciplinas {
    char codigo[9];
    char nome[250];
    int total_creditos;
} Disc;

typedef struct estudante {
    char *nome;
    char cpf[12];
    int ano_ingresso;
    int qnt_disciplinas;
    Disc *disciplinas_matriculadas;
} Std;

void menu();
void insereAluno(Std *estudante, int *num_alunos);
void mostraAlunos(Std *estudante, Disc *disciplinas, int num_alunos);
void mostraDisciplinas(Std *estudantes, Disc *disciplinas, int num_alunos, int indice);
void insereDisciplina(Std *estudante, Disc *disciplinas, int num_alunos);
void salvarDados(Std *estudante, int num_alunos);
void lerArquivo(Std *estudante, int *num_alunos);

int main() {
    int num_alunos = 0;
    int num_disciplinas = 10;

    Std *alunos = (Std *)malloc(MAX_ESTUDANTES * sizeof(Std));
    Disc *disciplinas = (Disc *)malloc(num_disciplinas * sizeof(Disc));

    int choice = 0;
    while (choice != 6) {
        menu();
        printf("Informe a acao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n");
                insereAluno(alunos, &num_alunos);
                printf("\nEstudante Cadastrado com Sucesso!\n");
                break;
            case 2:
                printf("\n");
                mostraAlunos(alunos, disciplinas, num_alunos);
                break;
            case 3:
                printf("\n");
                insereDisciplina(alunos, disciplinas, num_alunos);
                break;
            case 4:
                printf("\n");
                salvarDados(alunos, num_alunos);
                printf("\nDados Salvos com Sucesso!\n");
                break;
            case 5:
                printf("\n");
                lerArquivo(alunos, &num_alunos);
                break;
            case 6:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nIndice nao configurado!\n");
                break;
        }
    }

    for (int i = 0; i < num_alunos; i++) {
        free(alunos[i].nome);
        free(alunos[i].disciplinas_matriculadas);
    }
    free(alunos);
    free(disciplinas);
    return 0;
}

void insereAluno(Std *estudante, int *num_alunos) {
    Std *aluno = &estudante[*num_alunos];

    char nome[250];
    printf("Estudante: ");
    while (getchar() != '\n'); 
    fgets(nome, 249, stdin);
    nome[strcspn(nome, "\n")] = 0;
    aluno->nome = malloc((strlen(nome) + 1) * sizeof(char));
    strcpy(aluno->nome, nome);

    printf("Cpf: ");
    scanf("%s", aluno->cpf);
    printf("Ano de Ingresso: ");
    scanf("%i", &aluno->ano_ingresso);
    aluno->qnt_disciplinas = 0;
    aluno->disciplinas_matriculadas = NULL;
    (*num_alunos)++;
}

void insereDisciplina(Std *estudante, Disc *disciplinas, int num_alunos) {
    int indice;
    mostraAlunos(estudante, disciplinas, num_alunos);
    printf("Informe o numero do estudante que será matriculado: ");
    scanf("%d", &indice);

    if (indice < 0 || indice >= num_alunos) {
        printf("Indice de estudante invalido!\n");
        return;
    }

    Std *aluno = &estudante[indice];
    aluno->disciplinas_matriculadas = (Disc *)realloc(aluno->disciplinas_matriculadas, (aluno->qnt_disciplinas + 1) * sizeof(Disc));

    if (aluno->disciplinas_matriculadas == NULL) {
        printf("Erro ao alocar memoria para disciplinas!\n");
        return;
    }

    Disc *materia = &aluno->disciplinas_matriculadas[aluno->qnt_disciplinas]; 

    printf("Codigo: ");
    scanf("%s", materia->codigo);
    while (getchar() != '\n'); 
    printf("Nome: ");
    fgets(materia->nome, 250, stdin);
    materia->nome[strcspn(materia->nome, "\n")] = 0;
    printf("Total de Créditos: ");
    scanf("%i", &materia->total_creditos);

    aluno->qnt_disciplinas++;
}

void mostraAlunos(Std *estudante, Disc *disciplinas, int num_alunos) {
    Std *aluno;
    if (num_alunos == 0) {
        printf("\nSem alunos registrados\n");
    } else {
        printf("\nEstudantes:");
        for (int i = 0; i < num_alunos; i++) {
            aluno = &estudante[i];
            printf("\t\nAluno %i\n", i);
            printf("\tNome: %s\n", aluno->nome);
            printf("\tCpf: %s\n", aluno->cpf);
            printf("\tAno de Ingresso: %i\n", aluno->ano_ingresso);
            printf("\t\nDisciplinas Matriculadas:\n");

            if (aluno->qnt_disciplinas == 0) {
                printf("\t\tNao esta matriculado em nenhuma disciplina\n");
            } else {
                mostraDisciplinas(estudante, disciplinas, num_alunos, i);
                
            }
        }
    }
}

void mostraDisciplinas(Std *estudantes, Disc *disciplinas, int num_alunos, int indice) {
    Std *aluno = &estudantes[indice];
    Disc *materia;
    for (int i = 0; i < aluno->qnt_disciplinas; i++) {
        materia = &aluno->disciplinas_matriculadas[i];
        printf("\t\t\nCodigo: %s\t\t\nNome: %s\t\t\nTotal de Creditos: %d\n", materia->codigo, materia->nome, materia->total_creditos);
    }
}

void lerArquivo(Std *estudante, int *num_alunos) {
    FILE *arquivo = fopen("estudantes.bin", "rb");
    if (arquivo == NULL) {
        printf("\nNao foi possivel abrir o arquivo!\n");
        return;
    }

    fread(num_alunos, sizeof(int), 1, arquivo);

    if (*num_alunos == 0) {
        printf("\nNao ha estudantes cadastrados no arquivo!\n");
        fclose(arquivo);
        return;
    }

    printf("\nExistem %d estudantes cadastrados\n", *num_alunos);
    printf("\nInforme o indice que deseja buscar: ");
    int id;
    scanf("%d", &id);
    id--;
    if (id < 0 || id >= *num_alunos) {
        printf("\nIndice invalido! Nao existem registros suficientes\n");
    } else {
        fseek(arquivo, sizeof(int), SEEK_SET); 

        for (int i = 0; i <= id; i++) {
            int tam_nome;
            fread(&tam_nome, sizeof(int), 1, arquivo); 
            estudante[i].nome = (char *)malloc(tam_nome * sizeof(char));
            fread(estudante[i].nome, sizeof(char), tam_nome, arquivo);  

            fread(estudante[i].cpf, sizeof(char), 12, arquivo);  
            fread(&estudante[i].ano_ingresso, sizeof(int), 1, arquivo);  
            fread(&estudante[i].qnt_disciplinas, sizeof(int), 1, arquivo);  

            estudante[i].disciplinas_matriculadas = (Disc *)malloc(estudante[i].qnt_disciplinas * sizeof(Disc));
            for (int j = 0; j < estudante[i].qnt_disciplinas; j++) {
                fread(estudante[i].disciplinas_matriculadas[j].codigo, sizeof(char), 9, arquivo);
                fread(estudante[i].disciplinas_matriculadas[j].nome, sizeof(char), 250, arquivo);  
                fread(&estudante[i].disciplinas_matriculadas[j].total_creditos, sizeof(int), 1, arquivo);
            }
        }

        Std *aluno = &estudante[id];
        printf("\nAluno encontrado:\n");
        printf("Nome: %s\nCPF: %s\nAno de Ingresso: %d\n", aluno->nome, aluno->cpf, aluno->ano_ingresso);
        printf("\nDisciplinas Matriculadas:\n");
        for (int i = 0; i < aluno->qnt_disciplinas; i++) {
            printf("\t\nCodigo: %s\n\tNome: %s\n\tTotal de Creditos: %d\n",
                   aluno->disciplinas_matriculadas[i].codigo,
                   aluno->disciplinas_matriculadas[i].nome,
                   aluno->disciplinas_matriculadas[i].total_creditos);
        }
    }

    fclose(arquivo);
}


void salvarDados(Std *estudante, int num_alunos) {
    FILE *arquivo = fopen("estudantes.bin", "wb");
    if (arquivo == NULL) {
        printf("\nNao foi possivel abrir o arquivo!\n");
        exit(1);
    }

    fwrite(&num_alunos, sizeof(int), 1, arquivo); 

    for (int i = 0; i < num_alunos; i++) {
        int tam_nome = strlen(estudante[i].nome) + 1;
        fwrite(&tam_nome, sizeof(int), 1, arquivo);
        fwrite(estudante[i].nome, sizeof(char), tam_nome, arquivo);
        fwrite(estudante[i].cpf, sizeof(char), 12, arquivo);
        fwrite(&estudante[i].ano_ingresso, sizeof(int), 1, arquivo);
        fwrite(&estudante[i].qnt_disciplinas, sizeof(int), 1, arquivo);

        for (int j = 0; j < estudante[i].qnt_disciplinas; j++) {
            fwrite(estudante[i].disciplinas_matriculadas[j].codigo, sizeof(char), 9, arquivo);
            fwrite(estudante[i].disciplinas_matriculadas[j].nome, sizeof(char), 250, arquivo);
            fwrite(&estudante[i].disciplinas_matriculadas[j].total_creditos, sizeof(int), 1, arquivo);
        }
    }

    fclose(arquivo);
}

void menu() {
    printf("\n1- Cadastrar Estudante\n2- Mostrar Estudantes\n3- Cadastrar Disciplina\n4- Salvar Dados\n5- Fazer Busca\n6- Sair\n");
}
