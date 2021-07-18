#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <iomanip>
using namespace std;

typedef struct {
    double x;
    double y;
}Pontos;

typedef struct {
    int pai, rank;
}Subset;

class Aresta {
    int v1, v2;
    double peso;

    public:
        Aresta(int u, int v, double w) {
            v1 = u;
            v2 = v;
            this -> peso = w;
        }

        int get_v1() {
            return v1;
        }

        int get_v2() {
            return v2;
        }

        double get_peso() {
            return peso;
        }

        bool operator < (const Aresta& aresta2) const
	    {
		    return (peso < aresta2.peso);
	    }
};

class Grafo {
    int n_vertices;
    vector<Aresta> arestas;

    public:
        Grafo(int v) {
            this -> n_vertices = v;
        }

        void adiciona_arco(int u, int v, double w) {
            if (u != v) {
                Aresta aresta(u, v, w);
                arestas.push_back(aresta);
            }
        }

        int busca(Subset subgrafo[], int i) {
            if (subgrafo[i].pai != i) {
                subgrafo[i].pai = busca(subgrafo, subgrafo[i].pai);
            }
            return subgrafo[i].pai;
        }

        void uniao(Subset subgrafo[], int u, int v) {
            if (subgrafo[u].rank < subgrafo[v].rank) {
                subgrafo[u].pai = v;
            }
            else if (subgrafo[u].rank > subgrafo[v].rank) {
                subgrafo[v].pai = u;
            }
            else {
                subgrafo[v].pai = u;
                subgrafo[u].rank++;
            }
        }

        double kruskal() {
            vector<Aresta> arvore;
            int n_arestas = arestas.size();
            Subset * subgrafo = (Subset *)malloc(n_vertices * sizeof(Subset));
            
            for (int v = 0; v < n_vertices; v++) {
                subgrafo[v].pai = v;
                subgrafo[v].rank = 0;
            }

            sort(arestas.begin(), arestas.end());

            for (int i = 0; i < n_arestas; i++) {
                int u = busca(subgrafo, arestas[i].get_v1());
                int v = busca(subgrafo, arestas[i].get_v2());

                if (u != v) {
                    arvore.push_back(arestas[i]);
                    uniao(subgrafo, u, v);
                }
            }

            int n_arvore = arvore.size();
            double peso = 0;
            for (int i = 0; i < n_arvore; i++) {
                peso += arvore[i].get_peso();
            }

            return peso;
        }
};

double distancia(Pontos p1, Pontos p2) {
    double eixoX = (p1.x - p2.x);
    double eixoY = (p1.y - p2.y);
    return sqrt(eixoX * eixoX + eixoY * eixoY);
}

int main(int argc, char *argv[]) {
    int caso, vertices;
    cin >> caso;

    while (caso--) {
        cin >> vertices;
        Pontos pontos[vertices];

        for (int i = 0; i < vertices; i++) {
            cin >> pontos[i].x >> pontos[i].y;
        }

        Grafo grafo(vertices);
        for (int i = 0; i < vertices; i++){
            for (int j = 0; j < vertices; j++) {
                double peso = distancia(pontos[i], pontos[j]);
                grafo.adiciona_arco(i, j, peso);
            }
        }
        
        double p = grafo.kruskal() / 100;

        cout << fixed;
        cout.precision(2);
        cout << p << endl;
    }
}