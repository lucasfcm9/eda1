#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct lista_voo{
  char codigo[6];
  char modo;
  int combustivel;
  bool status;
  bool nenhumaPista;
  int countNoGas;
  struct lista_voo *prox;
} Lista_voo;

typedef struct fila{
  Lista_voo *ini;
  Lista_voo *fim;
} Fila;

void gera_voo(Fila*, int);
void imprime(Fila*);
void decresce_combustivel(Fila*, int);
int verificarPistas(Fila*,Lista_voo*, Lista_voo*, Lista_voo*);
bool verificarFila(Fila*);
void limparFila(Fila*);

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

int HORAS = 10;
int MIN = 0;

int main(){
  srand(time(NULL));
  Fila fila;
  int num_voos;
  fila.ini = NULL;
  fila.fim = NULL;

  Lista_voo *pista_1;
  Lista_voo *pista_2;
  Lista_voo *pista_3;

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
  int N_Aprox = 0;
  int N_Deco = 0;
  Lista_voo *atual;
  Lista_voo *verification;
  int i = 0;

  int pista1_count = 0;
  int pista2_count = 0;
  int pista3_count = 0;
  int verificarPistas_verification = 0;

  bool pista1_ocupada[2] = {false, false}; //    pista_ocupada[0] significa se a pista ta ocupada ou nao
  bool pista2_ocupada[2] = {false, false}; //    pista_ocupada[1] significa se é 'A'(false) ou 'D'(true)
  bool pista3_ocupada[2] = {false, false}; //

  for(atual = fila.ini, i = 0; atual != NULL ; i++, atual = atual->prox){
        if(atual->modo == 'A'){
          N_Aprox++;
        }
        else{
          N_Deco++;
        }
  }
  printf("\n---------------------------------------------------------------------------------\n");
  printf("“Aeroporto Internacional de Brasília”\n");
  printf("Hora Inicial: %.2d:%.2d:00\n",HORAS,MIN);
  printf("Fila de Pedidos: \n");
  imprime(&fila);
  printf("NVoos: %d\n", num_voos );
  printf("Naproximações: %d\n", N_Aprox);
  printf("NDecolagens: %d\n", N_Deco);
  printf("---------------------------------------------------------------------------------\n");
  printf("Listagem de eventos: \n\n");

   while(verificarFila(&fila) == true){


        verification = fila.ini;
        //FOR para printar o primeiro, segunda e terceiro da fila em cada pista
        for(atual = fila.ini, i = 0; i < 3 ; i++, atual = atual->prox){

            if(i == 0){
              printf("\n3 Primeiros da fila:\n");
              printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
              printf("%s\n%c\n%d\n", (atual->prox)->codigo, (atual->prox)->modo, (atual->prox)->combustivel);
              printf("%s\n%c\n%d\n", ((atual->prox)->prox)->codigo, ((atual->prox)->prox)->modo, ((atual->prox)->prox)->combustivel);
            }

            if((verification->modo == 'A' && verification->combustivel == 0) && ((verification->prox)->modo == 'A' && (verification->prox)->combustivel == 0) && (((verification->prox)->prox)->modo == 'A' && ((verification->prox)->prox)->combustivel == 0) && verificarPistas_verification == 0){

                    printf("\n !! ALERTA GERAL DE DESVIO DE AERONAVE !!\n");

                    //VERIFICAR PISTA 3
                      if(pista3_ocupada[0] == false && pista2_ocupada[0] == true && pista1_ocupada[0] == true){
                        if(atual->modo == 'A' && atual->combustivel == 0){

                          pista_3 = atual;
                          printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
                          printf("Código do voo: %s\n", atual->codigo);
                          pista3_ocupada[0] = true;
                          pista3_ocupada[1] = false;
                          printf("Status: “aeronave pousou”\n");
                          printf("Horário do início do procedimento: %.2d:%.2d:00\n", HORAS, MIN);
                          printf("Pista: 3\n");
                          printf("-----------------------------------------------------------------\n");
                          atual->status = true;

                        }
                        else if(atual->modo == 'D'){
                          pista_3 = atual;
                          printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
                          printf("Código do voo: %s\n", atual->codigo);
                          pista3_ocupada[0] = true;
                          pista3_ocupada[1] = true;
                          printf("Status: “aeronave decolou”\n");
                          printf("Horário do início do procedimento: %.2d:%.2d:00\n", HORAS, MIN);
                          printf("Pista: 3\n");
                          printf("-----------------------------------------------------------------\n");
                          atual->status = true;
                        }
                      }


                    //VERIFICAR PISTA 2
                      if(pista2_ocupada[0] == false && pista1_ocupada[0] == true ){
                        pista_2 = atual;
                        printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
                        printf("Código do voo: %s\n", atual->codigo);
                        if(atual->modo == 'A'){
                          pista2_ocupada[0] = true;
                          pista2_ocupada[1] = false;
                          printf("Status: “aeronave pousou”\n");
                        }
                        else{
                          pista2_ocupada[0] = true;
                          pista2_ocupada[1] = true;
                          printf("Status: “aeronave decolou”\n");
                        }
                        printf("Horário do início do procedimento: %.2d:%.2d:00\n", HORAS, MIN);
                        printf("Pista: 2\n");
                        printf("-----------------------------------------------------------------\n\n");
                        atual->status = true;
                      }

                    //VERIFICAR PISTA 1
                      if(pista1_ocupada[0] == false){
                        pista_1 = atual;
                        printf("\n-----------------------------------------------------------------\n");
                        printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
                        printf("Código do voo: %s\n", atual->codigo);
                        if(atual->modo == 'A'){
                          pista1_ocupada[0] = true;
                          pista1_ocupada[1] = false;
                          printf("Status: “aeronave pousou”\n");
                        }
                        else{
                          pista1_ocupada[0] = true;
                          pista1_ocupada[1] = true;
                          printf("Status: “aeronave decolou”\n");
                        }
                        printf("Horário do início do procedimento: %.2d:%.2d:00\n", HORAS, MIN);
                        printf("Pista: 1\n");
                        printf("-----------------------------------------------------------------\n\n");
                        atual->status = true;
                      }else{

                        atual->nenhumaPista = true;
                      }


                      i = 4;
            }
            else{


                  //VERIFICAR PISTA 3
                    if(pista3_ocupada[0] == false && pista2_ocupada[0] == true && pista1_ocupada[0] == true){
                      if(atual->modo == 'A' && atual->combustivel == 0){

                        pista_3 = atual;
                        printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
                        printf("Código do voo: %s\n", atual->codigo);
                        pista3_ocupada[0] = true;
                        pista3_ocupada[1] = false;
                        printf("Status: “aeronave pousou”\n");
                        printf("Horário do início do procedimento: %.2d:%.2d:00\n", HORAS, MIN);
                        printf("Pista: 3\n");
                        printf("-----------------------------------------------------------------\n");
                        atual->status = true;

                      }
                      else if(atual->modo == 'D'){
                        pista_3 = atual;
                        printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
                        printf("Código do voo: %s\n", atual->codigo);
                        pista3_ocupada[0] = true;
                        pista3_ocupada[1] = true;
                        printf("Status: “aeronave decolou”\n");
                        printf("Horário do início do procedimento: %.2d:%.2d:00\n", HORAS, MIN);
                        printf("Pista: 3\n");
                        printf("-----------------------------------------------------------------\n");
                        atual->status = true;
                      }
                    }


                  //VERIFICAR PISTA 2
                    if(pista2_ocupada[0] == false && pista1_ocupada[0] == true ){
                      pista_2 = atual;
                      printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
                      printf("Código do voo: %s\n", atual->codigo);
                      if(atual->modo == 'A'){
                        pista2_ocupada[0] = true;
                        pista2_ocupada[1] = false;
                        printf("Status: “aeronave pousou”\n");
                      }
                      else{
                        pista2_ocupada[0] = true;
                        pista2_ocupada[1] = true;
                        printf("Status: “aeronave decolou”\n");
                      }
                      printf("Horário do início do procedimento: %.2d:%.2d:00\n", HORAS, MIN);
                      printf("Pista: 2\n");
                      printf("-----------------------------------------------------------------\n\n");
                      atual->status = true;
                    }

                  //VERIFICAR PISTA 1
                    if(pista1_ocupada[0] == false){
                      pista_1 = atual;
                      printf("\n-----------------------------------------------------------------\n");
                      printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
                      printf("Código do voo: %s\n", atual->codigo);
                      if(atual->modo == 'A'){
                        pista1_ocupada[0] = true;
                        pista1_ocupada[1] = false;
                        printf("Status: “aeronave pousou”\n");
                      }
                      else{
                        pista1_ocupada[0] = true;
                        pista1_ocupada[1] = true;
                        printf("Status: “aeronave decolou”\n");
                      }
                      printf("Horário do início do procedimento: %.2d:%.2d:00\n", HORAS, MIN);
                      printf("Pista: 1\n");
                      printf("-----------------------------------------------------------------\n\n");
                      atual->status = true;
                    }



            }//FIM DO ELSE//

            verificarPistas_verification = 1;


        }// FIM DO FOR DE LISTAS //

        verificarPistas_verification = 0;

    //PISO 1 COUNT:

      /* UNIDADE DE TEMPO PARA PISTA 1 (POUSO) -> pista1_ocupada[1] == false */
      if(pista1_ocupada[0] == true && pista1_ocupada[1] == false){
        pista1_count++;
      }
      if(pista1_count == 4 && pista1_ocupada[1] == false){
        pista1_ocupada[0] = false;
        pista1_count = 0;
      }

      /* UNIDADE DE TEMPO PARA PISTA 1 (DESCOLAGEM) -> pista1_ocupada[1] == true */
      if(pista1_ocupada[0] == true && pista1_ocupada[1] == true){
        pista1_count++;
      }
      if(pista1_count == 2 && pista1_ocupada[1] == true){
        pista1_ocupada[0] = false;
        pista1_count = 0;
      }

    //FIM COUNT PISO 1//


    //PISO 2 COUNT:

      /* UNIDADE DE TEMPO PARA PISTA 2 (POUSO) -> pista2_ocupada[1] == false */
      if(pista2_ocupada[0] == true && pista2_ocupada[1] == false){
        pista2_count++;
      }
      if(pista2_count == 4 && pista2_ocupada[1] == false){
        pista2_ocupada[0] = false;
        pista2_count = 0;
      }

      /* UNIDADE DE TEMPO PARA PISTA 2 (DESCOLAGEM) -> pista2_ocupada[1] == true */
      if(pista2_ocupada[0] == true && pista2_ocupada[1] == true){
        pista2_count++;
      }
      if(pista2_count == 2 && pista2_ocupada[1] == true){
        pista2_ocupada[0] = false;
        pista2_count = 0;
      }

    //FIM COUNT PISO 2//


    //PISO 3 COUNT:

      /* UNIDADE DE TEMPO PARA PISTA 3 (POUSO) -> pista3_ocupada[1] == false */
      if(pista3_ocupada[0] == true && pista3_ocupada[1] == false){
        pista3_count++;
      }
      if(pista3_count == 4 && pista3_ocupada[1] == false){
        pista3_ocupada[0] = false;
        pista3_count = 0;
      }

      /* UNIDADE DE TEMPO PARA PISTA 3 (DESCOLAGEM) -> pista3_ocupada[1] == true */
      if(pista3_ocupada[0] == true && pista3_ocupada[1] == true){
        pista3_count++;
      }
      if(pista3_count == 2 && pista3_ocupada[1] == true){
        pista3_ocupada[0] = false;
        pista3_count = 0;
      }

    //FIM COUNT PISO 3//



     decresce_combustivel(&fila, d_combustivel);
     if(d_combustivel == 9){
       d_combustivel = 0;
     }

     if((HORAS + 1) == 25){
       HORAS = 0;
     }

     if((MIN + 5) == 60){
       MIN = 0;
       HORAS ++;
     }
     else{
       MIN += 5;
     }

     printf("HORAS: %.2d:%.2d:00",HORAS, MIN);
     count ++;
     i = 0;
     d_combustivel++;

     for(atual = fila.ini; atual != NULL; atual = atual->prox){
       if(atual->nenhumaPista == true){

         atual->countNoGas = atual->countNoGas + 1;

       }
     }

     //sleep(1);
   }

   //imprime(&fila);
   //decresce_combustivel(&fila);
   //printf("Decresce combustivel #######################\n");
   //imprime(&fila);
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
  elem->status = false;
  elem->nenhumaPista = false;
  elem->countNoGas = 0;

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
      printf("        [ %s – %c – prioridade]\n", atual->codigo, atual->modo);
      //printf("%s\n%c\n%d\n", atual->codigo, atual->modo, atual->combustivel);
    i++;
  }
}

void decresce_combustivel(Fila *fila, int unidade_count){
 // printf("Decresce\n");
  Lista_voo *elem;
  Lista_voo *anterior = NULL;
  Lista_voo *aux = NULL;

  if(unidade_count == 9){
    for(elem = fila->ini; elem != NULL; elem = elem->prox){
      if(elem->modo == 'A'){

        elem->combustivel = elem->combustivel - 1;
        printf("Aeronave: %s\nModo: %c\nNivel de Combustível: %d\n",elem->codigo,elem->modo,elem->combustivel );
      }
    }
  }

  int tamanhoFila = 0;

  printf("\n ---------------------------------------------------------------------\n");
  for(elem = fila->ini; elem != NULL; anterior = elem, elem = elem->prox){

    tamanhoFila++;

  }
  printf("Antes do for:\n");
  printf("Tamanho da fila: %d\n", tamanhoFila);

  //Deletando da fila que ja pousou ou decolou
  for(elem = fila->ini; elem != NULL; anterior = elem, elem = elem->prox){

      if(elem->status == true){

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
  tamanhoFila = 0;
  printf("\n ---------------------------------------------------------------------\n");
  for(elem = fila->ini; elem != NULL; anterior = elem, elem = elem->prox){

    tamanhoFila++;

  }
  printf("Depois do for:\n");
  printf("Tamanho da fila: %d\n", tamanhoFila);



//Deletando os elementos que possuirem gasolina menos que 0
  for(elem = fila->ini; elem != NULL; anterior = elem, elem = elem->prox){
    if(elem->combustivel < 0){
        //Se o elemento for o primeiro da Fila
        aux = elem;
        if(elem == fila->ini){
          fila->ini = elem->prox;
          printf("\n !! ALERTA CRÍTICO, AERONAVE IRÁ CAIR !!\n");
          free(aux);
        }
        //Se o elemento estiver no final da fila
         else if(elem->prox == NULL){
           anterior->prox = NULL;
           fila->fim = anterior;
           printf("\n !! ALERTA CRÍTICO, AERONAVE IRÁ CAIR !!\n");
           free(aux);
        }
        //se estiver no meio da fila
        else {
          anterior->prox = elem->prox;
          printf("\n !! ALERTA CRÍTICO, AERONAVE IRÁ CAIR !!\n");
          free(aux);
        }
      }

    }


  //Deletando os elementos que Acionaram ALERTA CRITICO e nao tiveram pista para pouso
    for(elem = fila->ini; elem != NULL; anterior = elem, elem = elem->prox){
      if(elem->countNoGas == 1){
          //Se o elemento for o primeiro da Fila
          aux = elem;
          if(elem == fila->ini){
            fila->ini = elem->prox;
            printf("\n !! ALERTA CRÍTICO, AERONAVE IRÁ CAIR !!\n");
            free(aux);
          }
          //Se o elemento estiver no final da fila
           else if(elem->prox == NULL){
             anterior->prox = NULL;
             fila->fim = anterior;
             printf("\n !! ALERTA CRÍTICO, AERONAVE IRÁ CAIR !!\n");
             free(aux);
          }
          //se estiver no meio da fila
          else {
            anterior->prox = elem->prox;
            printf("\n !! ALERTA CRÍTICO, AERONAVE IRÁ CAIR !!\n");
            free(aux);
          }
        }
      }





  //ordenando a lista após deletagem, onde os que possuirem 0 como combustivel irao para o inicio
  for(elem = fila->ini, anterior = NULL; elem != NULL; anterior = elem, elem = elem->prox){
    if(elem->combustivel == 0 && anterior != NULL){
      //colocar um elmento do final no inicio

      if(elem->prox == NULL){
        //printf("null\n");
        fila->fim = anterior;
        anterior->prox = NULL;
        elem->prox = fila->ini;
        fila->ini = elem;
      }else{
        //printf("else\n");
        anterior->prox = elem->prox;
        elem->prox = fila->ini;
        fila->ini = elem;
        elem = anterior;
      }
    }
  }
}

int verificarPistas(Fila *fila ,Lista_voo *p1, Lista_voo *p2, Lista_voo *p3){
  Lista_voo *atual;

  if((p1->combustivel == 0 && p1->modo == 'A') && (p2->combustivel == 0 && p2->modo == 'A') && (p3->combustivel == 0 && p3->modo == 'A')  ){

    return 1;

  }

}

bool verificarFila(Fila *fila){

  if(fila->ini == NULL){
      return false;
  }

  return true;

}

void limparFila(Fila *fila){

  Lista_voo *elem;
  Lista_voo *anterior = NULL;
  Lista_voo *aux = NULL;
  int tamanhoFila = 0;

  printf("\n ---------------------------------------------------------------------\n");
  for(elem = fila->ini; elem != NULL; anterior = elem, elem = elem->prox){

    tamanhoFila++;

  }
  printf("Antes do for:\n");
  printf("Tamanho da fila: %d\n", tamanhoFila);

  for(elem = fila->ini; elem != NULL; anterior = elem, elem = elem->prox){

      if(elem->status == true){

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
  tamanhoFila = 0;
  printf("\n ---------------------------------------------------------------------\n");
  for(elem = fila->ini; elem != NULL; anterior = elem, elem = elem->prox){

    tamanhoFila++;

  }
  printf("Depois do for:\n");
  printf("Tamanho da fila: %d\n", tamanhoFila);

}

void ordena(Fila *fila){

}
