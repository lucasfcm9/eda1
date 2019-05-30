#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ch char
int main()
{
    ch a[10001];
    ch b[10001];

    int sum_a = 0, sum_b = 0;
    bool check;
    scanf("%s %s", a, b);

    int i;
    int size = strlen(a) > strlen(b) ? strlen(b) : strlen(a);

    for (i = 0; i < size ; i++)
    {
        if(a[i] != b[i])
        {
            if(a[i] < b[i]) {
                check = false;
                break;
            }
            else
            {
                check = true;
                break;
            }
        }
    }

    if (check)
        printf("1\n");
    else
        printf("-1\n");

    return 0;
}