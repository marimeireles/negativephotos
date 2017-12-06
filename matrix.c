#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

/*--------------------------------------------------------------
Protótipo: PGM *LerPGM (char* entrada);
Função: Abre o arquivo de entrada, aloca dinamicamente um tipo 
PGM para receber os dados, grava os dados em um arquivo
temporário PGM e retorna esses dados ao final da execução.
Entrada: nome do arquivo de entrada.
Saída: Arquivo PGM idêntico ao lido na entrada.
--------------------------------------------------------------*/
PGM *LerPGM (char* entrada) {

/*abertura do arquivo*/
FILE *fin;
char ch;

fin = fopen(entrada, "r");

if (NULL == fin) {
	printf("Arquivo não encontrado.\n");
	exit(1);
}

/*variáveis necessárias para alocar a memória dinamicamente*/
char PB [2];
fscanf(fin, "%s\n", &PB);
int i, j;
PGM x;

/*aloca dinamicamente dados simples da PGM*/
x.c = malloc(sizeof(int));
x.l = malloc(sizeof(int));
x.maximo = malloc(sizeof(unsigned char));

/*atribui valores para os dados simples da PGM*/
fscanf(fin, "%d", &x.l);
fscanf(fin, "%d", &x.c);
fscanf(fin, "%d", &x.maximo);

/*aloca dinamicamente a matriz da PGM*/
x.imagem = malloc(x.l * sizeof(unsigned char *));

for(i = 0; i < x.l; i++)
	x.imagem[i] = malloc(x.c * sizeof(unsigned char));

/*atribui os valores do arquivo de entrada para a matriz 
x.imagem*/
for (i = 0; i < x.l; i++) {
	for (j = 0; j < x.c; j++) {
	fscanf(fin, "%d", &x.imagem[i][j]);
	printf("matrix.c: na posição [%d][%d]"
	" encontra-se o valor %d\n", i, j, x.imagem[i][j]);	
	}
}

fclose(fin);

/*atribui a recém criada PGM para uma variável do tipo ponteiro
para PGM*/
PGM *y;
y = malloc(sizeof(PGM));
y = &x;

return y;
}

/*--------------------------------------------------------------
Protótipo: void Convolucao (PGM *img, char **kernell, 
PGM *saida)
Função: cria uma matriz com bordas de números iguais às bordas
da matriz original e realiza uma multiplicação de matrizes
utilizando o kernell, por fim, cria um novo PGM com o resultado
da multiplicação.
Entrada: PGM de entrada, kernell e PGM modificado.
Saída: void
--------------------------------------------------------------*/
void Convolucao (PGM *img, char **kernell, PGM *saida) {

/*cria uma matriz aprazível de ser convolucionada*/
int i, j, k, coluna, linha, a, b, k1 = -1, k2 = 0; /*variaveis
responsáveis pelo controle de matrizes*/
linha = img->l + 2; coluna = img->c + 2;
int soma = 0;/*controla a soma de cada multiplicação feita pelo
kernell e a matriz*/
int matrix[linha][coluna];/*matriz que será utilizada para fazer
a multiplicação kernell/matriz*/

/*cuida para que o meio da matriz seja atribuido 
corretamente*/
for ( i = 1; i < linha-1; i++) {
	for (j = 1; j < coluna-1; j++) {
		matrix[i][j] = img->imagem[i-1][j-1];
	}
}

/*cuida para que as extremidades da matriz sejam atribuídas
corretamente*/
for ( i = 0; i < linha - 2; i++) {
	matrix[i+1][0] = img->imagem[i][0];
	matrix[i+1][coluna-1] = img->imagem[i][img->c-1];
}

for (i = 0; i < coluna - 2; i++) {
	matrix[0][i+1] = img->imagem[0][i];
	matrix[linha-1][i+1] = img->imagem[img->l-1][i];
}

/*cuida para que as quinas da matriz sejam atribuídas
corretamente*/
matrix[0][0] = img->imagem[0][(0)];
matrix[1][0] = matrix[0][0];
matrix[1][1] = matrix[0][0];
matrix[0][1] = matrix[0][0];

matrix[0][coluna-1] = img->imagem[0][img->c-1];
matrix[0][coluna-2] = matrix[0][coluna-1];
matrix[1][coluna-1] = matrix[0][coluna-1];
matrix[1][coluna-2] = matrix[0][coluna-1];

matrix[linha-2][0] = img->imagem[img->l-1][0];
matrix[linha-1][0] = matrix[linha-2][0];
matrix[linha-2][1] = matrix[linha-2][0];
matrix[linha-1][1] = matrix[linha-2][0];

matrix[linha-2][coluna-2] = img->imagem[img->l-1][img->c-1];
matrix[linha-1][coluna-1] = matrix[linha-2][coluna-2];
matrix[linha-1][coluna-2] = matrix[linha-2][coluna-2];
matrix[linha-2][coluna-1] = matrix[linha-2][coluna-2];

/*checa para ver se a matriz foi atribuida corretamente*/
for ( i = 0; i < linha; i++) {
	for (j = 0; j < coluna; j++) {
	printf("matrix[%d][%d] = %d\n", i, j, matrix[i][j]);		
	}
}

/*aloca a PGM de saída dinamicamente*/
/*aloca dinamicamente dados simples da PGM*/
saida->c = malloc(sizeof(int));
saida->l = malloc(sizeof(int));
saida->maximo = malloc(sizeof(unsigned char));

saida->c = img->c;
saida->l = img->l;
saida->maximo = img->maximo;

/*aloca dinamicamente a matriz da PGM*/
saida->imagem = malloc(img->l * sizeof(unsigned char *));

for(i = 0; i < img->l; i++)
	saida->imagem[i] = malloc(img->c * sizeof(unsigned char));

/*cria o kernell para convolução de processamento de imagem*/
kernell = malloc(3 * sizeof(char));

for(i = 0; i < 3; i++) //dar free no kernell no final
	kernell[i] = malloc(sizeof(char));

kernell[0][0] = -1;
kernell[0][1] = 0;
kernell[0][2] = 1;
kernell[1][0] = -1;
kernell[1][1] = 0;
kernell[1][2] = 1;
kernell[2][0] = -1;
kernell[2][1] = 0;
kernell[2][2] = 1;

/*realiza a convolução utlizando o kernell*/
for (i = 1; i < img->l; i++) {
	for (j = 1; j < img->c; j++) {
		for (a = i - 1; a < (i) + 2; a++){
			if (k1 > 2) k1 = 0;
			k1++;

			for (b = j - 1; b < (j) + 2; b++) {
			if (k2 > 2) k2 = 0;
				soma = soma + matrix[a][b] * kernell[k1][k2];
				printf("(%d)matrix[%d][%d] * "
				"(%d)kernell[%d][%d] = %d\n", 
				matrix[a][b], a, b, kernell[k1][k2], k1, 
				k2, soma);
			k2++;
			}
		}
	if(soma < 0) soma = 0;
	if(soma > 255) soma = 255;
	saida->imagem[i-1][j-1] = soma;
	printf("SAIDA: %d\n", soma);
	soma = 0;
	k1 = -1;
	k2 = 0;
	}
}

free(kernell);
}

/*-------------------------------------------------------------
Protótipo: void SalvarPGM (PGM *img, char *saida)
Função: cria uma matriz com bordas de números iguais às bordas
da matriz original e realiza uma multiplicação de matrizes
utilizando o kernell, por fim, cria um novo PGM com o resultado
da multiplicação.
Entrada: PGM de entrada, kernell e PGM modificado.
Saída: void
-------------------------------------------------------------*/
void SalvarPGM (PGM *img, char *saida) {
int i, j; /*variáveis utilizada na iteração*/

/*abre o arquivo de saída com o nome recebido pela função no
modo de escrita*/
FILE *fout = fopen(saida, "w");

if (NULL == fout) {
	printf("Arquivo não encontrado.\n");
	exit(1);
}

/*atribui informações de leitura para a imagem*/
fprintf(fout, "P2\n");
fprintf(fout, "%d %d 255\n", img->l, img->c);

/*copia os valores presentes na matriz para o arquivo*/
for (i = 0; i < img->l; i++) {
	for (j = 0; j < img->c; j++) {
		fprintf(fout, "%d ", img->imagem[i][j]);
	}
}

fclose(fout);
}