#include <stdio.h>
#include <stdlib.h>
#include "Grafo.c"

int main() {
    GRAFO *gr1 = criaGrafo(6); //Cria um grafo com 6 vértices

    // Adiciona as arestas ao grafo
    criaAresta(gr1, 0, 1, 1);
    criaAresta(gr1, 0, 2, 4);
    criaAresta(gr1, 1, 0, 1);
    criaAresta(gr1, 1, 2, 4);
    criaAresta(gr1, 1, 3, 2);
    criaAresta(gr1, 1, 4, 7);
    criaAresta(gr1, 2, 0, 4);
    criaAresta(gr1, 2, 1, 4);
    criaAresta(gr1, 2, 3, 3);
    criaAresta(gr1, 2, 4, 5);
    criaAresta(gr1, 3, 1, 2);
    criaAresta(gr1, 3, 2, 3);
    criaAresta(gr1, 3, 4, 4);
    criaAresta(gr1, 3, 5, 6);
    criaAresta(gr1, 4, 1, 7);
    criaAresta(gr1, 4, 2, 5);
    criaAresta(gr1, 4, 3, 4);
    criaAresta(gr1, 4, 5, 7);
    criaAresta(gr1, 5, 3, 6);
    criaAresta(gr1, 5, 4, 7);

    // Imprime a lista de adjacencia
    imprime(gr1);

    // Imprime a matriz de adjacência do grafo
    Matriz(gr1);
    printf("\n");

    // Calcula o caminho mais curto do vértice 0 ao vértice 5
    caminho_mais_curto(gr1, 0, 5);

    return 0;
}