#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string.h>

typedef struct SCHEDULE
{
    char name[101];
    char phone[101];
    char adress[101];
    unsigned long int cep;
    char date_of_birth[101];

    struct SCHEDULE *next, *prev;

} Agenda;

Agenda *head = NULL;
Agenda *tail;

Agenda *CreateSchedule()
{
    return NULL;
}

// Agenda *CreateContact()
// {
//     Agenda *new_contact; //Criando um novo contato pra Agenda;
//     new_contact = (Agenda *)malloc(sizeof(Agenda)); //Alocando memória para criar um contato;
//
//     if(new_contact == NULL)
//         printf("Erro de alocação\n\n");
//
//     printf("Informe o nome completo:\n");
//     scanf("%[^\n]", new_contact->name);
//     getchar();
//
//     printf("Informe seu número de telefone, nesse estilo, (XXXX-XXXX):\n");
//     scanf("%[^\n]", new_contact->phone);
//     getchar();
//
//     printf("Informe seu endereço:\n");
//     scanf("%[^\n]", new_contact->adress);
//     getchar();
//
//     unsigned long int aux = 0;
//     printf("Informa seu CEP:\n");
//     scanf("%lu", &aux);
//     new_contact->cep = (unsigned long int) aux;
//     getchar();
//
//     printf("Informe sua data de nascimento, nesse estilo, (XX/XX/XX):\n");
//     scanf("%s", new_contact->date_of_birth);
//
//
//     printf("%s\n", new_contact->name);
//     printf("%s\n", new_contact->phone);
//     printf("%s\n", new_contact->adress);
//     printf("%lu\n", new_contact->cep);
//     printf("%s\n", new_contact->date_of_birth);
//
//     return new_contact;
// }

void InsertContactInArchive()
{
    Agenda *new_contact;
    new_contact = (Agenda *)malloc(sizeof(Agenda));

    // FILE *fp;
    // fp = fopen("Contacts.txt", "a");

    getchar();
    printf("Insira seu nome:\n");
    scanf("%[^\n]", new_contact->name);
    getchar();

    printf("Insira seu número de telefone nesse formato, por favor -> XXXX-XXXX:\n");
    scanf("%[^\n]", new_contact->phone);
    getchar();

    printf("Insira seu endereço:\n");
    scanf("%[^\n]", new_contact->adress);
    getchar();

    unsigned long int aux = 0;
    printf("Insira seu CEP:\n");
    scanf("%lu", &aux);
    new_contact->cep = (unsigned long int) aux;
    getchar();

    printf("Insira sua data de nascimento nesse formato, por favor -> XX/XX/XX:\n");
    scanf("%[^\n]", new_contact->date_of_birth);
    getchar();

    new_contact->prev = NULL;
    new_contact->next = head;

    if(head != NULL)
        head->prev = new_contact;

    head = new_contact;
    free(new_contact);
}

Agenda *DeleteFirst()
{
    // FILE *fp;
    // fp = fopen("Contacts.txt", "r");

    Agenda *delete_contact = head;

    if(head->next == NULL)
    {
        tail = NULL;
    }
    else
    {
        head->next->prev = NULL;
    }

    head = head->next;

    return delete_contact;
}

void ShowContacts()
{
    Agenda *node;
    node = head;

    while(node != NULL)
    {
        printf("Name: %s\n", node->name);
        printf("Phone: %s\n", node->phone);
        printf("Adress: %s\n", node->adress);
        printf("CEP: %lu\n", node->cep);
        printf("Date of birth: %s\n", node->date_of_birth);
        printf("$\n");
        node = node->next;
    }
}

void RegisterContact()
{
    Agenda *new_contact;
    new_contact = (Agenda *)malloc(sizeof(Agenda));

    if(new_contact == NULL)
        printf("4ERROR!\n");

    printf("Insira seu nome:\n");
    scanf("%[^\n]", new_contact->name);
    getchar();

    printf("Insira seu número de telefone nesse formato, por favor -> XXXX-XXXX:\n");
    scanf("%[^\n]", new_contact->phone);
    getchar();

    printf("Insira seu endereço:\n");
    scanf("%[^\n]", new_contact->adress);
    getchar();

    unsigned long int aux = 0;
    printf("Insira seu CEP:\n");
    scanf("%lu", &aux);
    new_contact->cep = (unsigned long int) aux;
    getchar();

    printf("Insira sua data de nascimento nesse formato, por favor -> XX/XX/XX:\n");
    scanf("%[^\n]", new_contact->date_of_birth);
    getchar();

    FILE *file;
    file = fopen("Contacts.txt", "a");
    fprintf(file, "%s\n%s\n%s\n%lu\n%s\n", new_contact->name, new_contact->phone,
                                           new_contact->adress, new_contact->cep,
                                           new_contact->date_of_birth);
    fclose(file);

}

#endif
