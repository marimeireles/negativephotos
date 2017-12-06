typedef struct {
	int c;						/*número de colunas*/
	int l;						/*número de linhas*/
	unsigned char maximo;		/*valor max de um número*/
	unsigned char **imagem;		/*números que compõe a imagem*/
} PGM;

PGM *LerPGM (char* entrada);
void Convolucao (PGM *img, char **kernell, PGM *saida);
void SalvarPGM (PGM *img, char *saida);
