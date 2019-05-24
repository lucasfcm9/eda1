#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>


typedef struct SCHEDULE
{
    char name[101];
    char phone[101];
    char adress[101];
    unsigned long int cep;
    char date_of_birth[101];

    struct SCHEDULE *next, *prev;

} DataType;

DataType *newContact(char *, char *, char *, unsigned long int, char *, DataType*);
DataType *create();
void print(DataType *);
void printInverse(DataType *);
void freeList(DataType *);
DataType *newRegister(DataType *);
DataType *deleteContact(DataType *, DataType*);
DataType *searchString(DataType *);


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
    char value[101];

    int count = 0;
    int dollar = 0;

    while((fscanf(fp, "%[^\n]%*c", value)) != EOF)
    {
        // printf("%s\n%d\n", value, count);

        switch(count)
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
        if(value[0] == '$')
        {
            if(dollar == 0){
                head = newContact(name, phone, adress, cep, date_of_birth,head);
            }else{
                tail = newContact(name, phone, adress, cep, date_of_birth,head);
            }
            count = 0;
            dollar++;
            printf("%d\n", dollar);
        }
    }
    fclose(fp);
    //head = newRegister(head);
    print(head);
    head = searchString(head);
    //print(head);
    printInverse(tail);
    freeList(head);
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


    if(contact == NULL)
    {
        printf("\nCannot allocate memory\n");
    }

    strcpy(contact->name, name);
    strcpy(contact->phone, phone);
    strcpy(contact->adress, adress);
    strcpy(contact->date_of_birth, date_of_birth);
    contact->cep = cep;

    if(list == NULL)
    {
        contact->next = NULL;
        contact->prev = NULL;
        return contact;
    }

    DataType *current;
    for(current = list; current != NULL; current = current->next)
    {
        if(current->next == NULL)
        {
            current->next = contact;
            contact->next = NULL;
            contact->prev = current;
            return contact;
        }

    }
}

void print(DataType *list)
{
    DataType *contact;
    for(contact = list; contact != NULL; contact = contact->next)
    {
        printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
        printf("%s\n%s\n%s\n%lu\n%s\n", contact->name, contact->phone, contact->adress, contact->cep, contact->date_of_birth);
        printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    }
}
void printInverse(DataType *list)
{
    DataType *contact;
    for(contact = list; contact != NULL; contact = contact->prev)
    {
        printf("#################################################################\n");
        printf("%s\n%s\n%s\n%lu\n%s\n", contact->name, contact->phone, contact->adress, contact->cep, contact->date_of_birth);
        printf("##################################################################\n");
    }
}

DataType *newRegister(DataType *list)
{
    char name[101];
    char phone[101];
    char adress[101];
    unsigned long int cep;
    char date_of_birth[101];

    printf("Enter your name: ");
    scanf("%[^\n]%*c", name);

    bool check_phone = false;

    //XXXXX[-]XXXX
    do
    {
        printf("Enter your phone number -> [XXXXX-XXXX]: ");
        scanf("%[^\n]%*c", phone);

        if(phone[5] != '-')
        {
            printf("Error, type again\n");
            check_phone = true;
        }
        else{
            check_phone = false;
        }
    } while(check_phone);

    printf("Enter your adress: ");
    scanf("%[^\n]%*c", adress);

    unsigned long int tmp;

    printf("Enter your CEP: ");
    scanf("%lu%*c", &tmp);
    cep = (unsigned long int) tmp;

    bool check_date = false;

    do
    {
        printf("Enter your date of birth -> [XX/XX/XXXX]: ");
        scanf("%[^\n]%*c", date_of_birth);
        // 26[/]11[/]1996
        if(date_of_birth[2] != '/' || date_of_birth[5] != '/')
        {
            printf("Error, type again\n");
            check_date = true;
        }
        else
        {
            check_date = false;
        }
    } while(check_date);
    return newContact(name, phone, adress, cep, date_of_birth, list);
}

void freeList(DataType *list)
{
    DataType *contact;
    for(contact = list; contact != NULL; list = contact)
    {
        contact = contact->next;
        free(list);
    }
}

DataType *searchString(DataType* list)
{
    char *subStr;
    subStr = (char *)malloc(1001 * sizeof(char));

    printf("Enter the name:\n");
    scanf("%[^\n]%*c", subStr);

    DataType *contact;

    for(contact = list; contact != NULL; contact = contact->next)
    {
        if(strstr(contact->name, subStr))
          list = deleteContact(contact, list);
    }
    return list;
}
DataType *deleteContact(DataType* contact,DataType* list){
  DataType *temp;
  if(contact->prev == NULL){
    temp = contact;
    contact = contact->next;
    contact->prev = NULL;
    free(temp);
    return contact;
  }else{
    temp = contact;
    contact = contact->prev;
    contact->next = temp->next;
    free(temp);
    return list;
  }
}
