#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MetodosGrafos.h"
#include "MetodosGrafos.c"

int main()
{
    char nome_arquivo[MAX];
    Grafo grafo;
    FILE *arquivo_entrada = NULL;
    Lista_Adjacencia *lista_vertices, *lista_auxiliar;
    float **Matriz_Adjacencia;
    int numero_vertices, vertice1, vertice2, x, y, tamanho, vertice_fornecido, grau_vertice, cont1 = 0, cont2 = 0, numero_componentes;
    int *visitados, **exploradas, *sequencia_vertices, *rotulacao;
    float *distancia;
    Tipo_Aresta *aresta;
    float peso_aresta;

    printf("Informe o nome do arquivo para abertura: ");
    gets(nome_arquivo);
    fflush(stdin);

    arquivo_entrada = fopen(nome_arquivo, "rt");
    if(arquivo_entrada == NULL){
        printf("ERRO NA ABERTURA DO ARQUIVO DE ENTRADA!!!\nARQUIVO NAO ENCONTRADO");
        exit(1);
    }

    fscanf(arquivo_entrada, "%d\n", &numero_vertices);
    grafo.numero_vertices = numero_vertices;
    grafo.lista_vertices = (Lista_Adjacencia*) malloc(numero_vertices * sizeof(Lista_Adjacencia));
    grafo.Matriz_Adjacencia = Alocar_Matriz_Adajacente(numero_vertices);
    visitados = (int*) malloc(numero_vertices * sizeof(int));
    sequencia_vertices = (int*) malloc(numero_vertices * sizeof(int));
    rotulacao = (int*) malloc(numero_vertices * sizeof(int));
    distancia = (float*) malloc(numero_vertices * sizeof(float));
    exploradas = Alocar_Matriz_inteira(numero_vertices);

    for(x = 0; x < numero_vertices; x++){
        for(y = 0; y < numero_vertices; y++){
            grafo.Matriz_Adjacencia[x][y] = 0.0;
            exploradas[x][y] = 0;
        }
    }
    for(x = 0; x < numero_vertices; x++){
        visitados[x] = 0;
    }

    for(x = 0; x < numero_vertices; x++){
        iniciaLista(&grafo.lista_vertices[x], x + 1);
    }

    while((fscanf(arquivo_entrada, "%d %d %f\n", &vertice1, &vertice2, &peso_aresta)) != EOF){
        grafo.Matriz_Adjacencia[vertice1 - 1][vertice2 - 1] = peso_aresta;
        grafo.Matriz_Adjacencia[vertice2 - 1][vertice1 - 1] = peso_aresta;
    }

    rewind(arquivo_entrada);
    fscanf(arquivo_entrada, "%d\n", &numero_vertices);
     while((fscanf(arquivo_entrada, "%d %d %f\n", &vertice1, &vertice2, &peso_aresta)) != EOF){
        for(x = 0; x < numero_vertices; x++){
            if(grafo.lista_vertices[x].primeiro->vertice == vertice1){
                Insere_Aresta(&grafo.lista_vertices[x], vertice2);
                break;
            }
        }
         for(x = 0; x < numero_vertices; x++){
            if(grafo.lista_vertices[x].primeiro->vertice == vertice2){
                Insere_Aresta(&grafo.lista_vertices[x], vertice1);
                break;
            }
        }
    }
    fclose(arquivo_entrada);
    Exibe_Matriz_real(grafo.Matriz_Adjacencia, grafo.numero_vertices);

    for(x = 0; x < numero_vertices; x++){
        Imprime_Lista(&grafo.lista_vertices[x]);
    }
    tamanho = Retorna_Tamanho(grafo.lista_vertices, numero_vertices);
    aresta = (Tipo_Aresta*) malloc(tamanho * sizeof(Tipo_Aresta));

    tamanho = Retorna_Tamanho(grafo.lista_vertices, numero_vertices);
    printf("\n\nTamanho do grafo: %d\n", tamanho);
    printf("\n\n");

    printf("ordem do grafo: %d\n", Retorna_Ordem(grafo));
    printf("\n\n");

    printf("\n\nDigite o vertice de busca para retornar o grau: ");
    scanf("%d", &vertice_fornecido);
    fflush(stdin);
    grau_vertice = Retorna_Grau_Vertice(grafo.lista_vertices, grafo.numero_vertices, vertice_fornecido);
    printf("Grau do vertice: %d\n", grau_vertice);
    printf("\n\n");

    printf("Lista de vizinhos do vertice %d\n", vertice_fornecido);
    lista_auxiliar = Retorna_vizinhos(grafo.lista_vertices, grafo.numero_vertices, vertice_fornecido);
    Imprime_Lista(lista_auxiliar);
    printf("\n\n");

    printf("Busca em profundidade\n");
    Busca_Profundidade_Grafo(grafo, 1, visitados, exploradas, sequencia_vertices, aresta, &cont1, &cont2);

    printf("\n\nBusca em largura\n");
    Busca_Largura_Grafo(grafo, 1, visitados, exploradas, sequencia_vertices, aresta, &cont1, &cont2);
    printf("\n\n");

    printf("Contabilizando componentes conexas\n");
    numero_componentes = Verifica_Componentes(grafo, 1, visitados, exploradas, sequencia_vertices, aresta, &cont1, &cont2, rotulacao);
    printf("O numero de componentes conexas do grafo eh: %d\n", numero_componentes);
    for(y = 0; y < numero_componentes; y++){
        printf("Vertices da componente conexa %d: ", y + 1);
        for(x = 0; x < grafo.numero_vertices; x++){
            if(rotulacao[x] == y + 1){
                printf("%d ", x + 1);
            }
        }
    }

    printf("\n\nCalculando a menor distancia entre um vertice e os demais\n");
    Caminho_Mais_Curto(grafo, 2, distancia, rotulacao);
    for(x = 0; x < grafo.numero_vertices; x++){
        printf("Menor distancia entre o vertice 2 e o vertice %d: %.2f\n", x + 1, distancia[x]);
    }
    printf("\nRotulacao do caminho entre os vertices\n");
     for(x = 0; x < grafo.numero_vertices; x++){
        printf("%d\n", rotulacao[x]);
    }
    Arvore_Geradora_Minima(grafo);
    verifica_CicloNegativo(grafo);
    determina_ConjuntoIndependente(grafo);
    return 0;
}

