/**
 * @file graph.h
 * @author Francisco Arantes (a23504@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#define TAM 250

typedef struct regist4
{
    int ccode;
    char geocode[TAM];
    struct regist4 * nextr; 
} *ClientG;

typedef struct regist3
{
    int vcode;
    char geocode[TAM];
    char type[TAM];
    float batery;
    float weight;
    int state;
    float space;
    struct regist3 * nextr; 
} *VehicleG;
      
// Representação de um grafo orientado e pesado
typedef struct regist2
{
    char node[TAM]; // geocódigo what3words
    float weight;
    struct regist1 *nodes;
    VehicleG* vehicles;
    struct regist2 * nextr; 
} *Edge;
         
typedef struct regist1 
{
    char node[TAM]; // geocódigo what3words
    struct regist2 *edges;
    VehicleG vehicles; // Lista ligada com os códigos dos meios de transporte existente neste geocódigo
    ClientG clients;
    int state;
    struct regist1 *nextr;  
} *Graph;           
   
int createNode(Graph* g, char nodeId[]);
int existNode(Graph g, char node[]);
int createEdge(Graph g, char nodeOrigin[], char nodeDestiny[], float weight);
void listEdges(Graph g);
void listNodes(Graph g);
void listVehiclesG(Graph g);
void listClientsG(Graph g);
int insertVehicleGraph(Graph g, char geocode[], int vehicleCode, char tp[], float bat, float weight, float space);
int insertClientGraph(Graph g, char geocode[], int clientCode);

//Leitura e Escrita 
void saveNodes(Graph g);
void saveVehiclesGraph(Graph g);
void saveClientsGraph(Graph g);
void saveEdgeGraph(Graph g);
void readNodes(Graph* g);
void readVehiclesGraph(Graph* g);
void readClientsGraph(Graph* g);
void readEdges(Graph* g);

Graph findNode(Graph g, char geocode[]);
ClientG verifyClientGeocode(Graph g, char geocode[]);
void traverseEdgesDFS(Graph node, char type[], float radius, float currentWeight, Graph g);
void listVehiclesPerRadius(Graph g, char geocode[], char type[], float radius);
void resetState(Graph g);