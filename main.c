/**
 * @file main.c
 * @author Francisco Arantes (a23504@alunos.ipca.pt)
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

/**
 * @brief This funcion rents a vehicle in a client's name
 * 
 * @param client 
 * @param vehicle 
 * @return int 
 */
int rentVehicle(Client* client, Vehicle* vehicle) 
{
    int ccode, vcode;
    printf("Client code: ");
    scanf("%d", &ccode);
    printf("Vehicle code: ");
    scanf("%d", &vcode);


    Client* actual = client;
    while (actual != NULL) 
    {
        if (actual->cCode == ccode) 
        {
            break;
        }
        actual = actual->nextc;
    }


    Vehicle* actualv = vehicle;
    while (actualv != NULL) 
    {
        if (actualv->vCode == vcode) 
        {
            break;
        }
        actualv = actualv->nextv;
    }

    if (actual == NULL || actualv == NULL) 
    {
        printf("Client or Vehicle code invalid!\n");
        return 0;
    }

    if (actualv->state == 1) 
    {
        printf("Meio ja alugado!\n");
        return 0;
    }


    if (actual->balance < actualv->price) 
    {
        printf("Insufficient funds!\n");
        return 0;
    }


    actualv->state = 1;
    actual->balance -= actualv->price;
    printf("Vehicle code %d rent with sucess to %s!\n", actualv->vCode, actual->name);
    
    FILE *fp;
    fp = fopen("Text_Files/rent_list.txt", "a");
    fprintf(fp, "Client:%s;%d;%d\n", actual->name, actual->cCode, actual->nif);
    fprintf(fp, "Vehicle:%s;%d;%s;%.2f;%.2f;%.2f;%s\n", actualv->type, actualv->vCode, actualv->type, actualv->batery, actualv->autonomy, actualv->price, actualv->geocode);
    fclose(fp);
    return 1;

}

/**
 * @brief Lists the current rents maded from rent_list.txt file
 * 
 */
void registVehicleRent() 
{
    FILE *fp;
    char linha[100];

    fp = fopen("Text_Files/rent_list.txt", "r");

    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }
    while (fgets(linha, 100, fp) != NULL) {
        printf("%s", linha);
    }

    fclose(fp);
}

int menu()
{
    int op;
    printf("\t\t\n-------Welcome------\n\n");
    printf("1. Load data.\n");
    printf("2. Client Menu.\n");
    printf("3. Manager Menu.\n");
    printf("0. Leave.\n");
    printf("\tOption: ");
    scanf("%d", &op);
    return op;
}

int managerMenu()
{
    int opm;
    printf("\t\t\n-------Welcome Manager------\n\n");
    printf("1.  Save data.\n");
    printf("2.  Check all the entities.\n");
    printf("3.  Insert Client.\n");
    printf("4.  Remove Client.\n");
    printf("5.  Insert Vehicle.\n");
    printf("6.  Remove Vehicle.\n");
    printf("7.  Change Vehicle.\n");
    printf("8.  Vehicle rent register.\n");
    printf("9.  Insert Manager.\n");
    printf("10. Remove Manager.\n");
    printf("11. Change Manager.\n");
    printf("12. Graph Menu.\n");
    printf("0.  Leave.\n");
    printf("\tOption: ");
    scanf("%d", &opm);
    return opm;
}

int clientMenu()
{
    int opc;
    printf("\t\t\n-------Welcome Client------\n\n");
    printf("1.  Check vehicles per autonomy.\n");
    printf("2.  Check vehicles per geocode.\n");
    printf("3.  Charge balance.\n");
    printf("4.  Rent vehicle\n");
    printf("5.  Change client data.\n");
    printf("0.  Leave.\n");
    printf("\tOption: ");
    scanf("%d", &opc);
    return opc;
}

int graphMenu()
{
    int opg;
    printf("\t\t\n-------Graph Estatistics------\n\n");
    printf("1. Load data of graph.\n");
    printf("2. Save data of graph.\n");
    printf("3. List graph info.\n");
    printf("4. Add node.\n");
    printf("5. Add edge.\n");
    printf("6. Add vehicle in graph.\n");
    printf("7. Add client in graph.\n");
    printf("8. List vehicles inside radius.\n");
    printf("0. Leave.\n");
    printf("\tOption: ");
    scanf("%d", &opg);
    return opg;
}

int main()
{
    //Initialize empty list
    Vehicle* vehicles = NULL;
    Client* clients = NULL;
    Manager* managers = NULL;
    Graph g = NULL;

    int op, opc, opm, opg, bcode, cod, mcod, gcod, cont, updt, ccode, nif, state, space, vcode, cgcode;
    float bal, val, bvalue, battery, autonomy, price, radius, ewei, vwei, vbat, vspace;
    char name[TAM], addr[TAM], mname[TAM], geo[TAM], pass[TAM], newadd[TAM], cGgeo[TAM], vGtype[TAM], ggeo[TAM], oNode[TAM], dNode[TAM], vtype[TAM], vgeo[TAM], cgeo[TAM], newPassword[100], node[100], newUsername[100], geocode[100], type[100];

    do
    {
        op = menu();
        switch (op)
        {
            case 1: clients = readClients();
                    vehicles = readVehicles();
                    managers = readManagers();
                break;
            case 2: do{
                        opc = clientMenu();
                        switch (opc)
                        {
                            case 1:
                                    listVehicleDesc(vehicles); 
                                    listVehicles(vehicles);
                                break;
                            case 2: seekVehicle(vehicles); break;
                            case 3:
                                printf("Client code: ");
                                scanf("%d", &bcode);
                                printf("Value: ");
                                scanf("%f", &bvalue);
                                chargeBalance(clients, bcode, bvalue);
                                break;
                            case 4: rentVehicle(clients, vehicles); break; //?!
                            case 5: 
                                    printf("Insert the Client's Code you want to update: ");
                                    scanf("%d", &ccode);
                                    printf("Insert the Client's NIF you want to update: ");
                                    scanf("%d", &nif);
                                    printf("Insert the Client's new Address you want to update: ");
                                    scanf("%s", &newadd);
                                    int result = UpdateClients(clients, ccode, nif, newadd);
                                    if (result == 1) {
                                        printf("Client updated successfully!\n");
                                        saveClient(clients);
                                    } else {
                                        printf("Failed to update client. Client not found.\n");
                                    }
                                break;
                            default: break;
                        }
                    } while (opc != 0);
                    break;
            case 3: 
                    do{
                        opm = managerMenu();
                        switch (opm)
                        {
                            case 1:
                                    saveManager(managers);
                                    saveClient(clients);
                                    saveVehicle(vehicles);
                                break;
                            case 2: listClients(clients);
                                    listVehicles(vehicles);
                                    listManagers(managers);
                                break;
                            case 3: 
                                    printf("Client's Code: \n");
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
                            case 4:
                                    printf("Client's code to remove: ");
                                    scanf("%d", &ccode);
                                    clients = removeClient(clients, ccode);
                                break; 
                            case 5: 
                                    printf("Vehicle's Code: \n");
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
                            case 6:  
                                    printf("Vehicles code to remove: ");
                                    scanf("%d", &cod);
                                    vehicles = removeVehicle(vehicles, cod);
                                break;
                            case 7: 
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
                            case 8: registVehicleRent(clients, vehicles); break;
                            case 9:
                                    printf("Manager's Code: \n");
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
                            case 10: 
                                    printf("Manager's Code to remove: ");
                                    scanf("%d", &gcod);
                                    managers = removeManager(managers, gcod);
                                break; 
                            case 11: 
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
                            case 12:
                                    do{
                                        opg = graphMenu();
                                        switch (opg)
                                        {
                                            case 1:
                                                    readNodes(&g);
                                                    readVehiclesGraph(&g);
                                                    readClientsGraph(&g);
                                                    readEdges(&g);
                                                break;
                                            case 2:
                                                    saveNodes(g);
                                                    saveVehiclesGraph(g);
                                                    saveClientsGraph(g);
                                                    saveEdgeGraph(g); 
                                                break;
                                            case 3:
                                                    printf("Nodes:\n\n");
                                                    listNodes(g);
                                                    printf("\n\nEdges: \n\n");
                                                    listEdges(g);
                                                    printf("\n\nVehicles: \n\n");
                                                    listVehiclesG(g);
                                                    printf("\n\nClients: \n\n");
                                                    listClientsG(g);
                                                break;
                                            case 4:
                                                    printf("Insert geocode: ");
                                                    scanf("%s", ggeo);
                                                    int n = createNode(&g, ggeo);
                                                    if (n == 1) {
                                                    printf("Node created.\n");
                                                    } else {
                                                    printf("Error creating node.\n");
                                                    }
                                                break;
                                            case 5: 
                                                    printf("Insert origin node: ");
                                                    scanf("%s", oNode);
                                                    printf("Insert destiny node: ");
                                                    scanf("%s", dNode);
                                                    printf("Insert the edge weight: ");
                                                    scanf("%f", &ewei);
                                                    int e = createEdge(g, oNode, dNode, ewei);
                                                    if (e == 1) {
                                                    printf("Edge created.\n");
                                                    } else {
                                                    printf("Error creating edge.\n");
                                                    }
                                                break;
                                            case 6: 
                                                    printf("Insert vehicle geocode: ");
                                                    scanf("%s", vgeo);
                                                    printf("Insert vehicle code: ");
                                                    scanf("%d", &vcode);
                                                    printf("Insert vehicle type: ");
                                                    scanf("%s", vtype);
                                                    printf("Insert vehicle batery: ");
                                                    scanf("%f", &vbat);
                                                    printf("Insert vehicle weight: ");
                                                    scanf("%f", &vwei);
                                                    printf("Insert vehicle space: ");
                                                    scanf("%f", &vspace);
                                                    int v = insertVehicleGraph(g, vgeo, vcode, vtype, vbat, vwei, vspace);
                                                    if (v == 1) {
                                                    printf("Vehicle added.\n");
                                                    } else {
                                                    printf("Error adding vehicle.\n");
                                                    }
                                                break;
                                            case 7: 
                                                    printf("Insert client geocode: ");
                                                    scanf("%s", cgeo);
                                                    printf("Insert client code: ");
                                                    scanf("%d", &cgcode);
                                                    int c = insertClientGraph(g, cgeo, cgcode);
                                                    if (c == 1) {
                                                    printf("Client added.\n");
                                                    } else {
                                                    printf("Error adding client.\n");
                                                    }
                                                break;
                                            case 8: 
                                                    printf("Insert the Client's location: ");
                                                    scanf("%s", cGgeo);
                                                    ClientG foundClient = verifyClientGeocode(g, cGgeo);
                                                    if (foundClient != NULL)
                                                    {
                                                        printf("Client found!\n\n");
                                                        printf("Vehicle type: ");
                                                        scanf("%s", vGtype);
                                                        printf("Chose a radius: ");
                                                        scanf("%f", &radius);
                                                        listVehiclesPerRadius(g, cGgeo, vGtype, radius);
                                                    }
                                                    else
                                                    {
                                                        printf("Client not found.\n");
                                                    }
                                                break;
                                            default: break;
                                        }
                                        } while (opg != 0);
                                        break;
                            default: break;
                        }
                    } while (opm != 0);
                break;
            default: break;
        }
    } while (op != 0);
    return 0; 
}

