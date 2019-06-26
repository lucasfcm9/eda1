#include <stdio.h>
#include <stdlib.h>
typedef struct _neuron{
  struct _neuron *link;
  double *w;
  double bias;
  double s;
}Neuron;

int main(int argc, char *argv[ ]){
  // argc will recieve the number of arguments through command line
  // argv will recieve the arguments in a string format, so make sure to typecast these values
  int hidden_size = atoi(argv[1]);
  double example_feature[10] =  { 1.0, 3.4, 5.5, 1.6, 4.6, 8.9, 3.5, 4.0, 0.3, 1.2 };
  Neuron ent_layer[10];
  Neuron hidden_layer[hidden_size];
  Neuron final_layer;

  //linking each neuron to each other
  for(int i = 0; i < 10; i++){
    ent_layer[i].link = (Neuron*) malloc(hidden_size*sizeof(Neuron));
    printf("--------------------------------CAMADA DE ENTRADA: %d\n", &ent_layer[i]);
    for(int j = 0; j < hidden_size; j++){
      ent_layer[i].link[j].link = &hidden_layer[j];
      hidden_layer[j].link = (Neuron*) malloc(sizeof(Neuron));
      hidden_layer[j].link->link = &final_layer;

      printf("CAMADA DE OCULTA NO LINK: %d\n", ent_layer[i].link[j].link);
      printf("CAMADA DE OCULTA NORMAL: %d\n", &hidden_layer[j]);
      printf("CAMADA DE OCULTA FINAL: %d\n", hidden_layer[j].link->link);
      printf("CAMADA FINAL: %d\n", &final_layer);
    }
  }

  //
  

  return 0;
}
