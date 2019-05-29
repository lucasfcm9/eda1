#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ascending(void const *a, void const *b)
{
    return *(int *)a - *(int *)b;
}

int descending(void const *a, void const *b)
{
    return *(int*)b - *(int *)a;
}

int main()
{
    unsigned long N;
    scanf("%lu", &N);

    int v[100001];
    unsigned long i, j = 0, k = 0;
    int par[100001];
    int impar[100001];
    for(i = 0; i < N; i++)
    {
        scanf("%d", &v[i]);

        if(!(v[i] & 1))
        {
            par[j++] = v[i];
        }
        else
            impar[k++] = v[i];
    }

    qsort(par, j, sizeof(int), ascending);
    qsort(impar, k, sizeof(int), descending);

    for(i = 0; i < j; i++)
        printf("%d\n", par[i]);
    for(i = 0; i < k; i++)
        printf("%d\n", impar[i]);

    return 0;
}
