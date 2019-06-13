#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp = fopen("in.txt", "r");
    int n;
    int *arr;
    int count = 0;
    arr = (int *)malloc(10*sizeof(int));

    do
    {
        fscanf(fp, "%d ", &n);
        arr[count++] = n;

    } while (!feof(fp));
    for(int i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    free(arr);
    
}
