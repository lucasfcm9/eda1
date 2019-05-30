#include <stdio.h>
#include <stdlib.h>

int *alocaVetor(int qtd)
{
    int *vetor;
    if (qtd < 1)
        return NULL;

    vetor = (int *)calloc(qtd, sizeof(int));
    if (vetor == NULL)
        return NULL;

    return vetor;
}

void libera_matriz(int **matriz, int linhas)
{
    int i;
    for (i = 0; i < linhas; i++)
    {
        free(matriz[i]);
    }

    free(matriz);
}

int **alocaMatriz(int linhas, int colunas)
{
    int **matrix;
    int i, j;

    if (linhas < 1 || colunas < 1)
    {
        printf("Error!\n");
        return NULL;
    }

    matrix = (int **)calloc(linhas, sizeof(int *));
    if (matrix == NULL)
        return NULL;

    for (i = 0; i < linhas; i++)
    {
        matrix[i] = (int *)calloc(colunas, sizeof(int));
        for (j = 0; j < colunas; j++)
            scanf("%d", &matrix[i][j]);
    }

    return matrix;
}

int main()
{
    int linhas, colunas;
    scanf("%d %d", &linhas, &colunas);
    int i, j;
    int **matriz;
    int *somas_linhas = alocaVetor(linhas);
    int *somas_colunas = alocaVetor(colunas);
    matriz = alocaMatriz(linhas, colunas);

    printf("Matriz:\n");
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            if (j == 0)
                printf("%d", matriz[i][j]);
            else
                printf(" %d", matriz[i][j]);
        }
        printf("\n");
    }
    printf("Somas Linhas:\n");
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            somas_linhas[i] += matriz[i][j];
        }
        if (i == 0)
            printf("%d", somas_linhas[i]);
        else
            printf(" %d", somas_linhas[i]);
    }
    printf("\n");

    printf("Somas Colunas:\n");
    for (i = 0; i < colunas; i++)
    {
        for (j = 0; j < linhas; j++)
        {
            somas_colunas[i] += matriz[j][i];
        }
        if (i == 0)
            printf("%d", somas_colunas[i]);
        else
            printf(" %d", somas_colunas[i]);
    }
    printf("\n");

    libera_matriz(matriz, linhas);
    free(somas_linhas);
    free(somas_colunas);
    return 0;
}
