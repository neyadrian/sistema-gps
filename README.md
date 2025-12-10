# 🗺️ Sistema de GPS em C (Grafos e Dijkstra)

![C](https://img.shields.io/badge/language-C-blue.svg)
![Status](https://img.shields.io/badge/status-Finalizado-success.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

Um sistema de navegação via terminal desenvolvido em C que utiliza **Grafos** e o **Algoritmo de Dijkstra** para calcular a rota mais curta entre cidades.

O projeto foi estruturado de forma modular e conta com um sistema de **logs automáticos** para registro de atividades.

## 📋 Funcionalidades

- **Gerenciamento de Grafo:**
  - Adicionar Cidades (Vértices).
  - Adicionar Estradas com distâncias em Km (Arestas não direcionadas).
  - Listar todas as conexões existentes.
- **Cálculo de Rotas:**
  - Encontra o caminho mais curto entre dois pontos usando o Algoritmo de Dijkstra.
  - Exibe a distância total e o trajeto passo a passo.
- **Persistência de Dados:**
  - Salvar o mapa completo em arquivo de texto (`dados_gps.txt`).
  - Carregar dados automaticamente ou manualmente.
- **Sistema de Logs:**
  - Registra automaticamente as operações realizadas (erros, adições, cálculos) com data e hora em `logs.txt`.

## 🛠️ Tecnologias e Conceitos

Este projeto aplica conceitos fundamentais de Ciência da Computação:

- **Linguagem C:** Uso de ponteiros, alocação dinâmica, manipulação de arquivos e biblioteca `time.h`.
- **Estrutura de Dados:**
  - **Lista de Adjacência:** Otimização de memória para grafos esparsos.
  - **Listas Encadeadas:** Armazenamento dinâmico das conexões.
- **Algoritmos:**
  - **Dijkstra:** Caminho mínimo em grafos ponderados.

## 📂 Estrutura do Projeto

O código segue o padrão de modularização com separação de responsabilidades:

```text
📁 gps-system/
│
├── 📄 main.c          # Interface do usuário (Menu e Loop principal)
├── 📄 grafos.c        # Manipulação do grafo (Adicionar vértices/arestas)
├── 📄 grafos.h        # Definição das structs e protótipos
├── 📄 dijkstra.c      # Algoritmo de caminho mínimo isolado
├── 📄 dijkstra.h      # Cabeçalho para o algoritmo de busca
├── 📄 log.c           # Implementação do sistema de registros (NOVO)
├── 📄 log.h           # Cabeçalho para funções de log
├── 📄 dados_gps.txt   # Banco de dados do mapa
└── 📄 logs.txt        # Histórico de execução gerado automaticamente
