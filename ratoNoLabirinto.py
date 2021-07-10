from collections import defaultdict

class Grafo(object):
    def __init__(self, arestas):
        self.adj = defaultdict(set)
        self.adiciona_arestas(arestas)

    def get_vertices(self):
        return list(self.adj.keys())

    def get_arestas(self):
        return [(k, v) for k in self.adj.keys() for v in self.adj[k]]

    def adiciona_arestas(self, arestas):
        for u, v in arestas:
            self.adiciona_arco(u, v)

    def adiciona_arco(self, u, v):
        self.adj[u].add(v)
        self.adj[v].add(u)

    def existe_aresta(self, u, v):
        return u in self.adj and v in self.adj[u]

    def __str__(self):
        return '{}({})'.format(self.__class__.__name__, dict(self.adj))

def BFS(grafo, fonte, destino):
    visitados, fila = [], [[fonte]]

    if fonte == destino:
        return fila
    
    while fila:
        caminho = fila.pop(0)
        vertice = caminho[-1]
        if vertice not in visitados:
            vizinhos = grafo[vertice]

            for vizinho in vizinhos:
                novo_caminho = list(caminho)
                novo_caminho.append(vizinho)
                fila.append(novo_caminho)

                if vizinho == destino:
                    return novo_caminho
                
            visitados.append(vertice)

def main() :
    input_uri = input()
    n_vertices = int(input_uri.split(" ")[0])
    n_arestas = int(input_uri.split(" ")[1])

    arquivo = open('entradaRatoNoLabirinto.txt', 'w')
    for i in range(n_arestas):
        arquivo.write(input() + "\n")

    arquivo.close()
    arquivo = open('entradaRatoNoLabirinto.txt', 'r')
    entrada = [[] for _ in range(n_arestas)] 

    vertices = arquivo.readlines()
    for idx, val in enumerate(vertices):
        nos = val.split(" ")
        no1 = nos[0]
        no2 = nos[1].split("\n")[0]

        entrada[idx].append(no1)
        entrada[idx].append(no2)

    grafo = Grafo(entrada)
    resultado1 = BFS(grafo.adj, 'Entrada', '*')
    resultado2 = BFS(grafo.adj, '*', 'Saida')
    resultado = (len(resultado1) + len(resultado2) - 2)
    print(resultado)
    return resultado

if __name__ == "__main__":
    main()
