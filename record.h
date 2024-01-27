/*****************************************************************
//
//  NAME:        Emily Hsu
//
//  HOMEWORK:    3b
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        September 20, 2023
//
//  FILE:        record.h
//
//  DESCRIPTION:
//  This is the header file record.h. This file contains the 
//  struct record.
//
****************************************************************/

struct record
{
    int accountno;
    char name[30];
    char address[50];
    struct record* next;
};
