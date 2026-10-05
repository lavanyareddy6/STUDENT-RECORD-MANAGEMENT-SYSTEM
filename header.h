#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct student 
{
    int rollno;
    char name[50];
    float percentage;
    struct student *next;
} student;

void addRecord(student **);
void deleteRecord(student **);
void showRecords(student *);
void modifyRecord(student **);
void saveRecords(student *);
void loadRecords(student **);
void sortRecords(student **);
void deleteAll(student **);
void reverseList(student **);
