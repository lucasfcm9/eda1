#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct SCHEDULE
{
    char name[101];
    char phone[101];
    char adress[101];
    unsigned int cep;
    char date_of_birth[101];

    struct SCHEDULE *next, *prev;

} DataType;

DataType *newContact(char *, char *, char *, unsigned int, char *, DataType*);
DataType *create();
void imprime(DataType *);
void free_list(DataType *);
DataType *newRegister(DataType*);
DataType *deleteContact(DataType*);

int main()
{

    DataType *list;
    list = create();

    char name[101];
    char phone[101];
    char adress[101];
    unsigned int cep;
    char date_of_birth[101];

    FILE *fp = fopen("Contacts.txt", "r");
    char value[101];
    char ch;

    int count = 0;

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
            list = newContact(name, phone, adress, cep, date_of_birth, list);
            count = 0;
        }
    }
    fclose(fp);
  //  list = newRegister(list);
    imprime(list);
    list  = deleteContact(list);
    imprime(list);
    free_list(list);
    return 0;
}

DataType *create()
{
    return NULL;
}

DataType *newContact(char *name, char *phone, char *adress, unsigned int cep, char *date_of_birth, DataType *list)
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
    for(current = list; current != NULL; current = current->next){
      if(current->next == NULL){
        current->next = contact;
        contact->next = NULL;
        contact->prev = current;
      }
    }
    return list;
}

void imprime(DataType *list){
  DataType *elem;
  for(elem = list; elem != NULL; elem = elem->next){
     printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
     printf("%s\n%s\n%s\n%u\n%s\n", elem->name, elem->phone, elem->adress, elem->cep, elem->date_of_birth);
     printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
  }
}

DataType *newRegister(DataType *list){
  char name[101];
  char phone[101];
  char adress[101];
  unsigned int cep;
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

  unsigned int tmp;

  printf("Enter your CEP: ");
  scanf("%u%*c", &tmp);
  cep = (unsigned int) tmp;

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

void free_list(DataType *list){
  DataType *elem;
  for(elem = list; elem != NULL; list = elem){
    elem = elem->next;
    free(list);
  }
}

DataType *deleteContact(DataType* list){
  char subStrig[100];
  printf(" Type in the name of the substring: \n");
  scanf("%[^\n]%*c", subStrig);

  DataType *elem;
  DataType *aux;
  for(elem = list; elem != NULL; elem = elem->next){
    if(strstr(elem->name, subStrig)){
      aux = elem;
      printf("%s\n",elem->name);
      elem = elem->prev;
      elem->next = aux->next;
      free(aux);
    }
  }
  return list;
}
