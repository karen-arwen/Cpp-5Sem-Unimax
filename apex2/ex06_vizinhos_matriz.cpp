#include <iostream>
#include <vector>

using namespace std;

vector<int> vizinhos_matriz(
    const vector<vector<int> >& adj,
    int vertice)
{
    vector<int> vizinhos;
    int n = (int)adj.size();

    for (int j = 0; j < n; j++) {
        if (adj[vertice][j] != 0) {
            vizinhos.push_back(j);
        }
    }

    return vizinhos;
}

int main()
{
    // Grafo do exercicio 8 (sem pesos, apenas adjacencia)
    // Vertices: A=0, B=1, C=2, D=3, E=4, F=5
    int n = 6;
    char nomes[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    // Inicializa matriz 6x6 com zeros
    vector<vector<int> > adj(n, vector<int>(n, 0));

    // A-B
    adj[0][1] = 1; adj[1][0] = 1;
    // A-C
    adj[0][2] = 1; adj[2][0] = 1;
    // B-C
    adj[1][2] = 1; adj[2][1] = 1;
    // B-D
    adj[1][3] = 1; adj[3][1] = 1;
    // C-D
    adj[2][3] = 1; adj[3][2] = 1;
    // C-E
    adj[2][4] = 1; adj[4][2] = 1;
    // D-E
    adj[3][4] = 1; adj[4][3] = 1;
    // D-F
    adj[3][5] = 1; adj[5][3] = 1;
    // E-F
    adj[4][5] = 1; adj[5][4] = 1;

    // Testa para cada vertice
    for (int v = 0; v < n; v++) {
        cout << "Vizinhos de " << nomes[v] << ": ";
        vector<int> viz = vizinhos_matriz(adj, v);
        for (int i = 0; i < (int)viz.size(); i++) {
            cout << nomes[viz[i]];
            if (i + 1 < (int)viz.size()) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
Saida esperada:
Vizinhos de A: B C
Vizinhos de B: A C D
Vizinhos de C: A B D E
Vizinhos de D: B C E F
Vizinhos de E: C D F
Vizinhos de F: D E
*/
