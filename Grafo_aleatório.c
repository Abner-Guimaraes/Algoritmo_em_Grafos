#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Criar 10 grafos de 25 até 75 vertices, sendo grafo ponderado;
// Lista de adjacencia;

typedef struct noh {
  int valor;
  struct noh *proximo;
} No;

typedef struct grafo {
  No **A;
  int n; // Numero de vertices;
  int m; // Numero de arestas;
} * Grafo;

// Entrega um vertice aleatorio para a criação de aresta entre eles dois
// vertices;
int vertice_aleatorio(Grafo G) {
  double r;
  r = (double)rand() / ((double)RAND_MAX + 1.0);
  return (int)(r * G->n);
}

// Cria um grafo com n vertices e 0 arestas;
Grafo iniciarGrafo(int n) {

  Grafo G = malloc(sizeof *G);
  G->n = n;
  G->m = 0;
  G->A = malloc(n * sizeof(No *));

  for (int i = 0; i < n; i++) {
    G->A[i] = NULL;
  }
  return G;
}

// Percorre a lista com *p, caso não tenha, insere no começo da lista;
void insere_aresta(Grafo G, int v, int w) {
  No *p;
  for (p = G->A[v]; p != NULL; p = p->proximo) {
    if (p->valor == w) {
      return;
    }
  }
  p = malloc(sizeof(No));
  p->valor = w;
  p->proximo = G->A[v];
  G->A[v] = p;
  G->m++;
}

// Faz um grafo aleatorio, utilizando parametros definidos e utilizando funções
// acima;
Grafo grafo_aleatorio(int n, int m) {
  Grafo G = iniciarGrafo(n);
  while (G->m < m) {
    int v = vertice_aleatorio(G);
    int w = vertice_aleatorio(G);
    if (v != w) {
      insere_aresta(G, v, w);
    }
  }
  return G;
}

// Faz a impressão de um grafo em um arquivo;
void imprimeArquivoGrafo(Grafo G, FILE *saida) {
  int i;
  No *p;

  fprintf(saida, "Numero de Vertices: %d\n", G->n);
  fprintf(saida, "Numero de Arestas: %d\n", G->m);

  for (i = 0; i < G->n; i++) {
    fprintf(saida, "Vertice %d:", i);
    for (p = G->A[i]; p != NULL; p = p->proximo) {
      fprintf(saida, " %d", p->valor);
    }
    fprintf(saida, " -1\n");
  }
}

// free em tudo do grafo no final do código;
void liberaGrafo(Grafo G) {
  if (G == NULL)
    return;

  for (int i = 0; i < G->n; i++) {
    No *p = G->A[i];
    while (p != NULL) {
      No *temp = p;
      p = p->proximo;
      free(temp);
    }
  }

  free(G->A);
  free(G);
}

int main(void) {

  srand(time(NULL));
  FILE *saida;
  saida = fopen("grafo.txt", "w");

  if (saida == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  // for(int i = 0; i < 10; i++){
  // int n = rand() % 51 + 25;
  // printf("%d\n", n);

  int n = 13;
  printf("%d\n", n);
  int m = n * (n - 1) / 2;
  printf("%d\n", m);

  Grafo G = grafo_aleatorio(n, m);
  imprimeArquivoGrafo(G, saida);

  liberaGrafo(G);

  return 0;
}
