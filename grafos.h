#ifndef GRAFOS_H
#define GRAFOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> 

#define MAX_CIDADES 100
#define INFINITO INT_MAX //inicializar distancias no dijkstra(infinito)

// estrutura de adjacencia (aresta), uma estrada saindo de uma cidade
// é uma lista encadeada, cada estrada aponta para a próxima estrada da mesma cidade
typedef struct Adj {
    int destino;         // cidade para onde esta estrada vai
    int dist;            // distância em km 
    struct Adj* proximo; // ponteiro para a próxima estrada conectada a esta mesma cidade de origem
} Adj;


// estrutura da cidade (vertice), armazena os dados da cidade e o início da lista de estradas que saem dela
typedef struct {
    char nome[50];  // nome da cidade 
    int id;         // id de identificação
    Adj* cabeca;    // ponteiro para a primeira estrada (cabeça da lista encadeada)
} Cidade;


//estrutura do grafo, tem o vetor de cidades e o contador de quantas cidades foram cadastradas
typedef struct {
    Cidade listaCidades[MAX_CIDADES]; // vetor para armazenar as cidades
    int numCidades;                   // contator de cidades
} Grafo;

// funcoes para o .c
void inicializarGrafo(Grafo* g);
int buscaCidade(Grafo* g, char* nome); 
int addCidade(Grafo* g, char* nome);
void addEstrada(Grafo* g, char* origem, char* destino, int distancia);
void listarCidadesEConexoes(Grafo* g);

// salvar os dados
void salvarDados(Grafo* g, const char* nomeArquivo);
void carregarDados(Grafo* g, const char* nomeArquivo);

// liberar memória
void liberarMemoria(Grafo* g);

#endif