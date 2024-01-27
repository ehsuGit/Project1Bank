/*****************************************************************
//
//  NAME:        Emily Hsu
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        October 17, 2023
//
//  FILE:        database.c
//
//  DESCRIPTION:
//   This is file database.c. This file defines the function
//   declarations in database.h. Serves as the contact point between
//   UI and the database. Now completely implemented, along with
//   debug statements.
//
****************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "database.h"

extern int debugMode;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Allows the user to add a new banking record into
//                 the database
//
//  Parameters:    startpoint (struct record **) : address of the 
//                            pointer that points to where the first 
//                            banking record is held.
//                 acc (int) : The account number as specified by
//                             the user
//                 name (char[]) : Name connected to the account as 
//                                 specified by the user
//                 addy (char[]) : Address connected to the account 
//                                 as specified by the user 
//
//  Return Values: 0: The record was added successfully
//                -1: adding failed
****************************************************************/

int addRecord (struct record ** startpoint, int acc, char name[], char addy[])
{
    int success;
    struct record * start;
    struct record * temp;
    struct record * before;
    struct record * read;
    int count;
    int i;

    success = 1; 
    count = 0;
    start = *startpoint; 
    read = *startpoint;     
    
    if (debugMode == 1)
    {
        printf("\n***********************************\n");
        printf("DEBUG:\n");
        printf("Function addRecord\n");
        printf("\nstruct record **:\n");
        printf("AccountNum (acc): %d\n", acc);
        printf("Name (name): %s", name);
        printf("Address (addy): \n%s\n", addy);
        printf("***********************************\n");
    }

    if (start == NULL)
    {
        temp = (struct record *)malloc(sizeof(struct record));
        temp->accountno = acc;
        strcpy(temp->name, name);
        strcpy(temp->address, addy);
        temp->next = NULL;
        *startpoint = temp;
        success = 0;
    }

    while( read != NULL && success == 1 )
    {
        if( acc < read->accountno )
        {
            count++;
        }
        else if ( acc == read->accountno )
        {
            success = -1;
        }
        read = read->next;
    }

    if(success == 1)
    {
        if(acc > start->accountno)
        {
            temp = (struct record *)malloc(sizeof(struct record));
            temp->accountno = acc;
            strcpy(temp->name, name);
            strcpy(temp->address, addy);
            temp->next = start;
            *startpoint = temp;
            success = 0;
        }
        else if(acc < start->accountno)
        {
            i = 0;
            before = *startpoint;
            while (i < count - 1)
            {
                before = before->next;
                i++;
            }
            if( before->next == NULL )
            {
                temp = (struct record*)malloc(sizeof(struct record));
                temp->accountno = acc;
                strcpy(temp->name, name);
                strcpy(temp->address, addy);
                before->next = temp;
                temp->next = NULL;
                success = 0;
            }
            else if( before->next != NULL )
            {
                temp = (struct record*)malloc(sizeof(struct record));
                temp->accountno = acc;
                strcpy(temp->name, name);
                strcpy(temp->address, addy);
                temp->next = before->next;
                before->next = temp;
                success = 0;
            }
        }          
    }
    if( success == 1 )
    {
        success = -1;
    }
    return success;
}

/*****************************************************************
//
//  Function name: printAllRecord
//
//  DESCRIPTION:   Prints all existing banking records
//
//  Parameters:    start (struct record *) : Address of the beginning
//                                           of the banking records
//
****************************************************************/

void printAllRecords (struct record * start)
{

    if (debugMode == 1)
    {
        printf("\n***********************************\n");
        printf("DEBUG:\n");
        printf("Function printAllRecords\n");      
        printf("\tstruct record *:\n");
        printf("***********************************\n");
    }

    if( start == NULL )
    {
        printf("There are no records to print!\n");
    }
    else
    {
        struct record * read;
       
        read = start;
        while ( read != NULL )
        {
            printf("\nAccount no.: %d\n", read->accountno);
            printf("Name: %s", read->name);
            printf("Address: %s\n", read->address);
            read = read->next;
        }
    }
}

/*****************************************************************
//
//  Function name: findRecord
//
//
//  DESCRIPTION:   Finds banking record(s) with the use of the 
//                 account number
//                 
//  Parameters:    start (struct record *) : Address of the beginning
//                                           of the banking records
//                 acc (int) : Account number of the banking
//                             record to find
//  
//  Return Values: 0 : Succeeded in finding the record
//                -1 : Record was not found
//
****************************************************************/

int findRecord (struct record * start, int acc)
{
    int success;
    struct record * find;

    if (debugMode == 1)
    {
        printf("\n***********************************\n");
        printf("DEBUG:\n");
        printf("Function findRecord\n");
        printf("\tstruct record *:\n");
        printf("\tAccountNum (acc): %d\n", acc);
        printf("***********************************\n");
    }
    
    success = 1;  
    find = start;

    while ( find != NULL && success == 1 )
    {
        if(find->accountno == acc)
        {
            printf("Account no.: %d\n", find->accountno);
            printf("Name.: %s\n", find->name);
            printf("Address: %s\n", find->address);
            success = 0;
        }
        find = find->next; 
    }
    if(success == 1)
    {
        success = -1;
    }       
    return success;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//
//  DESCRIPTION:   Deletes banking records as specified by the 
//                 user using the account number
//                 
//  Parameters:    startpoint (struct record **) : address of the 
//                            pointer that points to where the 
//                            banking records are held.
//                 acc (int) : The account number as specified by
//                             the user
//
//  Return Values: 0 : Succeeded in deleting the records
//                -1 : Failed in deleting the records
//                 
****************************************************************/

int deleteRecord (struct record ** startpoint, int acc)
{
    int success;
    struct record * temp;
    struct record * before;
    struct record * after;
    struct record * read;
    struct record * start;
    int count;
    int i;

    if (debugMode == 1)
    {
        printf("\n***********************************\n");
        printf("DEBUG:\n");
        printf("Function deleteRecord\n");
        printf("\tstruct record **:\n");
        printf("\tAccountNum (acc): %d\n", acc);
        printf("***********************************\n");
    }

    count = 0;
    success = 1;
    start = *startpoint;  
    read = *startpoint;

    if (start == NULL)
    {
        success = -1;
    }
    else if( start != NULL )
    {
        if( start->accountno == acc )
        {
            if( start->next == NULL )
            {
                free(start);
                *startpoint = NULL;
                success = 0;
            }
            else if ( start->next != NULL )
            {
                temp = start->next;
                free(start);
                *startpoint = temp;
                success = 0;    
            }  
        }
        else if (acc > start->accountno)
        {
            success = -1;
        }
    }

    while( read != NULL && success == 1 )
    {
        if( acc < read->accountno )
        {
            count++;
        }
        else if ( acc == read->accountno )
        {
            success = 2;
        }
        read = read->next;
    }
    
    if( success == 2 )
    {
        i = 0;
        before = start;
        while(i < count - 1 )
        {
            before = before->next;
            i++;
        }
        temp = before->next;
        after = temp->next;
        free(temp);
        before->next = after;
    }
    else if (read == NULL && success == 1)
    {
        success = -1;
    }

    if(success == 1)
    {
        success = -1;
    }
    return success;
}

/*****************************************************************
//
//  Function name: writefile
//
//
//  DESCRIPTION:   This function writes to a file any current 
//                 records that have been added 
//                 
//                 
//  Parameters:    start (struct record *) : address of the 
//                            pointer that points to where the 
//                            banking records are held.
//                 records (char[]) : The account number as
//                                    specified by the user
//
//  Return Values: 0 : Succeeded in writing the records
//                -1 : Failed in writing the records
//                 
****************************************************************/

int writefile (struct record * start, char records[])
{
    FILE * outfile;
    int success;

    outfile = fopen(records, "w");

    if (debugMode == 1)
    {
        printf("\n***********************************\n");
        printf("DEBUG:\n");
        printf("Function writefile\n");
        printf("\tstruct record *:\n");
        printf("\nFile to write to: (char[]): %s\n", records);
        printf("***********************************\n");
    }

    if (outfile == NULL)
    {
        success = -1;
    } 

    if( start == NULL )
    {
        success = 0;
    }
    else
    {
        struct record * read;
       
        read = start;
        while ( read != NULL )
        {
            fprintf(outfile, "%d\n", read->accountno);
            fprintf(outfile, "%s", read->name);
            fprintf(outfile, "%s", read->address);
            fprintf(outfile, "~");
            read = read->next;
        }       
        success = 0;
        fclose(outfile);
    }
    return success;
}

/*****************************************************************
//
//  Function name: readfile
//
//
//  DESCRIPTION:   Reads all records from a file into the current 
//                 session. Allows "saving" by loading in records
//                 from previous sessions to use.
//                 
//  Parameters:    startpoint (struct record **) : address of the 
//                            pointer that points to where the 
//                            banking records are held.
//                 records (char[]): The account number as 
//                                   specified by the user
//
//  Return Values: 0 : Succeeded in reading in the records
//                -1 : Failed in reading the records
//                 
****************************************************************/

int readfile (struct record ** startpoint, char records[])
{
    FILE * infile;
    int success;
    int acc;
    char name[500];
    char addy[800];

    infile = fopen(records, "r");

    if (debugMode == 1)
    {
        printf("\n***********************************\n");
        printf("DEBUG:\n");
        printf("Function readfile\n");
        printf("\tstruct record **:\n");
        printf("\tFile to read from (char []): %s\n", records);
        printf("***********************************\n");
    }

    if(infile == NULL)
    {
        success = -1;
    }
    else if (infile != NULL)
    {
        while(fscanf(infile, "%d\n", &acc) != EOF)
        {
            fgets(name, 500, infile);
     
            getaddressfromfile(addy, 50, infile);
            addRecord(startpoint, acc, name, addy);
        }
        fclose(infile);
    }
    return success;
}

/*****************************************************************
//
//  Function name: cleanup
//
//
//  DESCRIPTION:   Releases all allocated spaces in the current 
//                 session. To be called at the end of the program.
//                 
//  Parameters:    startpoint (struct record **) : address of the 
//                            pointer that points to where the 
//                            banking records are held.
//
****************************************************************/

void cleanup (struct record ** startpoint)
{
    struct record * before;
    struct record * after;

    after = *startpoint;
    if (debugMode == 1)
    {
        printf("\n***********************************\n");
        printf("DEBUG:\n");
        printf("Function cleanup\n");
        printf("\tstruct record **:\n");
        if(after == NULL)
        {
            printf("Nothing to clean!\n");
        }
        printf("***********************************\n");
    }
    while(after != NULL)
    {
        before = after;
        after = after->next;
        free(before);
    }
}

/*****************************************************************
//
//  Function name: cleanup
//
//
//  DESCRIPTION:   Helper funtion for readfile, gets the address 
//                 from a file 
//                 
//  Parameters:    addy (char []) : address of the 
//                            pointer that points to where the 
//                            banking records are held.
//                 end (int): how large addy is
//                 filename (FILE*): the file that readfile is
//                                   reading from 
****************************************************************/

void getaddressfromfile (char addy[], int end, FILE* filename)
{
    int done = 0;
    char temp;
    int i;
   
    if (debugMode == 1)
    {
        printf("***********************************\n");
        printf("DEBUG:\n");
        printf("Function getaddressfromfile\n");
        printf("\tstruct record **:\n");
        printf("***********************************\n");
    }

    i = 0;
    while(i < 800)
    {
        addy[i] = '\0';
        i++;
    }

    while (done == 0)
    {
        for (i = 0; i < end; i++)
        {
            temp = fgetc(filename);
            if (temp == '~')
            {
                done = 1;
                i = 1000;
            }
            else
            {
                addy[i] = temp;
            }
        }
    }
}

