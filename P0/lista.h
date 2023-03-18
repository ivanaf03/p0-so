//**********Ivan Alvarez Fernandez**********
//**********ivan.alvarez.fernandez**********
//************Marcos Gomez Tejon************
//*****************m.tejon******************
//*************Rita Pardo Lopez*************
//****************rita.pardo****************

#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXDATA 4096
#define MAX 1024

typedef struct tLista{
    char *str[MAX];
    int lastPos; 
}tList;

void createEmptyList(tList *L);
bool isEmptyList(tList L);
int next(int lastPos, tList L);
int prev(int pos, tList L);
int first(tList L);
int last(tList L);
bool insertItem(char str[], tList *L);
char *getItem(int lastPos, tList L);
void delete(tList *L);

#endif