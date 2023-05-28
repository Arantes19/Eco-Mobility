/**
 * @file vehicles.h
 * @author Francisco Arantes (a23504@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#define TAM 250

typedef struct vehicle
{
    int vCode;
    char type[TAM];
    float batery;
    float autonomy;
    float price;
    char geocode[TAM];
    int state;
    int space;
    float vweight;
    struct vehicle* nextv; 
}Vehicle;

//Vehicle sub-rotines
Vehicle* insertVehicle(Vehicle* begin, int cod, char tp[], float bat, float aut, float prc, char geo[], int stat, int space);
Vehicle* readVehicles();
int saveVehicle(Vehicle* begin);  
int existVehicle(Vehicle* begin, int cod);
Vehicle* removeVehicle(Vehicle* begin, int cod);
void listVehicles(Vehicle* begin);
void listVehicleDesc(Vehicle* begin);
void seekVehicle(Vehicle* begin);
int changeVehicle(Vehicle* begin, int cod, char tp[], float bat, float aut, float prc, char geo[], int stat, int spac);