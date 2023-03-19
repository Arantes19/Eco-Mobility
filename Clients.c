#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "op.h"

int existClient(Client* begin, int ccode)
{
    while (begin != NULL)
    {
        if (begin->cCode == ccode) return(1);
        {
            begin = begin->nextc;
        }
        return(0);
    }
}

int saveClient(Client* begin)
{
    FILE* fp;
    fp = fopen("clients.txt", "w");
    if (fp!=NULL)
    {
        Client* aux = begin;
        while (aux !=NULL)
        {
            fprintf(fp, "%d;%d;%s;%f;%s\n",aux->cCode, aux->nif, aux->name, aux->balance, aux->address);
            aux = aux->nextc;
        }
        fclose(fp);
        return(1);
    }
    else return(0);
}

Client* readClients()
{
    FILE* fp;
    int nif, ccode;
    float bal;
    char name[50], addr[50];

    Client* aux = NULL;
    fp = fopen("clients.txt", "r");
    if (fp != NULL)
    {
        while(!feof(fp))
        {fscanf(fp, "%d;%d;%[^;];%f;%[^\n]\n", &ccode, &nif, name, &bal, addr);
        aux = insertClient(aux, ccode, nif, name, bal, addr);
        }
        fclose(fp);
    }
    return(aux);
}

Client* insertClient(Client* begin, int ccode, int nif, char name[],  float bal, char addr[])
{
    if (!existClient(begin, ccode))
    {
        Client* newClient = malloc(sizeof(struct client));  // Allocate memory for new node;
        if (newClient != NULL)
        {
            newClient->cCode = ccode;
            newClient->nif = nif;
            strcpy(newClient->name, name);
            newClient->balance = bal;
            strcpy(newClient->address, addr);
            newClient->nextc = begin;
            begin = newClient; //!!! 
            return (newClient);
        }
    }
    return(begin);
    printf("Client already exist!");
}

Client* removeClient(Client* begin, int ccode)
{
    Client *previous = begin, *actual = begin, *aux;
    if (actual == NULL) return(NULL);
    else if (actual->cCode == ccode)
    {
        aux = actual->nextc;
        free(actual);
        return(aux);
    }
    else
    {
        while((actual != NULL)&&(actual->cCode != ccode))
        {
            previous = actual;
            actual = actual->nextc;
        }
        if (actual == NULL) return(begin);
        else
        {
            previous->nextc = actual->nextc;
            free(actual);
            return(begin);
        }
    }  
}

void listClients(Client* begin)
{while (begin != NULL) 
 {printf("%d -> %d -> %s -> %.2f -> %s\n", begin->cCode, begin->nif, begin->name, begin->balance, begin->address);
  begin = begin->nextc;
 }
}


int countClients(Client *begin)
{
    int c = 0;
    while(begin!= NULL)
    {
        begin =begin->nextc;
        c++;
    }
    return c;
}

void UpdateClients(Client* begin, int ccode, int op) 
{
    int n = countClients(begin);
    int i, nif;
    float balance;
    char name[TAM], address[TAM];
   
    if(begin == NULL) {
        printf("Linked List is Empty");
        return;
    } 

    if(ccode > n) printf("Clients doesn't exist!!");
    else if (ccode > 0)
    {
        for (i = 0; i < ccode; i++)
            begin = begin->nextc;
        
         switch (op)
        {
            if (begin == NULL) {        
            printf("Error: Client is null.\n");
            return;
            }
        case 1:
            fflush(stdin);
            printf("Enter new NIF: ");
            scanf("%d", &nif);
            begin->nif = nif;
            break;
        case 2:
            fflush(stdin);
            printf("Enter new name: ");
            fgets(name, TAM, stdin);
            strtok(name, "\n"); // remove trailing newline character
            strcpy(begin->name, name);
            break;
        case 3:
            fflush(stdin);
            printf("Enter new balance: ");
            scanf("%f", &balance);
            begin->balance = balance;
            break;
        case 4:
            fflush(stdin);
            printf("Enter new address: ");
            fgets(address, TAM, stdin);
            strtok(address, "\n"); // remove trailing newline character
            strcpy(begin->address, address);
            break;
        default:
            break;
        }
        if (saveClient(begin))
            printf("Client updated successfully.\n");
        else printf("Failed to update client.\n");
        
        }
}
