/* Alunos: Lucas Fellipe Carvalho Moreira && Pedro Henrique Queiroz Miranda && Gabriel Davi Silva Pereira

   Matrículas: 16/0133394 && 150144474 && 17/0010341

Disciplina: Estruturas de Dados 1

Professor: Mateus Mendelson

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>
#include <ctype.h>

typedef struct SCHEDULE
{
    char name[101];
    char phone[101];
    char adress[101];
    unsigned long int cep;
    char date_of_birth[101];

    struct SCHEDULE *next, *prev;

} DataType;

DataType *newContact(char *, char *, char *, unsigned long int, char *, DataType *);
DataType *create();
void print(DataType *);
void printInverse(DataType *);
void freeList(DataType *);
void newRegister(DataType **, DataType **);
void deleteContact(DataType *, DataType **, DataType **);
void searchString(DataType **, DataType **);
void seeRegister(DataType *); //vizualizar registros que possuem certa string no nome
void sort(DataType **);
void getOut(DataType *);

int main()
{

    DataType *head;
    DataType *tail;
    head = create();
    tail = create();

    char name[101];
    char phone[101];
    char adress[101];
    unsigned long int cep;
    char date_of_birth[101];

    FILE *fp = fopen("Contacts.txt", "r");

    if (fp == NULL)
    {
        fp = fopen("Contacts.txt", "a+");
    }
    char value[101];

    int count = 0;
    int dollar = 0;

    while ((fscanf(fp, "%[^\n]%*c", value)) != EOF)
    {

        switch (count)
        {
        case 0:
            strcpy(name, value);
            break;
        case 1:
            strcpy(phone, value);
            break;
        case 2:
            strcpy(adress, value);
            break;
        case 3:
            cep = strtoul(value, NULL, 10);
            break;
        case 4:
            strcpy(date_of_birth, value);
            break;
        }
        count++;
        if (value[0] == '$')
        {
            if (dollar == 0)
            {
                head = newContact(name, phone, adress, cep, date_of_birth, head);
            }
            else
            {
                tail = newContact(name, phone, adress, cep, date_of_birth, head);
            }
            count = 0;
            dollar++;
        }
    }

    fclose(fp);

    int option;

    do
    {
        printf("--------------------------------------------------------------------------------\n");
        printf("\t\t\t AGENDA DE CONTATOS \t\t\t\n");
        printf("\t\t\tSelecione uma das opções\t\t\t\n");
        printf("1 - Inserir novo registro\n");
        printf("2 - Remover registros que contenham certa string no nome\n");
        printf("3 - Visualizar registros que contenham certa string no nome\n");
        printf("4 - Visualizar todos os registros em ordem alfabética de acordo com o nome\n");
        printf("5 - Sair\n");
        printf("--------------------------------------------------------------------------------\n");
        printf("Digite o número de uma das opções acima, por favor\n");
        scanf("%d%*c", &option);

        switch (option)
        {
        case 1:
            newRegister(&head, &tail);
            break;
        case 2:
            searchString(&head, &tail);
            break;
        case 3:
            seeRegister(head);
            break;
        case 4:
            sort(&head);
            print(head);
            break;
        case 5:
            getOut(head);
            break;
        default:
            printf("Digite uma opção válida, por favor\n");
        }
    } while (option != 5);

    return 0;
}

DataType *create()
{
    return NULL;
}

DataType *newContact(char *name, char *phone, char *adress, unsigned long int cep, char *date_of_birth, DataType *list)
{
    DataType *contact;
    contact = (DataType *)malloc(sizeof(DataType));

    if (contact == NULL)
    {
        printf("\nCannot allocate memory\n");
    }

    strcpy(contact->name, name);
    strcpy(contact->phone, phone);
    strcpy(contact->adress, adress);
    strcpy(contact->date_of_birth, date_of_birth);
    contact->cep = cep;

    if (list == NULL)
    {

        contact->next = NULL;
        contact->prev = NULL;
        return contact;
    }

    DataType *current;
    for (current = list; current != NULL; current = current->next)
    {
        if (current->next == NULL)
        {
            current->next = contact;
            contact->next = NULL;
            contact->prev = current;
            return contact;
        }
    }

    return contact;
}

void print(DataType *list)
{

    DataType *contact;
    for (contact = list; contact != NULL; contact = contact->next)
    {
        printf("\n------------------------------------------------------------\n");
        printf("%s\n%s\n%s\n%lu\n%s\n", contact->name, contact->phone, contact->adress, contact->cep, contact->date_of_birth);
        printf("\n------------------------------------------------------------\n");
    }
}
void printInverse(DataType *list)
{
    DataType *contact;
    for (contact = list; contact != NULL; contact = contact->prev)
    {
        printf("\n------------------------------------------------------------\n");
        printf("%s\n%s\n%s\n%lu\n%s\n", contact->name, contact->phone, contact->adress, contact->cep, contact->date_of_birth);
        printf("\n------------------------------------------------------------\n");
    }
}

void newRegister(DataType **list, DataType **ptail)
{
    char name[101];
    char phone[101];
    char adress[101];
    unsigned long int cep;
    char date_of_birth[101];

    printf("Insira o nome: ");
    scanf("%[^\n]%*c", name);

    bool check_phone = false;

    //XXXXX[-]XXXX
    do
    {
        printf("Insira um número de telefone -> [XXXXX-XXXX]: ");
        scanf("%[^\n]%*c", phone);

        if (phone[5] != '-' || strlen(phone) > 10)
        {
            printf("Erro, Digite Novamente\n");
            check_phone = true;
        }
        else
        {
            check_phone = false;
        }
    } while (check_phone);

    printf("Insira o endereço: ");
    scanf("%[^\n]%*c", adress);

    unsigned long int tmp;

    printf("Insira o CEP: ");
    scanf("%lu%*c", &tmp);
    cep = (unsigned long int)tmp;

    bool check_date = false;

    do
    {
        printf("Insira a Data de Nascimento (Neste formato) -> [XX/XX/XXXX]: ");
        scanf("%[^\n]%*c", date_of_birth);
        // 26[/]11[/]1996
        if (date_of_birth[2] != '/' || date_of_birth[5] != '/' || strlen(date_of_birth) > 10)
        {
            printf("Erro, tente novamente\n");
            check_date = true;
        }
        else
        {
            check_date = false;
        }
    } while (check_date);

    printf("\n---------------------------------\n\n");
    printf("Contato cadastrado com sucesso!\n\n");
    printf("---------------------------------\n\n");

    if (*(list) == NULL)
    {
        *(list) = newContact(name, phone, adress, cep, date_of_birth, *(list));
    }
    else
    {
        *(ptail) = newContact(name, phone, adress, cep, date_of_birth, *(list));
    }
}

void freeList(DataType *list)
{
    DataType *contact;
    for (contact = list; contact != NULL; list = contact)
    {
        contact = contact->next;
        free(list);
    }
}

void searchString(DataType **head, DataType **tail)
{
    char subStr[101];

    printf("Insira um Caracter ou uma String:\n");
    scanf("%[^\n]%*c", subStr);

    //PASSANDO A SUBSTRING PARA MINUSCULO
    for (int i = 0; subStr[i]; i++)
    {
        subStr[i] = tolower(subStr[i]);
    }
    DataType *contact;

    if (*(head) == NULL)
    {
        printf("\n---------------------------\n\n");
        printf("Nenhum Contato existente.\nNada Excluído\n\n");
        printf("---------------------------\n\n");
        return;
    }

    for (contact = *(head); contact != NULL; contact = contact->next)
    {
        //PASSANDO TODAS AS LETRAS DO NOME DA AGENDA PARA MINUSCULO
        for (int i = 0; contact->name[i]; i++)
        {
            contact->name[i] = tolower(contact->name[i]);
        }

        if (strstr(contact->name, subStr))
            deleteContact(contact, head, tail);
    }
}
void deleteContact(DataType *contact, DataType **head, DataType **tail)
{

    DataType *temp;
    if (contact->prev == NULL && contact->next == NULL)
    {

        *head = NULL;
        printf("\n---------------------------------\n\n");
        printf("Contato EXCLUÍDO com sucesso!\n\n");
        printf("---------------------------------\n\n");
    }
    else if (contact->prev == NULL)
    {
        temp = contact;
        contact = contact->next;
        contact->prev = NULL;
        free(temp);
        *(head) = contact;
        printf("\n---------------------------------\n\n");
        printf("Contato EXCLUÍDO com sucesso!\n\n");
        printf("---------------------------------\n\n");
    }
    else if (contact->next == NULL)
    {
        temp = contact;
        contact = contact->prev;
        contact->next = NULL;
        free(temp);
        *(tail) = contact;
        printf("\n---------------------------------\n\n");
        printf("Contato EXCLUÍDO com sucesso!\n\n");
        printf("---------------------------------\n\n");
    }
    else
    {
        temp = contact;
        contact = contact->prev;
        contact->next = temp->next;
        contact = temp->next;
        contact->prev = temp->prev;
        free(temp);
        printf("\n---------------------------------\n\n");
        printf("Contato EXCLUÍDO com sucesso!\n\n");
        printf("---------------------------------\n\n");
    }
}

void seeRegister(DataType *head)
{
    char subStr[101];

    printf("Insira um Caracter ou uma String:\n");
    scanf("%[^\n]%*c", subStr);

    //PASSANDO A SUBSTRING PARA MINUSCULO
    for (int i = 0; subStr[i]; i++)
    {
        subStr[i] = tolower(subStr[i]);
    }

    if (head == NULL)
    {
        printf("\n---------------------------\n\n");
        printf("Nenhum Contato existente.\n\n");
        printf("---------------------------\n\n");
        return;
    }

    DataType *contact;
    int countContacts = 0;
    for (contact = head; contact != NULL; contact = contact->next)
    {
        //PASSANDO TODAS AS LETRAS DO NOME DA AGENDA PARA MINUSCULO
        for (int i = 0; contact->name[i]; i++)
        {
            contact->name[i] = tolower(contact->name[i]);
        }

        if (strstr(contact->name, subStr))
        {
            printf("------------------------------------------------------------------------------------------\n");
            printf("%s\n%s\n%s\n%lu\n%s\n", contact->name, contact->phone, contact->adress, contact->cep, contact->date_of_birth);
            printf("-------------------------------------------------------------------------------------------\n");
            countContacts++;
        }
    }

    if (countContacts == 0)
    {
        printf("\n---------------------------\n\n");
        printf("Nenhum Contato existente.\n\n");
        printf("---------------------------\n\n");
    }
}

void sort(DataType **phead)
{

    if (*(phead) == NULL)
    {
        printf("\n---------------------------\n\n");
        printf("Nenhum Contato existente.\n\n");
        printf("---------------------------\n\n");
        return;
    }

    int n;
    DataType *current;

    for (current = *phead; current != NULL; current = current->next)
    {
        for (int i = 0; current->name[i]; i++)
        {
            current->name[i] = tolower(current->name[i]);
        }
    }

    current = *phead;

    if (current->next == NULL)
    {
        return;
    }

    DataType *aux, *temp;
    current = current->next;

    while (current != NULL)
    {
        n = 0;
        aux = current;
        temp = current->prev;
        current = current->next;

        while (temp != NULL && strcmp(temp->name, aux->name) > 0)
        {
            n++;
            temp = temp->prev;
        }
        if (n)
        {
            aux->prev->next = aux->next;

            if (aux->next != NULL)
            {
                aux->next->prev = aux->prev;
            }
            if (temp == NULL)
            {
                temp = *(phead);
                aux->prev = NULL;
                aux->next = temp;
                aux->next->prev = aux;
                *(phead) = aux;
            }
            else
            {
                temp = temp->next;
                temp->prev->next = aux;
                aux->prev = temp->prev;
                temp->prev = aux;
                aux->next = temp;
            }
        }
    }
}

void getOut(DataType *head)
{
    FILE *fp = fopen("Contacts.txt", "w+");
    DataType *elem;
    for (elem = head; elem != NULL; elem = elem->next)
    {
        fprintf(fp, "%s\n%s\n%s\n%lu\n%s\n$\n", elem->name, elem->phone, elem->adress, elem->cep, elem->date_of_birth);
    }
    fclose(fp);
    freeList(head);
}
