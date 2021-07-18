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

        int busca(int subgrafo[], int i) {
            if (subgrafo[i] == -1) {
                return i;
            }
            return busca(subgrafo, subgrafo[i]);
        }

        void uniao(int subgrafo[], int u, int v) {
            int u_set = busca(subgrafo, u);
            int v_set = busca(subgrafo, v);
            subgrafo[u_set] = v_set;
        }

        double kruskal() {
            vector<Aresta> arvore;
            int n_arestas = arestas.size();
            int * subgrafo = new int[n_vertices];
            memset(subgrafo, -1, sizeof(int) * n_vertices);

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