import networkx as nx
import matplotlib.pyplot as plt

# Ler as informações do arquivo e criar um grafo
def read_graph(filename):
    with open(filename, 'r') as file:
        num_vertices = int(file.readline().split()[-1])
        num_edges = int(file.readline().split()[-1])
        graph = nx.Graph()
        for _ in range(num_vertices):
            line = file.readline().strip().split(':')
            vertex, neighbors = int(line[0].split()[-1]), list(map(int, line[1].split()))
            for neighbor in neighbors:
                graph.add_edge(vertex, neighbor)
        return graph

# Carregar o grafo
filename = 'grafo.txt'
G = read_graph(filename)

# Desenhar o grafo
nx.draw(G, with_labels=True, node_color='lightblue', node_size=1000, font_size=12, font_color='black', font_weight='bold')
plt.show()
