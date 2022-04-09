import networkx as nx
G = nx.read_gml('data/football.gml')
nx.write_graphml(G, 'data/football.graphml')