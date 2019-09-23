#ifndef PGM_H
#define PGM_H

typedef struct _PGM {
	char magic_number[4];
	char *commentary;
	int w, h;
	int max_gray;
	unsigned char *pixels;
} PGM;

extern int load_PGM(PGM *pgm, const char *caminho_arquivo);

extern int save_PGM(const PGM *pgm, const char *caminho_arquivo);

extern int negative(PGM *output, const PGM *input);

#endif
