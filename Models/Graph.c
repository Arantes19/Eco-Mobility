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

// Criar um novo vértice
// Devolve 1 em caso de sucesso ou 0 caso contrário
int createNode(Graph* g, char novoId[])
{
    Graph new = malloc(sizeof(struct regist1));
    if (new != NULL)
    {
        strcpy(new->node, novoId);
        new->vehicles = NULL;
        new->nextr = *g;
        *g = new;
        return 1;
    }
    else
    {
        return 0;
    }
}

// Devolve 1 se o vertice existe no grafo ou 0 caso contrário
int existNode(Graph g, char node[])
{
    while (g != NULL)
    {
        if (strcmp(g->node, node) == 0) return(1);
    else g = g->nextr;
    }
    return(0);
}

// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
int createEdge(Graph g, char nodeOrigin[], char nodeDestiny[], float weight)
{
    Edge new;
    if (existNode(g, nodeOrigin) && existNode(g, nodeDestiny))
    {
        while(strcmp(g->node, nodeOrigin)!=0) g = g->nextr;
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

// Listar os vértices adjacentes 
void listAdjacents(Graph g, char node[])
{
    Edge aux;
    if (existNode(g, node))
    {
        while (strcmp(g->node,node)!= 0) g = g->nextr;
        aux = g->edges;
        while (aux != NULL) 
        {
            printf("Adjacente:%s Peso:%.2f\n", aux->node, aux->weight);
            aux = aux->nextr;
        }
    }
}

// Inserir meio de transporte na localização com geocódigo passado por parâmetro
// Devolve 1 em caso de sucesso ou 0 caso contrário
int insertVehicleGraph(Graph g, char geocode[], int vehicleCode)
{
    while ((g!=NULL)&&(strcmp(g->node, geocode)!=0))
	g = g->nextr;
    if (g == NULL) return(0);
    else 
        {
            Vehicles new = malloc(sizeof(struct regist3));
            new->code = vehicleCode;
            new->nextr = g->vehicles;
            g->vehicles = new;
            return(1);	 
      }
}

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listVehiclesGraph(Graph g, char geocode[])
{
 while ((g != NULL) && (strcmp(g->node, geocode) !=0 ))
	g = g->nextr;
    if (g != NULL) 
    {
        Vehicles aux = g->vehicles;
        if (aux == NULL) printf("sem meios de transporte\n");
        else while(aux != NULL)
        {
            printf("Codigo meio: %d\n", aux->code);
            aux = aux->nextr;
        }
    }
    else printf("geocodigo inexistente\n");
}
