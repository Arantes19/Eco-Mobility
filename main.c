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
#include "Header_Files/vehicles.h"
#include "Header_Files/manager.h"
#include "Header_Files/graph.h"

#define TAM 250

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
    printf("11. List Vehicles Descendent Order\n");
    printf("12. List Vehicles per Location\n");
    printf("13. Register Vehicle\n\n");

    printf("14. Read Managers\n");
    printf("15. Insert Manager\n");
    printf("16. Save Manager\n");
    printf("17. Remove Manager\n");
    printf("18. Change Manager\n");
    
    printf("19. Check total clients\n");
    printf("20. Check total vehicles\n");
    printf("21. Check Total managers\n");

    printf("22. Read data from graph file\n");
    printf("23. Save data on graph file\n");
    printf("24. List edges\n");
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
    Graph g = NULL;

    //Create graph
    createNode(&g, "Braga");
    createNode(&g, "Porto");
    createNode(&g, "Lisboa");
    createEdge(g, "Braga", "Porto", 50.0);
    createEdge(g, "Braga", "Lisboa", 390.0);
    createEdge(g, "Lisboa", "Porto", 50.0);
    createEdge(g, "Porto", "Lisboa", 390.0);
    insertVehicleGraph(g, "Braga", 1, "Car", 80.0, 100.0, 17);
    insertVehicleGraph(g, "Porto", 2, "Car", 50.0, 500.0, 16);
    insertVehicleGraph(g, "Lisboa", 3, "Car", 50.0, 3000.0, 15);
    insertClientGraph(g, "Braga", 1);
    insertClientGraph(g, "Porto", 2);
    insertClientGraph(g, "Lisboa", 2);


    int op, ccode, nif, cod, mcod, gcod, cont, updt;
    float bal, val;
    char name[TAM], addr[TAM], mname[TAM], geo[TAM], pass[TAM], newadd[TAM];
    
    char type[100];
    float battery, autonomy, price;
    char geocode[100];
    int state, space;
    
    char newUsername[100];
    char newPassword[100], node[100];



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
                    scanf("%*c");
                    printf("Client's Geocode: \n");
                    scanf("%[^\n]", geocode);
                    clients = insertClient(clients, ccode, nif, name, bal, addr, geocode);
                break;
            case 3: saveClient(clients);    break;
            case 4: printf("Client's code to remove: ");
                    scanf("%d", &ccode);
                    clients = removeClient(clients, ccode);
                break;
            case 5: printf("Insert the Client's Code you want to update: ");
                    scanf("%d", &ccode);
                    printf("Insert the Client's NIF you want to update: ");
                    scanf("%d", &nif);
                    printf("Insert the Client's new Address you want to update: ");
                    scanf("%s", &newadd);
                    int result = UpdateClients(clients, ccode, nif, newadd);
                    if (result == 1) {
                        printf("Client updated successfully!\n");
                    } else {
                        printf("Failed to update client. Client not found.\n");
                    }
                
                break;
            
            case 6: vehicles = readVehicles();   break;
            case 7: printf("Vehicle's Code: \n");
                    scanf("%d", &cod);
                    scanf("%*c"); 
                    printf("Vehicle's Type: \n");
                    scanf("%[^\n]", type);
                    printf("Vehicle's Battery: \n");
                    scanf("%f", &battery);
                    printf("Vehicle's Autonomy: \n");
                    scanf("%f", &autonomy);
                    printf("Vehicle's Price: \n");
                    scanf("%f", &price);
                    scanf("%*c");
                    printf("Vehicle's Geocode: \n");
                    scanf("%[^\n]", geo);
                    printf("Vehicle's State: \n");
                    scanf("%d", &state);
                    printf("Vehicle's Space: \n");
                    scanf("%d", &space);
                    vehicles = insertVehicle(vehicles, cod, type, battery, autonomy, price, geo, state, space);
                break;
            case 8: saveVehicle(vehicles);  break;
            case 9: printf("Vehicles code to remove: ");
                    scanf("%d", &cod);
                    vehicles = removeVehicle(vehicles, cod);
                break;
            case 10: 
                    printf("Insert the Vehicle's Code you want to update: ");
                    int vehicleCode;
                    scanf("%d", &vehicleCode);
                    getchar(); // Consume newline character

                    printf("Enter the new type: ");
                    fgets(type, sizeof(type), stdin);
                    type[strcspn(type, "\n")] = '\0';

                    printf("Enter the new battery capacity: ");
                    scanf("%f", &battery);
                    getchar(); // Consume newline character

                    printf("Enter the new autonomy: ");
                    scanf("%f", &autonomy);
                    getchar(); // Consume newline character

                    printf("Enter the new price: ");
                    scanf("%f", &price);
                    getchar(); // Consume newline character

                    printf("Enter the new geocode: ");
                    fgets(geocode, sizeof(geocode), stdin);
                    geocode[strcspn(geocode, "\n")] = '\0';

                    printf("Enter the new state: ");
                    scanf("%d", &state);
                    getchar(); // Consume newline character

                    printf("Enter the new space: ");
                    scanf("%d", &space);
                    getchar(); // Consume newline character

                    int resultv = changeVehicle(vehicles, vehicleCode, type, battery, autonomy, price, geocode, state, space);
                    if (resultv == 1) {
                        printf("Vehicle updated successfully.\n");
                    } else {
                        printf("Vehicle with code %d not found.\n", vehicleCode);
                    }
                break;
            case 11: listVehicleDesc(vehicles); break;
            case 12: seekVehicle(vehicles); break;
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
                    scanf("%d", &gcod);
                    managers = removeManager(managers, gcod);
                break; 
            case 18:
                        printf("Enter the Manager's Geocode: ");
                        scanf("%d", &gcod);
                        getchar(); // Consume newline character

                        printf("Enter the current password: ");
                        fgets(pass, sizeof(pass), stdin);
                        pass[strcspn(pass, "\n")] = '\0';

                        printf("Enter the new username: ");
                        fgets(newUsername, sizeof(newUsername), stdin);
                        newUsername[strcspn(newUsername, "\n")] = '\0';

                        printf("Enter the new password: ");
                        fgets(newPassword, sizeof(newPassword), stdin);
                        newPassword[strcspn(newPassword, "\n")] = '\0';

                        int resultm = changeManager(managers, gcod, pass, newUsername, newPassword);
                        if (resultm == 1) {
                            printf("Manager information updated successfully.\n");
                        } else {
                            printf("Manager with geocode %d and provided password not found.\n", gcod);
                        }
                break; 
            case 19: listClients(clients); break;
            case 20: listVehicles(vehicles); break;
            case 21: listManagers(managers); break;
            case 22: readNodes(g);
                     readVehiclesGraph(g);
                     readClientsGraph(g);
                     readNodes(g);
                break;
            case 23: 
                    saveNodes(g);
                    saveVehiclesGraph(g);
                    saveClientsGraph(g);
                    saveEdgeGraph(g); break;
            case 24: listEdges(g, "Braga"); break;
            default: 
                break;
        }
    } while (op != 0);

    return 0;
}
