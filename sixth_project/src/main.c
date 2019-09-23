/* Alunos: Lucas Fellipe Carvalho Moreira && Pedro Henrique Queiroz Miranda && Gabriel Davi Silva Pereira

   Matrículas: 16/0133394 && 150144474 && 17/0010341

   Disciplina: Estruturas de Dados 1

   Professor: Mateus Mendelson

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define quantidade_de_neuronios 536
#define numero_de_imagens 100

typedef struct _neuron
{
  double *w;
  double bias;
  double somatorio;
  double s;
} Neuron;

void valores_aleatorios(Neuron *);
void somatorio(Neuron *, double *, double);
void funcao_logistica(Neuron *);
double derivada_funcao_logistica(double *);
void liberaAlocacao(Neuron *, Neuron *, Neuron *, double *, int);
void taxa_de_aceitacao(Neuron *, Neuron *, Neuron *, double *, double *, double *, int);

int main(int argc, char *argv[])
{
  srand(time(NULL)); // Resetar o rand

  int tamanho_da_camada = atoi(argv[1]); // Tamanho de elementos na camada oculta

  double saida_da_primeira_camada[quantidade_de_neuronios];
  double saida_da_camada_oculta[tamanho_da_camada];
  Neuron camada_de_entrada[quantidade_de_neuronios];
  Neuron camada_oculta[tamanho_da_camada];
  Neuron camada_de_saida;

  double **feature = (double **)calloc(numero_de_imagens, sizeof(double *));

  for (int i = 0; i < numero_de_imagens; i++)
  {
    feature[i] = (double *)calloc(quantidade_de_neuronios, sizeof(double));
  }
  FILE *fp = fopen("normalized_vectors.txt", "r"); //abertura Arquivo com vetor normalizado
  for (int i = 0; i < numero_de_imagens; i++)
  {
    if (i < 50)
      feature[i][0] = 1;
    for (int j = 1; j < quantidade_de_neuronios + 1; j++)
    {
      fscanf(fp, "%lf", &feature[i][j]);
    }
  }

  double vetor_grama[numero_de_imagens / 4][quantidade_de_neuronios + 1];
  double vetor_asfalto[numero_de_imagens / 4][quantidade_de_neuronios + 1];
  //CRIACAO ARRAY AUXILIAR COM NUMEROS ALEATORIOS DE 0 À 49.
  int array[numero_de_imagens / 2];
  for (int i = 0; i < numero_de_imagens / 2; i++)
  {
    array[i] = i;
  }

  for (int i = 0; i < numero_de_imagens / 2; i++)
  {
    int temp = array[i];
    int random_index = rand() % (numero_de_imagens / 2);

    //printf("%d\n", random_index);
    array[i] = array[random_index];
    array[random_index] = temp;
  }
  for (int i = 0; i < (numero_de_imagens / 4); i++)
  { //pegar 25 imagens de grama aleatorios p treino
    for (int j = 0; j < quantidade_de_neuronios + 1; j++)
    {
      vetor_grama[i][j] = *feature[array[i]];
    }
  }
  for (int i = 0; i < (numero_de_imagens / 4); i++)
  { //pegar 25 imagens de asfalto aleatorios p treino
    for (int j = 0; j < quantidade_de_neuronios + 1; j++)
    {
      vetor_asfalto[i][j] = *feature[array[i + (numero_de_imagens / 4)] + (numero_de_imagens / 2)];
    }
  }

  double vetor_treino[numero_de_imagens / 2][quantidade_de_neuronios + 1];
  for (int i = 0; i < (numero_de_imagens / 2); i++)
  {
    for (int j = 0; j < quantidade_de_neuronios + 1; j++)
    {
      if (i < 25)
        vetor_treino[i][j] = vetor_grama[i][j];
      else
        vetor_treino[i][j] = vetor_asfalto[i][j];
    }
  }

  double *erros = (double *)calloc(numero_de_imagens, sizeof(double));
  double erro_geral = 1;
  double limiar_erro_geral = 0.2;
  int epocas = 0;
  double taxa_de_aprendizagem = 0.2;
  int count = 0;
  int contador_de_erros = 0;
  double gradiente; //gradiente local para usar na backpropagation

  while (epocas < 1000)
  {
    for (int i = 0; i < quantidade_de_neuronios; i++)
    {
      valores_aleatorios(&camada_de_entrada[i]);
      somatorio(&camada_de_entrada[i], *feature, sizeof(feature) / sizeof(double));
      saida_da_primeira_camada[i] = camada_de_entrada[i].s;
      //printf("camada de entrada %d: %.2lf\n", i, camada_de_entrada[i].s);
    }

    for (int i = 0; i < tamanho_da_camada; i++)
    {
      valores_aleatorios(&camada_oculta[i]);
      somatorio(&camada_oculta[i], saida_da_primeira_camada, sizeof(saida_da_primeira_camada) / sizeof(double));

      saida_da_camada_oculta[i] = camada_oculta[i].s;
    }

    valores_aleatorios(&camada_de_saida);
    somatorio(&camada_de_saida, saida_da_camada_oculta, sizeof(saida_da_primeira_camada) / sizeof(double));
    //printf("camada final de saida: %.2lf\n", camada_de_saida.s);

    if (contador_de_erros < (numero_de_imagens / 2))
    {
      erros[contador_de_erros] = (vetor_treino[array[count]][0] == 0) ? (camada_de_saida.s) : (1 - camada_de_saida.s);

      printf("\t\tIniciando backpropagation %d Epoca\n\n\n", epocas);
      gradiente = derivada_funcao_logistica(&camada_de_saida.s) * erros[contador_de_erros];

      for (int i = 0; i < tamanho_da_camada; i++)
      {
        camada_de_saida.w[i] = camada_de_saida.w[i] + taxa_de_aprendizagem * (camada_de_saida.s) * gradiente;
      }

      camada_de_saida.bias = camada_de_saida.bias + taxa_de_aprendizagem * gradiente;
      for (int i = 0; i < tamanho_da_camada; i++)
      {
        gradiente = derivada_funcao_logistica(&camada_de_saida.s) * gradiente * erros[contador_de_erros];
        for (int j = 0; j < quantidade_de_neuronios; j++)
        {
          camada_oculta[i].w[j] = camada_oculta[i].w[j] + taxa_de_aprendizagem * (camada_de_saida.s) * gradiente;
        }
        camada_oculta[i].bias = camada_oculta[i].bias + taxa_de_aprendizagem * gradiente;
      }

      for (int i = 0; i < quantidade_de_neuronios; i++)
      {
        gradiente = derivada_funcao_logistica(&camada_de_saida.s) * gradiente * erros[contador_de_erros];

        //updateWeight(&camada_de_entrada[i], camada_de_entrada[i].w,taxa_de_aprendizagem,camada_de_saida.s,gradiente);
        for (int j = 0; j < quantidade_de_neuronios; j++)
        {
          camada_de_entrada[i].w[j] = camada_de_entrada[i].w[j] + taxa_de_aprendizagem * (camada_de_saida.s) * gradiente;
        }

        camada_de_entrada[i].bias = camada_de_entrada[i].bias + taxa_de_aprendizagem * gradiente;
      }
    }
    else
    { //calculando erro geral
      erro_geral = 0;
      contador_de_erros = 0;
      for (int i = 0; i < (numero_de_imagens / 2); i++)
      {
        erro_geral += pow(erros[i], 2);
      }
      erro_geral /= 50.0;
      printf("Precisão em %d epoca é %.45lf\n\n", epocas, erro_geral);
    }
    if (erro_geral <= limiar_erro_geral)
    {
      break;
    }
    contador_de_erros++;
    epocas = epocas + 1;
    count++;
    if (count > 50)
    {
      count = 0;
    }
    if (epocas % 50 == 0)
      printf("%d epocas prontas\n\n", epocas);
  }

  printf("Tempo de treinamento: %d epocas\n\n Precisao: %.45lf\n\n", epocas, erro_geral);

  printf("---------------------------------------------------------------------\n\n\n");

  taxa_de_aceitacao(camada_de_entrada, camada_oculta, &camada_de_saida, *feature, saida_da_primeira_camada, saida_da_camada_oculta, tamanho_da_camada);

  liberaAlocacao(camada_de_entrada, camada_oculta, &camada_de_saida, erros, tamanho_da_camada);
  return 0;
}

void taxa_de_aceitacao(Neuron *camada_de_entrada, Neuron *camada_oculta, Neuron *camada_de_saida, double *feature, double *saida_da_primeira_camada, double *saida_da_camada_oculta, int tamanho_da_camada)
{

  double taxa_de_acerto = 0;
  double taxa_de_falsa_aceitacao = 0; // ASFALTOS CLASSIFICADOS COMO GRAMA.
  double taxa_de_falsa_rejeicao = 0;  // GRAMA CLASSIFICADOS COMO ASFALTO
  int count = 0;

  do
  {
    //enviar a entrada para a primeira camada e salvar os resultados
    for (int i = 0; i < quantidade_de_neuronios; i++)
    {
      //printf("aqui first %d\n\n", i);
      somatorio(&camada_de_entrada[i], feature, quantidade_de_neuronios);
      saida_da_primeira_camada[i] = camada_de_entrada[i].s;
    }
    //enviar os resultados anteriores para a camada escondida e salvar os novos resultados
    for (int i = 0; i < tamanho_da_camada; i++)
    {
      somatorio(&camada_oculta[i], saida_da_primeira_camada, tamanho_da_camada);
      saida_da_camada_oculta[i] = camada_oculta[i].s;
    }
    //enviar os novos resultados para a ultima camada, calcular o erro e backpropagation
    somatorio(camada_de_saida, saida_da_camada_oculta, sizeof(saida_da_primeira_camada) / sizeof(double));
    if (feature[count] == 0)
    { //asfalto
      camada_de_saida->s <= 0.5 ? (taxa_de_acerto++) : (taxa_de_falsa_aceitacao++);
    }
    else
    {
      camada_de_saida->s > 0.5 ? (taxa_de_acerto++) : (taxa_de_falsa_rejeicao++);
    }

    count++;
  } while (count < numero_de_imagens);
  printf("Número de neurônios na camada oculta: %d\n", tamanho_da_camada);
  printf("\n\n - - - - - - - - - - - - - - -\n\n");
  printf("Taxa de Acerto: %.3lf\n", taxa_de_acerto / 100.0);
  printf("Taxa de Falsa Rejeição: %.3lf\n", taxa_de_falsa_rejeicao / 100.0);
  printf("Taxa de Falsa Aceitação: %.3lf\n", taxa_de_falsa_aceitacao / 100.0);
}

void liberaAlocacao(Neuron *camada_de_entrada, Neuron *camada_oculta, Neuron *camada_de_saida, double *errors, int tamanho_da_camada)
{
  for (int i = 0; i < quantidade_de_neuronios; i++)
  {
    free(camada_de_entrada[i].w);
  } //liberando neuronios na primeira camada
  for (int i = 0; i < tamanho_da_camada; i++)
  {
    free(camada_oculta[i].w);
  }                         //liberando neuronios camada oculta
  free(camada_de_saida->w); //liberando ultima camada
  free(errors);             //liberando vetor de erros
}

void valores_aleatorios(Neuron *neuron)
{
  neuron->w = (double *)calloc(quantidade_de_neuronios, sizeof(double));
  for (int i = 0; i < quantidade_de_neuronios; i++)
  {
    neuron->w[i] = (rand() % 32767) - 16384;
  }
  neuron->bias = (rand() % 32767) - 16384;
}

void somatorio(Neuron *neuron, double *feature, double size)
{
  neuron->somatorio = 0;
  for (int i = 0; i < size; i++)
  {
    neuron->somatorio += neuron->w[i] * feature[i];
  }
  neuron->somatorio += neuron->bias;
  funcao_logistica(neuron);
}

void funcao_logistica(Neuron *neuron)
{
  neuron->s = 1.0 / (1.0 + exp(-(neuron->somatorio)));
}

double derivada_funcao_logistica(double *value)
{ //derivada da funcao logistica
  return exp(*value) / (pow((exp(*value) + 1), 2));
}
