/*  Aluno: Lucas Fellipe Carvalho Moreira
    Matrícula: 16/0133394
    Disciplina: Estruturas de dados 1
    Professor: Matheus Mendelson
*/

#include <stdio.h>
#include <stdlib.h>
#define print(array, length) \
for(int i = 0; i < length; i++) \
printf("%.10lf%s", array[i], (i+1 == length ? "\n" : " "));
#define read(array, length) \
for(int i = 0; i < length; i++) \
scanf("%lf", &array[i]);
typedef double vector;
#define FOR(x, n) \
for(int i = 0; i < n; i++)

int fneuronio(vector *input, vector *weight, int n, double threshold)
{
    double SOMA_P = 0;
    FOR(0, n)
    {
        SOMA_P += input[i] * weight[i];
    }
    printf("Sum: %.10lf\n", SOMA_P);
    if(SOMA_P > threshold)
        return 1;
    return 0;
}

int main()
{
    vector *INPUT, *WEIGHT;
    INPUT = malloc(sizeof(double) * 10);
    WEIGHT = malloc(sizeof(double) * 10);
    printf("Input the 10 values of INPUT:\n");
    read(INPUT, 10);
    print(INPUT, 10);

    printf("Input the 10 values of WEIGHT:\n");
    read(WEIGHT, 10);
    print(WEIGHT, 10);

    printf("Input the threshold T:\n");
    double threshold;
    scanf("%lf", &threshold);
    if(fneuronio(INPUT, WEIGHT, 10, threshold))
        printf("Activated neuron!\n");
    else
        printf("Inhibited neuron!\n");

    free(INPUT);
    free(WEIGHT);
}