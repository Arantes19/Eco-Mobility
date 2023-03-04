#include <stdio.h>
#define TAM 100

typedef struct vehicle
{
    int code;
    char type[TAM];
    int batery;
    float price;
    struct vehicle* nextv; 
}Vehicle;

typedef struct client
{
    int NIF;
    float balane;
    char Cname[TAM];
    char address[TAM];
    struct client* nextc;
}Client;

typedef struct manager
{
    int Mcode;
    char Mname;
    struct manager* nextm;
}Manager;