//**********Ivan Alvarez Fernandez**********
//**********ivan.alvarez.fernandez**********
//************Marcos Gomez Tejon************
//*****************m.tejon******************
//*************Rita Pardo Lopez*************
//****************rita.pardo****************

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>
#include "lista.h"

#define MAXDATA 4096 //Maximo de elementos de la lista
#define MAX 1024 //Maximo de chars de un string
#define MAXTROZOS 100 //Maximo de palabras que forman un comando de la shell

//Cabeceras de funciones del programa principal y de la P0
void printPrompt();
void readIn(char *cadena, char *trozos[], char *comando);
int trocearCadena(char *cadena, char *trozos[]);
void processIn(char *trozos[], char *comando, tList *L, int *a);
void comAutores(char *trozos[], char *comando);
void comEnd(char *trozos[], char *comando, tList *L, int *a);
void comHist(char *trozos[], tList *L, char *comando);
void comPid(char *trozos[], char *comando);
void comCarpeta(char *trozos[], char *comando);
void comFecha(char *trozos[], char *comando);
void comInfosis(char *trozos[], char *comando);
void comAyuda(char *trozos[], char *comando);
void comComandoN(char *trozos[], char *comando, tList *L, int *a);

int main(){
    char cadena[MAX];
    char *trozos[MAXTROZOS];
    char comando[MAX];
    tList L;
    createEmptyList(&L);
    int a=1; //Variable de salida del bucle de la shell (1=bucle, 0=salida)

    do{
        printPrompt();
        readIn(cadena, trozos, comando);
        processIn(trozos, comando,&L, &a);
    } while(a==1);
}

int trocearCadena(char *cadena,char *trozos[]){ //FUNCIÓN DE CLASE (guarda en trozos[i] cada palabraᵢ del comando)
    int i=1;
    if((trozos[0]=strtok(cadena," \n\t"))==NULL){
        return 0;
    } 
    while((trozos[i]=strtok(NULL, " \n\t"))!=NULL){
        i++;
    }
    return i;  
}

void printPrompt(){
    printf("-> ");
    //Printea la forma del prompt de la shell
}

void readIn(char *cadena, char *trozos[], char *comando){
    fgets(cadena, MAXDATA, stdin);
    strcpy(comando, cadena);
    strtok(comando, "\n"); //Esta línea y la variable comando simplemente evitan
    //imprimir un salto de linea en el mensaje de error, ya que fgets guarda un salto de línea en la cadena que recoge
    trocearCadena(cadena,trozos);
    //Lee el comando de la shell y separa las palabras que forman el comando en "trozos"
}


void processIn(char *trozos[], char *comando, tList *L, int *a){ //CORRECTO, SE PUEDE CAMBIAR POR TABLA
    if(trozos[0]!=NULL){
        insertItem(comando,L);
        if(strcmp(trozos[0],"autores")==0){
            comAutores(trozos, comando);
        } else if(((strcmp(trozos[0],"bye")==0)||(strcmp(trozos[0],"salir")==0)||(strcmp(trozos[0],"fin")==0))&&(trozos[1]==NULL)){
            comEnd(trozos, comando, L, a);
        } else if(strcmp(trozos[0],"hist")==0){
            comHist(trozos, L, comando);
        } else if(strcmp(trozos[0],"pid")==0){
            comPid(trozos, comando);
        } else if(strcmp(trozos[0],"carpeta")==0){
            comCarpeta(trozos, comando);
        } else if(strcmp(trozos[0],"fecha")==0){
            comFecha(trozos,comando);
        } else if(strcmp(trozos[0],"infosis")==0){
            comInfosis(trozos, comando);
        } else if(strcmp(trozos[0],"ayuda")==0){
            comAyuda(trozos,comando);
        } else if(strcmp(trozos[0],"comando")==0){
            comComandoN(trozos,comando, L, a);
        } else{
            fprintf(stderr, "%s '%s' \n", strerror(3), comando);
        }
    }
    //Encadenamiento de if-else que llaman a la respectiva función del comando solicitado
}

void comAutores(char *trozos[], char *comando){
    if(trozos[1]==NULL){
        printf("Iván Álvarez Fernández : ivan.alvarez.fernandez\n");
        printf("Marcos Gómez Tejón : m.tejon\n");
        printf("Rita Pardo López : rita.pardo\n");
        //Imprime los nombres y los users de los miembros de la práctica
    } else if(strcmp(trozos[1],"-l")==0 && trozos[2]==NULL){ 
            printf("ivan.alvarez.fernandez\n");
            printf("m.tejon\n");
            printf("rita.pardo\n");
            //Imprime los users de los miembros de la práctica
            } else if(strcmp(trozos[1],"-n")==0 && trozos[2]==NULL){
                printf("Iván Álvarez Fernández\n");
                printf("Marcos Gómez Tejón\n");
                printf("Rita Pardo López\n");
                //Imprime los nombres de los miembros de la práctica
            }else{
                fprintf(stderr, "%s '%s'\n", strerror(3), comando);
            }
}


void comEnd(char *trozos[], char *comando, tList *L, int *a){
    if(trozos[1]==NULL){
        delete(L);
        *a=0;
    } else{
        fprintf(stderr, "%s '%s'\n", strerror(3), comando);
    }
    //Limpia la lista y cierra el bucle (a vale 0), dando por acabada la ejecución de la shell
}

void comHist(char *trozos[], tList *L, char *comando){
        if(trozos[1]==NULL){
            for(int i=0;i<=last(*L);i++){
                printf("%d->%s\n",i, getItem(i, *L));
            }
            //Recorre la lista de inicio a fin, imprimiendo los comandos en orden, junto a su respectiva posición en el historial
        } else if(trozos[2]==NULL){
            if (strcmp(trozos[1],"-c")==0 && trozos[2]==NULL){
                delete(L);
                //Limpia el historial, vaciando la lista en la que se guardan los comandos
        } else {
            const char *a=strtok(trozos[1],"-");
            long int x=strtol(a, NULL,10);
            if(x<=(last(*L))){
                for(int i=0;i<x && i<=last(*L);i++){
                    printf("%d->%s\n",i, getItem(i, *L));
                }
                //Imprime el historial de forma similar a hist, pero solo hasta la posición pedida por el usuario 
            } else{
                printf("Error: there are not %li elements on the list\n", x);
                //Pero si el usuario pide un valor mayor al de elementos de la lista, salta un error
            }
        }
    } else{
        fprintf(stderr, "%s '%s'\n", strerror(3), comando);
    }
    //En el historial aparecerán tanto el comando 'comando N' como la llamada al comando de la posición N cuando este sea ejecutado.
}

void comPid(char *trozos[],char *comando){ 
    if(trozos[1]==NULL){
        printf("Pid de shell: %d\n", getpid());
        //Imprime el pide del shell que devuelve la función getpid();
    } else if(strcmp(trozos[1],"-p")==0 && trozos[2]==NULL){
        printf("Pid del padre del shell: %d\n", getppid());
        ////Imprime el pide del proceso padre de la shell que devuelve la función getppid();
    } else {
        fprintf(stderr, "%s '%s'\n", strerror(3), comando);
    }
}

void comCarpeta(char *trozos[], char *comando){
    char dir[MAX];
    if(trozos[1]==NULL){
        if(getcwd(dir, MAX)==NULL){
           perror("getcwd");
        }  
        else{
           printf("El directorio actual es: %s\n", dir);
        }  //Imprime el directorio actual que devuelve la función getcwd();
    } else if(trozos[2]==NULL){
        strcpy(dir,trozos[1]);
        if(chdir(dir)==-1){
            fprintf(stderr,"%s \n", strerror(1)); 
            //Si no se pude cambiar de directorio, ya sea por que no existe o no se tienen permisos,
            //muestra un error
        } else{
            chdir(dir);
            //Si se puede, se cambia el directorio al solicitado con la funcion chdir();
        } 
    } else{
            fprintf(stderr, "%s '%s'\n", strerror(3), comando);
    }
}

void comFecha(char *trozos[], char *comando){
    time_t *now;
    struct tm *bdTime;
    now=malloc(sizeof(time_t));
    time(now);
    bdTime=localtime(now);
    //Se obtiene la representación del tiempo en distintas medidas en forma de un registro bdTime
    if(trozos[1]==NULL){
        printf("%d:%d:%d\n",bdTime->tm_hour,bdTime->tm_min,bdTime->tm_sec);
        printf("%d/%d/%d\n", bdTime->tm_mday, bdTime->tm_mon+1, bdTime->tm_year+1900);
        //Imprime la hora y la fecha actuales
    } else if(strcmp(trozos[1],"-d")==0 && trozos[2]==NULL){
        printf("%d/%d/%d\n", bdTime->tm_mday, bdTime->tm_mon+1, bdTime->tm_year+1900);
        //Imprime la fecha actual
    } else if(strcmp(trozos[1],"-h")==0 && trozos[2]==NULL){
        printf("%d:%d:%d\n",bdTime->tm_hour,bdTime->tm_min,bdTime->tm_sec);
        //Imprime la hora actual
    } else{
        fprintf(stderr, "%s '%s'\n", strerror(3), comando);
    }
}

void comInfosis(char *trozos[],char *comando){
    if(trozos[1]==NULL){
        struct utsname info;
        uname(&info);
        printf("%s (%s) %s-%s %s\n",info.nodename,info.machine,info.sysname,info.release,info.version);
        //Se obtiene la información del sistema operativo que está ejecutando la shell en forma de un registro ustname. La función
        //imprime la información de la máquina, sistema operativo, versión, etc.
    } else {
        fprintf(stderr, "%s '%s'\n", strerror(3), comando);
    }
}


void comAyuda(char *trozos[], char *comando){
    //Muestra una breve descripción de lo que hace cada comando de la shell
    if(trozos[1]==NULL){
        printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:\nfin salir bye fecha pid autores hist comando carpeta infosis ayuda\n");
    } else if(strcmp(trozos[1],"fin")==0 || strcmp(trozos[1],"salir")==0 || strcmp(trozos[1],"bye")==0){
        printf("%s\tTermina la ejecucion del shell\n",trozos[1]);
    } else if(strcmp(trozos[1],"fecha")==0){
        printf("fecha [-d|.h\tMuestra la fecha y o la hora actual\n");
    } else if(strcmp(trozos[1],"pid")==0){
        printf("pid [-p]\tMuestra el pid del shell o de su proceso padre\n");
    } else if(strcmp(trozos[1],"autores")==0){
        printf("autores [-n|-l]\tMuestra los nombres y logins de los autores\n");
    } else if(strcmp(trozos[1],"hist")==0){
        printf("hist [-c|-N]\tMuestra el historico de comandos, con -c lo borra\n");
    } else if(strcmp(trozos[1],"comando")==0){
        printf("comando [-N]\tRepite el comando N (del historico)\n");
    } else if(strcmp(trozos[1],"carpeta")==0){
        printf("carpeta [dir]\tCambia (o muestra) el directorio actual del shell\n");
    } else if(strcmp(trozos[1],"infosis")==0){
        printf("infosis\tMuestra informacion de la maquina donde corre el shell\n");
    } else if(strcmp(trozos[1],"ayuda")==0){
        printf("ayuda [cmd]\tMuestra ayuda sobre los comandos\n");
    } else{
        fprintf(stderr, "%s '%s'\n", strerror(3), comando);
    }
}

void comComandoN(char *trozos[], char *comando, tList *L, int *a){ 
    if(trozos[1]==NULL){
        for(int i=0;i<=last(*L);i++){
                printf("%d->%s\n",i, getItem(i,*L));
        }
        //Hace lo mismo que el comando hist
    } else{
            char str[MAX];
            long int x=strtol(trozos[1], NULL,10);
            if(x>=0 && x<last(*L)){
                strcpy(str, getItem(x,*L));
                char instruccion[MAX];
                strcpy(instruccion, str);
                trocearCadena(str,trozos);
                if(strcmp(trozos[0], "comando")!=0){
                    printf("Executing command %li: %s\n", x, getItem(x,*L));
                    processIn(trozos,instruccion, L, a);
                    //Se transforma a entero el valor que se le pasa como argumento a comando, obtiene el comando de la lista
                    //que se guarda en esa posición y ejecuta su correspondiente procedimiento
                } else{
                    printf("Error: you are calling the commando 'comando' recursively or your 'comando [int value]' is not a integer\n");
                    
                }
            } else{
                printf("Error: there are not %li elements on the list\n", x);
            }
        } 
        //En caso de que comando llame a otro comando, para evitar segmentation faults y bucles infinitos de llamadas de comando a comando a comando...
        //hemos decidido prohibilro. Ocurre otro error cuando se pide un comando [valor no numerico] y el primer comando del historial es comando.
        //En caso de que el primer comando de la shell no fuera comando, 'comando [valor no numerico]' ejecutaría el comando 0 del historial. Esto ocurre por
        //el funcionamiento de strtol, que devuelve 0 en caso de que no se le haya pasado algun número en la cadena.
}

