#ifndef SCHEDULE_H
#define SCHEDULE_H

typedef struct SCHEDULE
{
    char name[101];
    char phone[101];
    char adress[101];
    unsigned int cep;
    char date_of_birth[101];

    struct SCHEDULE *next, *prev;

} DataType;

DataType *createContact()
{
    DataType *contact;
    contact = (DataType *)malloc(sizeof(DataType));

    if(contact == NULL)
    {
        printf("\nCannot create a new contact\n");
        return NULL;
    }
    else
    {
        contact->next = NULL;
        contact->prev = NULL;
    }
    return contact;
}

DataType *newContact()
{
    DataType *contact;
    contact = (DataType *)malloc(sizeof(DataType));

    if(contact == NULL)
    {
        printf("\nCannot allocate memory\n");
    }

    printf("Enter your name: ");
    scanf("%[^\n]%*c", contact->name);

    bool check_phone = false;

    //XXXXX[-]XXXX
    do
    {
        printf("Enter your phone number -> [XXXXX-XXXX]: ");
        scanf("%[^\n]%*c", contact->phone);

        if(contact->phone[5] != '-')
        {
            printf("Error, type again\n");
            check_phone = true;
        }
        else{
            check_phone = false;
        }
    } while(check_phone);

    printf("Enter your adress: ");
    scanf("%[^\n]%*c", contact->adress);

    unsigned int tmp;

    printf("Enter your CEP: ");
    scanf("%u%*c", &tmp);
    contact->cep = (unsigned int) tmp;

    bool check_date = false;

    do
    {
        printf("Enter your date of birth -> [XX/XX/XXXX]: ");
        scanf("%[^\n]%*c", contact->date_of_birth);
        // 26[/]11[/]1996
        if(contact->date_of_birth[2] != '/' || contact->date_of_birth[5] != '/')
        {
            printf("Error, type again\n");
            check_date = true;
        }
        else
        {
            check_date = false;
        }
    } while(check_date);


    return contact;
}



#endif
