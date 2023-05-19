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

/**
 * @brief Create a Node object
 * 
 * @param g 
 * @param nodeId 
 * @return int 
 */
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

/**
 * @brief Verify is the node given exists
 * 
 * @param g 
 * @param node 
 * @return int 
 */
int existNode(Graph g, char node[])
{
    while (g != NULL)
    {
        if (strcmp(g->node, node) == 0) return(1);
    else g = g->nextr;
    }
    return(0);
}

/**
 * @brief Create a Edge object
 * 
 * @param g 
 * @param nodeOrigin 
 * @param nodeDestiny 
 * @param weight 
 * @return int 
 */
int createEdge(Graph g, char nodeOrigin[], char nodeDestiny[], float weight)
{
    Edge new;
    if (existNode(g, nodeOrigin) && existNode(g, nodeDestiny))
    {
        while(strcmp(g->node, nodeOrigin) !=0 ) g = g->nextr;
        new = malloc(sizeof(struct regist2));
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

/**
 * @brief List all the edges of the graph
 * 
 * @param g 
 * @param node 
 */
void listEdges(Graph g, char node[])
{
    Edge aux;
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

/**
 * @brief Insert a vehicle giving the vehicle geocode in the node of graph with the same geocode 
 * 
 * @param g 
 * @param geocode 
 * @param vehicleCode 
 * @param tp 
 * @param bat 
 * @param weight 
 * @return int 
 */
int insertVehicleGraph(Graph g, char geocode[], int vehicleCode, char tp[], float bat, float weight, float space)
{
    while ((g != NULL) && (strcmp(g->node, geocode) != 0))
	g = g->nextr;
    if (g == NULL) return(0);
    else 
        {
            VehicleG new = malloc(sizeof(struct regist3));
            new->vcode = vehicleCode;
            strcpy(new->geocode, geocode); 
            strcpy(new->type, tp); 
            new->batery = bat;
            new->weight = weight;
            new->space = space;
            new->nextr = g->vehicles;
            g->vehicles = new;
            return(1);	 
        }
}

/**
 * @brief Insert a client giving the client geocode in the node of graph with the same geocode 
 * 
 * @param g 
 * @param geocode 
 * @param clientCode 
 * @return int 
 */
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

/**
 * @brief Write all the nodes from the graph
 * 
 * @param g 
 */
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

/**
 * @brief Write the all the edges from all the Nodes of the graph
 * 
 * @param g 
 */
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

