// Usando arvore generica dinamica de grau "N". crie as rotinas:
// encontre o menor elemento da arvore
// encontre o maior elemento da arvore
// encontre a soma de todos os elementos da arvore
// descubra o total de nós da arvore
// descubra a altura da arvore
#include<iostream>
#include<vector>
using namespace std;

class No{
public:
    int data;
    vector<No*> filho;
    No(int val){
        data = val;
    }
};

template <typename T>
class arvore_generica{
public:
    No* no_raiz;
    arvore_generica(T Valor_raiz){
        no_raiz = new No(Valor_raiz);
    }

    void Add_filho(No* pai, T Valor_filho){
        No*  no_filho = new No(Valor_filho);
        pai->filho.push_back(no_filho);
    }

    int menor_elemento(No* no_filho){
        if(!no_filho) return INT_MAX;
        int menor = no_filho->data;
        for(int i=0; i<no_filho->filho.size(); i++){
            int menor_filho = menor_elemento(no_filho->filho[i]);
            if(menor_filho < menor){
                menor = menor_filho;
            }
        }
        return menor;
    }

    int maior_elemento(No* no_filho){
        if(!no_filho) return INT_MIN;
        int maior = no_filho->data;
        for(int i=0; i<no_filho->filho.size(); i++){
            int maior_filho = maior_elemento(no_filho->filho[i]);
            if(maior_filho > maior){
                maior = maior_filho;
            }
        }
        return maior;
    }

    int soma_elementos(No* no_filho){
        if(!no_filho) return 0;
        int soma = no_filho->data;
        for(int i=0; i<no_filho->filho.size(); i++){
            soma += soma_elementos(no_filho->filho[i]);
        }
        return soma;
    }

    int total_nos(No* no_filho){
        if(!no_filho) return 0;
        int total = 1; // conta o nó atual
        for(int i=0; i<no_filho->filho.size(); i++){
            total += total_nos(no_filho->filho[i]);
        }
        return total;
    }

    int altura_arvore(No* no_filho){
        if(!no_filho) return -1; // altura de uma árvore vazia é -1
        int altura_max = -1;
        for(int i=0; i<no_filho->filho.size(); i++){
            int altura_filho = altura_arvore(no_filho->filho[i]);
            if(altura_filho > altura_max){
                altura_max = altura_filho;
            }
        }
        return altura_max + 1; // adiciona 1 para contar o nó atual
    }
};

int main(){
    arvore_generica<int> arvore(1);
    arvore.Add_filho(arvore.no_raiz, 2);
    arvore.Add_filho(arvore.no_raiz, 3);
    arvore.Add_filho(arvore.no_raiz, 4);
    arvore.Add_filho(arvore.no_raiz->filho[0], 5);
    arvore.Add_filho(arvore.no_raiz->filho[0], 6);
    arvore.Add_filho(arvore.no_raiz->filho[0], 7);
    arvore.Add_filho(arvore.no_raiz->filho[0], 5);

    cout << "Menor elemento: " << arvore.menor_elemento(arvore.no_raiz) << endl;
    cout << "Maior elemento: " << arvore.maior_elemento(arvore.no_raiz) << endl;
    cout << "Soma de todos os elementos: " << arvore.soma_elementos(arvore.no_raiz) << endl;
    cout << "Total de nós: " << arvore.total_nos(arvore.no_raiz) << endl;
    cout << "Altura da árvore: " << arvore.altura_arvore(arvore.no_raiz) << endl;

    return 0;
}