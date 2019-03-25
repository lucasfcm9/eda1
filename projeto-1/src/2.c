#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void print(double *NOTAS, int size);
int *recebe_notas(double *NOTAS, int size);
int *conta_notas(int *apr, int size, int *approved, int *reproved);
int percent_aprov(int *approved, int *reproved, double *percent_approved, double *percent_reproved);

int main () {

    int i;
    double NOTAS[SIZE];
    
    printf("Digite a nota dos 10 alunos: \n");
    
    for(i = 0; i < SIZE; i++) {
        scanf("%lf", &NOTAS[i]);
    }
    
    print(NOTAS, SIZE);
    
    int *x;
    x = recebe_notas(NOTAS, SIZE);
    
    for(i = 0; i < SIZE; i++) {
        printf("Aluno %d: %d\n", i + 1, *(x + i));
    }
    
    int approved = 0, reproved = 0;
    int *c;
    c = conta_notas(x, SIZE, &approved, &reproved);
    
    printf("Quantidade de alunos aprovados: %d\n", approved);
    printf("Quantidade de alunos reprovados: %d\n", reproved);
    
    double percent_approved = 0.0, percent_reproved = 0.0;
    
    int z;
    z = percent_aprov(&approved, &reproved, &percent_approved, &percent_reproved);
    
    printf("A porcentagem de aprovados é: %.2lf%%\n", percent_approved);
    printf("A porcentagem de reprovados é: %.2lf%%\n", percent_reproved);
    
    if(z) {
        printf("Mais da metade da turma foi aprovada!\n");
    }
    else {
        printf("Menos da metade da turma foi aprovada!\n");
    }
    
    return 0;
}

void print(double *NOTAS, int size) {
    
    int i;
    for(i = 0; i < size; i++) {
        printf("Nota do aluno %d = %.3lf\n", i + 1, *(NOTAS + i));
    }
}

int *recebe_notas(double *NOTAS, int size) {
    
    int i;
    static int apr[SIZE];
    
    for(i = 0; i < size; i++) {
        if(NOTAS[i] >= 6.0)
            apr[i] = 1;
        else
            apr[i] = 0;
    }
    return apr;
}

int *conta_notas(int *apr, int size, int *approved, int *reproved) {
    
    int i;
    for(i = 0; i < size; i++) {
        if(apr[i] == 1)
            (*approved)++;
        else
            (*reproved)++;
    }
    return approved;
    return reproved;
}

int percent_aprov(int *approved, int *reproved, double *percent_approved, double *percent_reproved) {
    
    double t = *approved + *reproved;
    
    *percent_approved = (double)(*approved/t) * 100.0;
    *percent_reproved = (double)(*reproved/t) * 100.0;
    
    if(*percent_approved >= 50.0)
        return 1;
    
    return 0;
    
}
