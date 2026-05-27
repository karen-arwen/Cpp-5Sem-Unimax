#include <iostream>
#include <vector>
#include <queue>
#include <utility>   
#include <climits>   
#include <stack>
#include <string>

using namespace std;

typedef pair<int, int> ParPesoVertice;
typedef vector<vector<ParPesoVertice> > Grafo;

struct MenorDistancia {
    bool operator()(const ParPesoVertice& a, const ParPesoVertice& b) const {
        return a.first > b.first;
    }
};

// Item e -- Dijkstra: retorna vetor de distancias minimas
vector<int> dijkstra_distancias(
    const Grafo& grafo,
    int origem,
    int n)
{
    priority_queue<ParPesoVertice,
                   vector<ParPesoVertice>,
                   MenorDistancia> fila;

    vector<int> dist(n, INT_MAX);
    dist[origem] = 0;
    fila.push(make_pair(0, origem));

    while (!fila.empty()) {
        int d = fila.top().first;
        int u = fila.top().second;
        fila.pop();

        if (d > dist[u]) continue;

        for (int i = 0; i < (int)grafo[u].size(); i++) {
            int peso = grafo[u][i].first;
            int v    = grafo[u][i].second;
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                fila.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

// Item f -- Dijkstra: distancias + exibe caminho ate destino
void dijkstra_com_caminho(
    const Grafo& grafo,
    int origem,
    int destino,
    int n,
    const vector<char>& nomes)
{
    priority_queue<ParPesoVertice,
                   vector<ParPesoVertice>,
                   MenorDistancia> fila;

    vector<int> dist(n, INT_MAX);
    vector<int> anterior(n, -1);

    dist[origem] = 0;
    fila.push(make_pair(0, origem));

    while (!fila.empty()) {
        int d = fila.top().first;
        int u = fila.top().second;
        fila.pop();

        if (d > dist[u]) continue;

        for (int i = 0; i < (int)grafo[u].size(); i++) {
            int peso = grafo[u][i].first;
            int v    = grafo[u][i].second;
            if (dist[u] + peso < dist[v]) {
                dist[v]    = dist[u] + peso;
                anterior[v] = u;
                fila.push(make_pair(dist[v], v));
            }
        }
    }

    stack<int> caminho;
    int atual = destino;
    while (atual != -1) {
        caminho.push(atual);
        atual = anterior[atual];
    }

    cout << "Menor caminho de "
         << nomes[origem] << " ate " << nomes[destino] << ": ";

    while (!caminho.empty()) {
        cout << nomes[caminho.top()];
        caminho.pop();
        if (!caminho.empty()) cout << " -> ";
    }

    cout << "\nCusto total: " << dist[destino] << "\n" << endl;
}

// Main -- demonstracao com o grafo do exercicio 8
int main()
{
    // Vertices: A=0, B=1, C=2, D=3, E=4, F=5
    int n = 6;
    vector<char> nomes;
    nomes.push_back('A');
    nomes.push_back('B');
    nomes.push_back('C');
    nomes.push_back('D');
    nomes.push_back('E');
    nomes.push_back('F');

    Grafo grafo(n);

    // grafo[u] e grafo[v] recebem o par (peso, outro_vertice)
    // A-B: 4
    grafo[0].push_back(make_pair(4, 1));
    grafo[1].push_back(make_pair(4, 0));
    // A-C: 2
    grafo[0].push_back(make_pair(2, 2));
    grafo[2].push_back(make_pair(2, 0));
    // B-C: 1
    grafo[1].push_back(make_pair(1, 2));
    grafo[2].push_back(make_pair(1, 1));
    // B-D: 5
    grafo[1].push_back(make_pair(5, 3));
    grafo[3].push_back(make_pair(5, 1));
    // C-D: 8
    grafo[2].push_back(make_pair(8, 3));
    grafo[3].push_back(make_pair(8, 2));
    // C-E: 10
    grafo[2].push_back(make_pair(10, 4));
    grafo[4].push_back(make_pair(10, 2));
    // D-E: 2
    grafo[3].push_back(make_pair(2, 4));
    grafo[4].push_back(make_pair(2, 3));
    // D-F: 6
    grafo[3].push_back(make_pair(6, 5));
    grafo[5].push_back(make_pair(6, 3));
    // E-F: 3
    grafo[4].push_back(make_pair(3, 5));
    grafo[5].push_back(make_pair(3, 4));

    // --- Item e: apenas distancias ---
    cout << "=== Item e: distancias minimas a partir de A ===" << endl;
    vector<int> dists = dijkstra_distancias(grafo, 0, n);
    for (int i = 0; i < n; i++) {
        cout << "A -> " << nomes[i] << ": " << dists[i] << endl;
    }
    cout << endl;

    // --- Item f: caminho completo ---
    cout << "=== Item f: caminhos minimos com rota ===" << endl;
    dijkstra_com_caminho(grafo, 0, 3, n, nomes); // A -> D
    dijkstra_com_caminho(grafo, 0, 4, n, nomes); // A -> E
    dijkstra_com_caminho(grafo, 0, 5, n, nomes); // A -> F

    return 0;
}

/*
Saida esperada:
=== Item e: distancias minimas a partir de A ===
A -> A: 0
A -> B: 3
A -> C: 2
A -> D: 8
A -> E: 10
A -> F: 13

=== Item f: caminhos minimos com rota ===
Menor caminho de A ate D: A -> C -> B -> D
Custo total: 8

Menor caminho de A ate E: A -> C -> B -> D -> E
Custo total: 10

Menor caminho de A ate F: A -> C -> B -> D -> E -> F
Custo total: 13
*/
