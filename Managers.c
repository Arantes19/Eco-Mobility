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
            fprintf(fp, "%d;%s;%d;%s\n", aux->gCode, aux->password, aux->contact, aux->username);
            aux = aux->nextm;
        }
        fclose(fp);
        return 1;
    }
    else 
    {
        printf("Falha na abertura do ficheiro");
        return(0);
    }
}

void listManagers(Manager* begin)
{while (begin != NULL) 
 {printf("%d -> %s -> %d -> %s\n", begin->gCode, begin->password, begin->contact, begin->username);
  begin = begin->nextm;
 }
}

Manager* readManagers()
{
    FILE* fp;
    int gcod, cont;
    char mname[50], pass[50];

    Manager* aux = NULL;
    fp = fopen("managers.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%[^;];%d;%[^\n]\n", &gcod, pass, &cont, mname);
        aux = insertManager(aux, gcod, pass, cont, mname);
        }
        fclose(fp);
    }
    return(aux);
}

Manager* insertManager(Manager* begin, int gcod, char pass[], int cont, char mname[])
{
    if (!existManager(begin, gcod))
    {
        Manager* newManager = malloc(sizeof(struct manager));
        if (newManager != NULL)
        {
            newManager->gCode = gcod;
            strcpy(newManager->password, pass);
            newManager->contact = cont;
            strcpy(newManager->username, mname);
            newManager->nextm = begin;
            begin = newManager;
            return (newManager);
        }
        else return(begin);
    }
}

int existManager(Manager* begin, int gcod)
{
    while (begin != NULL)
    {
        if (begin->gCode == gcod) return(1);
        {
            begin = begin->nextm;
        }
        return(0);
    }    
}

Manager* removeManager(Manager* begin, int gcod)
{
    Manager *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->gCode == gcod)
    {
        aux = actual->nextm;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->gCode!=gcod))
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