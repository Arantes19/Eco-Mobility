#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "op.h"

int saveVehicle(Vehicle* begin)
{
    FILE* fp;
    fp = fopen("vechicles.txt", "w");
    if (fp!=NULL)
    {
        Vehicle* aux = begin;
        while (aux !=NULL)
        {
            fprintf(fp, "%d;%f;%s;%s\n", aux->code, aux->type, aux->batery, aux->price);
            aux = aux->nextv;
        }
        fclose((fp));
        return(1);
    }
    else return(0);
}

Vehicle* readVehicle()
{
    FILE* fp;
    int cod, bat;
    float prc;
    char tp[50];

    Vehicle* aux = NULL;
    fp = fopen("vehicles.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%[^\n];%d;%f\n", &cod, &tp, &bat, &prc);
        aux = insertVehicle(aux, cod, tp, bat, prc);
        }
        fclose(fp);
    }
    return(aux);
}

Vehicle* insertVehicle(Vehicle* begin, int cod, char tp[], int bat, float prc)
{
    if (!existVehicle(begin, cod))
    {
        Vehicle* new = malloc(sizeof(struct vehicle));
        if (new != NULL)
        {
            new->code = cod;
            strcpy(new->type, tp);
            new->batery = bat;
            new->price = prc;
            return (new);
        }
        else return(begin);
    }
}

int existVehicle(Vehicle* begin, int cod)
{
    while (begin != NULL)
    {
        if (begin->code == cod) return(1);
        {
            begin = begin->nextv;
        }
        return(0);
    }
}

/*void listVehicle(Vehicle* begin)
{
    while (begin != NULL)
    {
        printf("%d %s %d %f\n", begin->code, begin->type, begin->batery, begin->price);
        begin = begin->nextv;
    }
}*/

Vehicle* removeVehicle(Vehicle* begin, int cod)
{
    Vehicle *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->code == cod)
    {
        aux = actual->nextv;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->code!=cod))
        {
            previous = actual;
            actual = actual->nextv;
        }
        if (actual == NULL) return(begin);
        else
        {
            previous->nextv = actual->nextv;
            free(actual);
            return(begin);
        }
    }  
}