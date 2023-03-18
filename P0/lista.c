//**********Ivan Alvarez Fernandez**********
//**********ivan.alvarez.fernandez**********
//************Marcos Gomez Tejon************
//*****************m.tejon******************
//*************Rita Pardo Lopez*************
//****************rita.pardo****************
#include "lista.h"

void createEmptyList(tList *L){
    L->lastPos=-1; 
    //Inicializa la lista con la posición a -1 para que al añadir un elemento pase a estar en la 0.
}

bool isEmptyList(tList L){
    return L.lastPos==-1; 
    //Devuelve true si no se ha añadido ningún elemento a la lista.
}

int next(int pos, tList L){
    if(pos>=0 && pos<L.lastPos){
        pos++;
        return pos;
    } else {
        return -1; 
    }
    //La posición que se le pasa debe estar en la lista. En caso de
    //que no esté o sea justo la última, devuelve -1.
}

int prev(int pos, tList L){
    if(pos>0 && pos<=L.lastPos){
        pos--;
        return pos;
    } else {
        return -1; 
    }
    //La posición que se le pasa debe estar en la lista. En caso de
    //que no esté o sea justo la primera, devuelve -1.
}

int first(tList L){
    return 0;
    //Devuleve la primera posición, que es la 0.
}

int last(tList L){
    return L.lastPos;
    //Devuelve el valor actual de la posición final.
}

bool insertItem(char str[], tList *L){
    if(L->lastPos < MAXDATA){
        L->lastPos++;
        char *s=malloc(sizeof(char[MAXDATA]));
        L->str[L->lastPos]=s;
        strcpy(L->str[L->lastPos],str);
        return true;
    } else {
        return false;
    }
    //Si todavía quedan huecos en la lista, reserva memoria para un string
    //y copia el string que se le pasa en la lista, incrementando a su vez
    //la última posición en 1 y devuleve true. En caso de que esté la lista 
    //llena, devuelve false.
}

char* getItem(int pos, tList L){
    if(pos <MAXDATA && pos >= 0){
    return L.str[pos];
    } else{
        return NULL;
    }
    //Devuelve la cadena de la posición solicitada. Si la posición no
    //pertenece a la lista, devuelve NULL.
}

void delete(tList *L){
    for(int i=last(*L);i>=0;i--){
        L->str[i]=NULL;
        free(L->str[i]);
        L->lastPos--;
    }
    //Recorre la lista de fin a principio, dejando la posición en 0
    //y liberando la memoria que ocupaban los elementos de esta.
}
