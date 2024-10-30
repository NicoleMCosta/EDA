#include <stdio.h>
#include <stdlib.h>
struct Coord {
 int n1, n2, n3;
};
int main() {
 int n;
 struct Coord ponto;
 FILE *fptr;
 if ((fptr = fopen("fonte.bin","rb")) == NULL){
    fprintf(stderr, "\nErro ao abrir arquivo");
  
  exit(1);
}


for(n = 1; n < 5; ++n) {
    fread(&ponto, sizeof(struct Coord), 1, fptr); 
    printf("\n n1: %d\tn2: %d\tn3: %d", ponto.n1, ponto.n2, ponto.n3);
}

fclose(fptr); 
return 0;
} 
