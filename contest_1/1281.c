#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
int ascending(void const *a, void const *b)
{
    return *(int*)a + *(int*)b;
}
*/

typedef struct _Frutas
{
    char nome[101];
    float preco;
} Frutas;

int main()
{
    Frutas Frutas[550];
    int N;
    int qtd;
    char nome[101];
    scanf("%d", &N);

    int i;
    float soma = 0.0f;
    while(N--)
    {
        int p;
        scanf("%d", &p);
        for(i = 0; i < p; i++)
        {
            scanf("%s%*c%f", Frutas[i].nome, &Frutas[i].preco);
        }
        int k;
        scanf("%d", &k);
        for(i = 0; i < k; i++)
        {
            scanf("%s%*c%d", nome, &qtd);
            int h;
            for(h = 0; h < p; h++)
            {
                if(!strcmp(Frutas[h].nome, nome))
                {
                    soma += qtd*Frutas[h].preco;
                }
            }
        }
        printf("R$ %.2f\n", soma);
        soma = 0.0f;
    }
    return 0;
}
