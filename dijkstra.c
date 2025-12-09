#include "dijkstra.h"

// algoritimo de dijkstra
// calcula o caminho da origem ao destino
// usa um vetor de distâncias e um vetor 'anterior' para reconstruir a rota
void dijkstra(Grafo* g, char* origemStr, char* destinoStr) {
    int inicio = buscaCidade(g, origemStr); 
    int fim = buscaCidade(g, destinoStr);  

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
        int min = INFINITO, u = -1;

        for (int v = 0; v < g->numCidades; v++) {
            if (visitado[v] == 0 && distancia[v] <= min) {
                min = distancia[v];
                u = v;
            }
        }

        // se não houver caminho ou acabarem as conexões
        if (u == -1 || distancia[u] == INFINITO) break;

        visitado[u] = 1; // marca cidade 'u' como processada

        // relaxamento (verifica vizinhos de 'u')
        Adj* temp = g->listaCidades[u].cabeca; 
        while (temp) {
            int v = temp->destino;
            // se achar um caminho mais curto passando por 'u', atualiza
            if (!visitado[v] && distancia[u] != INFINITO && 
                distancia[u] + temp->dist < distancia[v]) {
                
                distancia[v] = distancia[u] + temp->dist; // nova menor distância
                anterior[v] = u; // salva que viemos de 'u'
            }
            temp = temp->proximo;
        }
    }

    // exibe resultado
    if (distancia[fim] == INFINITO) {
        printf("\nNao ha caminho entre %s e %s.\n", origemStr, destinoStr);
    } else {
        printf("\n--- Melhor Rota Encontrada ---\n");
        printf("Custo Total: %d km\n", distancia[fim]);
        printf("Trajeto: ");
        
        // reconstrói o caminho de trás para frente usando o vetor 'anterior'
        int caminho[MAX_CIDADES];
        int cont = 0;
        int curr = fim;
        while (curr != -1) {
            caminho[cont++] = curr;
            curr = anterior[curr];
        }

        // imprimir do início ao fim
        for (int i = cont - 1; i >= 0; i--) {
            printf("%s", g->listaCidades[caminho[i]].nome);
            if (i > 0) printf(" -> ");
        }
        printf("\n");
    }
}