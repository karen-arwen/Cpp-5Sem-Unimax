#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct No {
    char data;
    vector<No*> filhos;
};

No* criarNo(char data) {
    No* novo = new No;
    novo->data = data;
    return novo;
}

void mostrarArvore(No* raiz, string prefixo, bool ultimo) {
    if (raiz == NULL) {
        return;
    }

    cout << prefixo;
    if (ultimo) {
        cout << "+-- ";
        prefixo += "   ";
    } else {
        cout << "+-- ";
        prefixo += "|  ";
    }
    cout << raiz->data << endl;

    for (size_t i = 0; i < raiz->filhos.size(); ++i) {
        bool ehUltimo = (i == raiz->filhos.size() - 1);
        mostrarArvore(raiz->filhos[i], prefixo, ehUltimo);
    }
}

void dfs(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    stack<No*> pilha;
    pilha.push(raiz);

    cout << "DFS iterativo a partir da raiz: ";
    while (!pilha.empty()) {
        No* atual = pilha.top();
        pilha.pop();

        cout << atual->data << " ";

        for (int i = static_cast<int>(atual->filhos.size()) - 1; i >= 0; --i) {
            pilha.push(atual->filhos[i]);
        }
    }
    cout << '\n';
}

void liberarArvore(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    for (size_t i = 0; i < raiz->filhos.size(); ++i) {
        liberarArvore(raiz->filhos[i]);
    }

    delete raiz;
}

int main() {
    No* A = criarNo('A');
    No* B = criarNo('B');
    No* C = criarNo('C');
    No* D = criarNo('D');
    No* E = criarNo('E');
    No* F = criarNo('F');
    No* G = criarNo('G');
    No* H = criarNo('H');

    A->filhos.push_back(B);
    A->filhos.push_back(C);
    A->filhos.push_back(D);
    C->filhos.push_back(E);
    D->filhos.push_back(F);
    F->filhos.push_back(G);
    F->filhos.push_back(H);

    cout << "Arvore:\n";
    mostrarArvore(A, "", true);
    cout << endl;

    dfs(A);

    liberarArvore(A);
    return 0;
}
