#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct lista_voo{
  char codigo[6];
  char modo;
  int combustivel;
  struct lista_voo *prox;
} Lista_voo;

typedef struct fila{
  Lista_voo *ini;
  Lista_voo *fim;
} Fila;

void gera_voo(Fila*, int);
void imprime(Fila*);
void decresce_combustivel(Fila*);


char *CODIGO_VOO[] =  {"VG3001",
"JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009", "AZ1008",
"AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012",
"TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002",
"AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", "AZ1001",
"LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601",
"TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392",
"GF4681", "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065",
"LF0978", "RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510",
"TT1020", "AZ1098", "BA2312", "VG3030", "BA2304", "KL5609",
"KL5610", "KL5611"};

int main(){
  srand(time(NULL));
  Fila fila;
  int num_voos;
  fila.ini = NULL;
  fila.fim = NULL;
  //GERANDO UM NUMERO ENTRE 20 E 64
  num_voos = rand() % 44 + 20;
  //Iniciando os voos de acordo com o num_voos
  for(int i=0; i<num_voos; i++){
    gera_voo(&fila, i);
  }


  // Relógio Global
  int d_combustivel = 0;
  int pouso = 0;
  int decolagem = 0;
  int count = 0;
  
  // while(count != 120){
  //   if(d_combustivel==10){
  //     d_combustivel = 0;
  //   }
  //   d_combustivel++;
  //   count++;
  // }

   imprime(&fila);
   decresce_combustivel(&fila);
   printf("Decresce combustivel #######################\n");
   imprime(&fila);
  return 0;
}

void gera_voo(Fila *fila, int num_voo){
  Lista_voo *elem = (Lista_voo*)malloc(sizeof(Lista_voo));

  if(elem == NULL){
    exit(0);
  }

  //Iniciando os valores dos elementos do voo de forma aleatoria
  strcpy(elem->codigo, CODIGO_VOO[num_voo]);
  elem->modo = rand()%2 > 0 ? 'A' : 'D';
  if(elem->modo == 'A'){
    elem->combustivel = rand()%13;
  }else{
    elem->combustivel = 100;
  }

  if(fila->ini == NULL){
    elem->prox = NULL;
    fila->ini = elem;
    fila->fim = elem;
    return;
  }

  Lista_voo *atual;
  for(atual = fila->ini; atual != NULL; atual = atual->prox){
    if(elem->combustivel == 0){
      elem->prox  = fila->ini;
      fila->ini = elem;
      return;
    }else if(atual->prox == NULL){
      atual->prox = elem;
      elem->prox = NULL;
      fila->fim = elem;
    }
  }

}

void imprime(Fila *fila){
  Lista_voo *atual;
  int i = 0;
  for(atual = fila->ini; atual != NULL; atual = atual->prox){
    printf("----------------------  %d ---------------------------------\n", i);
    printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
    i++;
  }
}

void decresce_combustivel(Fila *fila){
  printf("Decresce\n");
  Lista_voo *elem;
  Lista_voo *anterior = NULL;
  Lista_voo *aux = NULL;
  for(elem = fila->ini; elem != NULL; elem = elem->prox){
    if(elem->modo == 'A'){
      elem->combustivel--;
    }
  }

//Deletando os elementos que possuirem gasolina menos que 0
  for(elem = fila->ini; elem != NULL; anterior = elem, elem = elem->prox){
    if(elem->combustivel < 0){
        //Se o elemento for o primeiro da Fila
        aux = elem;
        if(elem == fila->ini){
          fila->ini = elem->prox;
          free(aux);
        }
        //Se o elemento estiver no final da fila
         else if(elem->prox == NULL){
           anterior->prox = NULL;
           fila->fim = anterior;
           free(aux);
        }
        //se estiver no meio da fila
        else {
          anterior->prox = elem->prox;
          free(aux);
        }
    }
  }

  //ordenando a lista após deletagem, onde os que possuirem 0 como combustivel irao para o inicio
  for(elem = fila->ini, anterior = NULL; elem != NULL; anterior = elem, elem = elem->prox){
    if(elem->combustivel == 0 && anterior != NULL){
      //colocar um elmento do final no inicio

      if(elem->prox == NULL){
        printf("null\n");
        fila->fim = anterior;
        anterior->prox = NULL;
        elem->prox = fila->ini;
        fila->ini = elem;
      }else{
        printf("else\n");
        anterior->prox = elem->prox;
        elem->prox = fila->ini;
        fila->ini = elem;
        elem = anterior;
      }
    }
  }
}

void ordena(Fila *fila){

}
