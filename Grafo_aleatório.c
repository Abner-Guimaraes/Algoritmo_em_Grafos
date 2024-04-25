#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

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

// Faz um grafo aleatorio, utilizando parametros definidos e utilizando funções acima;
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

// Dijkstra: Inicializa os dois vetores auxiliares colocando infinito e NULL(-1);
void INICIALIZA(Grafo G, int *p, int *d, int s) {
  for (int v = 0; v < G->MaxNumeroVertices; v++) {
    d[v] = INT_MAX / 2;
    p[v] = -1;
  }
  d[s] = 0;
}

void RELAXA(Grafo G, int *d, int *p, int u, int v) {
  No *ad = G->ListaAdjacencia[u];
  while (ad && ad->valor != v) {
    ad = ad->proximo;
  }
  if (ad) {
    if (d[v] > d[u] + ad->peso) {
      d[v] = d[u] + ad->peso;
      p[v] = u;
    }
  }
}

bool ExisteAberto(Grafo G, bool *aberto) {
  for (int i = 0; i < G->MaxNumeroVertices; i++) {
    if (aberto[i]) {
      return true;
    }
  }
  return false;
}

int menorDistancia(Grafo G, bool *aberto, int *d) {
  int minDistancia = INT_MAX;
  int verticeMenorDistancia = -1;
  for (int i = 0; i < G->MaxNumeroVertices; i++) {
    if (aberto[i] && d[i] < minDistancia) {
      minDistancia = d[i];
      verticeMenorDistancia = i;
    }
  }
  return verticeMenorDistancia;
}

void Dijkstra(Grafo G, int s) {
  int *d = malloc(G->MaxNumeroVertices * sizeof(int));
  int *p = malloc(G->MaxNumeroVertices * sizeof(int));
  bool *aberto = malloc(G->MaxNumeroVertices * sizeof(bool));

  INICIALIZA(G, p, d, s);

  for (int i = 0; i < G->MaxNumeroVertices; i++) {
    aberto[i] = true;
  }

  while (ExisteAberto(G, aberto)) {
    int u = menorDistancia(G, aberto, d);
    aberto[u] = false;
    No *ad = G->ListaAdjacencia[u];
    while (ad != NULL) {
      RELAXA(G, d, p, u, ad->valor);
      ad = ad->proximo;
    }
  }

  printf("\nMenor caminho a partir do vértice %d:\n", s);
  for (int i = 0; i < G->MaxNumeroVertices; i++) {
    printf("Para o vértice %d: Distância mínima = %d, Vértice anterior = %d\n",i, d[i], p[i]);
  }

  free(d);
  free(p);
  free(aberto);
}

// Faz a impressão de um grafo em um arquivo;
void imprime_ArquivoGrafo(Grafo G, FILE *saida) {
  int i;
  No *p;
  int resposta = 0;

  fprintf(saida, "Numero de Vertices: %d\n", G->MaxNumeroVertices);
  fprintf(saida, "Numero de Arestas: %d\n", G->QuantidadeArestas);


while(resposta != 1 && resposta != 2){
printf("Escolha a opção com peso ou sem peso para escrever no arquivo txt:");
printf("\n1. Digite 1 para mostrar sem peso\n2. Digite 2 para mostrar com peso\n> ");
scanf("%d", &resposta);
}


switch (resposta)
{
case 1:
for (i = 0; i < G->MaxNumeroVertices; i++) {
    fprintf(saida, "Vertice %d:", i);
    for (p = G->ListaAdjacencia[i]; p != NULL; p = p->proximo) {
      fprintf(saida, " %d", p->valor);
    }
    fprintf(saida, "\n");
  }
  break;
case 2:
for (i = 0; i < G->MaxNumeroVertices; i++) {
    fprintf(saida, "Vertice %d:", i);
  for (p = G->ListaAdjacencia[i]; p != NULL; p = p->proximo) {
  fprintf(saida, "(%d peso é:%d)", p->valor, p->peso);
  }
    fprintf(saida, "\n");
  }
  break;

default: printf("\nOpção inválida!\n");
  break;
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

  Grafo G = Criacao_grafo_aleatorio(NumeroMaxVertices, QuantidadeMaxArestas,PesoMaximo);
  imprime_ArquivoGrafo(G, saida);
  Dijkstra(G, 0);
  free_liberaGrafo(G);
  fclose(saida);
  return 0;
}