#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MetodosGrafos.h"
#include <math.h>
#include <time.h>


float **Alocar_Matriz_Adajacente (int N){
  float **Matriz_Adjacencia;  /* ponteiro para a matriz */
  int   i;    /* variavel auxiliar      */
  if (N < 1) { /* verifica parametros recebidos */
     printf ("** Erro ao alocar matriz de adjacencia: Parametro invalido **\n");
     return (NULL);
  }
  /* aloca as linhas da matriz */
  Matriz_Adjacencia = (float**) malloc(N * sizeof(float*));
  if (Matriz_Adjacencia == NULL) {
     printf ("** Erroao alocar matri\ de adjacencia: Memoria Insuficiente **");
     return (NULL);
     }
  /* aloca as colunas da matriz */
  for ( i = 0; i < N; i++ ) {
      Matriz_Adjacencia[i] = (float*) malloc(N * sizeof(float));
      if (Matriz_Adjacencia[i] == NULL) {
         printf ("** Erro ao alocar matriz de adjacencia: Memoria Insuficiente **");
         return (NULL);
         }
      }
  return Matriz_Adjacencia; /* retorna o ponteiro para a matriz */
}

void Exibe_Matriz_real(float **Matriz_Adjacencia, int N){
    int x, y;
    printf("Exibindo Matriz de Adjacencia do Grafo\n\n");
     for(x = 0; x < N; x++){
        for(y = 0; y < N; y++){
            printf("%.2f|",  Matriz_Adjacencia[x][y]);
        }
        printf("\n");
    }
}

int **Alocar_Matriz_inteira (int N){
  int **Matriz_Inteira;  /* ponteiro para a matriz */
  int   i;    /* variavel auxiliar      */
  if (N < 1) { /* verifica parametros recebidos */
     printf ("** Erro ao alocar matriz de adjacencia: Parametro invalido **\n");
     return (NULL);
  }
  /* aloca as linhas da matriz */
  Matriz_Inteira = (int**) malloc(N * sizeof(int*));
  if (Matriz_Inteira == NULL) {
     printf ("** Erroao alocar matri\ de adjacencia: Memoria Insuficiente **");
     return (NULL);
     }
  /* aloca as colunas da matriz */
  for ( i = 0; i < N; i++ ) {
      Matriz_Inteira[i] = (int*) malloc(N * sizeof(int));
      if (Matriz_Inteira[i] == NULL) {
         printf ("** Erro ao alocar matriz de adjacencia: Memoria Insuficiente **");
         return (NULL);
         }
      }
  return Matriz_Inteira; /* retorna o ponteiro para a matriz */
}

void Exibe_Matriz_inteira(int **Matriz_inteira, int N){
    int x, y;
    printf("Exibindo Matriz de Adjacencia do Grafo\n\n");
     for(x = 0; x < N; x++){
        for(y = 0; y < N; y++){
            printf("%d|",  Matriz_inteira[x][y]);
        }
        printf("\n");
    }
}

void Faz_Fila_Vazia(Fila *pont_fila){
    pont_fila->frente = ((Celula_Fila*) malloc(sizeof(Celula_Fila)));
    pont_fila->tras = pont_fila->frente;
    pont_fila->frente->proximo = NULL;
}

void Enfileira(Fila *pont_fila, int vertice){
    Celula_Fila *nova_celula;

    nova_celula = ((Celula_Fila*) malloc(sizeof(Celula_Fila)));
    pont_fila->tras->proximo = nova_celula;
    pont_fila->tras = nova_celula;
    nova_celula->vertice = vertice;
    nova_celula->proximo = NULL;
}

int Desenfileira(Fila *pont_fila){
    Celula_Fila *celula_aux;
    int vertice;

    if(pont_fila->frente != pont_fila->tras){
        celula_aux = pont_fila->frente;
        pont_fila->frente = pont_fila->frente->proximo;
        vertice = pont_fila->frente->vertice;
        free(celula_aux);
        return vertice;
    }
    return -1;
}

void iniciaLista(Lista_Adjacencia *pont_Lista, int vertice){
    NO_Grafo *novo_NO;

    novo_NO = ((NO_Grafo*) malloc(sizeof(NO_Grafo)));

    novo_NO->proximo = NULL;
    novo_NO->grau = 0;
    novo_NO->vertice = vertice;
    pont_Lista->primeiro = novo_NO;
    pont_Lista->ultimo = novo_NO;
}

void Insere_Aresta(Lista_Adjacencia *pont_Lista, int vertice_inserir){
   NO_Grafo *NO_auxiliar, *NO_temporario;

   NO_auxiliar  = ((NO_Grafo*) malloc(sizeof(NO_Grafo)));
   NO_auxiliar->grau = 0;
   NO_auxiliar->vertice = vertice_inserir;
   NO_auxiliar->proximo = NULL;

   pont_Lista->primeiro->grau++;
   if(pont_Lista->primeiro->proximo == NULL){
        pont_Lista->primeiro->proximo = NO_auxiliar;
        pont_Lista->ultimo = NO_auxiliar;
   }

   else{
      NO_temporario = pont_Lista->primeiro->proximo;
      if(NO_temporario->vertice > vertice_inserir){
        NO_auxiliar->proximo = NO_temporario;
        pont_Lista->primeiro->proximo = NO_auxiliar;
      }
      else if (NO_temporario->proximo == NULL){
        NO_auxiliar->proximo = NO_temporario->proximo;
        NO_temporario->proximo = NO_auxiliar;
        pont_Lista->ultimo = NO_auxiliar;
      }
      else {
        while (NO_temporario->proximo != NULL && NO_temporario->proximo->vertice < vertice_inserir){
            NO_temporario = NO_temporario->proximo;
        }
        if(NO_temporario->proximo == NULL){
            pont_Lista->ultimo = NO_auxiliar;
        }
        NO_auxiliar->proximo = NO_temporario->proximo;
        NO_temporario->proximo = NO_auxiliar;
      }
   }
}

void Imprime_Lista(Lista_Adjacencia *pont_Lista){
      NO_Grafo *NO_Auxiliar;

      if(pont_Lista == NULL){
        printf("Lista Vazia ou vertice nao localizado\n");
        return;
      }

      printf("Vertice: %d", pont_Lista->primeiro->vertice);

      if (pont_Lista->primeiro->proximo == NULL){
          printf("-->\n");
      }

      else{
            NO_Auxiliar = pont_Lista->primeiro->proximo;

            do{
                printf("--> %d", NO_Auxiliar->vertice);
                NO_Auxiliar = NO_Auxiliar->proximo;

            }while(NO_Auxiliar != NULL);
            printf("\n");
      }
}

int Retorna_Ordem(Grafo grafo){
    return grafo.numero_vertices;
}

int Retorna_Tamanho (Lista_Adjacencia lista_vertices[], int numero_vertices){
    int i, tamanho = 0;
    for (i = 0; i < numero_vertices; i++){
        tamanho = tamanho + lista_vertices[i].primeiro->grau;
    }
    return tamanho/2;
}

int Retorna_Grau_Vertice(Lista_Adjacencia lista_vertices[], int numero_vertice,int vertice_fornecido){
    int x;
    for(x = 0; x < numero_vertice; x++){
        if(lista_vertices[x].primeiro->vertice == vertice_fornecido){
            return lista_vertices[x].primeiro->grau;
        }
    }
    return -1;
}

Lista_Adjacencia* Retorna_vizinhos(Lista_Adjacencia lista_vertices[], int numero_vertice,int vertice_fornecido){
    int x;
    for(x = 0; x < numero_vertice; x++){
        if(lista_vertices[x].primeiro->vertice == vertice_fornecido){
            return &lista_vertices[x];

        }
    }
    return NULL;
}

void Busca_Profundidade_Grafo(Grafo grafo, int vertice_inicial, int *visitados, int **exploradas, int *sequencia_vertices, Tipo_Aresta *aresta, int *cont1, int *cont2){
    int y, x;
    for(y = 0; y < grafo.numero_vertices; y++){
        if(visitados[y] == 0){
            vertice_inicial = y + 1;
            Busca_Profundidade(grafo, vertice_inicial, visitados, exploradas, sequencia_vertices, aresta, cont1, cont2);
            printf("Sequencia de vertices visitados\n");
            for(x = 0; x < *cont1; x++){
                printf("%d - ", sequencia_vertices[x]);
            }
            printf("\nArestas de retorno\n");
            for(x = 0; x < *cont2; x++){
                printf("%d - %d\n", aresta[x].vertice1, aresta[x].vertice2);
            }
        }
        (*cont1) = 0;
        (*cont2) = 0;
    }
    for(x = 0; x < grafo.numero_vertices; x++){
        for(y = 0; y < grafo.numero_vertices; y++){
            exploradas[x][y] = 0;
        }
    }
    for(x = 0; x < grafo.numero_vertices; x++){
        visitados[x] = 0;
    }
}

void Busca_Profundidade(Grafo grafo, int vertice_inicial, int *visitados, int **exploradas, int *sequencia_vertices, Tipo_Aresta *aresta, int *cont1, int *cont2){
    NO_Grafo *NO_Auxiliar;
    int vertice_auxiliar;
    int x;

    for(x = 0; x < grafo.numero_vertices; x++){
        if(grafo.lista_vertices[x].primeiro->vertice == vertice_inicial){
            NO_Auxiliar = grafo.lista_vertices[x].primeiro->proximo;
        }
    }
    visitados[vertice_inicial - 1] = 1;
    sequencia_vertices[*cont1] = vertice_inicial;
    (*cont1)++;
    //printf("Vertice visitado: %d\n", vertice_inicial);

    while(NO_Auxiliar != NULL){
        vertice_auxiliar = NO_Auxiliar->vertice;
        if(visitados[vertice_auxiliar - 1] == 0){
            exploradas[vertice_inicial - 1][vertice_auxiliar - 1] = 1;
            exploradas[vertice_auxiliar - 1][vertice_inicial - 1] = 1;
            visitados[vertice_auxiliar - 1] = 1;
            Busca_Profundidade(grafo, vertice_auxiliar, visitados, exploradas, sequencia_vertices, aresta, cont1, cont2);
        }
        else if(exploradas[vertice_inicial - 1][vertice_auxiliar - 1] == 0){
            exploradas[vertice_inicial - 1][vertice_auxiliar - 1] = 1;
            exploradas[vertice_auxiliar - 1][vertice_inicial - 1] = 1;
            sequencia_vertices[*cont1] = vertice_auxiliar;
            (*cont1)++;
            aresta[*cont2].vertice1 = vertice_inicial;
            aresta[*cont2].vertice2 = vertice_auxiliar;
            (*cont2)++;
            //printf("Aresta de retorno: %d - %d\n", vertice_inicial, vertice_auxiliar);
        }
        NO_Auxiliar = NO_Auxiliar->proximo;
    }
}

void Busca_Largura_Grafo(Grafo grafo, int vertice_inicial, int *visitados, int **exploradas, int *sequencia_vertices, Tipo_Aresta *aresta, int *cont1, int *cont2){
    int y, x;
    for(y = 0; y < grafo.numero_vertices; y++){
        if(visitados[y] == 0){
            vertice_inicial = y + 1;
            Busca_Largura(grafo, vertice_inicial, visitados, exploradas, sequencia_vertices, aresta, cont1, cont2);
            printf("Sequencia de vertices visitados\n");
            for(x = 0; x < *cont1; x++){
                printf("%d - ", sequencia_vertices[x]);
            }
            printf("\nArestas que nao fazem parte da arvore de busca em largura\n");
            for(x = 0; x < *cont2; x++){
                printf("%d - %d\n", aresta[x].vertice1, aresta[x].vertice2);
            }
        }
        (*cont1) = 0;
        (*cont2) = 0;
    }
    for(x = 0; x < grafo.numero_vertices; x++){
        for(y = 0; y < grafo.numero_vertices; y++){
            exploradas[x][y] = 0;
        }
    }
    for(x = 0; x < grafo.numero_vertices; x++){
        visitados[x] = 0;
    }
}

void Busca_Largura(Grafo grafo, int vertice_inicial, int *visitados, int **exploradas, int *sequencia_vertices, Tipo_Aresta *aresta, int *cont1, int *cont2){
    Fila fila;
    NO_Grafo *NO_Auxiliar;
    int vertice_auxiliar;
    int x;

    Faz_Fila_Vazia(&fila);
    visitados[vertice_inicial - 1] = 1;
    Enfileira(&fila, vertice_inicial);

    while(fila.frente != fila.tras){
        vertice_inicial = Desenfileira(&fila);
        for(x = 0; x < grafo.numero_vertices; x++){
            if(grafo.lista_vertices[x].primeiro->vertice == vertice_inicial){
                NO_Auxiliar = grafo.lista_vertices[x].primeiro->proximo;
            }
        }
        //printf("Vertice visitado: %d\n", vertice_inicial);
        sequencia_vertices[*cont1] = vertice_inicial;
        (*cont1)++;
        while(NO_Auxiliar != NULL){
            vertice_auxiliar = NO_Auxiliar->vertice;
            if(visitados[vertice_auxiliar - 1] == 0){
                exploradas[vertice_inicial - 1][vertice_auxiliar - 1] = 1;
                exploradas[vertice_auxiliar - 1][vertice_inicial - 1] = 1;
                sequencia_vertices[*cont1] = vertice_auxiliar;
                (*cont1)++;
                Enfileira(&fila, vertice_auxiliar);
                visitados[vertice_auxiliar - 1] = 1;
            }
            else if(exploradas[vertice_inicial - 1][vertice_auxiliar - 1] == 0){
                exploradas[vertice_inicial - 1][vertice_auxiliar - 1] = 1;
                exploradas[vertice_auxiliar - 1][vertice_inicial - 1] = 1;
                aresta[*cont2].vertice1 = vertice_inicial;
                aresta[*cont2].vertice2 = vertice_auxiliar;
                (*cont2)++;
            }
            NO_Auxiliar = NO_Auxiliar->proximo;
        }
    }
}

int Verifica_Componentes(Grafo grafo, int vertice_inicial, int *visitados, int **exploradas, int *sequencia_vertices, Tipo_Aresta *aresta, int *cont1, int *cont2, int *rotulacao){
    int y, x, conta_componentes = 0;
    for(y = 0; y < grafo.numero_vertices; y++){
        if(visitados[y] == 0){
            vertice_inicial = y + 1;
            Busca_Profundidade(grafo, vertice_inicial, visitados, exploradas, sequencia_vertices, aresta, cont1, cont2);
            conta_componentes++;

            for(x = 0; x < grafo.numero_vertices; x++){
                if(visitados[x] == 1){
                    rotulacao[x] = conta_componentes;
                }
            }
        }
        (*cont1) = 0;
        (*cont2) = 0;
    }
    for(x = 0; x < grafo.numero_vertices; x++){
        for(y = 0; y < grafo.numero_vertices; y++){
            exploradas[x][y] = 0;
        }
    }
    for(x = 0; x < grafo.numero_vertices; x++){
        visitados[x] = 0;
    }

    return conta_componentes;
}

void Caminho_Mais_Curto(Grafo grafo, int vertice_inicial, float *distancia, int *rotulacao){
    int i, j, k, altera, vertice_auxiliar;
    NO_Grafo *NO_Auxiliar;

    distancia[vertice_inicial - 1] = 0.0;
    rotulacao[vertice_inicial - 1] = pow(2, 32);

    for(i = 0; i < grafo.numero_vertices; i++){
        if(i != (vertice_inicial - 1)){
            if(grafo.Matriz_Adjacencia[vertice_inicial - 1][i] != 0.0){
                rotulacao[i] = vertice_inicial;
                distancia[i] = grafo.Matriz_Adjacencia[vertice_inicial - 1][i];
            }
            else{
                rotulacao[i] = 0.0;
                distancia[i] = pow(2, 32);
            }
        }
    }

    for(k = 0; k < (grafo.numero_vertices - 1); k++){
        altera = 0;
        Lista_Adjacencia *lista_auxiliar;

        for(i = 0; i < grafo.numero_vertices; i++){
            if(i != vertice_inicial - 1){
                lista_auxiliar = Retorna_vizinhos(grafo.lista_vertices, grafo.numero_vertices, i + 1);
                NO_Auxiliar = lista_auxiliar->primeiro->proximo;

                do{
                    vertice_auxiliar = NO_Auxiliar->vertice;
                    if(distancia[i] > (distancia[vertice_auxiliar - 1] + grafo.Matriz_Adjacencia[vertice_auxiliar - 1][i]) && (rotulacao[vertice_auxiliar - 1] != i + 1)){
                        distancia[i] = distancia[vertice_auxiliar - 1] + grafo.Matriz_Adjacencia[vertice_auxiliar - 1][i];
                        rotulacao[i] = vertice_auxiliar;
                        altera = 1;
                    }
                    NO_Auxiliar = NO_Auxiliar->proximo;

                }while(NO_Auxiliar != NULL);
            }
        }
        if(!altera){
            break;
        }
    }
}

void Arvore_Geradora_Minima(Grafo grafo){
    srand((unsigned) time(NULL));
    int tamanho, contador1 = 0, contador2 = 0, x, y, marcador, vertice1, vertice2;
    int *verticas_selecionados, *vertices_nao_selecionados;
    Tipo_Aresta *aresta;
    FILE *Saida_ArvoreMinima;
    char nome_arvore[MAX];
    float peso_minimo = 0.0;

    verticas_selecionados = (int*) malloc(grafo.numero_vertices * sizeof(int));
    vertices_nao_selecionados = (int*) malloc(grafo.numero_vertices * sizeof(int));
    tamanho = Retorna_Tamanho(grafo.lista_vertices, grafo.numero_vertices);
    aresta = (Tipo_Aresta*) malloc(tamanho * sizeof(Tipo_Aresta));

    verticas_selecionados[contador1] = 1 + (rand() % grafo.numero_vertices);
    contador1++;
    for(x = 0; x < grafo.numero_vertices; x++){
        vertices_nao_selecionados[x] = x + 1;
    }
    vertices_nao_selecionados[verticas_selecionados[contador1 - 1] - 1] = 0;
    while(contador1 < grafo.numero_vertices){
        marcador = 0;
        for (x = 0; x < contador1; x++){
            vertice1 = verticas_selecionados[x];
            for(y = 0; y < grafo.numero_vertices; y++){
                vertice2 = vertices_nao_selecionados[y];
                if(vertice2 != 0 && grafo.Matriz_Adjacencia[vertice1 - 1][vertice2 - 1] != 0){
                    if(marcador == 0){
                        marcador++;
                        aresta[contador2].peso = grafo.Matriz_Adjacencia[vertice1 - 1][vertice2 - 1];
                        aresta[contador2].vertice1 = vertice1;
                        aresta[contador2].vertice2 = vertice2;

                    }
                    else if(aresta[contador2].peso > grafo.Matriz_Adjacencia[vertice1 - 1][vertice2 - 1]){
                        aresta[contador2].peso = grafo.Matriz_Adjacencia[vertice1 - 1][vertice2 - 1];
                        aresta[contador2].vertice1 = vertice1;
                        aresta[contador2].vertice2 = vertice2;
                    }
                }
            }
        }
        verticas_selecionados[contador1] = aresta[contador2].vertice2;
        contador1++;
        vertices_nao_selecionados[verticas_selecionados[contador1 - 1] - 1] = 0;
        peso_minimo = peso_minimo + aresta[contador2].peso;
        contador2++;

    }
    printf("Informe o nome para a arvore gerada: ");
    gets(nome_arvore);
    fflush(stdin);
    strcat(nome_arvore, ".txt");

    Saida_ArvoreMinima = fopen(nome_arvore, "wt");
    if(Saida_ArvoreMinima == NULL){
        printf("FALHA NA ESCRITA!!!");
        exit(1);
    }
    fprintf(Saida_ArvoreMinima, "%d\n", grafo.numero_vertices);
    for(x = 0; x < contador2; x++){
        fprintf(Saida_ArvoreMinima,"%d %d %.2f\n", aresta[x].vertice1, aresta[x].vertice2, aresta[x].peso);
    }
    fprintf(Saida_ArvoreMinima, "%.2f\n", peso_minimo);
    fclose(Saida_ArvoreMinima);
}

void verifica_CicloNegativo(Grafo grafo){
    float **matrizL, **matrizR;
    int x, y, z;

    matrizL = Alocar_Matriz_Adajacente(grafo.numero_vertices);
    matrizR = Alocar_Matriz_Adajacente(grafo.numero_vertices);

    for(x = 0; x < grafo.numero_vertices; x++){
        for(y = 0; y < grafo.numero_vertices; y++){
            matrizL[x][y] = grafo.Matriz_Adjacencia[x][y];
            if(x != y && (grafo.Matriz_Adjacencia[x][y] == 0)){
                matrizL[x][y] = pow(2, 30);
            }
            if(matrizL[x][y] == pow(2, 30)){
                matrizR[x][y] = 0;
            }
            else{
                matrizR[x][y] = x + 1;
            }
        }
    }

    for(z = 0; z < grafo.numero_vertices; z++){
        for(x = 0; x < grafo.numero_vertices; x++){
            for(y = 0; y < grafo.numero_vertices; y++){
                if(matrizL[x][y] > (matrizL[x][z] + matrizL[z][y])){
                   matrizL[x][y] = (matrizL[x][z] + matrizL[z][y]);
                   matrizR[x][y] =  matrizR[z][y];
                }
            }
        }
    }
    for(x = 0; x < grafo.numero_vertices; x++){
        if(matrizL[x][x] < 0){
            printf("Grafo possui ciclo negativo\n\n");
            return;
        }
    }
    printf("Grafo nao possui ciclo negativo\n\n");
}

void determina_ConjuntoIndependente(Grafo grafo){
    grau_vertice conjunto_vertices[grafo.numero_vertices];
    int x, y, numero_independencia = 0, conjunto_independente[grafo.numero_vertices], conta = grafo.numero_vertices;
    grau_vertice auxiliar;
    NO_Grafo *noAux;

    for(x = 0; x < grafo.numero_vertices; x++){
        conjunto_vertices[x].vertice = grafo.lista_vertices[x].primeiro->vertice;
        conjunto_vertices[x].grau = grafo.lista_vertices[x].primeiro->grau;
    }

    for(x = 0; x < grafo.numero_vertices; x++){
        for(y = 1; y < grafo.numero_vertices - x; y++){
            if(conjunto_vertices[y].grau > conjunto_vertices[y - 1].grau){
                auxiliar = conjunto_vertices[y - 1];
                conjunto_vertices[y - 1] = conjunto_vertices[y];
                conjunto_vertices[y] = auxiliar;
            }
        }
    }
    int z;
    for(z = 0; z  < grafo.numero_vertices; z++){
        printf("%d %d\n", conjunto_vertices[z].vertice, conjunto_vertices[z].grau);
    }
    x = 0;
    while(conta != 0){
        for(y = 0; y < grafo.numero_vertices; y++){
            if(conjunto_vertices[y].vertice != 0){
                conjunto_independente[x] = conjunto_vertices[y].vertice;
                x++;
                numero_independencia++;
                conjunto_vertices[y].vertice = 0;
                conta--;
                break;
            }
        }

        for(y = 0; y < grafo.numero_vertices; y++){
            if(grafo.lista_vertices[y].primeiro->vertice == conjunto_independente[x - 1]){
                noAux = grafo.lista_vertices[y].primeiro;
                break;
            }
        }

        while(noAux->proximo != NULL){
            for(y = 0; y < grafo.numero_vertices; y++){
                if(noAux->proximo->vertice == conjunto_vertices[y].vertice){
                    conjunto_vertices[y].vertice = 0;
                    conta--;
                    break;
                }
            }
            noAux = noAux->proximo;
        }
    }

    printf("Conjunto independencia: ");
    for(y = 0; y < x; y++){
        printf("%d ", conjunto_independente[y]);
    }
    printf("\n\nNumero de independencia: %d\n\n", numero_independencia);
}
