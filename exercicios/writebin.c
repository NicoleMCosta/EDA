#include <stdio.h>
#include <stdlib.h>
struct Coord {
  int n1, n2, n3;
};
int main() {
 int n;
 struct Coord co;
 FILE *fptr;
if ((fptr = fopen("fonte.bin","wb")) == NULL){
  fprintf(stderr, "\nErro ao abrir arquivo");
  exit(1);
}
 for(n = 1; n < 5; ++n) {
  co.n1 = n;
  co.n2 = 5*n;
  co.n3 = 5*n + 1;
  fwrite(&co, sizeof(struct Coord), 1, fptr); 
 }
 fclose(fptr); 
return 0;
}
