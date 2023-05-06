#include <stdio.h>
#define TAM 100

typedef struct client
{
    int cCode;
    int nif;
    char name[TAM];
    float balance;
    char address[TAM];
    struct client* nextc;
}Client;

//Client sub-rotines
Client* insertClient(Client* begin, int ccode, int nif, char name[],  float bal, char addr[]);
Client* readClients();
int saveClient(Client* begin);
int existClient(Client* begin, int ccode);
Client* removeClient(Client* begin, int ccode);
void UpdateClients(Client* clients ,int ccode, int op);
int countClients(Client *begin);
void listClients(Client* begin);
