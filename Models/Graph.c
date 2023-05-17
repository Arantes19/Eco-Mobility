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
int criarVertice(Graph *g, char novoId[])
{
    Graph new = malloc(sizeof(struct registo1));
    if (new!=NULL)
    {
        strcpy(new->vertice,novoId);
        new->vehicles = NULL;
        new->nextr = *g;
        *g = new;
        return(1);
    }
    else return(0);
}

// Devolve 1 se o vertice existe no grafo ou 0 caso contrário
int existeVertice(Graph g, char vertice[])
{
    while (g!=NULL)
    {
        if (strcmp(g->vertice,vertice)==0) return(1);
    else g=g->nextr;
    }
    return(0);
}

// Criar uma nova aresta
// Devolve 1 em caso de sucesso ou 0 caso contrário
int criarAresta(Graph g, char vOrigem[], char vDestino[], float weight)
{
    Adjacent new;
    if (existeVertice(g,vOrigem) && existeVertice(g,vDestino))
    {
        while(strcmp(g->vertice,vOrigem)!=0) g=g->nextr;
        new = malloc(sizeof(struct registo1));
        if (new!=NULL)
	    {
            strcpy(new->vertice,vDestino);
            new->weight = weight;
            new->nextr=g->adjacents;
            g->adjacents=new;
            return(1);
	    }
    else return(0);
    }
    else return(0);
}

// Listar os vértices adjacentes 
void listarAdjacentes(Graph g, char vertice[])
{
    Adjacent aux;
    if (existeVertice(g,vertice))
    {
        while (strcmp(g->vertice,vertice)!=0) g=g->nextr;
        aux = g->adjacents;
        while (aux!=NULL) 
        {
            printf("Adjacente:%s Peso:%.2f\n", aux->vertice, aux->weight);
            aux=aux->nextr;
        }
    }
}

// Inserir meio de transporte na localização com geocódigo passado por parâmetro
// Devolve 1 em caso de sucesso ou 0 caso contrário
int inserirMeio(Graph g, char geocodigo[], int codigoMeio)
{
    while ((g!=NULL)&&(strcmp(g->vertice,geocodigo)!=0))
	g=g->nextr;
    if (g==NULL) return(0);
    else 
        {
            Vehicles new = malloc(sizeof(struct regist3));
            new->code = codigoMeio;
            new->nextr = g->vehicles;
            g->vehicles = new;
            return(1);	 
      }
}

// Listar os códigos dos meios de transporte presente numa determinada localização passada por parâmetro
void listarMeios(Graph g, char geocodigo[])
{
 while ((g!=NULL)&&(strcmp(g->vertice,geocodigo)!=0))
	g=g->nextr;
    if (g!=NULL) 
    {
        Vehicles aux=g->vehicles;
        if (aux==NULL) printf("sem meios de transporte\n");
        else while(aux!=NULL)
        {
            printf("Codigo meio: %d\n", aux->code);
            aux = aux->nextr;
        }
    }
    else printf("geocodigo inexistente\n");
}
