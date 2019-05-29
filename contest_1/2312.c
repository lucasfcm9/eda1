#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long

typedef struct _PAIS
{
    char nome[101];
    int ouro, prata, bronze;
} Pais;

int medalhacmp(Pais a, Pais b)
{
    if(a.ouro > b.ouro)
        return 1;
    else if(a.ouro < b.ouro)
        return -1;
    else
    {
        if(a.prata > b.prata)
            return 1;
        else if(a.prata < b.prata)
            return -1;
        else
        {
            if(a.bronze > b.bronze)
                return 1;
            else if(a.bronze < b.bronze)
                return -1;
            else
            {
                if(strcmp(a.nome, b.nome) < 0)
                    return 1;
                else if(strcmp(a.nome, b.nome) > 0)
                    return -1;
            }
        }
    }
    return 0;
}

void ordena(Pais pais[], int size)
{
    int i, j;
    Pais aux;

    for(i = 0; i < size; i++)
    {
        for(j = i+1; j < size; j++)
        {
            if(medalhacmp(pais[i], pais[j]) == -1)
            {
                aux = pais[i];
                pais[i] = pais[j];
                pais[j] = aux;
            }
        }
    }
    return;
}

int main()
{
    ll N;
    scanf("%lld", &N);

    ll i, j;
    Pais pais[1001];
    for(i = 0; i < N; i++)
    {
        scanf("%s%*c%d%d%d", pais[i].nome, &pais[i].ouro, &pais[i].prata, &pais[i].bronze);
    }

    ordena(pais, N);

    for(i = 0; i < N; i++)
    {
        printf("%s %d %d %d\n", pais[i].nome, pais[i].ouro, pais[i].prata, pais[i].bronze);
    }
    return 0;
}
