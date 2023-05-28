/**
 * @file client.h
 * @author Francisco Arantes (a23504@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#define TAM 250

typedef struct client
{
    int cCode;
    int nif;
    char name[TAM];
    float balance;
    char address[TAM];
    char geocode[TAM];
    struct client* nextc;
}Client;

//Client sub-rotines
Client* insertClient(Client* begin, int ccode, int nif, char name[],  float bal, char addr[], char geocode[]);
Client* readClients();
int saveClient(Client* begin);
int existClient(Client* begin, int ccode);
Client* removeClient(Client* begin, int ccode);
int UpdateClients(Client* begin ,int ccode, int nif, char newaddress[]);
void listClients(Client* begin);
Client* chargeBalance(Client *begin, int ccod, float value);
