#include <stdio.h>
#include <stdlib.h>

typedef struct _LISTA
{
    int valor;
    struct _LISTA *next;
} Lista;

Lista *head = NULL;

Lista *cria()
{
    return NULL;
}

Lista *insere(Lista *l, int valor)
{
    Lista *n;
    n = (Lista *)malloc(sizeof(Lista));

    if (n == NULL)
        exit(-1);

    n->valor = valor;

    if (l == NULL)
    {
        n->next = NULL;
        return n;
    }
    else
    {
        n->next = l;
        return n;
    }
    return n;
}

void print(Lista *l, int n)
{
    Lista *c;
    for (c = l; c != NULL; c = c->next)
    {
        if (n == 0)
            printf("%d\n", c->valor);
        n--;
    }
}

void libera(Lista *l)
{
    Lista *a;
    for (a = l; a != NULL; l = a)
    {
        a = a->next;
        free(l);
    }
}

int main()
{
    int i = 0;
    int n = 1;
    Lista *l;
    l = NULL;
    do
    {
        scanf("%d", &n);
        l = insere(l, n);
        i++;

    } while (n != -1);
    scanf("%d", &i);

    print(l, i);
    libera(l);

    return 0;
}