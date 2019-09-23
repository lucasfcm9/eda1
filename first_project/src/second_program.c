/*  Aluno: Lucas Fellipe Carvalho Moreira
    Matrícula: 16/0133394
    Disciplina: Estruturas de dados 1
    Professor: Matheus Mendelson
*/

#include <stdio.h>
#include <stdlib.h>
#define print_double(array, length) \
for(int i = 0; i < length; i++) \
printf("%.3lf%s", array[i], (i+1 == length ? "\n" : " "));
#define print_integer(array, length) \
for(int i = 0; i < length; i++) \
printf("%d%s", array[i], (i+1 == length ? "\n" : " "));
#define read(array, length) \
for(int i = 0; i < length; i++) \
scanf("%lf", &array[i]);
typedef double vector;
#define FOR(x, n) \
for(int i = 0; i < n; i++)

typedef struct
{
    int approved;
    int reproved;
} Students;

int *received_notes(vector *NOTES, int n)
{
    int *APR = malloc(sizeof(int) * 10);
    FOR(0, n)
    {
        if(NOTES[i] >= 6.0)
            APR[i] = 1;
        else
            APR[i] = 0;
    }
    return APR;
}

Students count_notes(int *APR, int n)
{
    Students s;
    s.approved = 0;
    s.reproved = 0;

    FOR(0, n)
    {
        if(APR[i] == 1)
            s.approved++;
        else
            s.reproved++;
    }
    return s;
}

int percentage_approved(Students s)
{
    printf("Percentage of approved: %.3lf%%\n", ((double)(s.approved)/(10.0))*100.0);
    printf("Percentage of reproved: %.3lf%%\n", ((double)(s.reproved)/(10.0))*100.0);

    if(((double)(s.approved)/(10.0)) > 51.0)
        return 1;
    else
        return 0;
}

int main()
{
    vector *NOTES;
    Students s;
    NOTES = malloc(sizeof(double) * 10);
    printf("Input the 10 notes of your students:\n");
    read(NOTES, 10);
    print_double(NOTES, 10);

    printf("Array with 0's and 1's. 1 indicate if student was approved and 0 reproved!\n");
    print_integer(received_notes(NOTES, 10), 10);

    printf("Number of students approved and reproved!\n");
    s = count_notes(received_notes(NOTES, 10), 10);
    printf("Approved: %d\n", s.approved);
    printf("Reproved: %d\n", s.reproved);

    if(percentage_approved(s))
        printf("More than half of the class has passed!\n");
    else
        printf("Less than half of the class passed!\n");
    return 0;
}