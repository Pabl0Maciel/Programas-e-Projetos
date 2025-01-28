import networkx as nx
import matplotlib.pyplot as plt
import random

# numero de nos
N = 10

# probabilidade fixa de conexao
#Pe = 0.2

# probalilidade de distribuicao uniforme
Pe = random.uniform(0, 1)

# criar grafo baseado na 

# criar um grafo completo
#G = nx.complete_graph(N)

# criar grafo com probabilidade de conexao
G = nx.erdos_renyi_graph(N, Pe)

# desenhar o grafo
plt.figure(figsize=(6,6))
nx.draw(G, with_labels=True, node_color='lightblue', edge_color='gray', node_size=700, font_size=12)
plt.title(f'Grafo com {N} nos')
plt.show()

# criando histogramas
graus = [d for n, d in G.degree()]
plt.figure(figsize=(8, 6))
plt.hist(graus, bins=range(min(graus), max(graus) + 2), color='skyblue', edgecolor='black', align='left')
plt.title('Histograma dos graus dos nós', fontsize=14)
plt.xlabel('Grau dos nós', fontsize=12)
plt.ylabel('Frequência', fontsize=12)
plt.xticks(range(min(graus), max(graus) + 1))
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.show()