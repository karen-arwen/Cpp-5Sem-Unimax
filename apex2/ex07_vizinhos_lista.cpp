#include <iostream>
#include <vector>

using namespace std;

vector<int> vizinhos_lista(
    const vector<vector<int> >& lista,
    int vertice)
{
    return lista[vertice];
}

int main()
{
    // Grafo do exercicio 8 
    // Vertices: A=0, B=1, C=2, D=3, E=4, F=5
    int n = 6;
    char nomes[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    vector<vector<int> > lista(n);

    // A-B
    lista[0].push_back(1); lista[1].push_back(0);
    // A-C
    lista[0].push_back(2); lista[2].push_back(0);
    // B-C
    lista[1].push_back(2); lista[2].push_back(1);
    // B-D
    lista[1].push_back(3); lista[3].push_back(1);
    // C-D
    lista[2].push_back(3); lista[3].push_back(2);
    // C-E
    lista[2].push_back(4); lista[4].push_back(2);
    // D-E
    lista[3].push_back(4); lista[4].push_back(3);
    // D-F
    lista[3].push_back(5); lista[5].push_back(3);
    // E-F
    lista[4].push_back(5); lista[5].push_back(4);

    // Testa para cada vertice
    for (int v = 0; v < n; v++) {
        cout << "Vizinhos de " << nomes[v] << ": ";
        vector<int> viz = vizinhos_lista(lista, v);
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
