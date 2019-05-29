#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long

typedef struct _Camisetas
{
    char cor[101];
    char tam;
    char nome[101];
} Camisetas;

int camisetaCmp(Camisetas c1, Camisetas c2)
{
    if(strcmp(c1.cor, c2.cor) > 0)
        return 1;
    else if(strcmp(c1.cor, c2.cor) < 0)
        return -1;

    if(c1.tam < c2.tam)
        return 1;
    else if(c1.tam > c2.tam)
        return -1;

    if(strcmp(c1.nome, c2.nome) > 0)
        return 1;
    else if(strcmp(c1.nome, c2.nome) < 0)
        return -1;
}

void ordena(Camisetas camiseta[], int size)
{
    int i, j;
    int aux;
    for(i = 0; i < size; i++)
    {
        for(j = i+1; j < size; j++)
        {
            if(camisetaCmp(camiseta[i], camiseta[j]) == 1)
            {
                Camisetas aux = camiseta[i];
                camiseta[i] = camiseta[j];
                camiseta[j] = aux;
            }
        }
    }
}

int main()
{   
    ll n;
    Camisetas camiseta[1001];
    scanf("%lld", &n);
    do {
        if(!n)
            break;
        else
        {
            for(int i = 0; i < n; i++)
            {
                scanf("%*c%[^\n]", camiseta[i].nome);
                scanf("%*c%s%*c%c", camiseta[i].cor, &camiseta[i].tam);

            }
            ordena(camiseta, n);
        }
        for(int i = 0; i < n; i++)
            printf("%s %c %s\n", camiseta[i].cor, camiseta[i].tam, camiseta[i].nome);
        
        scanf("%lld", &n);
        if(n != 0)
            printf("\n");
    } while(n != 0);
    return 0;
}
