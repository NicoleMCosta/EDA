#define TRUE 1
#define FALSE 0

struct pilha{
    struct tag *topo;
    int tam;
};

typedef struct tag{
    char info[50];
    int linha;
    struct tag *abaixo;
}tag;


int vazia(struct pilha *pil);
struct pilha * cria(void);
int empilha(tag *novo, struct pilha *pil);
int desempilha(tag *reg, struct pilha *pil);
void reinicia(struct pilha *pil);
struct pilha *destroi(struct pilha *pil);
tag *iniciaTag();

//Funções adicionais para manuseio das Tags
void removeChar(char *str, char removed);
int excessao(char texto[]);
