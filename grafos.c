#include "grafos.h"

// funcao auxiliar, cria um novo nó de estrada (aresta), recebe o destino e a dist, aloca memória e retorna o ponteiro
Adj* novoNo (int destino, int dist){
    Adj* novo = (Adj*) malloc(sizeof(Adj));
    novo->destino = destino;
    novo->dist = dist;
    novo->proximo = NULL;
    return novo;
}

// inicializa o grafo, zerando o contador e o ponteiro
void inicializarGrafo(Grafo* g) {
    g->numCidades = 0;
    for(int i = 0; i < MAX_CIDADES; i++) {
        g->listaCidades[i].cabeca = NULL; // nenhuma estrada
        g->listaCidades[i].id = -1;
    }
}

// procura a cidade pelo nome que retorna o seu id
int buscaCidade(Grafo* g, char* nome){
    for(int i = 0; i < g->numCidades; i++) {
        if(strcmp(g->listaCidades[i].nome, nome) == 0) {
            return i;
        }
    }
    
    return -1; // caso não encontre a cidade
}

// adiciona uma nova cidade ao vetor (vertice)
int addCidade(Grafo* g, char* nome) {
    if (g->numCidades >= MAX_CIDADES) {
        printf("Erro: Limite de cidades atingido.\n");
        return -1;
    }
    // verifica se ha duplicidade
    if (buscaCidade(g, nome) != -1) { 
        printf("Erro: Cidade ja existe.\n");
        return -1;
    }

    int id = g->numCidades;
    strcpy(g->listaCidades[id].nome, nome);
    g->listaCidades[id].id = id;
    g->listaCidades[id].cabeca = NULL; // inicializa sem estradas
    g->numCidades++;
    return id;
}

// adciona uma estrada (aresta) entre duas cidades
// como é um grafo NÃO DIRECIONADO (estrada de mão dupla), criamos a conexão de A->B e também de B->A
void addEstrada(Grafo* g, char* origem, char* destino, int distancia) {
    int org = buscaCidade(g, origem); 
    int dest = buscaCidade(g, destino);

    if (org == -1 || dest == -1) {
        printf("Erro: Uma ou ambas as cidades nao foram encontradas.\n");
        return;
    }

    // adiciona aresta na lista de 'org' (origem -> destino)
    Adj* novo = novoNo(dest, distancia);
    // inserção no início da lista encadeada
    novo->proximo = g->listaCidades[org].cabeca;
    g->listaCidades[org].cabeca = novo;

    // adiciona aresta na lista de 'dest' (destino -> origem) - reciprocidade
    novo = novoNo(org, distancia);
    novo->proximo = g->listaCidades[dest].cabeca;
    g->listaCidades[dest].cabeca = novo;

    printf("Estrada adicionada: %s <--> %s (%d km)\n", origem, destino, distancia);
}

void listarCidadesEConexoes(Grafo* g) {
    printf("\n--- Mapa de Rotas ---\n");
    for (int i = 0; i < g->numCidades; i++) {
        Adj* temp = g->listaCidades[i].cabeca; 
        printf("Cidade: %s\n", g->listaCidades[i].nome);
        while (temp) {
            printf("  -> Conecta com %s (%d km)\n", g->listaCidades[temp->destino].nome, temp->dist);
            temp = temp->proximo;
        }
    }
}

// salva a estrutura do grafo em um arquivo de texto
void salvarDados(Grafo* g, const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "w");
    if (!file) {
        printf("Erro ao abrir arquivo para salvar.\n");
        return;
    }

    // número de Cidades -> Lista de Nomes -> Lista de Conexões
    fprintf(file, "%d\n", g->numCidades);

    for (int i = 0; i < g->numCidades; i++) {
        fprintf(file, "%s\n", g->listaCidades[i].nome);
    }

    for (int i = 0; i < g->numCidades; i++) {
        Adj* temp = g->listaCidades[i].cabeca; 
        while (temp) {
            // salva apenas se ID origem < ID destino para não duplicar no arquivo
            // salva (0, 1) mas não salva (1, 0)
            if (i < temp->destino) {
                fprintf(file, "%d %d %d\n", i, temp->destino, temp->dist);
            }
            temp = temp->proximo;
        }
    }

    fclose(file);
    printf("Dados salvos em '%s'.\n", nomeArquivo);
}

void carregarDados(Grafo* g, const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Arquivo nao encontrado. Iniciando novo grafo.\n");
        return;
    }

    inicializarGrafo(g);
    int numCidadesArq;
    if (fscanf(file, "%d", &numCidadesArq) != 1) return;

    // recupera nomes
    char nomeBuffer[50];
    for (int i = 0; i < numCidadesArq; i++) {
        fscanf(file, "%s", nomeBuffer);
        addCidade(g, nomeBuffer); 
    }

    // recupera conexões
    int u, v, dist;
    while (fscanf(file, "%d %d %d", &u, &v, &dist) == 3) {
        // reconstrói as listas de adjacência manualmente
        Adj* novo = novoNo(v, dist); 
        novo->proximo = g->listaCidades[u].cabeca;
        g->listaCidades[u].cabeca = novo;

        novo = novoNo(u, dist);
        novo->proximo = g->listaCidades[v].cabeca;
        g->listaCidades[v].cabeca = novo;
    }

    fclose(file);
    printf("Dados carregados com sucesso!\n");
}

void liberarMemoria(Grafo* g) {
    for (int i = 0; i < g->numCidades; i++) {
        Adj* temp = g->listaCidades[i].cabeca; 
        while (temp) {
            Adj* prox = temp->proximo;
            free(temp); // libera cada nó da lista encadeada
            temp = prox;
        }
        g->listaCidades[i].cabeca = NULL;
    }
}
