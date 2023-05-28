/**
 * @file Vehicles.c
 * @author Francisco Arantes (a23504@alunos.ipca.pt)
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
#include "../Header_Files/client.h"

/**
 * @brief Save current data of vehicles in vehicles.txt file
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
            fprintf(fp, "%d;%s;%f;%f;%f;%s;%d;%d;\n", aux->vCode, aux->type, aux->batery, aux->autonomy, aux->price, aux->geocode, aux->state, aux->space);
            aux = aux->nextv;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}
 
/**
  * @brief Reads vehicles data from vehicles.txt file
  * 
  * @return Vehicle* 
  */
Vehicle* readVehicles()
{
    FILE* fp;
    int cod, stat, space;
    float prc, bat, aut;
    char tp[100], geo[100];
    
    Vehicle* aux = NULL;
    fp = fopen("Text_Files/vehicles.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%[^;];%f;%f;%f;%[^;];%d;%d;\n", &cod, tp, &bat, &aut, &prc, geo, &stat, &space);
        aux = insertVehicle(aux, cod, tp, bat, aut, prc, geo, stat, space);
        }
        fclose(fp);
    }
    return(aux);
}

/**
 * @brief Insert a new vehicle on the linked list
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
            begin = newVehicle;
        }
    }
    return begin; // Return the old head pointer if the vehicle already exists or memory allocation failed
}

/**
 * @brief Verify is a certain vehicle exists in the linked list given his code
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
            begin = begin->nextv;
    }
    return 0;
}

/**
 * @brief Lists all the vehicles of the linked list
 * 
 * @param begin 
 */
void listVehicles(Vehicle* begin)
{  
    printf("List of Vehicles: \n\n");
    while (begin != NULL) 
    {
        printf("%d -> %s -> %.2f -> %.2f -> %.2f -> %s -> %d -> %d ->\n", begin->vCode, begin->type, begin->batery, begin->autonomy, begin->price, begin->geocode, begin->state, begin->space);
        begin = begin->nextv;
    }
}

/**
 * @brief Lists all the vehicles in descendent order by their autonomy
 * 
 * @param begin 
 */
void listVehicleDesc(Vehicle* begin) 
{
    Vehicle *x, *y;
    float i, bat, price, change, wei;
    int code, st, sp;
    char tp[250], geo[250];

    if (begin == NULL) {
        printf("Linked list is empty\n");
        return;
    }
    do {
            change = 0;
            x = begin;
            while(x->nextv != NULL)
            {
                y = x->nextv;
                if (x->autonomy < y->autonomy)
                {
                    code = x->vCode;
                    x->vCode = y->vCode;
                    y->vCode = code;

                    strcpy(tp, x->type);
                    strcpy(x->type, y->type);
                    strcpy(y->type, tp);

                    bat = x->batery;
                    x->batery = y->batery;
                    y->batery = bat;

                    i = x->autonomy;
                    x->autonomy = y->autonomy;
                    y->autonomy = i;

                    price = x->price;
                    x->price = y->price;
                    y->price = price;

                    strcpy(geo, x->geocode);
                    strcpy(x->geocode, y->geocode);
                    strcpy(y->geocode, geo);

                    st = x->state;
                    x->state = y->state;
                    y->state = st;

                    sp = x->space;
                    x->space = y->space;
                    y->space = sp;
                    
                    wei = x->vweight;
                    x->vweight = y->vweight;
                    y->vweight = wei;

                    change = 1;
                }
                x = x->nextv;
            }
        }while(change);

}

/**
 * @brief Remove a vehicle from the linked list given his code
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
 * @brief Seek vehicles by a given geocode 
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
 * @brief Change vehicle data from the linked list
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