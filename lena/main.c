#include "pgm.h"
#include <stdio.h>

int main () {

  PGM original;
  int rc;

  rc = load_PGM(&original, "lena.pgm");
  if(rc != 0) {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return -1;
  }

  negative(&original, &original);
  rc = save_PGM(&original, "copia.pgm");
  if(rc != 0) {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return -2;
  }


  return 0;
}
