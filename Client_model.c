#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "op.h"

int saveClient(Client* begin)
{
    FILE* fp;
    fp = fopen("clients.txt", "w");
    if (fp!=NULL)
    {
        Client* aux = begin;
        while (aux !=NULL)
        {
            fprintf(fp, "%d;%f;%s;%s\n", aux->NIF, aux->balance, aux->Cname, aux->address);
            aux = aux->nextc;
        }
        fclose((fp));
        return(1);
    }
    else return(0);
}

Client* readClient()
{
    FILE* fp;
    int nif;
    float bal;
    char name[50], addr[50];

    Client* aux = NULL;
    fp = fopen("clients.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%f;%[^\n];%[^\n]\n", &nif, &bal, &name, &addr);
        aux = insertClient(aux, nif, bal, name, addr);
        }
        fclose(fp);
    }
    return(aux);
}

Client* insertClient(Client* begin, int nif, float bal, char name[], char addr[])
{
    if (!existClient(begin, nif))
    {
        Client* new = malloc(sizeof(struct client));
        if (new != NULL)
        {
            new->NIF = nif;
            new->balance = bal;
            strcpy(new->address, addr);
            strcpy(new->Cname, name);
            new->nextc=begin;
            return (new);
        }
        else return(begin);
    }
}

int existClient(Client* begin, int nif)
{
    while (begin != NULL)
    {
        if (begin->NIF == nif) return(1);
        {
            begin = begin->nextc;
        }
        return(0);
    }
}

Client* removeClient(Client* begin, int nif)
{
    Client *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->NIF == nif)
    {
        aux = actual->nextc;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->NIF!=nif))
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
