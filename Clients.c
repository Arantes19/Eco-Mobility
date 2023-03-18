#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "op.h"

int existClient(Client* begin, int ccode)
{
    while (begin != NULL)
    {
        if (begin->cCode == ccode) return(1);
        {
            begin = begin->nextc;
        }
        return(0);
    }
}

int saveClient(Client* begin)
{
    FILE* fp;
    fp = fopen("clients.txt", "a");
    if (fp!=NULL)
    {
        Client* aux = begin;
        while (aux !=NULL)
        {
            fprintf(fp, "%d;%d;%s;%f;%s\n",aux->cCode, aux->nif, aux->name, aux->balance, aux->address);
            aux = aux->nextc;
        }
        fclose((fp));
        return(1);
    }
    else return(0);
}

Client* readClients()
{
    FILE* fp;
    int nif, ccode;
    float bal;
    char name[50], addr[50];

    Client* aux = NULL;
    fp = fopen("clients.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%d;%[^;];%f;%[^\n]\n", &ccode, &nif, name, &bal, addr);
        aux = insertClient(aux, ccode, nif, name, bal, addr);
        }
        fclose(fp);
    }
    return(aux);
}

Client* insertClient(Client* begin, int ccode, int nif, char name[],  float bal, char addr[])
{
    if (!existClient(begin, ccode))
    {
        Client* newClient = malloc(sizeof(struct client));
        if (newClient != NULL)
        {
            newClient->cCode = ccode;
            newClient->nif = nif;
            strcpy(newClient->name, name);
            newClient->balance = bal;
            strcpy(newClient->address, addr);
            newClient->nextc = begin;
            begin = newClient; //!!! 
            return (newClient);
        }
    }
    return(begin);
    printf("Client already exist!");
}

Client* removeClient(Client* begin, int ccode)
{
    Client *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->cCode == ccode)
    {
        aux = actual->nextc;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->cCode != ccode))
        {
            previous = actual;
            actual = actual->nextc;
        }
        if (actual == NULL) return(begin);
        else
        {
            previous->nextc = actual->nextc;
            free(actual);
            return(begin);
        }
    }  
}
