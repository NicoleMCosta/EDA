#include <stdio.h>
#define TAM 10


void selectionSort(int *vetor, int tam){
    int min,aux = 0;
    
    for(int i = 0; i<= tam-1; i++){
        min = i;
        for(int j =i+1; j<=tam-1;j++){
            if(vetor[min]>vetor[j])
                min = j;
        }
        if(i != min){
            aux = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = aux;
        }
    }
}

int main (){
    int i, a[TAM] = { 2, 6, 4, 8, 10, 12, 89, 68, 45, 37 };

    printf ("Itens de dados na ordem original\n");
    
    for (i = 0; i <= TAM - 1; i++)
        printf ("%d\t", a[i]);

    
    printf("\n");
    selectionSort(a, TAM);
    printf ("\nltens de dados em ordem ascendente\n");
    
    for (i = 0; i <= TAM - 1; i++)
        printf ("%d\t", a[i]);

    printf("\n");
    return 0;
}
