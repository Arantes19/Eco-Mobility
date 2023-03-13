#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "op.h"

int menu()
{int op;
 printf("M E N U\n");
 printf("1. Insert Client\n");
 printf("2. Insert Vehicle\n");
 printf("3. Insert Manager\n");
 printf("4. Save Client\n");
 printf("5. Save Vehicle\n");
 printf("6. Save Manager\n");
 printf("7. Read Client\n");
 printf("8. Read Vehicle\n");
 printf("9. Read Manager\n");
 printf("Opcao:\n");
 scanf("%d",&op);
 return(op);
}


int main()
{
   Vehicle* vehicles = NULL;
   Client* clients = NULL;
   Manager* managers = NULL;

   int op, nif, cod, bat, mcod;
   float bal, prc;
   char name[50], addr[50], tp[50], mname[50];
    do
    {
        op = menu();
        switch (op)
        {
            case 1: printf("Client's NIF: \n");
                    scanf("%d", &nif);
                    printf("Client's Balance: \n");
                    scanf("%f", &bal);
                    printf("Client's Name: \n");
                    scanf("%[^\n]", name);
                    printf("Client's Address: \n");
                    scanf("%[^\n]", addr);
                    clients = insertClient(clients, nif, bal, name, addr);
                break;
            case 2: printf("Vehicle's Code: \n");
                    scanf("%d", &cod);
                    printf("Vehicle's Type: \n");
                    scanf("%[^\n]", tp);
                    printf("Vehicle's Battery: \n");
                    scanf("%d", &bat);
                    printf("Vehicle's Price: \n");
                    scanf("%f", &prc);
                    vehicles = insertVehicle(vehicles, cod, tp, bat, prc);
                break;
            case 3: printf("Manager's Code: \n");
                    scanf("%d", &mcod);
                    printf("Manager's Name: \n");
                    scanf("%[^\n]", mname);
                    managers = insertManager(managers, mcod, mname);
                break;
            case 4: saveClient(clients);    break;
            case 5: saveVehicle(vehicles);  break;
            case 6: saveManager(managers);  break;
            case 7: clients = readClient();     break;
            case 8: vehicles = readVehicle();   break;
            case 9: managers = readManager();   break;
            default:
                break;
        }
    } while (op != 0);

    return 0;
}
