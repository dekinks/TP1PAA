from collections import defaultdict
import string

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

def DFS(visitados, grafo, no):
    if no not in visitados:
        visitados.append(no)
        for vizinho in grafo[no]:
            DFS(visitados, grafo, vizinho)
    return visitados

def main() :
    caso = 1
    n_casos = int(input())

    while n_casos != 0 :
        input_uri = input()
        n_vertices = int(input_uri.split(" ")[0])
        n_arestas = int(input_uri.split(" ")[1])

        arquivo = open('entradaComponentesConexos.txt', 'w')
        for i in range(n_arestas):
            arquivo.write(input() + "\n")

        arquivo.close()
        arquivo = open('entradaComponentesConexos.txt', 'r')
        entrada = [[] for _ in range(n_arestas)]
        elementos = [] 

        arestas = arquivo.readlines()
        for idx, val in enumerate(arestas):
            nos = val.split(" ")
            no1 = nos[0]
            no2 = nos[1].split("\n")[0]

            entrada[idx].append(no1)
            entrada[idx].append(no2)

            if (no1 not in elementos):
                elementos.append(no1)
            if (no2 not in elementos):
                elementos.append(no2)
        
        elementos.sort()
        a = list(string.ascii_lowercase[0 : n_vertices])
        
        if (elementos != a and n_vertices > len(elementos)):
            tam = n_vertices - len(elementos)
            diferenca = list(set(a) - set(elementos))
            diferenca[0 : tam]
            for letra in diferenca:
                elementos.append(letra)
        
        grafo = Grafo(entrada)

        print("Case #" + str(caso) + ":")

        visitados = []
        num = 0
        elementos.sort()
        for fonte in elementos:
            if (fonte not in visitados):
                componente = DFS([], grafo.adj, fonte)
                visitados = visitados + componente
                componente.sort()
                print(str(','.join(componente))+",")
                num += 1

        print(str(num) + " connected components\n")
        n_casos -= 1
        caso += 1

if __name__ == "__main__":
    main()
