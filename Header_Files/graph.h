/**
 * @file graph.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#define TAM 100

typedef struct regist3
{ int code;
  struct regist3 * nextr;
} * Vehicles;

// Representação de um grafo orientado e pesado
typedef struct regist2
{
    char vertice[TAM]; // geocódigo what3words
    float weight;
    struct regist2 * nextr; 
} * Adjacent;  

typedef struct registo1 
{
    char vertice[TAM]; // geocódigo what3words
    Adjacent adjacents;
    Vehicles vehicles; // Lista ligada com os códigos dos meios de transporte existente
	      // neste geocódigo
    struct regist1 * nextr;
} * Graph;  