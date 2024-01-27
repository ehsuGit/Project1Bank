/*****************************************************************
//
//  NAME:        Emily Hsu
//
//  HOMEWORK:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 17, 2023
//
//  FILE:        user_interface.c
//
//  DESCRIPTION:
//   This is file user_interface.c. The part of the banking sysytem
//   that directly interacts with the user. Now fully implemented 
//   and works in tandem with database.c. Allows for adding, deleting
//   printing, finding banking records
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include "database.h"

int debugMode = 0;

void getaddress(char[], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   Serves as majority of the code for the UI and 
//                 gets user input for use in accessing and 
//                 modifying the database 
//                 
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : Success
//
****************************************************************/

int main(int argc, char* argv[])
{
    struct record * start = NULL;
    struct record ** pstart = &start;
    int select = -1;
    int quit = 0;
    int i;
    char filename[] = "savedrecords.txt";

    if (argc > 2)
    {
        debugMode = 0;
        quit = 1;
        printf("No such file or directory\n");
    }

    if (argc == 2)
    {
        int length = strlen(argv[1]);
        if (length == 5)
        {
            if (strcmp(argv[1], "debug") == 0)
            {
                debugMode = 1;
                printf("DEBUG MODE ON\n");
            }
            else
            {
                debugMode = 0;
                quit = 1;
                printf("No such file or directory\n");
            }
        }   
        else
        {
            debugMode = 0;
            i = 10;
            quit = 1;
            printf("No such file or directory\n");
        }
    }

    if(quit == 0)
    {
        printf("Welcome to Banking XX, where we take care of all your banker needs :)\n");
    }
    
    readfile(pstart, filename); 
    while(quit == 0)
    {
        char menu[20];
        char trash[80];
        select = -1;

        printf("\nPlease type what you would like to do today from the options below.\n");
        printf("\tadd: add a new banking record into the database.\n");
        printf("\tprintall: print all existing records in the database.\n");
        printf("\tfind: find specific banking record(s).\n");
        printf("\tdelete: delete specified banking record(s).\n");
        printf("\tquit: Quit this program.\n");

        if(scanf("%s", menu) == 1)
        {
            char add[] = "add";
            char del[] = "delete";
            char fnd[] = "find";
            char prnt[] = "printall";
            char qit[] = "quit";
          
            int len = strlen(menu);
            if (len < 8)
            {
                if (menu[0] == 'a')
                {
                    for (i = 0; i <= len-1; i++)
                    {
                        if (menu[i] == add[i])
                        {
                            select = 0;
                        }
                        else
                        {
                            select = -1;
                            i = 10;
                        }
                    }
                }
                else if (menu[0] == 'p')
                {
                    for (i = 0; i <= len-1; i++)
                    {
                        if (menu[i] == prnt[i])
                        {
                            select = 1;
                        }
                        else
                        {
                            select = -1;
                            i = 10;
                        }
                    }
                }
                if (menu[0] == 'f')
                {
                    for (i = 0; i <= len-1; i++)
                    {
                        if (menu[i] == fnd[i])
                        {
                            select = 2;
                        }
                        else
                        {
                            select = -1;
                            i = 10;
                        }
                    }
                }
                if (menu[0] == 'd')
                {
                    for (i = 0; i <= len-1; i++)
                    {
                        if (menu[i] == del[i])
                        {
                            select = 3;
                        }
                        else
                        {
                            select = -1;
                            i = 10;
                        }
                    }
                }
                if (menu[0] == 'q')
                {
                    for (i = 0; i <= len-1; i++)
                    {
                        if (menu[i] == qit[i])
                        {
                            quit = 1;
                            select = 4;
                        }
                        else
                        {
                            quit = 0;
                            select = -1;
                            i = 10;
                        }
                    }
                }
            }
            if (select == -1)
            {
                printf("\nWe're sorry, that is not a valid input. Please try again.\n");
                fgets(trash, 80, stdin); 
            }
            else
            {
                fgets(trash, 80, stdin);
                if (select == 0)
                {
                    int scanned;
                    int num;
                    char check;
                    char name[30];
                    char address[50];
                    scanned = 0;
                    
                    printf("You have selected to add new banking records.\n"); 
                    while (scanned == 0)
                    {
                        printf("\nPlease enter the account number of the record: ");
                        if (scanf("%d", &num) == 1)
                        {
                            if (num <= 0)
                            {
                                printf("You have inputted an integer less than or equal");
                                printf(" to 0. Please input a positive integer.");
                            }
                            else
                            {
                                scanned = 1;
                            }
                        }
                        else if (scanf("%c", &check) >= 1)
                        {
                            printf("You have entered characters.");
                            printf(" Please input characters only.");
                            fgets(trash, 80, stdin);
                        }
                    }
                    fgets(trash, 80, stdin);
                    scanned = 0;
                    while (scanned == 0)
                    {
                        printf("Please enter the name(s) connected to the banking account: ");
                        fgets(name, 80, stdin);
                        scanned = 1;
                    }
                    getaddress(address, 50);
                    if(addRecord(pstart, num, name, address) == -1)
                    {
                        printf("\nThe record could not be added.\n");
                    }
                }
                else if (select == 1)
                {
                    printf("You have selected to print all existing banking records.\n");
                    printAllRecords(start);
                    printf("\n");
                }
                else if (select == 2)
                {
                    int scanned;
                    int num;
                    char check;
                    scanned = 0;

                    printf("You have selected to find specific banking record(s).\n");
                    while (scanned == 0) 
                    {
                        printf("\nPlease enter the account number of the record: ");
                        if (scanf("%d", &num) == 1)
                        {
                            if (num <= 0)
                            {
                                printf("You have inputted an integer less than or equal");
                                printf(" to 0. Please input a positive integer.");
                            }
                            else
                            {
                                scanned = 1;
                            }
                        }
                        else if (scanf("%c", &check) >= 1)
                        {
                            printf("You have entered characters.");
                            printf(" Please input characters only.");
                            fgets(trash, 80, stdin);
                        }
                    }
                    if(findRecord(start, num) == -1)
                    {
                        printf("\nThe record could not be found.\n");
                    }
                }
                else if (select == 3)
                {
                    int scanned;
                    int num;
                    char check;
                    scanned = 0;

                    printf("You have selected to delete banking record(s).\n");
                    while (scanned == 0)
                    {
                        printf("\nPlease enter the account number of the record: ");
                        if (scanf("%d", &num) == 1)
                        {
                            if (num <= 0)
                            {
                                printf("You have inputted an integer less than or equal");
                                printf(" to 0. Please input a positive integer.");
                            }
                            else
                            {
                                scanned = 1;
                            }
                        }
                        else if (scanf("%c", &check) >= 1)
                        {
                            printf("You have entered characters.");
                            printf(" Please input characters only.");
                            fgets(trash, 80, stdin);
                        }
                    }
                    if(deleteRecord(pstart, num) == -1)
                    {
                        printf("\nThe record could not be deleted.\n");
                    }
                }
            }
        }
    }
    if (select == 4)
    {
        writefile(start, filename);
        printf("Thank you for choosing Banking XX! We hope you choose our services again.\n");
        cleanup(pstart); 
    }
    return 0;
}

/*****************************************************************
//
//  Function name: getaddress
//
//
//  DESCRIPTION:   Obtains banking address as inputted by the user.
//
//  Parameters:    addy (char[]): the character array that the 
//                                address will be read into
//                 end  (int)   : the max size of the addy array
//
****************************************************************/

void getaddress(char addy[], int end)
{
    int done = 0;
    char temp;
    char trash[500];
    int i;
    int len;

    i = 0;
    len = strlen(addy);
    while(i < len)
    {
        addy[i] = '\0';
        i++;
    }
    printf("Please enter the address connected to the banking account.");
    printf(" Once you are done, please enter a tilde '~': ");
    while (done == 0)
    {
        for (i = 0; i < end; i++)
        {
            temp = fgetc(stdin);
            if (temp == '~')
            {
                done = 1;
                i = 1000;
                fgets(trash, 500, stdin);
            }
            else
            {
                addy[i] = temp;
            }
        }
    }
}

