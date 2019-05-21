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

DataType *newContact(char *, char *, char *, unsigned int, char *);
DataType *create();

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
                cep = (unsigned int)value;
                break;
            case 4:
                strcpy(date_of_birth, value);
                break;
        }
        count++;
        if(value[0] == '$')
        {
            list = newContact(name, phone, adress, cep, date_of_birth);
            count = 0;
        }
    }
    fclose(fp);
    return 0;
}

DataType *create()
{
    return NULL;
}

DataType *newContact(char *name, char *phone, char *adress, unsigned int cep, char *date_of_birth, DataType *list)
{
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    printf("%s\n%s\n%s\n%u\n%s\n", name, phone, adress, cep, date_of_birth);
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");
    DataType *contact;
    contact = (DataType *)malloc(sizeof(DataType));

    if(list == NULL)
    {
        printf("\nCannot allocate memory\n");
    }

    if(contact == NULL)
    {
        printf("\nCannot allocate memory\n");
    }



    // printf("Enter your name: ");
    // scanf("%[^\n]%*c", contact->name);
    //
    // bool check_phone = false;
    //
    // //XXXXX[-]XXXX
    // do
    // {
    //     printf("Enter your phone number -> [XXXXX-XXXX]: ");
    //     scanf("%[^\n]%*c", contact->phone);
    //
    //     if(contact->phone[5] != '-')
    //     {
    //         printf("Error, type again\n");
    //         check_phone = true;
    //     }
    //     else{
    //         check_phone = false;
    //     }
    // } while(check_phone);
    //
    // printf("Enter your adress: ");
    // scanf("%[^\n]%*c", contact->adress);
    //
    // unsigned int tmp;
    //
    // printf("Enter your CEP: ");
    // scanf("%u%*c", &tmp);
    // contact->cep = (unsigned int) tmp;
    //
    // bool check_date = false;
    //
    // do
    // {
    //     printf("Enter your date of birth -> [XX/XX/XXXX]: ");
    //     scanf("%[^\n]%*c", contact->date_of_birth);
    //     // 26[/]11[/]1996
    //     if(contact->date_of_birth[2] != '/' || contact->date_of_birth[5] != '/')
    //     {
    //         printf("Error, type again\n");
    //         check_date = true;
    //     }
    //     else
    //     {
    //         check_date = false;
    //     }
    // } while(check_date);


    return contact;
}
