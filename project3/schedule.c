#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "schedule.h"

int main()
{
    Agenda *new_contact;

    int option;
    do {
        printf("1 - Inserir contato no ínicio da Agenda\n");
        printf("2 - Inserir contato no final da Agenda\n");
        printf("3 - Mostrar todos os contatos da Agenda\n");
        printf("Digite sua opção: ");
        scanf("%d%*c", &option);

        switch(option) {
            case 1:
                insertContactAtHead();
                break;
            case 2:
                insertContactAtTail();
                break;
            case 3:
                ShowContacts();
            default:
                printf("Digite uma opção válida\n");
        }
    } while(option);

    return 0;
}
