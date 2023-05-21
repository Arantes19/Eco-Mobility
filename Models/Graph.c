/**
 * @file Graph.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Header_Files/graph.h"
#define MAX_VEHICLESG 50

int createNode(Graph *g, char nodeId[])
{
    Graph new = malloc(sizeof(struct regist1));
    if (new != NULL)
    {
        strcpy(new->node, nodeId);
        new->vehicles = NULL;
        new->clients = NULL;   
        new->edges = NULL;
        new->nextr = *g;
        *g = new;
        return 1;
    }
    else return 0;
}

int existNode(Graph g, char node[])
{
    while (g != NULL)
    {
        if (strcmp(g->node, node) == 0) return(1);
    else g = g->nextr;
    }
    return(0);
}

int createEdge(Graph g, char nodeOrigin[], char nodeDestiny[], float weight)
{
    Edge new;
    if (existNode(g, nodeOrigin) && existNode(g, nodeDestiny))
    {
        while(strcmp(g->node, nodeOrigin) !=0 ) g = g->nextr;
        new = malloc(sizeof(struct regist1));
        if (new != NULL)
	    {
            strcpy(new->node, nodeDestiny);
            new->weight = weight;
            new->nextr = g->edges;
            g->edges = new;
            return(1);
	    }
    else return(0);
    }
    else return(0);
}

int insertVehicleGraph(Graph g, char geocode[], int vehicleCode, char tp[], float bat, float weight, float space)
{
    while ((g != NULL) && (strcmp(g->node, geocode) != 0))
	g = g->nextr;
    if (g == NULL) return(0);
    else 
        {
            VehicleG new = malloc(sizeof(struct regist3));
            strcpy(new->geocode, geocode); 
            new->vcode = vehicleCode;
            strcpy(new->type, tp); 
            new->batery = bat;
            new->weight = weight;
            new->space = space;
            new->nextr = g->vehicles;
            g->vehicles = new;
            return(1);	 
        }
}

int insertClientGraph(Graph g, char geocode[], int clientCode)
{
    while ((g != NULL) && (strcmp(g->node, geocode) != 0))
	g = g->nextr;
    if (g == NULL) return(0);
    else 
        {
            ClientG new = malloc(sizeof(struct regist4));
            new->ccode = clientCode;
            new->nextr = g->clients;
            g->clients = new;
            return(1);	 
        }
}

void saveNodes(Graph g)
{
    FILE* fp = fopen("Text_Files/nodes_graph.txt", "w");
    if (fp == NULL)
    {
           printf("Failed to open the file.\n");
           return;
    }
    while(g != NULL)
    {
        fprintf(fp, "%s;\n", g->node);
        g = g->nextr;
    }
    fclose(fp);
}

void saveVehiclesGraph(Graph g)
{
    FILE* fp = fopen("Text_Files/vehicles_graph.txt", "w");
    if (fp == NULL)
    {
           printf("Failed to open the file.\n");
           return;
    }
    while(g != NULL)
    {
        fprintf(fp, "%s->", g->node);
        VehicleG aux = g->vehicles;
        while (aux != NULL)
        {
            fprintf(fp, "%d;%s;%f;%f;%f\n", aux->vcode, aux->type, aux->batery, aux->weight, aux->space);
            aux = aux->nextr;
        }
        g = g->nextr;
    }
    fclose(fp);
}

void saveClientsGraph(Graph g)
{
    FILE* fp = fopen("Text_Files/clients_graph.txt", "w");
    if (fp == NULL)
    {
           printf("Failed to open the file.\n");
           return;
    }
    while(g != NULL)
    {
        fprintf(fp, "%s->", g->node);
        ClientG aux = g->clients;
        while (aux != NULL)
        {
            fprintf(fp, "%d;\n", aux->ccode);
            aux = aux->nextr;
        }
        g = g->nextr;
    }
    fclose(fp);
}

void saveEdgeGraph(Graph g)
{
    FILE* fp = fopen("Text_Files/edge_graph.txt", "w");
    if (fp == NULL)
    {
           printf("Failed to open the file.\n");
           return;
    }
    while(g != NULL)
    {
        fprintf(fp, "%s->", g->node);
        Edge aux = g->edges; 
        printf("%s -> ", aux);
        while (aux != NULL)
        {
            fprintf(fp, "%s;%f;\n", aux->node, aux->weight);
            aux = aux->nextr;
        }
        g = g->nextr;
    }
    fclose(fp);
}

Graph readNodes(Graph g)
{
    FILE* fp;
    char node[250];

    Graph* aux = NULL;
    fp = fopen("Text_Files/nodes_graph.txt", "r");
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%[^;];\n", node); 
        }
        fclose(fp);
    }
     return g;
}

Graph readVehiclesGraph(Graph g)
{
    FILE* fp;
    int vcode;
    float bat, space, weight;
    char node[250], type[100];

    Graph* auxg = NULL;
    VehicleG* aux = NULL;
    fp = fopen("Text_Files/vehicles_graph.txt", "r");
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%s->%d;%s;%f;%f;\n",node, &vcode, type, &bat, &weight, &space);
        }
        fclose(fp);
    }
    return g;
}

Graph readClientsGraph(Graph g)
{
    FILE* fp;
    int ccode;
    char node[250];

    Graph* auxg = NULL;
    ClientG* aux = NULL;
    fp = fopen("Text_Files/clients_graph.txt", "r");
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%s->%d;\n", node, &ccode);
        }
        fclose(fp);
    }
    return g;
}

Graph readEdges(Graph g)
{
    FILE* fp;
    char nodeO[250], nodeD[250];
    float weight;

    Graph* aux = NULL;
    fp = fopen("Text_Files/edges_graph.txt", "r");
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%[^->]->%[^;];%f;\n", nodeO, nodeD, &weight);
        }
        fclose(fp);
    }
    return g;
}

void listEdges(Graph g, char node[])
{
    Edge aux = NULL;
    if (existNode(g, node))
    {
        while (strcmp(g->node,node) != 0) g = g->nextr;
        aux = g->edges;
        while (aux != NULL) 
        {
            printf("Edge: %s | Weight: %.2f\n", aux->node, aux->weight);
            aux = aux->nextr;
        }
    }
}

void listNodes(Graph g)
{   
    if (existNode(g, g->node))
    {
        while (g != NULL) 
        {
            printf("%s\n", g->node);
            g = g->nextr;
        }
    }
    printf("\n\n");
}

// ClientG verifyClientGeocode(Graph g, char geocode[])
// {
//     ClientG clients = NULL;
//     while(g != NULL)
//     {
//         ClientG aux = g->clients;
//         while (aux != NULL)
//         {
//             if(strcmp(g->node, geocode) == 0)
//             {
//                 clients = aux;
//                 return clients;
//                 printf("Client found!!\n");
//                 break;
//             }
//             aux = aux->nextr;
//         }
//         if(clients != NULL) break;
//         g = g->nextr; 
//     }
//     if(clients == NULL) //main
//     {
//         printf("Client not found.\n");
//     }
// }

Graph findNode(Graph g, char geocode[])
{
    while (g != NULL)
    {
        if (strcmp(g->node, geocode) == 0)
        {
            return g;
        }
        g = g->nextr;
    }
    return NULL;
}

Graph findNodeNext(Graph g, char geocode[])
{
    while (g != NULL)
    {
        if (strcmp(g->node, geocode) != 0)
        {
            return g;
        }
        g = g->nextr;
    }
    return NULL;
}


ClientG verifyClientGeocode(Graph g, char geocode[])
{
    while (g != NULL)
    {
        ClientG aux = g->clients;
        while (aux != NULL)
        {
            if (strcmp(g->node, geocode) == 0)
            {
                return aux;
            }
            aux = aux->nextr;
        }
        g = g->nextr;
    }
    return NULL;
}

void traverseEdgesDFS(Graph node, char type[], float radius, float currentWeight)
{
    // Traverse the vehicles list of the current node
    VehicleG auxV = node->vehicles;
    while (auxV != NULL)
    {
        // Check if the vehicle type matches the desired type
        if (strcmp(auxV->type, type) == 0)
        { 
            printf("Vehicle: %s -> %d -> %s -> %.2f -> %.2f -> %d;\n",auxV->geocode, auxV->vcode, auxV->type, auxV->batery, auxV->weight, auxV->space);
            
        }
        auxV = auxV->nextr;
    }

    // Traverse the edges of the current node recursively
    Edge aux = node->edges;
    while (aux != NULL)
    {
        printf("\t%s ->", aux->node);
        printf("aqui! -> ");
        float newWeight = currentWeight + aux->weight;
        printf("%.2f -> ", newWeight);
        // Verify if the cumulative weight is within the radius
        if (newWeight <= radius)
        {
            printf("check -> ");
            // Traverse the next node
            Graph nextNode = findNode(node, aux->node); // Helper function to find the next node by its geocode
            if (nextNode != NULL)
            {
                traverseEdgesDFS(nextNode, type, radius, newWeight);
            }
        }
        printf("%s\n", aux->node);
        aux = aux->nextr;
    }
}

void listVehiclesPerRadius(Graph g, char geocode[], char type[], float radius)
{
    // Find the client's node in the graph
    Graph clientNode = findNode(g, geocode);
    printf("\n%s\n\n", clientNode);
    if (clientNode != NULL)
    {
        float weightTotal = 0;

        VehicleG auxV = clientNode->vehicles;
        while (auxV != NULL)
        {
            // Check if the vehicle type matches the type imputed.
            if (strcmp(auxV->type, type) == 0)
            {
                printf("Vehicle: %s -> %d -> %s -> %.2f -> %.2f -> %d;\n",auxV->geocode, auxV->vcode, auxV->type, auxV->batery, auxV->weight, auxV->space);
            }
            auxV = auxV->nextr;
        }

        // Traverse the edges of the client's node
        Edge aux = clientNode->edges;
        while (aux != NULL)
        {
            printf("%s ->", aux->node);
            printf("aqui! -> ");
            weightTotal += aux->weight;
            printf("%.2f -> ", weightTotal);
            // Check if the cumulative weight is within the radius
            if (weightTotal <= radius)
            {
                printf("check -> ");
                Edge nextNode = findNodeNext(clientNode, aux->node);
                printf("%s -> ", nextNode);
                if (nextNode != NULL)
                {
                    printf("pop -> ");
                    traverseEdgesDFS(nextNode, type, radius, weightTotal);
                }
                nextNode = nextNode->nextr;
            }
            printf("%s\n", aux->node);
            weightTotal = 0;
            aux = aux->nextr;
        }

        // Display the vehicles found within the radius and matching the type
        // else
        // {
        //     printf("No vehicles of type %s found within radius %.2f from client's geocode %s.\n", type, radius, geocode);
        // }
    }
    else
    {
        printf("Client not found.\n");
    }
}

//

