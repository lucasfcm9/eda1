#include "pgm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int load_PGM(PGM *pgm, const char *caminho_arquivo) {

		if(pgm == NULL || caminho_arquivo == NULL) {
			return -1; //Erro
	}
	FILE* f = fopen(caminho_arquivo, "r");

	if(f == NULL) {
		return -2;
	}

	fgets(pgm -> magic_number, 4, f);
	pgm -> magic_number[strlen(pgm->magic_number) - 1] = 0; //Substitui o \n por \0;

	long a, b, c, tamanho;
	a = ftell(f); //Onde ta o cursor de leitura;

	while((c = fgetc(f)) != '\n'); //Move o cursor de leitura até o \n;
	b = ftell(f) + 1;

	tamanho = b - a; //Qtd de caracteres

	pgm -> commentary = (char *) malloc(tamanho + 1);

	fseek(f, a, SEEK_SET); //Vai rebobinar o arquivo; (Cursor do arquivo)

	fgets(pgm -> commentary, tamanho + 1, f);
	pgm -> commentary[strlen(pgm -> commentary) - 1] = 0; //Substitui o \n por \0;

	fscanf(f, "%d %d\n", &pgm->w, &pgm->h);
	fscanf(f, "%d\n", &pgm->max_gray);

	pgm->pixels = (unsigned char*) malloc(pgm -> w * pgm -> h);
	fread(pgm -> pixels, sizeof(unsigned char), pgm -> w * pgm -> h, f);

	free(pgm -> pixels);
	free(pgm -> commentary);
	fclose(f);

	return 0;
}

int save_PGM(const PGM *pgm, const char *caminho_arquivo) {

	if(pgm == NULL || caminho_arquivo == NULL) {
		return -1; //Erro
	}

	if(pgm -> pixels == NULL) { //Usa-se seta pq é ponteiro
		return -2;
	}

	FILE* f = fopen(caminho_arquivo, "w");

	if(f == NULL) {
		return -3;
	}

	fprintf(f, "%s\n", pgm -> magic_number);

	if(pgm -> commentary != NULL) { //pgm -> commentary
		fprintf(f, "%s\n", pgm -> commentary);
	}

	fprintf(f, "%d %d\n", pgm->w, pgm->h);

	fprintf(f, "%d\n", pgm -> max_gray);

	fwrite(pgm -> pixels, sizeof(unsigned char), pgm -> h * pgm -> w, f); //fwrite -> bytes

	//fscanf(f, "%d %d\n", &pgm->w, &pgm->h);
	//fscanf(f, "%d\n", &pgm->max_gray);

	//pgm->pixels = (unsigned char*) malloc(pgm -> w * pgm -> h);
	//fread(pgm -> pixels, sizeof(unsigned char), pgm -> w * pgm -> h, f);

	fclose(f);

	return 0;
}

int negative(PGM *output, const PGM *input) {

	for(int i = 0; i < input -> w; i++) {
		for(int j = 0; j < input -> h; j++) {
			output -> pixels[i + j * input -> h] = 25 - input -> pixels[i + j * input -> w];
		}
	}
	return 0;
}
