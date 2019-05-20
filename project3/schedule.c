#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"

int main()
{
    Agenda *new_contact;
    new_contact = CreateSchedule();

    int option;
    while(option != 4)
    {
        printf("CADASTRO DE USUÁRIO EM UMA AGENDA\n\n");
        printf("1 - Inserir contato no ínicio da lista\n");
        printf("2 - Remover contato\n");
        printf("3 - Listar todos os contatos");
        printf("Digite uma opção:\n\n");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                InsertContactInArchive();
                break;
            case 2:
                new_contact = DeleteFirst();
                break;
            case 3:
                ShowContacts();
                break;
            case 4:
                exit(-1);
        }
    }
    return 0;
}
