#include <stdio.h>
#define TAM 50

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
    int cCode;
    int nif;
    char name[TAM];
    float balance;
    char address[TAM];
    struct client* nextc;
}Client;

typedef struct manager
{
    int Mcode;
    char Mname[TAM];
    struct manager* nextm;
}Manager;

//Client sub-rotines
Client* insertClient(Client* begin, int ccode, int nif, char name[],  float bal, char addr[]);
Client* readClients();
int saveClient(Client* begin);
int existClient(Client* begin, int ccode);
Client* removeClient(Client* begin, int ccode);


//Vehicle sub-rotines
Vehicle* insertVehicle(Vehicle* begin, int cod, char tp[], int bat, float prc);
Vehicle* readVehicle();
int saveVehicle(Vehicle* begin);
int existVehicle(Vehicle* begin, int cod);
//void listVehicle(Vehicle* begin);
Vehicle* removeVehicle(Vehicle* begin, int cod);

//Manager sub-rotines
Manager* insertManager(Manager* begin, int mcod, char mname[]);
Manager* readManager();
int saveManager(Manager* begin);
int existManager(Manager* begin, int mcod);
Manager* removeManager(Manager* begin, int mcod);

