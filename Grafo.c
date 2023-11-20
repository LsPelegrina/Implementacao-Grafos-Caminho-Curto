#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

#define true 1
#define false 0

typedef int bool; // Define um tipo booleano como um inteiro
typedef int TIPOPESO; // Define um tipo para o peso das arestas como um inteiro

// Estrutura para representar uma adjacência em um grafo
typedef struct adjacencia{
    int vertice; // Vértice de destino
    TIPOPESO peso; // Peso associado à aresta que leva ao vértice
    struct adjacencia *prox; // Próximo elemento da lista de adjacências
}ADJACENCIA;

// Estrutura para representar um vértice em um grafo
typedef struct vertice{
    ADJACENCIA *cab; // Cabeça da lista de adjacências
}VERTICE;

// Estrutura para representar um grafo
typedef struct grafo{
    int vertices; // Número total de vértices
    int arestas; // Número total de arestas
    VERTICE *adj; // Arranjo de vértices da estrutura
}GRAFO;

// Função para criar um grafo com v vértices
GRAFO *criaGrafo (int v){
    int i;

    // Aloca memória para o grafo
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(v*sizeof(VERTICE));

    // Inicializa a lista de adjacências de cada vértice
    for(i=0; i<v; i++){
        g->adj[i].cab=NULL;
    }
    return (g);
}

// Função para criar uma adjacência com um vértice v e um peso
ADJACENCIA *criadAdj(int v, int peso){
    // Aloca espaço para a adjacência
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice =v; // Vértice alvo da adjacência
    temp->peso = peso; // Peso da aresta
    temp->prox = NULL; 
    return(temp); // Retorna o endereço da adjacência
}

// Função para criar uma aresta de vi a vf com peso p em um grafo gr
bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p){
    // Validações se o grafo existe e se os vértices são válidos
    if(!gr) return(false);
    if((vf<0)||(vf>=gr->vertices))return(false);
    if((vi<0)||(vf>=gr->vertices))return(false);

    // Cria a adjacência com o vértice final e o peso
    ADJACENCIA *novo = criadAdj(vf,p);

    // Coloca a adjacência na lista do vértice inicial
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab=novo;

    // Atualiza o número de arestas no grafo
    gr->arestas++;
    return (true);
}

// Função para imprimir um grafo
void imprime(GRAFO *gr){
    printf("Vertices..: %d. Arestas..: %d \n",gr->vertices,gr->arestas);
    int i;

    // Percorre cada vértice do grafo
    for(i = 0; i<gr->vertices; i++){
        printf("v%d:",i+1);

        // Percorre a lista de adjacências do vértice
        ADJACENCIA *ad = gr->adj[i].cab;
        while (ad){
            printf("v%d(%d) ",ad->vertice+1,ad->peso);
            ad=ad->prox;
        }
        printf("\n");
    }
}

// Função para imprimir a matriz de adjacência de um grafo
void Matriz(GRAFO *gr) {
    printf("\n\nMatriz de Adjacencia:\n");

    // Percorre cada vértice do grafo
    for (int i = 0; i < gr->vertices; i++) {
        for (int j = 0; j < gr->vertices; j++) {
            int adjacencia = 0;

            // Percorre a lista de adjacências do vértice
            ADJACENCIA *ad = gr->adj[i].cab;
            while (ad) {
                if (ad->vertice == j) {
                    adjacencia = ad->peso;
                }
                ad = ad->prox;
            }
            printf("%d\t", adjacencia);
        }
        printf("\n");
    }
}

int** geraMatriz(GRAFO* gr) {
    int** Mat = (int**) malloc(gr->vertices * sizeof(int*));
    for (int i = 0; i < gr->vertices; i++) {
        Mat[i] = (int*) malloc(gr->vertices * sizeof(int));
        for (int j = 0; j < gr->vertices; j++) {
            Mat[i][j] = 0; // Inicializa a matriz com 0
        }
    }

    for (int i = 0; i < gr->vertices; i++) {
        ADJACENCIA* ad = gr->adj[i].cab;
        while (ad) {
            Mat[i][ad->vertice] = ad->peso; // Atribui o peso à posição correspondente na matriz
            ad = ad->prox;
        }
    }

    return Mat;
}

void caminho_mais_curto(GRAFO *gr, int origem, int destino){
    if (gr == NULL) {
        printf("O grafo não existe.\n");
        return;
    }
    int i, vert, k, NovaDist, min;
    int *M, *L, *A, *caminho;
    M = (int*) malloc(gr->vertices*sizeof(int)); // Vetor de marcação de vértices visitados
    L = (int*) malloc(gr->vertices*sizeof(int)); // Vetor de distâncias
    A = (int*) malloc(gr->vertices*sizeof(int)); // Vetor de antecessores
    caminho = (int*) malloc(gr->vertices*3*sizeof(int)); // vetor auxiliar para armazenar o caminho
    
    int** Mat = (int**) malloc(gr->vertices*sizeof(int*)); // Matriz do grafo
    Mat = geraMatriz(gr);
    
    // Inicializando as variaveis
    for(i=0;i<gr->vertices;i++){
        M[i] = 0; // False -> determina se o vertice ja foi visitado
        L[i] = 300000; // Infinito -> determina o comprimento do caminho mais curto
        A[i] = -1; // Determina o caminho mais curto entre origem e destino
    }
    vert = origem;
    L[vert] = 0;
    while (vert != destino && vert != -1){ //Não terminou ou caminho inexistente
        for(i=0;i<gr->vertices;i++) //Percorre vertices adjacentes de vert
            if(Mat[vert][i] != 0 && M[i] == 0){ //Se aresta existe e ela não foi visitada
                NovaDist = L[vert] + Mat[vert][i];
                if(NovaDist < L[i]){
                    L[i] = NovaDist;
                    A[i] = vert;
                }
            }
        M[vert] = 1;
        min = 300000;
        vert = -1;
        
        for(i=0;i<gr->vertices;i++)
            if(M[i]==0 && L[i] < min){
                min = L[i];
                vert = i;
            }
        
    }

    if(vert == destino){
        printf("O caminho mais curto entre v%d e v%d, tem comprimento: %d\nCaminho: ", origem, destino, L[destino]);
        caminho[0] = destino;
        k = 1;
        while(vert != origem){
            caminho[k] = A[vert];
            vert = A[vert];
            k++;
        }
        for(i=k-1;i>=0;i--){
            printf("%d", caminho[i]);
            if(i > 0)
                printf(" -> ");
        }
    }else
        printf("Nao existe caminho entre v%d e v%d", origem, destino);
}



