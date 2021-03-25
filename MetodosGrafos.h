#ifndef METODOSGRAFOS_H_INCLUDED
#define METODOSGRAFOS_H_INCLUDED
#define MAX 50

typedef struct Tipo_Aresta{
    int vertice1, vertice2;
    float peso;
}Tipo_Aresta;

typedef struct NO_Grafo{
        int vertice;
        int grau;
        struct NO_Grafo *proximo;
}NO_Grafo;

typedef struct {
          NO_Grafo *primeiro, *ultimo;
}Lista_Adjacencia;

typedef struct Grafo{
    int numero_vertices;
    Lista_Adjacencia *lista_vertices;
    float **Matriz_Adjacencia;
}Grafo;

typedef struct Celula_Fila{
    int vertice;
    struct Celula_Fila *proximo;
}Celula_Fila;

typedef struct Fila{
    Celula_Fila *frente, *tras;
}Fila;

typedef struct grau_vertice{
    int vertice;
    int grau;
}grau_vertice;

void iniciaLista(Lista_Adjacencia *pont_Lista, int vertice);
void Insere_Aresta(Lista_Adjacencia *pont_Lista, int vertice_inserir);
void Imprime_Lista(Lista_Adjacencia *pont_Lista);

#endif // METODOSGRAFOS_H_INCLUDED
