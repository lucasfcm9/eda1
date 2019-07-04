#ifndef PGM_H
#define PGM_H

typedef struct _PGM {
	char magic_number[4];
	char *commentary;
	int w, h; //Largura e altura
	int max_gray;
	unsigned char *pixels; //Não sabemos o tamanho, por isso o uso do ponteiro;
} PGM;

//Declarando as funções

extern int load_PGM(PGM *pgm, const char *caminho_arquivo); //Vai ler a PGM com um char constante para encontrar o caminho do arquivo;
//int para retornar sucesso(0) ou não(!=0)

extern int save_PGM(const PGM *pgm, const char *caminho_arquivo);

extern int negative(PGM *output, const PGM *input);

#endif
