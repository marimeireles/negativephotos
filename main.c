#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main () {

char nomeArquivoEntrada [30];
printf("Digite o nome do arquivo de entrada:\n");
scanf("%s", nomeArquivoEntrada);
char nomeArquivoSaida [30];
printf("Digite o nome do arquivo de saída:\n");
scanf("%s", nomeArquivoSaida);
PGM PGMEntrada; /*PGM de entrada*/
PGM PGMSaida; /*PGM de saída*/
int i, j;
char **kernell;


/*armazena os dados do arquivo de entrada na variável PGMEntrada de tipo 
PGM*/
PGMEntrada = *LerPGM (nomeArquivoEntrada);

/*checa se os arquivos foram alocados corretamente*/
for (i = 0; i < PGMEntrada.l; i++) {
	for (j = 0; j < PGMEntrada.c; j++) {
	printf("main: na posição [%d][%d] encontra-se o valor %d\n", i, j, PGMEntrada.imagem[i][j]);	
	}
}

Convolucao (&PGMEntrada, kernell, &PGMSaida);

SalvarPGM (&PGMSaida, nomeArquivoSaida);

return 0;
}