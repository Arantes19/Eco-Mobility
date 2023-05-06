/**
 * @file Vehicles.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Header_Files/vehicles.h"

/**
 * @brief Done
 * 
 * @param begin 
 * @return int 
 */
int saveVehicle(Vehicle* begin)
{
    FILE* fp;
    fp = fopen("Text_Files/vehicles.txt", "w");
    if (fp != NULL)
    {
        Vehicle* aux = begin;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%s;%f;%f;%f;%s;%d\n", aux->vCode, aux->type, aux->batery, aux->autonomy, aux->price, aux->geocode, aux->state, aux->space);
            aux = aux->nextv;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}
 
/**
  * @brief Done
  * 
  * @return Vehicle* 
  */
Vehicle* readVehicles()
{
    FILE* fp;
    int cod, stat, space;
    float prc, bat, aut;
    char tp[50], geo[50];
    Vehicle* aux = NULL;

    fp = fopen("Text_Files/vehicles.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%[^;\n];%f;%f;%f;%[^;\n];%d;%d\n", &cod, tp, &bat, &aut, &prc, geo, &stat, &space);
        aux = insertVehicle(aux, cod, tp, bat, aut, prc, geo, stat, space);
        }
        fclose(fp);
    }
    return(aux);
}

/**
 * @brief Done
 * 
 * @param begin 
 * @param cod 
 * @param tp 
 * @param bat 
 * @param aut 
 * @param prc 
 * @param geo 
 * @param stat 
 * @param space 
 * @return Vehicle* 
 */
Vehicle* insertVehicle(Vehicle* begin, int cod, char tp[], float bat, float aut, float prc, char geo[], int stat, int space)
{
    if (!existVehicle(begin, cod))
    {
        Vehicle* newVehicle = malloc(sizeof(struct vehicle));
        if (newVehicle != NULL)
        {
            newVehicle->vCode = cod;
            strcpy(newVehicle->type, tp);
            newVehicle->batery = bat;
            newVehicle->price = prc;
            newVehicle->autonomy = aut;
            strcpy(newVehicle->geocode, geo);
            newVehicle->state = stat;
            newVehicle->space = space;
            newVehicle->nextv = begin; //update next pointer
            begin = newVehicle; //!!! 
        }
    }
    return begin; // Return the old head pointer if the vehicle already exists or memory allocation failed
}

/**
 * @brief Done
 * 
 * @param begin 
 * @param cod 
 * @return int 
 */
int existVehicle(Vehicle* begin, int cod)
{
    while (begin != NULL)
    {
        if (begin->vCode == cod) return 1;
        {
            begin = begin->nextv;
        }
        return 0;
    }
}

/**
 * @brief Done
 * 
 * @param begin 
 */
void listVehicles(Vehicle* begin)
{while (begin != NULL) 
 {printf("%d -> %s -> %.2f -> %.2f -> %.2f -> %s -> %d -> %d\n", begin->vCode, begin->type, begin->batery, begin->autonomy, begin->price, begin->geocode, begin->state, begin->space);
  begin = begin->nextv;
 }
}

/**
 * @brief Done
 * 
 * @param begin 
 */
void listVehicleDesc(Vehicle* begin) 
{
    Vehicle *x, *y;
    float i;
    int change;

    if (begin == NULL) {
        printf("Linked list is empty\n");
        return;
    } 
    while(change)
    {
        change = 0;
        x = begin;
        while(x->nextv == NULL)
        {
            y = x->nextv;
            if (x->autonomy < y->autonomy)
            {
                i = x->autonomy;
                x->autonomy = y->autonomy;
                y->autonomy = i;
                change = 1;
            }
            x = x->nextv;
        }
    }
    printf("List of Vehicles: \n\n");
    while(begin != NULL) {
        printf("%d -> %s -> %.2f -> %.2f -> %.2f -> %s -> %d -> %d\n", begin->vCode, begin->type, begin->batery, begin->autonomy, begin->price, begin->geocode, begin->state);
        begin = begin->nextv;
    }
}

/**
 * @brief Done
 * 
 * @param begin 
 * @param cod 
 * @return Vehicle* 
 */
Vehicle* removeVehicle(Vehicle* begin, int cod)
{
    Vehicle *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->vCode == cod)
    {
        aux = actual->nextv;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->vCode!=cod))
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

/**
 * @brief Done
 * 
 * @param begin 
 */
void seekVehicle(Vehicle* begin)
{
    char geo[TAM];
    int found = 0;
    printf("Insert the Vehicle's Geocode: \n");
    scanf("%s", geo);

    while(begin != NULL)
    {
        if(strcmp(begin->geocode, geo) == 0)
        {
            printf("Vehicle found: Code: %d | State: %d \n", begin->vCode, begin->state);
            found = 1;
        }
        begin = begin->nextv;
    }

    if(found != 1)
        printf("Vehicle not found!!");
}

/**
 * @brief Done
 * 
 * @param begin 
 * @param cod 
 * @param tp 
 * @param bat 
 * @param aut 
 * @param prc 
 * @param geo 
 * @param stat 
 * @param spac 
 * @return int 
 */
int changeVehicle(Vehicle* begin, int cod, char tp[], float bat, float aut, float prc, char geo[], int stat, int spac)
{
    Vehicle* actual = begin;
    while(actual != NULL)
    {
        if(actual->vCode == cod)
        {
            strcpy(actual->type, tp);
            actual->batery= bat;
            actual->autonomy = aut;
            actual->price = prc;
            strcpy(actual->geocode, geo);
            actual->state = stat;
            actual->space = spac;
            return 1;
        }
        actual = actual->nextv;
    }
    return 0;
}

/**
 * @brief Done
 * 
 * @param begin 
 */
void freeVehicle(Vehicle* begin)
{
    Vehicle* actual = begin;
    int free = 0;
    printf("Vehicles free: \n");
    while (actual != NULL)
    {
        if(actual->state == 0)
            printf("Code: %d | Type: %s | Price : %.2f | Batery: %.2f | Autonomy: %.2f | Geocode: %s\n", 
                    actual->vCode, actual->type, actual->price, actual->batery, actual->autonomy, actual->geocode);
        actual = actual->nextv;
    }
}