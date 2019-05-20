#ifndef SCHEDULE_H
#define SCHEDULE_H

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
Agenda *tail = NULL;
Agenda *current = NULL;

bool isEmpty()
{
    return head == NULL;
}

int length() //Função que verifica o tamanho da lista duplamente encadeada;
{
    int size = 0;
    Agenda *current;

    for(current = head; current != NULL; current = current->next)
    {
        size++;
    }
    return size;
}

// Agenda *createContact()
// {
//     Agenda *new_contact;
//     new_contact = (Agenda *)malloc(sizeof(Agenda));
//
//     int length = 0;
//
//     if(new_contact == NULL)
//     {
//         printf("Cannot allocate memory\n");
//     }
//
//     printf("Informe seu nome: ");
//     scanf("%[^\n]", new_contact->name);
//     getchar();
//
//     printf("Informe seu número de telefone: ");
//     scanf("%[^\n]", new_contact->phone);
//     getchar();
//
//     printf("Informe seu endereço: ");
//     scanf("%[^\n]", new_contact->adress);
//     getchar();
//
//     unsigned long int aux = 0;
//     printf("Informe seu CEP: ");
//     scanf("%lu", &aux);
//     new_contact->cep = (unsigned long int) aux;
//     getchar();
//
//     printf("Informe sua data de nascimento: ");
//     scanf("%[^\n]", new_contact->date_of_birth);
//
//     // strcpy(new_contact->name, name);
//     // strcpy(new_contact->phone, phone);
//     // strcpy(new_contact->adress, adress);
//     // new_contact->cep = cep;
//     // strcpy(new_contact->date_of_birth, date_of_birth);
//
//     printf("Nome: %s\n", new_contact->name);
//     printf("Phone: %s\n", new_contact->phone);
//     printf("Endereço: %s\n", new_contact->adress);
//     printf("CEP: %lu\n", new_contact->cep);
//     printf("Data de nascimento: %s\n", new_contact->date_of_birth);
//
//     return new_contact;
// }


void insertContactAtHead()
{
    Agenda *new_contact;
    new_contact = (Agenda *)malloc(sizeof(Agenda));

    isEmpty() ? (tail = new_contact) : (head->prev = new_contact);

    printf("Insira seu nome: ");
    scanf("%[^\n]", new_contact->name);
    getchar();

    printf("Insira seu número de telefone: ");
    scanf("%[^\n]", new_contact->phone);
    getchar();

    printf("Insira seu endereço: ");
    scanf("%[^\n]", new_contact->adress);
    getchar();

    unsigned long int aux = 0;
    printf("Insira seu CEP: ");
    scanf("%lu", &aux);
    new_contact->cep = (unsigned long int) aux;
    getchar();

    printf("Insira sua data de nascimento: ");
    scanf("%[^\n]%*c", new_contact->date_of_birth);

    new_contact->next = head;
    head = new_contact;
}

void insertContactAtTail()
{
    Agenda *new_contact;
    new_contact = (Agenda *)malloc(sizeof(Agenda));

    if(isEmpty())
        tail = new_contact;
    else
    {
        tail->next = new_contact;
        new_contact->prev = tail;
    }

    printf("Insira seu nome: ");
    scanf("%[^\n]", new_contact->name);
    getchar();

    printf("Insira seu número de telefone: ");
    scanf("%[^\n]", new_contact->phone);
    getchar();

    printf("Insira seu endereço: ");
    scanf("%[^\n]", new_contact->adress);
    getchar();

    unsigned long int aux = 0;
    printf("Insira seu CEP: ");
    scanf("%lu", &aux);
    new_contact->cep = (unsigned long int) aux;
    getchar();

    printf("Insira sua data de nascimento: ");
    scanf("%[^\n]%*c", new_contact->date_of_birth);

    tail = new_contact;
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

#endif
