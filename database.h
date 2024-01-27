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
//  
//  DATE:        October 17, 2023
//
//  FILE:        database.h
//
//  DESCRIPTION:
//   This is header file database.h. This file contains certain
//   function declarations for use in other files
//
****************************************************************/

#include "record.h"

int addRecord (struct record **, int, char [], char []);
void printAllRecords (struct record *);
int findRecord (struct record *, int);
int deleteRecord (struct record **, int);
int writefile(struct record*, char []);
int readfile(struct record **, char[]);
void cleanup(struct record **);
void getaddressfromfile(char [], int, FILE*);
