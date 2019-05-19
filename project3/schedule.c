#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"

int main()
{
    Agenda *new_contact;
    new_contact = CreateSchedule();
    RegisterContact();
    return 0;
}
