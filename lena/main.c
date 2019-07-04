#include "pgm.h"
#include <stdio.h>

int main () {

  PGM original;
  int rc; //Return code; Vai receber (loag_PGM)

  rc = load_PGM(&original, "lena.pgm");
  if(rc != 0) {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return -1; //exit(1) - Indica erro;
  }

  negative(&original, &original);
  rc = save_PGM(&original, "copia.pgm");
  if(rc != 0) {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return -2; //exit(2) - Indica erro;
  }


  return 0;
}
