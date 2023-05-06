#include <stdio.h>
#define TAM 100

typedef struct vehicle
{
    int vCode;
    char type[TAM];
    float batery;
    float autonomy;
    float price;
    char geocode[TAM];
    int state;
    struct vehicle* nextv; 
}Vehicle;

//Vehicle sub-rotines
Vehicle* insertVehicle(Vehicle* begin, int cod, char tp[], float bat, float aut, float prc, char geo[], int stat);
Vehicle* readVehicles();
int saveVehicle(Vehicle* begin);
int existVehicle(Vehicle* begin, int cod);
//void listVehicleDesc(Vehicle* begin);
Vehicle* removeVehicle(Vehicle* begin, int cod);
int countVehicles(Vehicle *begin);
void listVehicles(Vehicle* begin);