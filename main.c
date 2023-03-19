#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "op.h"

int menu()
{
    int op;
    printf("\t\t\nM E N U\n");
    printf("1. Read Clients\n");
    printf("2. Insert Client\n");
    printf("3. Save Client\n");
    printf("4. Remove Client\n");
    printf("5. Change Client\n\n");

    printf("6. Read Vehicles\n");
    printf("7. Insert Vehicle\n");
    printf("8. Save Vehicle\n");
    printf("9. Remove Vehicle\n");
    printf("10. Change Vehicle\n");
    printf("11. List Vehicles\n");
    printf("12. List Vehicles per Location\n");
    printf("13. Register Vehicle\n\n");

    printf("14. Read Managers\n");
    printf("15. Insert Manager\n");
    printf("16. Save Manager\n");
    printf("17. Remove Manager\n");
    printf("18. Change Manager\n\n");
    printf("0. Leave\n\n");

    printf("Opcao: ");
    scanf("%d",&op);
    return(op);
}


int main()
{
    //Initialize empty list
    Vehicle* vehicles = NULL;
    Client* clients = NULL;
    Manager* managers = NULL;

    int op, ccode, nif, cod, mcod, stat;
    float bal, prc, aut, bat;
    char name[TAM], addr[TAM], tp[TAM], mname[TAM], geo[TAM];
    do
    {
        op = menu();
        switch (op)
        {
            case 1: clients = readClients();     break;
            case 2: printf("Client's Code: \n");
                    scanf("%d", &ccode);
                    printf("Client's NIF: \n");
                    scanf("%d", &nif);
                    scanf("%*c"); 
                    printf("Client's Name: \n");
                    scanf("%[^\n]", name);
                    printf("Client's Balance: \n");
                    scanf("%f", &bal);
                    scanf("%*c"); 
                    printf("Client's Address: \n");
                    scanf("%[^\n]", addr);
                        clients = insertClient(clients, ccode, nif, name, bal, addr);
                break;
            case 3: saveClient(clients);    break;
            case 4: printf("Client's code to remove: ");
                    scanf("%d", &ccode);
                    clients = removeClient(clients, ccode);
                break;
            case 5: break;
            
            case 6: vehicles = readVehicles();   break;
            case 7: printf("Vehicle's Code: \n");
                    scanf("%d", &cod);
                    scanf("%*c"); 
                    printf("Vehicle's Type: \n");
                    scanf("%[^\n]", tp);
                    printf("Vehicle's Battery: \n");
                    scanf("%f", &bat);
                    printf("Vehicle's Autonomy: \n");
                    scanf("%f", &aut);
                    printf("Vehicle's Price: \n");
                    scanf("%f", &prc);
                    scanf("%*c");
                    printf("Vehicle's Geocode: \n");
                    scanf("%[^\n]", geo);
                    printf("Vehicle's State: \n");
                    scanf("%d", &stat);
                        vehicles = insertVehicle(vehicles, cod, tp, bat, aut, prc, geo, stat);
                break;
            case 8: saveVehicle(vehicles);  break;
            case 9: printf("Vehicles code to remove: ");
                    scanf("%d", &cod);
                    vehicles = removeVehicle(vehicles, cod);
                break;
            case 10: break;
            case 11: break;
            case 12: break;
            case 13: break;

            case 14: managers = readManager();   break;
            case 15: printf("Manager's Code: \n");
                    scanf("%d", &mcod);
                    printf("Manager's Name: \n");
                    scanf("%s", mname);
                    managers = insertManager(managers, mcod, mname);
                break; 
            case 16: saveManager(managers);  break;
            case 17: printf("Manager's Code to remove: ");
                    scanf("%d",&cod);
                    managers = removeManager(managers, cod);
                break;  break;
            case 18:   break;
            default:
                break;
        }
    } while (op != 0);

    return 0;
}
