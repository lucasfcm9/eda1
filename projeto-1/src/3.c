#include <stdio.h>
#include <math.h>

void hanoi(int number_of_disks, char origin, char destination, char aux)
{

    if (number_of_disks == 1)
    {
        printf("Mover disco da torre A para torre C\n");
        return;
    }

    hanoi(number_of_disks - 1, origin, aux, destination);
    printf("Mover disco %d da torre %c para a torre %c\n", number_of_disks, origin, destination);

    hanoi(number_of_disks - 1, aux, destination, origin);
}

int main()
{
    int number_of_disks;
    printf("Digite a quantidade de discos: ");
    scanf("%d", &number_of_disks);

    hanoi(number_of_disks, 'A', 'C', 'B');
    printf("Quantidade de movimentos: %.0f\n", pow(2, number_of_disks) - 1);

    return 0;
}