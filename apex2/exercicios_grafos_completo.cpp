#include <climits>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> ParPesoVertice; // (peso, vertice)
typedef vector<vector<ParPesoVertice> > GrafoPonderado;

struct MenorDistancia {
    bool operator()(const ParPesoVertice& a, const ParPesoVertice& b) const {
        return a.first > b.first;
    }
};

vector<int> vizinhos_matriz(const vector<vector<int> >& adj, int vertice) {
    vector<int> vizinhos;

    if (vertice < 0 || vertice >= (int)adj.size()) {
        return vizinhos;
    }

    for (int j = 0; j < (int)adj[vertice].size(); j++) {
        if (adj[vertice][j] != 0) {
            vizinhos.push_back(j);
        }
    }

    return vizinhos;
}

vector<int> vizinhos_lista(const vector<vector<int> >& lista, int vertice) {
    if (vertice < 0 || vertice >= (int)lista.size()) {
        return vector<int>();
    }

    return lista[vertice];
}

void dijkstra(const GrafoPonderado& grafo,
              int origem,
              vector<int>& dist,
              vector<int>& anterior) {
    int n = (int)grafo.size();
    priority_queue<ParPesoVertice, vector<ParPesoVertice>, MenorDistancia> fila;

    dist.assign(n, INT_MAX);
    anterior.assign(n, -1);

    dist[origem] = 0;
    fila.push(make_pair(0, origem));

    while (!fila.empty()) {
        int distancia_atual = fila.top().first;
        int u = fila.top().second;
        fila.pop();

        if (distancia_atual > dist[u]) {
            continue;
        }

        for (int i = 0; i < (int)grafo[u].size(); i++) {
            int peso = grafo[u][i].first;
            int v = grafo[u][i].second;

            if (dist[u] != INT_MAX && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                anterior[v] = u;
                fila.push(make_pair(dist[v], v));
            }
        }
    }
}

vector<int> montar_caminho(int destino, const vector<int>& anterior) {
    stack<int> pilha;
    vector<int> caminho;

    int atual = destino;
    while (atual != -1) {
        pilha.push(atual);
        atual = anterior[atual];
    }

    while (!pilha.empty()) {
        caminho.push_back(pilha.top());
        pilha.pop();
    }

    return caminho;
}

void adicionar_aresta_nao_orientada(GrafoPonderado& grafo, int a, int b, int peso) {
    grafo[a].push_back(make_pair(peso, b));
    grafo[b].push_back(make_pair(peso, a));
}

void imprimir_vizinhos(const vector<int>& vizinhos, const vector<char>& nomes) {
    if (vizinhos.empty()) {
        cout << "nenhum";
    }

    for (int i = 0; i < (int)vizinhos.size(); i++) {
        cout << nomes[vizinhos[i]];
        if (i + 1 < (int)vizinhos.size()) {
            cout << " ";
        }
    }

    cout << endl;
}

int main() {
    const int n = 6;
    vector<char> nomes;
    nomes.push_back('A');
    nomes.push_back('B');
    nomes.push_back('C');
    nomes.push_back('D');
    nomes.push_back('E');
    nomes.push_back('F');

    vector<vector<int> > matriz(n, vector<int>(n, 0));
    vector<vector<int> > lista(n);
    GrafoPonderado grafo(n);

    int arestas[][3] = {
        {0, 1, 4},
        {0, 2, 2},
        {1, 2, 1},
        {1, 3, 5},
        {2, 3, 8},
        {2, 4, 10},
        {3, 4, 2},
        {3, 5, 6},
        {4, 5, 3}
    };

    int quantidade_arestas = sizeof(arestas) / sizeof(arestas[0]);

    for (int i = 0; i < quantidade_arestas; i++) {
        int a = arestas[i][0];
        int b = arestas[i][1];
        int peso = arestas[i][2];

        matriz[a][b] = 1;
        matriz[b][a] = 1;

        lista[a].push_back(b);
        lista[b].push_back(a);

        adicionar_aresta_nao_orientada(grafo, a, b, peso);
    }

    cout << "=== Exercicio 6: vizinhos por matriz de adjacencia ===" << endl;
    for (int v = 0; v < n; v++) {
        cout << "Vizinhos de " << nomes[v] << ": ";
        imprimir_vizinhos(vizinhos_matriz(matriz, v), nomes);
    }

    cout << "\n=== Exercicio 7: vizinhos por lista de adjacencia ===" << endl;
    for (int v = 0; v < n; v++) {
        cout << "Vizinhos de " << nomes[v] << ": ";
        imprimir_vizinhos(vizinhos_lista(lista, v), nomes);
    }

    cout << "\n=== Exercicio 8: Dijkstra a partir de A ===" << endl;
    vector<int> dist;
    vector<int> anterior;
    dijkstra(grafo, 0, dist, anterior);

    cout << "Distancias minimas:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "A -> " << nomes[i] << ": " << dist[i] << endl;
    }

    cout << "\nCaminhos solicitados:" << endl;
    int destinos[] = {3, 4, 5}; // D, E, F
    for (int i = 0; i < 3; i++) {
        int destino = destinos[i];
        vector<int> caminho = montar_caminho(destino, anterior);

        cout << "Menor caminho de A ate " << nomes[destino] << ": ";
        for (int j = 0; j < (int)caminho.size(); j++) {
            cout << nomes[caminho[j]];
            if (j + 1 < (int)caminho.size()) {
                cout << " -> ";
            }
        }
        cout << "\nCusto total: " << dist[destino] << "\n" << endl;
    }

    int destino_usuario;
    cout << "Digite um destino para ver o caminho a partir de A (0=A, 1=B, 2=C, 3=D, 4=E, 5=F): ";
    cin >> destino_usuario;

    if (destino_usuario >= 0 && destino_usuario < n) {
        vector<int> caminho = montar_caminho(destino_usuario, anterior);

        cout << "Menor caminho de A ate " << nomes[destino_usuario] << ": ";
        for (int i = 0; i < (int)caminho.size(); i++) {
            cout << nomes[caminho[i]];
            if (i + 1 < (int)caminho.size()) {
                cout << " -> ";
            }
        }
        cout << "\nCusto total: " << dist[destino_usuario] << endl;
    } else {
        cout << "Destino invalido." << endl;
    }

    return 0;
}
