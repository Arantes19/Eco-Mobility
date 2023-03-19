#include <stdio.h>
#define TAM 50

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
    int gCode;
    char password[TAM];
    int contact;
    char username[TAM];
    struct manager* nextm;
}Manager;

//Client sub-rotines
Client* insertClient(Client* begin, int ccode, int nif, char name[],  float bal, char addr[]);
Client* readClients();
int saveClient(Client* begin);
int existClient(Client* begin, int ccode);
Client* removeClient(Client* begin, int ccode);


//Vehicle sub-rotines
Vehicle* insertVehicle(Vehicle* begin, int cod, char tp[], float bat, float aut, float prc, char geo[], int stat);
Vehicle* readVehicles();
int saveVehicle(Vehicle* begin);
int existVehicle(Vehicle* begin, int cod);
//void listVehicle(Vehicle* begin);
Vehicle* removeVehicle(Vehicle* begin, int cod);

//Manager sub-rotines
Manager* insertManager(Manager* begin, int gcod, char pass[], int cont, char mname[]);
Manager* readManagers();
int saveManager(Manager* begin);
int existManager(Manager* begin, int gcod);
Manager* removeManager(Manager* begin, int gcod);

