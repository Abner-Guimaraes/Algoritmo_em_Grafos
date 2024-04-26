import networkx as nx
import matplotlib.pyplot as plt

# Faz a leitura do arquivo grafo.txt;
with open("grafo.txt", "r") as f:
    lines = f.readlines()

# Cria o grafo
G = nx.Graph()
for line in lines:
    if line.startswith("Vertice"):
        vertex = int(line.split(":")[0].split(" ")[1])
        neighbors = [int(n) for n in line.split(":")[1].strip().split(" ")]
        for neighbor in neighbors:
            G.add_edge(vertex, neighbor)

# Faz a leitura do arquivo centralidade.txt;
with open("centralidade.txt", "r") as f:
    lines = f.readlines()
    centrality = {}
    for line in lines:
        try:
            vertex = int(line.split(":")[0].split(" ")[1])
            value = float(line.split(":")[1].strip())
            centrality[vertex] = value
        except (ValueError, IndexError):
            # Ignora linhas que não podem ser convertidas corretamente;
            pass

# Calcula a média dos valores de centralidade;
mean_centrality = sum(centrality.values()) / len(centrality)

# Calcula a cor de cada vértice com base na sua centralidade em relação à média;
colors = []
for node in G.nodes():
    if node in centrality:
        if centrality[node] > mean_centrality * 1.05:
            colors.append('blue')
        elif centrality[node] > mean_centrality:
            colors.append('yellow')
        else:
            colors.append('red')

# Calcula a posição dos vértices com base na centralidade;
pos = {}
for node in G.nodes():
    if node in centrality:
        if centrality[node] > mean_centrality * 1.05:
            pos[node] = nx.circular_layout(G, scale=0.6, center=(0, 0))[node]
        elif centrality[node] > mean_centrality:
            pos[node] = nx.circular_layout(G, scale=0.9, center=(0, 0))[node]
        else:
            pos[node] = nx.shell_layout(G, nlist=[list(G.nodes())], scale=1.2)[node]

# Ajuste o tamanho da figura para espaçar os vértices;
plt.figure(figsize=(16, 9))

# Exibe o grafo com vértices menores;
nx.draw(G, pos, with_labels=True, node_color=colors, edge_color='lightgray', node_size=700,font_weight="bold")

# Mostra o gráfico
plt.show()
