#include <stdio.h>
#include <stdlib.h>

int somaDig(int num)
{
    if (num == 0)
        return 0;
    else
        return (num % 10) + somaDig(num / 10);
}

int main()
{
    int n;
    scanf("%d", &n);

    printf("%d\n", somaDig(n));
    return 0;
}