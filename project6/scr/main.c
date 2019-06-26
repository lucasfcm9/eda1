#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define neuron_size 536
#define numero_de_imagens 100

typedef struct _neuron{
  double *w;
  double bias;
  double sum;
  double s;
}Neuron;

void randomValues(Neuron *);
void sum(Neuron *, double *, double);
void logistic_function(Neuron *);
double d_dx_logistic_function(double *);
void freeAlocation(Neuron *, Neuron *, Neuron *, double *, int );
void finalRates(Neuron *, Neuron *, Neuron *,  double* , double *, double *, int );
void loopEpoca(Neuron *, Neuron *, Neuron *,int*,double**,double*, double *, double *, int );


int main(int argc, char *argv[ ]){
  srand(time(NULL)); // Resetar o rand
  
  int hidden_size = atoi(argv[1]); // Tamanho de elementos na camada oculta

  double ent_exit[neuron_size];
  double hidden_exit[hidden_size];
  Neuron ent_layer[neuron_size];
  Neuron hidden_layer[hidden_size];
  Neuron final_layer;


  double feature[536];
  double number;
  FILE *fp = fopen("normalizados.txt", "r"); //abertura Arquivo com vetor normalizado
  /* For para leitura de arquivo */
  for(int i = 0; i < 536; i++)
  {
    fscanf(fp, "%lf ", &number);
    feature[i] = number;
  }


  double vetor_grama[numero_de_imagens/4][neuron_size+1];
  double vetor_asfalto[numero_de_imagens/4][neuron_size+1];
  //CRIACAO ARRAY AUXILIAR COM NUMEROS ALEATORIOS DE 0 À 49.
      int array[numero_de_imagens/2];
        for(int i=0; i<numero_de_imagens/2; i++){
        array[i] = i; //fill the array from 0 up to 49 -> 50 numbers
    //printf("%d\n", array[i]);
  }//end for array auxiliar
  
  for(int i=0; i<numero_de_imagens/2; i++){
      int temp = array[i];
      int random_index = rand() % (numero_de_imagens/2); //random number from 0 up to 49

      //printf("%d\n", random_index);
      array[i] = array[random_index];
      array[random_index] = temp;
    }//end for embaralha array auxiliar
    for(int i=0; i<(numero_de_imagens/4); i++){//pegar 25 de grama aleatorios p treino
      for(int j=0; j<neuron_size + 1; j++){
        vetor_grama[i][j] = feature[array[i]];//linha array[i] e um nuemro aleatorio de 0 a 49
      }
    }//end for pegar 25 de grama aleatorios p treino
    for(int i=0; i<(numero_de_imagens/4); i++){//pegar 25 de asfalto aleatorios p treino
      for(int j=0; j<neuron_size + 1; j++){
        vetor_asfalto[i][j] = feature[array[i+(numero_de_imagens/4)]+(numero_de_imagens/2)];//linha array[i+(numero_de_imagens/4)]+(numero_de_imagens/2) e um numero aleatorio de 50 a 99
      }
    }

  double vetor_treino[numero_de_imagens/2][neuron_size + 1];
  for(int i=0; i<(numero_de_imagens/2); i++){
    for(int j=0; j< neuron_size + 1; j++){
      if(i<25) vetor_treino[i][j] = vetor_grama[i][j];
      else vetor_treino[i][j] = vetor_asfalto[i][j];
    }
  }//end for vetor_treino

  loopEpoca(ent_layer, hidden_layer, &final_layer, array ,&vetor_treino, feature, ent_exit, hidden_exit, hidden_size);
 
  
  
  return 0;
}

void loopEpoca(Neuron *ent_layer, Neuron *hidden_layer, Neuron *final_layer,int* array,double** vetor_treino ,double* feature, double *ent_exit, double *hidden_exit, int hidden_size){
  double *erros = (double *)calloc(numero_de_imagens, sizeof(double));
  double erro_geral=1;
  double limiar_do_erro_geral = 0.2;
  int epocas=0;
  double taxa_de_aprendizagem = 0.2;
  int count = 0;
  int contador_de_erros=0;
  double gradiente; //gradiente local para usar na backpropagation

  while(epocas < 1000){
      //linking each neuron to each other
      for(int i = 0; i < neuron_size; i++){
        randomValues(&ent_layer[i]);
        sum(&ent_layer[i], feature, sizeof(feature)/sizeof(double));
        ent_exit[i] = ent_layer[i].s;
        //printf("Ent Layer %d: %.2lf\n", i, ent_layer[i].s);
      }

      for(int i = 0; i < hidden_size; i++){
        randomValues(&hidden_layer[i]);
        sum(&hidden_layer[i], ent_exit, sizeof(ent_exit)/sizeof(double));
        
        hidden_exit[i] = hidden_layer[i].s;
       // printf("hidden layer saida: %.2lf\n", hidden_exit[i]);
      }

      randomValues(&final_layer);
      sum(&final_layer, hidden_exit, sizeof(ent_exit)/sizeof(double));
      //printf("final Layer saida: %.2lf\n", final_layer.s);

      if(contador_de_erros<(numero_de_imagens/2)){
        erros[contador_de_erros] = (vetor_treino[array[count]][0] == 0) ? (final_layer->s) : (1 - final_layer->s);
        
        printf("BACKPROPAGATION initiating...%d period\n\n", epocas);
        gradiente = d_dx_logistic_function(&final_layer->s)*erros[contador_de_erros];

        for(int i=0; i<hidden_size; i++){
          final_layer->w[i] = final_layer->w[i] + taxa_de_aprendizagem*(final_layer->s)*gradiente;
        }


        final_layer->bias = final_layer->bias + taxa_de_aprendizagem*gradiente;
        for(int i=0; i<hidden_size; i++){
          gradiente = d_dx_logistic_function(&final_layer->s)*gradiente*erros[contador_de_erros];
          for(int j=0; j<neuron_size; j++){
            hidden_layer[i].w[j] = hidden_layer[i].w[j] + taxa_de_aprendizagem*(final_layer->s)*gradiente;
          }
          hidden_layer[i].bias = hidden_layer[i].bias + taxa_de_aprendizagem*gradiente;
        }

        for(int i=0; i<neuron_size; i++){
          gradiente = d_dx_logistic_function(&final_layer->s)*gradiente*erros[contador_de_erros];


          //updateWeight(&ent_layer[i], ent_layer[i].w,taxa_de_aprendizagem,final_layer.s,gradiente);
          for(int j=0; j<neuron_size; j++){
            ent_layer[i].w[j] = ent_layer[i].w[j] + taxa_de_aprendizagem*(final_layer->s)*gradiente;
          }
          
          ent_layer[i].bias = ent_layer[i].bias + taxa_de_aprendizagem*gradiente;
        }
        
      }
    else {//calcular erro geral
      erro_geral = 0;
      contador_de_erros = 0;
      for(int i=0; i<(numero_de_imagens/2); i++){
        erro_geral += pow(erros[i],2);
      }//erro geral
      erro_geral /= 50.0;
      printf("Accuracy on %d period was %.50lf\n\n", epocas, erro_geral);
    }
    if(erro_geral<=limiar_do_erro_geral){
      break;
    }
    contador_de_erros++;
    epocas = epocas + 1;
    count++;
    if(count > 50){
      count = 0;
    }
    printf("\n\n - - - -- - - - - - - - - - - ");
    printf("\nVALOR DO count: %d\n", count);
    printf("- - - -- - - - - - - - - - - \n\n");
    if(epocas % 50 == 0) printf("%d periods already done\n\n", epocas);
      
  } 

  printf("Training time : %d periods\n\nAccuracy reached : %.50lf\n\n", epocas, erro_geral);
  //TESTING NEURAL NETWORK
  printf("\n\nInitiating Neural Network ...\n\n\t\t********\n\n");

  finalRates(ent_layer,hidden_layer, &final_layer, &feature, &ent_exit, &hidden_exit, &hidden_size);

  freeAlocation(ent_layer, hidden_layer, &final_layer, erros, hidden_size);  
}


void finalRates(Neuron *ent_layer, Neuron *hidden_layer, Neuron *final_layer,  double* feature, double *ent_exit, double *hidden_exit, int hidden_size){
  
  double taxa_de_acerto = 0;
  double taxa_de_falsa_aceitacao = 0; // ASFALTOS CLASSIFICADOS COMO GRAMA.
  double taxa_de_falsa_rejeicao = 0; // GRAMA CLASSIFICADOS COMO ASFALTO
  int count = 0;

  do{
    //enviar a entrada para a primeira camada e salvar os resultados
    for(int i=0; i<neuron_size; i++){
      //printf("aqui first %d\n\n", i);
      sum(&ent_layer[i], feature, neuron_size);
      ent_exit[i]  = ent_layer[i].s;
    }
    //enviar os resultados anteriores para a camada escondida e salvar os novos resultados
    for(int i=0; i< hidden_size; i++){
      //printf("aqui second %d\n\n", i);
      sum(&hidden_layer[i], ent_exit, hidden_size);
      hidden_exit[i] = hidden_layer[i].s;
    }
    //enviar os novos resultados para a ultima camada, calcular o erro e backpropagation
    sum(&final_layer, hidden_exit, sizeof(ent_exit)/sizeof(double));
    if(feature[count] == 0){//asfalto
      final_layer->s <= 0.5 ? (taxa_de_acerto++) : (taxa_de_falsa_aceitacao++);
    }//end if asfalto
    else{//else grama
      final_layer->s > 0.5 ? (taxa_de_acerto++) : (taxa_de_falsa_rejeicao++);
    }//end else grama

    count++;
  }while(count < numero_de_imagens);
  printf("Número de neurônios na camada oculta: %d\n", hidden_size);
  printf("\n\n - - - - - - - - - - - - - - -\n\n");
  printf("Taxa de acerto: %.3lf\n", taxa_de_acerto/100.0);
  printf("Taxa de falsa rejeicao: %.3lf\n", taxa_de_falsa_rejeicao/100.0);
  printf("Taxa de falsa aceitacao: %.3lf\n", taxa_de_falsa_aceitacao/100.0);
}

void freeAlocation(Neuron *ent_layer, Neuron *hidden_layer, Neuron *final_layer, double *errors, int hidden_size){
  for(int i=0; i<neuron_size; i++){
    free(ent_layer[i].w);
  }//liberando neuronios na primeira camada
  for(int i=0; i<hidden_size; i++){
    free(hidden_layer[i].w);
  }//liberando neuronios camada oculta
  free(final_layer->w);//liberando ultima camada
  free(errors);//liberando vetor de erros
 
}

void randomValues(Neuron * neuron){
  neuron->w= (double*)calloc(neuron_size, sizeof(double));
  for(int i = 0; i < neuron_size; i++){
      neuron->w[i] = (rand()%32767) - 16384;
  }
  neuron->bias = (rand()%32767) - 16384;
}

void sum(Neuron * neuron, double * feature, double size){
    neuron->sum = 0;
    for(int i = 0; i < size; i++){
      neuron->sum += neuron->w[i]*feature[i];
    }
    neuron->sum+=neuron->bias;
    logistic_function(neuron);
}

void logistic_function(Neuron * neuron){
  neuron->s = 1.0/(1.0 + exp(-(neuron->sum)));
}

double d_dx_logistic_function(double *value){//derivada da logistica
  return exp(*value)/( pow( (exp(*value)+1) , 2) );//e^x / (e^x + 1)^2
}//end of d_dx_logistic_function
