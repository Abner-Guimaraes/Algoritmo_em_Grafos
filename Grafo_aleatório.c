#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Criar 10 grafos de 25 até 75 vertices, sendo grafo ponderado;
// Lista de adjacencia;

typedef struct noh {
  int valor;
  int peso;
  struct noh *proximo;
} No;

typedef struct grafo {
  No **ListaAdjacencia;
  int MaxNumeroVertices;
  int QuantidadeArestas;
} * Grafo;

// Entrega um vertice aleatorio para a criação de aresta entre dois vertices;
int vertice_aleatorio(Grafo G) {
  double r;
  r = (double)rand() / ((double)RAND_MAX + 1.0);
  return (int)(r * G->MaxNumeroVertices);
}

// Cria um grafo com n vertices e 0 arestas;
Grafo iniciar_Grafo(int n) {

  Grafo G = malloc(sizeof *G);
  G->MaxNumeroVertices = n;
  G->QuantidadeArestas = 0;
  G->ListaAdjacencia = malloc(n * sizeof(No *));

  for (int i = 0; i < n; i++) {
    G->ListaAdjacencia[i] = NULL;
  }
  return G;
}

// Percorre a lista com *PercorreLista, caso não tenha, insere no começo da lista;
void insere_aresta(Grafo G, int v, int w, int peso) {
  No *PercorreLista;
  for (PercorreLista = G->ListaAdjacencia[v]; PercorreLista != NULL;
       PercorreLista = PercorreLista->proximo) {
    if (PercorreLista->valor == w) {
      return;
    }
  }
  PercorreLista = malloc(sizeof(No));
  PercorreLista->valor = w;
  PercorreLista->peso = peso;
  PercorreLista->proximo = G->ListaAdjacencia[v];
  G->ListaAdjacencia[v] = PercorreLista;
  G->QuantidadeArestas++;
}

// Faz um grafo aleatorio, utilizando parametros definidos e utilizando funções
// acima;
Grafo Criacao_grafo_aleatorio(int n, int m, int PesoMaximo) {
  Grafo G = iniciar_Grafo(n);
  while (G->QuantidadeArestas < m) {
    int v = vertice_aleatorio(G);
    int w = vertice_aleatorio(G);
    if (v != w) {
      int peso = rand() % PesoMaximo + 1;
      insere_aresta(G, v, w, peso);
    }
  }
  return G;
}

// Faz a impressão de um grafo em um arquivo;
void imprime_ArquivoGrafo(Grafo G, FILE *saida) {
  int i;
  No *p;

  fprintf(saida, "Numero de Vertices: %d\n", G->MaxNumeroVertices);
  fprintf(saida, "Numero de Arestas: %d\n", G->QuantidadeArestas);

  for (i = 0; i < G->MaxNumeroVertices; i++) {
    fprintf(saida, "Vertice %d:", i);
    for (p = G->ListaAdjacencia[i]; p != NULL; p = p->proximo) {
      fprintf(saida, "(%d peso é:%d)", p->valor, p->peso);
    }
    fprintf(saida, "\n");
  }
}

// Free em tudo do grafo no final do código;
void free_liberaGrafo(Grafo G) {
  if (G == NULL)
    return;

  for (int i = 0; i < G->MaxNumeroVertices; i++) {
    No *p = G->ListaAdjacencia[i];
    while (p != NULL) {
      No *temp = p;
      p = p->proximo;
      free(temp);
    }
  }

  free(G->ListaAdjacencia);
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

  int NumeroMaxVertices = rand() % 51 + 25;
  printf("Numero total de Vertices: %d\n", NumeroMaxVertices);
  int QuantidadeMaxArestas = NumeroMaxVertices * (NumeroMaxVertices - 1) / 2; //== n.(n-1)/2;
  printf("Numero total de Arestas: %d\n", QuantidadeMaxArestas);

  int PesoMaximo = 50;
  //printf("Digite o numero maximo de pesos que pode ser utilizado em uma aresta: ");
  //scanf(" %d", &PesoMaximo);

  Grafo G = Criacao_grafo_aleatorio(NumeroMaxVertices, QuantidadeMaxArestas, PesoMaximo);
  
  imprime_ArquivoGrafo(G, saida);

  free_liberaGrafo(G);

  return 0;
}