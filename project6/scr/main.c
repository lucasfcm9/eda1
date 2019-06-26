#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct _neuron{
  struct _neuron *link;
  double *w;
  double bias;
  double sum;
  double s;
}Neuron;

void randomValues(Neuron *);
void sum(Neuron *, double *, double);
void logistic_function(Neuron *);

int main(int argc, char *argv[ ]){
  // argc will recieve the number of arguments through command line
  // argv will recieve the arguments in a string format, so make sure to typecast these values
  int hidden_size = atoi(argv[1]);
  double example_feature[10] =  { 14334334.430943083400, 3.4, 53040349.5, 1.643434344, 4.434346, 84341.9, 34341.5, 4.0, 0.33333333, 133333.2 };
  double ent_exit[10];
  Neuron ent_layer[10];
  Neuron hidden_layer[hidden_size];
  Neuron final_layer;

  //linking each neuron to each other
  for(int i = 0; i < 10; i++){
    ent_layer[i].link = (Neuron*) malloc(hidden_size*sizeof(Neuron));
    randomValues(&ent_layer[i]);
    sum(&ent_layer[i], example_feature, sizeof(example_feature)/sizeof(double));
    ent_exit[i] = ent_layer[i].s;
    for(int j = 0; j < hidden_size; j++){
      ent_layer[i].link[j].link = &hidden_layer[j];
      hidden_layer[j].link = (Neuron*) malloc(sizeof(Neuron));
      hidden_layer[j].link->link = &final_layer;

      randomValues(&hidden_layer[j]);
    }
  }
  randomValues(&final_layer);
  printf("HIDDEN\n");
  for(int i = 0; i < hidden_size; i++){
    sum(&hidden_layer[i], ent_exit, sizeof(ent_exit)/sizeof(double));
    printf("hidden_layer %d saida %.2lf\n",i, hidden_layer[i].s);
  }

  return 0;
}

void randomValues(Neuron * neuron){
  neuron->w= (double*)calloc(10, sizeof(double));
  for(int i = 0; i < 10; i++){
      neuron->w[i] = rand()%1500;
  }
  neuron->bias = rand()%1500;
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
