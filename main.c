/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header_Files/client.h"
#include "Header_Files/manager.h"
#include "Header_Files/vehicles.h"

#define TAM 100

int menu()
{
    int op;
    printf("\t\t\nM E N U\n");
    printf("1. Read Clients\n");
    printf("2. Insert Client\n");
    printf("3. Save Client\n");
    printf("4. Remove Client\n");
    printf("5. Change Client\n\n");

    // printf("6. Read Vehicles\n");
    // printf("7. Insert Vehicle\n");
    // printf("8. Save Vehicle\n");
    // printf("9. Remove Vehicle\n");
    // printf("10. Change Vehicle\n");
    // printf("11. List Vehicles\n");
    // printf("12. List Vehicles per Location\n");
    // printf("13. Register Vehicle\n\n");

    // printf("14. Read Managers\n");
    // printf("15. Insert Manager\n");
    // printf("16. Save Manager\n");
    // printf("17. Remove Manager\n");
    // printf("18. Change Manager\n");
    // printf("19. Check total clients\n");
    // printf("20. Check total vehicles\n");
    // printf("21. Check Total managers\n");
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

    int op, ccode, nif, cod, mcod, stat, gcod, cont, updt;
    float bal, prc, aut, bat, val;
    char name[TAM], addr[TAM], tp[TAM], mname[TAM], geo[TAM], pass[TAM], geocode[TAM], newadd[TAM];
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
                        clients = insertClient(clients, ccode, nif, name, bal, addr, geocode);
                break;
            case 3: saveClient(clients);    break;
            case 4: printf("Client's code to remove: ");
                    scanf("%d", &ccode);
                    clients = removeClient(clients, ccode);
                break;
            case 5: printf("Insert the Client's Code you want to update: ");
                    scanf("%d", &ccode);
                    printf("What do you want to update: (1)-NIF | (2)-Name | (3)-Balance | (4)-Address\n Option: ");
                    scanf("%d", &updt);
                    UpdateClients(clients, ccode, nif, newadd);
                break;
            
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
            //case 11: listVehicle(vehicles); break;
            case 12: break;
            case 13: break;

            case 14: managers = readManagers();   break;
            case 15: printf("Manager's Code: \n");
                    scanf("%d", &gcod);
                    scanf("%*c");
                    printf("Manager's Password: \n");
                    scanf("%[^\n]", pass);
                    printf("Manager's Contact: \n");
                    scanf("%d", &cont);
                    scanf("%*c");
                    printf("Manager's Name: \n");
                    scanf("%[^\n]", mname);
                    managers = insertManager(managers, gcod, pass, cont, mname);
                break; 
            case 16: saveManager(managers);  break;
            case 17: printf("Manager's Code to remove: ");
                    scanf("%d",&gcod);
                    managers = removeManager(managers, gcod);
                break;  break;
            case 18:   break;
            case 19: listClients(clients); break;
            case 20: listVehicles(vehicles); break;
            case 21: listManagers(managers); break;
            default: 
                break;
        }
    } while (op != 0);

    return 0;
}
