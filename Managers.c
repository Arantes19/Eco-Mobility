#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "op.h"

int saveManager(Manager* begin)
{
    FILE* fp;
    fp = fopen("managers.txt", "w");
    if (fp!=NULL)
    {
        Manager* aux = begin;
        while (aux !=NULL)
        {
            fprintf(fp, "%d;%s\n", aux->Mcode, aux->Mname);
            aux = aux->nextm;
        }
        fclose((fp));
        return(1);
    }
    else return(0);
}

Manager* readManager()
{
    FILE* fp;
    int mcod;
    char mname[50];

    Manager* aux = NULL;
    fp = fopen("managers.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%[^\n]\n", &mcod, &mname);
        aux = insertManager(aux, mcod, mname);
        }
        fclose(fp);
    }
    return(aux);
}

Manager* insertManager(Manager* begin, int mcod, char mname[])
{
    if (!existManager(begin, mcod))
    {
        Manager* new = malloc(sizeof(struct manager));
        if (new != NULL)
        {
            new->Mcode = mcod;
            strcpy(new->Mname, mname);
            return (new);
        }
        else return(begin);
    }
}

int existManager(Manager* begin, int mcod)
{
    while (begin != NULL)
    {
        if (begin->Mcode == mcod) return(1);
        {
            begin = begin->nextm;
        }
        return(0);
    }    
}

Manager* removeManager(Manager* begin, int mcod)
{
    Manager *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->Mcode == mcod)
    {
        aux = actual->nextm;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->Mcode!=mcod))
        {
            previous = actual;
            actual = actual->nextm;
        }
        if (actual == NULL) return(begin);
        else
        {
            previous->nextm = actual->nextm;
            free(actual);
            return(begin);
        }
    }  
}