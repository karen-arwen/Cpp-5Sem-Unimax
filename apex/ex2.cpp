#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct No {
    int valor;
    int altura;
    No* esquerda;
    No* direita;
};

int altura(No* no) {
    return (no == NULL) ? 0 : no->altura;
}

int fb(No* no) {
    return (no == NULL) ? 0 : altura(no->esquerda) - altura(no->direita);
}

No* criarNo(int valor) {
    No* novo = new No;
    novo->valor = valor;
    novo->altura = 1;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

void atualizarAltura(No* no) {
    if (no != NULL) {
        no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
    }
}

No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* t2 = x->direita;

    x->direita = y;
    y->esquerda = t2;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* t2 = y->esquerda;

    y->esquerda = x;
    x->direita = t2;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) {
        cout << "Inserindo " << valor << '\n';
        return criarNo(valor);
    }

    if (valor < raiz->valor) {
        raiz->esquerda = inserir(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = inserir(raiz->direita, valor);
    } else {
        return raiz;
    }

    atualizarAltura(raiz);
    int fator = fb(raiz);

    if (fator > 1 && valor < raiz->esquerda->valor) {
        cout << "Rotacao LL aplicada no no " << raiz->valor << '\n';
        return rotacaoDireita(raiz);
    }

    if (fator < -1 && valor > raiz->direita->valor) {
        cout << "Rotacao RR aplicada no no " << raiz->valor << '\n';
        return rotacaoEsquerda(raiz);
    }

    if (fator > 1 && valor > raiz->esquerda->valor) {
        cout << "Rotacao LR aplicada no no " << raiz->valor << '\n';
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (fator < -1 && valor < raiz->direita->valor) {
        cout << "Rotacao RL aplicada no no " << raiz->valor << '\n';
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void mostrarEmOrdem(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    mostrarEmOrdem(raiz->esquerda);
    cout << raiz->valor << " ";
    mostrarEmOrdem(raiz->direita);
}

void mostrarArvore(No* raiz, string prefixo, bool ehUltimo) {
    if (raiz == NULL) {
        return;
    }

    cout << prefixo;
    cout << (ehUltimo ? "R----" : "L----");
    cout << raiz->valor << " (h=" << raiz->altura << ", fb=" << fb(raiz) << ")\n";

    string novoPrefixo = prefixo + (ehUltimo ? "     " : "|    ");
    mostrarArvore(raiz->esquerda, novoPrefixo, false);
    mostrarArvore(raiz->direita, novoPrefixo, true);
}

void liberarArvore(No* raiz) {
    if (raiz == NULL) {
        return;
    }

    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    delete raiz;
}

int main() {
    No* raiz = NULL;
    vector<int> valores;
    valores.push_back(50);
    valores.push_back(30);
    valores.push_back(70);
    valores.push_back(20);
    valores.push_back(40);
    valores.push_back(10);

    for (size_t i = 0; i < valores.size(); ++i) {
        raiz = inserir(raiz, valores[i]);
    }

    cout << "\nArvore AVL final:\n";
    mostrarArvore(raiz, "", true);

    cout << "\nEm ordem: ";
    mostrarEmOrdem(raiz);
    cout << '\n';

    liberarArvore(raiz);
    return 0;
}
