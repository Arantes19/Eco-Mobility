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

int createNode(Graph *g, char node[])
{
    Graph new = malloc(sizeof(struct regist1));
    if (new != NULL)
    {
        strcpy(new->node, node);
        new->vehicles = NULL;
        new->clients = NULL;   
        new->edges = NULL;
        new->state = 0;
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
    if (fp != NULL)
    {
        Graph node = g;

        while (node != NULL) {
            fprintf(fp, "%s\n", node->node);
            node = node->nextr;
        }

        fclose(fp);
    } else {
        printf("Erro opening the file!!\n");
    }
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
        VehicleG aux = g->vehicles;
        while (aux != NULL)
        {
            fprintf(fp, "%s ", g->node);
            fprintf(fp, "%d %s %f %f %f\n", aux->vcode, aux->type, aux->batery, aux->weight, aux->space);
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
        ClientG aux = g->clients;
        while (aux != NULL)
        {
            fprintf(fp, "%s ", g->node);
            fprintf(fp, "%d\n", aux->ccode);
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
        Edge aux = g->edges; 
        while (aux != NULL)
        {
            fprintf(fp, "%s ", g->node);
            fprintf(fp, "%s %f\n", aux->node, aux->weight);
            aux = aux->nextr;
        }
        g = g->nextr;
    }
    fclose(fp);
}

void readNodes(Graph* g)
{
    FILE* fp = fopen("Text_Files/nodes_graph.txt", "r");
    char node[250];

    if(fp != NULL)
    {
        while(fgets(node, sizeof(node), fp) != NULL)
        {
            node[strcspn(node, "\n")] = '\0';
            createNode(g, node);
        }
        fclose(fp);
    }
    else printf("Error opening the file");
}

void readVehiclesGraph(Graph* g)
{
    FILE* fp;
    int vcode;
    float bat, space, weight;
    char node[250], type[100], line[250];

    fp = fopen("Text_Files/vehicles_graph.txt", "r");
    if(fp != NULL)
    {
       while(fgets(line, sizeof(line), fp) != NULL)
        {
            if(sscanf(line, "%s %d %s %f %f %f", node, &vcode, type, &bat, &weight, &space) == 6)
            insertVehicleGraph(*g, node, vcode, type, bat, weight, space);
        }
        fclose(fp);
    }
    else printf("Error opening the file");
}

void readClientsGraph(Graph* g)
{
    FILE* fp;
    int ccode;
    char node[250], line[250];

    fp = fopen("Text_Files/clients_graph.txt", "r");
    if(fp != NULL)
    {
        while(fgets(line, sizeof(line), fp) != NULL)
        {
            if(sscanf(line, "%s %d", node, &ccode) == 2);
            insertClientGraph(*g, node, ccode);
        }
        fclose(fp);
    }
    else printf("Error opening the file");
}

void readEdges(Graph* g)
{
    FILE* fp;
    char nodeO[250], nodeD[250], line[250];
    float weight;

    fp = fopen("Text_Files/edge_graph.txt", "r");
    if(fp != NULL)
    {
        while(fgets(line, sizeof(line), fp) != NULL)
        {
            if(sscanf(line, "%s %s %f", nodeO, nodeD, &weight) == 3);
            createEdge(*g, nodeO, nodeD, weight);
        }
        fclose(fp);
    }
    else printf("Error opening the file");
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

Graph findNode(Graph g, char geocode[])
{
    while (g != NULL)
    {
        if (strcmp(g->node, geocode) == 0 && (g->state==0))
        {
            return g;
        }
        g = g->nextr;
    }
    return NULL;
}

void traverseEdgesDFS(Graph node, char type[], float radius, float currentWeight, Graph g)
{
    if((node->state == 1) || (node->state == 2) || currentWeight>radius) return;                //state 0 - Não visitado
    node->state = 1;                                                                            //state 1-  Visitado mas caminho não aceite
   VehicleG vehicles = node->vehicles;                                                          //state 2 - Visitado 
   while(vehicles != NULL)
   {
        if(strcmp(vehicles->type, type) == 0 && currentWeight<=radius)
        {
            node->state = 2;
            printf("Vehicle: %s -> %d -> %s -> %.2f -> %.2f -> %d;\n",
                vehicles->geocode, vehicles->vcode, vehicles->type, 
                vehicles->batery, vehicles->weight, vehicles->space);   
        }
        vehicles = vehicles->nextr;
   }
   Edge edges = node->edges;
   while(edges != NULL)
   {
        printf("\t-> %s", edges->node);
        Graph nextNode = findNode(g, edges->node);
        if(nextNode != NULL)
        {
            float newWeight = currentWeight+edges->weight;
            printf(" -> %f\n", newWeight);
            traverseEdgesDFS(nextNode, type, radius, newWeight, g);
        }
        edges = edges->nextr;
   }
   if(node->state == 1) node->state = 0;
}

void listVehiclesPerRadius(Graph g, char geocode[], char type[], float radius)
{
    if (g != NULL)
    {
        Graph clientNode = findNode(g, geocode);
        if(clientNode == NULL) 
        {
            printf("Geocode doesn't exists in graph!!");
            return;
        }
        traverseEdgesDFS(clientNode, type, radius, 0.0, g);
    }
    else{
        printf("Nodes list empty");
    }
}
