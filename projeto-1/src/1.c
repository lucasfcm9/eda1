#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void print(double *v, int size);
int *fneuronio(double *entradas, double *pesos, double limiar, int size, int *x);

int main()
{

    int i;
    double ENTRADAS[SIZE], PESOS[SIZE], limiar;

    printf("Entre com os 10 valores de ENTRADAS: \n");
    for (i = 0; i < SIZE; i++)
    {
        scanf("%lf", &ENTRADAS[i]);
    }

    print(ENTRADAS, SIZE);

    printf("Entre com os 10 valores de PESOS: \n");
    for (i = 0; i < SIZE; i++)
    {
        scanf("%lf", &PESOS[i]);
    }

    print(PESOS, SIZE);

    printf("Entre com o valor do limiar T: ");
    scanf("%lf", &limiar);

    printf("Limiar T: %.3lf\n", limiar);

    int x;

    fneuronio(ENTRADAS, PESOS, limiar, SIZE, &x);

    if (x)
        printf("Neurônio ativado!\n");

    else
        printf("Neurônio inibido!\n");

    return 0;
}

void print(double *v, int size)
{

    int i;
    for (i = 0; i < size; i++)
    {
        printf("%.3lf\n", *(v + i));
    }
}

int *fneuronio(double *ENTRADAS, double *PESOS, double limiar, int size, int *x)
{

    int i;
    double SOMAP = 0.0;
    for (i = 0; i < size; i++)
    {
        SOMAP += ENTRADAS[i] * PESOS[i];
    }

    printf("SOMAP = %.3lf\n", SOMAP);

    if (SOMAP > limiar)
    {
        *x = 1;
    }
    else
    {
        *x = 0;
    }

    return x;
}
