#include "dijkstra.h"

// algoritimo de dijkstra
// calcula o caminho da origem ao destino
// usa um vetor de distâncias e um vetor 'anterior' para reconstruir a rota
void dijkstra(Grafo* g, char* origem, char* destino) {
    int inicio = buscaCidade(g, origem); 
    int fim = buscaCidade(g, destino);  

    if (inicio == -1 || fim == -1) {
        printf("Cidades invalidas.\n");
        return;
    }

    int distancia[MAX_CIDADES]; // menor distância conhecida até cada cidade
    int anterior[MAX_CIDADES];  // armazena quem é o pai no caminho (para refazer a rota)
    int visitado[MAX_CIDADES];  // marca se já processamos a cidade

    // inicialização
    for (int i = 0; i < g->numCidades; i++) {
        distancia[i] = INFINITO; // assume que todas estão inalcançáveis
        anterior[i] = -1;
        visitado[i] = 0;
    }

    distancia[inicio] = 0; // distância da origem para ela mesma é 0

    // loop principal (processa todas as cidades)
    for (int count = 0; count < g->numCidades - 1; count++) {
        // encontrar a cidade não visitada com a MENOR distância atual
        int min = INFINITO, cidAtual = -1;

        for (int cidVis = 0; cidVis < g->numCidades; cidVis++) {
            if (visitado[cidVis] == 0 && distancia[cidVis] <= min) {
                min = distancia[cidVis];
                cidAtual = cidVis;
            }
        }

        // se não houver caminho ou acabarem as conexões
        if (cidAtual == -1 || distancia[cidAtual] == INFINITO) break;

        visitado[cidAtual] = 1; // marca cidade 'cidAtual' como processada

        // relaxamento (verifica vizinhos de 'cidAtual')
        Adj* temp = g->listaCidades[cidAtual].cabeca; 
        while (temp) {
            int cidViz = temp->destino;
            // se achar um caminho mais curto passando por 'cidAtual', atualiza
            if (!visitado[cidViz] && distancia[cidAtual] != INFINITO && 
                distancia[cidAtual] + temp->dist < distancia[cidViz]) {
                
                distancia[cidViz] = distancia[cidAtual] + temp->dist; // nova menor distância
                anterior[cidViz] = cidAtual; // salva que viemos de 'cidAtual'
            }
            temp = temp->proximo;
        }
    }

    // exibe resultado
    if (distancia[fim] == INFINITO) {
        printf("\nNao ha caminho entre %s e %s.\n", origem, destino);
    } else {
        printf("\n--- Melhor Rota Encontrada ---\n");
        printf("Custo Total: %d km\n", distancia[fim]);
        printf("Trajeto: ");
        
        // reconstrói o caminho de trás para frente usando o vetor 'anterior'
        int caminho[MAX_CIDADES];
        int cont = 0;
        int atual = fim;
        while (atual != -1) {
            caminho[cont++] = atual;
            atual = anterior[atual];
        }

        // imprimir do início ao fim
        for (int i = cont - 1; i >= 0; i--) {
            printf("%s", g->listaCidades[caminho[i]].nome);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}
