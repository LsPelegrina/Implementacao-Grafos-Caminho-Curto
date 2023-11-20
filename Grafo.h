#ifndef GRAFO_H
#define GRAFO_H

// Estruturas
typedef struct adjacencia ADJACENCIA; // Estrutura para representar uma adjacência em um grafo
typedef struct vertice VERTICE; // Estrutura para representar um vértice em um grafo
typedef struct grafo GRAFO; // Estrutura para representar um grafo
typedef int TIPOPESO; // Tipo de dado para representar o peso de uma aresta
typedef int bool; // Tipo de dado para representar um valor booleano

// Funções

// Função para criar um grafo com v vértices
GRAFO *criaGrafo (int v);

// Função para criar uma adjacência com um vértice v e um peso
ADJACENCIA *criadAdj(int v, int peso);

// Função para criar uma aresta de vi a vf com peso p em um grafo gr
bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p);

// Função para imprimir um grafo
void imprime(GRAFO *gr);

// Função para imprimir a matriz de adjacência de um grafo
void Matriz(GRAFO *gr);

// Função para gerar a matriz de adjacência de um grafo
int** geraMatriz(GRAFO* gr);

// Função para calcular o caminho mais curto entre dois vértices em um grafo
void caminho_mais_curto(GRAFO *gr, int origem, int destino);
#endif