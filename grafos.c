#include <stdio.h>
#include "grafos.h"
#include "dijkstra.h"
#include "log.h"

void menu() {
	printf("\n=== SISTEMA GPS ===\n");
	printf("1. Adicionar Cidade\n");
	printf("2. Adicionar Estrada\n");
	printf("3. Listar Cidades e Estradas\n");
	printf("4. Calcular Menor Rota\n");
	printf("5. Salvar Dados\n");
	printf("6. Carregar Dados\n");
	printf("0. Sair\n");
	printf("Escolha: ");
}

int main() {
	Grafo grafo;
	inicializarGrafo(&grafo); // prepara a estrutura

	int opcao;
	char nome1[50], nome2[50];
	int dist;
	int alterado = 0;
	FILE *fp = fopen("sistema.log", "a");
	char logMsg[100];

	carregarDados(&grafo, "dados_gps.txt");

	do {
		menu();
		scanf("%d", &opcao);

		switch(opcao) {
		case 1:
			printf("Nome da cidade: ");
			scanf("%s", nome1);
			addCidade(&grafo, nome1);
			sprintf(logMsg,"Cidade adicionada: %s", nome1);
			registrarLog(logMsg);
			alterado = 1;
			break;
		case 2:
			printf("Origem: ");
			scanf("%s", nome1);
			printf("Destino: ");
			scanf("%s", nome2);
			printf("Distancia (km): ");
			scanf("%d", &dist);
			addEstrada(&grafo, nome1, nome2, dist);
			sprintf(logMsg,"Estrada criada: %s -> %s (%d km)", nome1, nome2, dist);
			registrarLog(logMsg);
			alterado = 1;
			break;
		case 3:
			listarCidadesEConexoes(&grafo);
			sprintf(logMsg,"Listagem de cidades e estradas exibida!");
			registrarLog(logMsg);
			break;
		case 4:
			printf("Ponto de Partida: ");
			scanf("%s", nome1);
			printf("Destino Final: ");
			scanf("%s", nome2);
			dijkstra(&grafo, nome1, nome2);
			sprintf(logMsg,"Menor rota calculada: %s -> %s", nome1, nome2);
			registrarLog(logMsg);
			break;
		case 5:
			salvarDados(&grafo, "dados_gps.txt");
			
			sprintf(logMsg,"Dados Salvos!");
			registrarLog(logMsg);
			alterado = 0;
			break;
		case 6:
			carregarDados(&grafo, "dados_gps.txt");
			sprintf(logMsg,"Dados Carregados!");
			registrarLog(logMsg);
			break;
		case 0:
			if (alterado == 1) {
				int escolha;
				printf("\nVocê tem alteracões não salvas!\n");
				printf("1. Salvar e sair\n");
				printf("2. Sair sem salvar\n");
				printf("Escolha: ");
				scanf("%d", &escolha);

				if (escolha == 1) {
					salvarDados(&grafo, "dados_gps.txt");
					sprintf(logMsg,"Dados salvos!");
					registrarLog(logMsg);
					printf("Dados salvos. Encerrando...\n");
				} else {
				    
					sprintf(logMsg,"Encerrado sem salvar!\n");
					registrarLog(logMsg);
					printf("Encerrando sem salvar...\n");
				}
			} else {
			    sprintf(logMsg,"Encerrado...\n");
					registrarLog(logMsg);
				printf("Encerrando...\n");
			}
			break;
		default:
			printf("Opcao invalida!\n");
		}
	} while (opcao != 0);

	liberarMemoria(&grafo);
	return 0;
}