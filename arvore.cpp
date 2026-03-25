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

    // 1. Contagem de Folhas - Conta nós que não possuem filhos
    int contar_folhas(No* no_filho){
        if(!no_filho) return 0;
        // Se o nó não possui filhos, é uma folha
        if(no_filho->filho.empty()){
            return 1;
        }
        // Caso contrário, soma as folhas de todos os filhos
        int folhas = 0;
        for(int i=0; i<no_filho->filho.size(); i++){
            folhas += contar_folhas(no_filho->filho[i]);
        }
        return folhas;
    }

    // 2. Maior Valor na Árvore - Retorna o maior valor inteiro armazenado
    int maior_valor(No* raiz){
        if(!raiz) return INT_MIN;
        int maior = raiz->data;
        for(int i=0; i<raiz->filho.size(); i++){
            int maior_filho = maior_valor(raiz->filho[i]);
            if(maior_filho > maior){
                maior = maior_filho;
            }
        }
        return maior;
    }

    // 3. Contagem de Nós em um Nível Específico - BFS para percorrer nível por nível
    int contar_nos_nivel(No* raiz, int k){
        if(!raiz) return 0;
        if(k < 0) return 0;
        
        if(k == 0) return 1; // a raiz está no nível 0
        
        int contador = 0;
        for(int i=0; i<raiz->filho.size(); i++){
            // Reduz k em 1 para cada chamada recursiva
            contador += contar_nos_nivel(raiz->filho[i], k - 1);
        }
        return contador;
    }

    // 4. Remoção de um Nó pela Valor - Remove o nó e sua subárvore
    bool remover(No* raiz, int valor){
        if(!raiz) return false;
        
        // Procura o valor nos filhos da raiz
        for(int i=0; i<raiz->filho.size(); i++){
            if(raiz->filho[i]->data == valor){
                // Encontrou! Agora deleta a subárvore
                deletar_subarvore(raiz->filho[i]);
                // Remove o ponteiro do vetor
                raiz->filho.erase(raiz->filho.begin() + i);
                return true;
            }
            // Continua procurando nos filhos
            if(remover(raiz->filho[i], valor)){
                return true;
            }
        }
        return false;
    }

    // Função auxiliar para deletar toda uma subárvore
    void deletar_subarvore(No* no){
        if(!no) return;
        // Primeiro deleta todos os filhos recursivamente
        for(int i=0; i<no->filho.size(); i++){
            deletar_subarvore(no->filho[i]);
        }
        // Depois deleta o nó
        delete no;
    }

    // 5. Identificar o Grau da Árvore - Retorna o maior grau entre todos os nós
    int grau_arvore(No* raiz){
        if(!raiz) return 0;
        
        // O grau do nó atual é a quantidade de filhos
        int grau_atual = raiz->filho.size();
        int grau_maximo = grau_atual;
        
        // Procura o maior grau nos filhos
        for(int i=0; i<raiz->filho.size(); i++){
            int grau_filho = grau_arvore(raiz->filho[i]);
            if(grau_filho > grau_maximo){
                grau_maximo = grau_filho;
            }
        }
        return grau_maximo;
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
    arvore.Add_filho(arvore.no_raiz->filho[0], 8);

    cout << "===== MÉTODOS ORIGINAIS =====" << endl;
    cout << "Menor elemento: " << arvore.menor_elemento(arvore.no_raiz) << endl;
    cout << "Maior elemento: " << arvore.maior_elemento(arvore.no_raiz) << endl;
    cout << "Soma de todos os elementos: " << arvore.soma_elementos(arvore.no_raiz) << endl;
    cout << "Total de nós: " << arvore.total_nos(arvore.no_raiz) << endl;
    cout << "Altura da árvore: " << arvore.altura_arvore(arvore.no_raiz) << endl;
    
    cout << "\n===== NOVOS MÉTODOS =====" << endl;
    cout << "1. Contagem de Folhas: " << arvore.contar_folhas(arvore.no_raiz) << endl;
    cout << "2. Maior Valor: " << arvore.maior_valor(arvore.no_raiz) << endl;
    cout << "3. Nós no nível 0: " << arvore.contar_nos_nivel(arvore.no_raiz, 0) << endl;
    cout << "3. Nós no nível 1: " << arvore.contar_nos_nivel(arvore.no_raiz, 1) << endl;
    cout << "3. Nós no nível 2: " << arvore.contar_nos_nivel(arvore.no_raiz, 2) << endl;
    cout << "5. Grau da árvore: " << arvore.grau_arvore(arvore.no_raiz) << endl;
    
    cout << "\n===== TESTE DE REMOÇÃO =====" << endl;
    cout << "Total de nós antes da remoção: " << arvore.total_nos(arvore.no_raiz) << endl;
    arvore.remover(arvore.no_raiz, 2);
    cout << "Total de nós após remover 2: " << arvore.total_nos(arvore.no_raiz) << endl;

    return 0;
}