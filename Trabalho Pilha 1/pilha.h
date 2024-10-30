
typedef struct pilha {
    int tamanho;
    int *vetorP;
    int topo1;
    int topo2;

} Pilha;

Pilha *create(int tam);
void destroy(Pilha **p);
void restart(Pilha *p, int num);
int empilha (Pilha *p, int num, int novo);
int desempilha(Pilha *p, int num);
int empty(int num, Pilha *p);
int full(Pilha *p);
int busca(int num, Pilha *p);
int count(int num, Pilha *p);