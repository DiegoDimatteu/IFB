#include <stdio.h>
#include <string.h>

#define MAX_L 80
#define MAX_C 82
#define QTD_PAL 10

void le_palavras(char palavras[QTD_PAL][MAX_C], int pal);
void le_matriz(char matriz[MAX_L][MAX_C], int n);
void percorrer_matriz(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int n, int pal);
void horizontal(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int i, int n, int* teste);
void vertical(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int i, int n, int* teste);
void diagonal(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int i, int n, int* teste);
void anti_diagonal(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int i, int n, int* teste);

int main(){
	int n, pal; //n = tamanho da matriz/ pal = quantidade de palavras
	char matriz[MAX_L][MAX_C], palavras[QTD_PAL][MAX_C];
	scanf("%d", &n);
	scanf("%d", &pal);
	getchar();
	le_palavras(palavras, pal);
	le_matriz(matriz, n);
	percorrer_matriz(matriz, palavras, n, pal);
	return 0 ;
}

void le_palavras(char palavras[QTD_PAL][MAX_C], int pal){
	int i;
	for(i = 0; i < pal; i++){
		fgets(palavras[i], MAX_C, stdin);
		 if(palavras[i][strlen(palavras[i])-1]=='\n') {
                palavras[i][strlen(palavras[i])-1] = '\0';
        }
	}
}

void le_matriz(char matriz[MAX_L][MAX_C], int n){
	int i;
	for(i = 0; i < n; i++){
		fgets(matriz[i], MAX_C, stdin);
		 if(matriz[i][strlen(matriz[i])-1]=='\n') {
                matriz[i][strlen(matriz[i])-1] = '\0';
        }
	}
}

void percorrer_matriz(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int n, int pal){
	int i, teste; //teste vai garantir que quando encontrar a palavra em alguma dessas operacoes ela nao continue procurando nas outras operacoes e as pule
	for(i = 0; i < pal; i++){
		teste = 0;
		horizontal(matriz, palavras, i, n, &teste);
		if(!teste){
			vertical(matriz, palavras, i, n, &teste);
		}
		if(!teste){
			diagonal(matriz, palavras, i, n, &teste);
		}
		if(!teste){
			anti_diagonal(matriz, palavras, i, n, &teste);
		}
	}
}

void horizontal(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int i, int n, int* teste){
	int j, k, cont = 0, jp = 0, kp = 0, indice_palavra = 0, t;
	for(j = 0; j < n; j++){
		for(k = 0; k < n; k++){
			if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
				if(cont < strlen(palavras[i])){
					if(cont == 0){
						jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
					}
					cont++;
					indice_palavra++;
				}
				if(cont ==  strlen(palavras[i])){
					//printf("JP = %d && KP = %d\n", jp, kp);
					printf("%s ", palavras[i]);
					for(t = 0; t < strlen(palavras[i]); t++){
						printf("(%d,%d) ", jp, kp);
						kp++;
					}
					*teste = 1;
					printf("\n");
				}
			}
			else{
				k -= cont; //anulara a possibilidade de pular letras repetidas Ex: CCACHORRO, sem isso ele nao encontra a palavra CACHORRO
				cont = 0;
				indice_palavra = 0;
			}
		}
		cont = 0; //anulara a possibilidade de encontrar a palavra quebrada entre as linhas
		indice_palavra = 0;
	}

	// Fazendo o mesmo, porém com a palavra no sentido contrário. Para ver se o inverso dela se encontra na horizontal

	if (*teste == 0){ //caso teste = 1 ela nao fara o inverso da palavra, pois foi encontrado acima 
		cont = 0;
		indice_palavra = strlen(palavras[i]) - 1;

		for(j = 0; j < n; j++){
			for(k = 0; k < n; k++){
				if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
					if(cont < strlen(palavras[i])){
						if(cont == 0){
							jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
							kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						}
						cont++;
						indice_palavra--;
					}
					if(cont ==  strlen(palavras[i])){
						printf("%s ", palavras[i]);
						for(t = 0; t < strlen(palavras[i]); t++){
							printf("(%d,%d) ", jp, kp);
							kp++;
						}
						*teste = 1;
						printf("\n");
					}
				}
				else{
					k -= cont; //anulara a possibilidade de pular letras repetidas Ex: CCACHORRO, sem isso ele nao encontra a palavra CACHORRO
					cont = 0;
					indice_palavra = strlen(palavras[i]) - 1;
				}
			}
			cont = 0; //anulara a possibilidade de encontrar a palavra quebrada entre as linhas
			indice_palavra = strlen(palavras[i]) - 1;
		}
	}
}

void vertical(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int i, int n, int* teste){
	int j, k, cont = 0, jp = 0, kp = 0, indice_palavra = 0, t;
	for(k = 0; k < n; k++){
		for(j = 0; j < n; j++){
			if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
				if(cont < strlen(palavras[i])){
					if(cont == 0){
						jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
					}
					cont++;
					indice_palavra++;
				}
				if(cont ==  strlen(palavras[i])){
					printf("%s ", palavras[i]);
					for(t = 0; t < strlen(palavras[i]); t++){
						printf("(%d,%d) ", jp, kp);
						jp++;
					}
					*teste = 1;
					printf("\n");
				}
			}
			else{
				j -= cont;
				cont = 0;
				indice_palavra = 0;
			}
		}
		cont = 0;
		indice_palavra = 0;
	}

	// Fazendo o mesmo, porém com a palavra no sentido contrário. 

	if(*teste == 0){
		cont = 0;
		indice_palavra = strlen(palavras[i]) - 1;

		for(k = 0; k < n; k++){
			for(j = 0; j < n; j++){
				if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
					if(cont < strlen(palavras[i])){
						if(cont == 0){
							jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
							kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						}
						cont++;
						indice_palavra--;
					}
					if(cont ==  strlen(palavras[i])){
						printf("%s ", palavras[i]);
						for(t = 0; t < strlen(palavras[i]); t++){
							printf("(%d,%d) ", jp, kp);
							jp++;
						}
						*teste = 1;
						printf("\n");
					}
				}
				else{
					j -= cont;
					cont = 0;
					indice_palavra = strlen(palavras[i]) - 1;
				}
			}
			cont = 0;
			indice_palavra = strlen(palavras[i]) - 1;
		}
	}
}

void diagonal(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int i, int n, int* teste){
	int j, k, m, cont = 0, jp = 0, kp = 0, indice_palavra = 0, t;
	for(m= -n + 1; m <= 0; m++){ //diagonais negativas ate a zero, considerando as diagonais negativas situadas abaixo da diagonal principal, e diagonal zero a principal
		j = m < 0? -m : 0;
		while(j < n){
			k = j + m;
			if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
				if(cont < strlen(palavras[i])){
					if(cont == 0){
						jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
					}
					cont++;
					indice_palavra++;
				}
				if(cont ==  strlen(palavras[i])){
					printf("%s ", palavras[i]);
					for(t = 0; t < strlen(palavras[i]); t++){
						printf("(%d,%d) ", jp, kp);
						jp++;
						kp++;
					}
					*teste = 1;
					printf("\n");
				}
			}
			else{
				j -= cont;
				cont = 0;
				indice_palavra = 0;
			}
			j++;
		}
		cont = 0;
		indice_palavra = 0;
	}
	for(m = 1; m < n; m++){ //diagonais positivas acima de zero, considerando as diagonais positivas situadas acima da diagonal principal, e diagonal zero a principal
		k = m < 0? 0 : m;
		while(k < n){
			j = k - m;
			if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
				if(cont < strlen(palavras[i])){
					if(cont == 0){
						jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
					}
					cont++;
					indice_palavra++;
				}
				if(cont ==  strlen(palavras[i])){
					printf("%s ", palavras[i]);
					for(t = 0; t < strlen(palavras[i]); t++){
						printf("(%d,%d) ", jp, kp);
						jp++;
						kp++;
					}
					*teste = 1;
					printf("\n");
				}
			}
			else{
				k -= cont;
				cont = 0;
				indice_palavra = 0;
			}
			k++;
		}
		cont = 0;
		indice_palavra = 0;
	}

	// Fazendo o mesmo, porém com a palavra no sentido contrário. 

	if(*teste == 0){
		cont = 0;
		indice_palavra = strlen(palavras[i]) - 1;

		for(m= -n + 1; m <= 0; m++){
			j = m < 0? -m : 0;
			while(j < n){
				k = j + m;
				if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
						if(cont < strlen(palavras[i])){
							if(cont == 0){
								jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
								kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
							}
							cont++;
							indice_palavra--;
						}
						if(cont ==  strlen(palavras[i])){
							printf("%s ", palavras[i]);
							for(t = 0; t < strlen(palavras[i]); t++){
								printf("(%d,%d) ", jp, kp);
								jp++;
								kp++;
							}
							*teste = 1;
							printf("\n");
						}
					}
					else{
						j -= cont;
						cont = 0;
						indice_palavra = strlen(palavras[i]) - 1;
					}
				j++;
			}
			cont = 0;
			indice_palavra = strlen(palavras[i]) - 1;
		}
		for(m = 1; m < n; m++){
			k = m < 0? 0 : m;
			while(k < n){
				j = k - m;
				if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
						if(cont < strlen(palavras[i])){
							if(cont == 0){
								jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
								kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
							}
							cont++;
							indice_palavra--;
						}
						if(cont ==  strlen(palavras[i])){
							printf("%s ", palavras[i]);
							for(t = 0; t < strlen(palavras[i]); t++){
								printf("(%d,%d) ", jp, kp);
								jp++;
								kp++;
							}
							*teste = 1;
							printf("\n");
						}
					}
					else{
						k -= cont;
						cont = 0;
						indice_palavra = strlen(palavras[i]) - 1;
					}
				k++;
			}
			cont = 0;
			indice_palavra = strlen(palavras[i]) - 1;
		}
	}
}


void anti_diagonal(char matriz[MAX_L][MAX_C], char palavras[QTD_PAL][MAX_C], int i, int n, int* teste){
	int j, k, m, cont = 0, jp = 0, kp = 0, indice_palavra = 0, t;
	for(m= -n + 1; m <= 0; m++){
		j = m < 0? -m : 0;
		while(j < n){
			k = (n - 1) - (j + m);
			if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
				if(cont < strlen(palavras[i])){
					if(cont == 0){
						jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
					}
					cont++;
					indice_palavra++;
				}
				if(cont ==  strlen(palavras[i])){
					printf("%s ", palavras[i]);
					for(t = 0; t < strlen(palavras[i]); t++){
						printf("(%d,%d) ", jp, kp);
						jp++;
						kp--;
					}
					*teste = 1;
					printf("\n");
				}
			}
			else{
				j -= cont;
				cont = 0;
				indice_palavra = 0;
			}
			j++;
		}
		cont = 0;
		indice_palavra = 0;
	}
	for(m = n - 2; m >= 0; m--){
		k = m < 0? 0 : m;
		while(k > -1){
			j = (n - 2) - (k + ((n - 2) - m));
			if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
				if(cont < strlen(palavras[i])){
					if(cont == 0){
						jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
					}
					cont++;
					indice_palavra++;
				}
				if(cont ==  strlen(palavras[i])){
					printf("%s ", palavras[i]);
					for(t = 0; t < strlen(palavras[i]); t++){
						printf("(%d,%d) ", jp, kp);
						jp++;
						kp--;
					}
					*teste = 1;
					printf("\n");
				}
			}
			else{
				k += cont;
				cont = 0;
				indice_palavra = 0;
			}
			k--;
		}
		cont = 0;
		indice_palavra = 0;
	}

	// Fazendo o mesmo, porém com a palavra no sentido contrário. 

	if(!(*teste)){
		cont = 0;
		indice_palavra = strlen(palavras[i]) - 1;

		for(m= -n + 1; m <= 0; m++){
			j = m < 0? -m : 0;
			while(j < n){
				k = (n - 1) - (j + m);
				if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
					if(cont < strlen(palavras[i])){
						if(cont == 0){
							jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
							kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						}
						cont++;
						indice_palavra--;
					}
					if(cont ==  strlen(palavras[i])){
						printf("%s ", palavras[i]);
						for(t = 0; t < strlen(palavras[i]); t++){
							printf("(%d,%d) ", jp, kp);
							jp++;
							kp--;
						}
						*teste = 1;
						printf("\n");
					}
				}
				else{
					j -= cont;
					cont = 0;
					indice_palavra = strlen(palavras[i]) - 1;
				}
				j++;
			}
			cont = 0;
			indice_palavra = strlen(palavras[i]) - 1;
		}
		for(m = n - 2; m >= 0; m--){
			k = m < 0? 0 : m;
			while(k > -1){
				j = (n - 2) - (k + ((n - 2) - m));
				if((*teste == 0) && matriz[j][k] == palavras[i][indice_palavra]){
					if(cont < strlen(palavras[i])){
						if(cont == 0){
							jp = j; //armazana a posição da linha onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
							kp = k; //armazana a posição da coluna onde o primeiro carácter semelhante a palavra se encontra (possível candidato)
						}
						cont++;
						indice_palavra--;
					}
					if(cont ==  strlen(palavras[i])){
						printf("%s ", palavras[i]);
						for(t = 0; t < strlen(palavras[i]); t++){
							printf("(%d,%d) ", jp, kp);
							jp++;
							kp--;
						}
						*teste = 1;
						printf("\n");
					}
				}
				else{
					k += cont;
					cont = 0;
					indice_palavra = strlen(palavras[i]) - 1;
				}
				k--;
			}
			cont = 0;
			indice_palavra = strlen(palavras[i]) - 1;
		}
	}
}



