typedef struct {
	int c;						/*número de colunas*/
	int l;						/*número de linhas*/
	unsigned char maximo;		/*valor max de um número*/
	unsigned char **imagem;		/*números que compõe a imagem*/
} PGM;

typedef struct {
	Celula *topo; /*armazena somente a célula no topo da pilha*/
} pilha;

typedef struct C{
	int l;						
	int c;						
	struct C *proximo;			
} celula;

PGM *LerPGM (char* entrada);


