#include<iostream>
#include<vector>
#include<climits>
#include<stack>
#include<queue>
using namespace std;

// Estrutura da árvore Genérica
class No{
public:
    int data;
    vector<No*> filho; // vetor para armazenar filhos do nó

    No(int val){
        data = val;
    }
};

// Classe da árvore genérica de grau n
template <typename T>
class arvore_generica{
public:
    No* no_raiz;

    arvore_generica(T Valor_raiz){
        no_raiz = new No(Valor_raiz);
    }

    // método para adicionar um filho a um nó especifico
    void Add_filho(No* pai, T Valor_filho){
        No* no_filho = new No(Valor_filho);
        pai->filho.push_back(no_filho);
    }

    // método para exibir a árvore
    void mostra_arvore(No* no_filho, string prefixo="", bool e_ultimo=true){
        if(!no_filho) return;

        cout << prefixo;
        cout << (e_ultimo ?
            string() + (char)192 + (char)196 + (char)196 + " " :
            string() + (char)195 + (char)196 + (char)196 + " ");
        cout << no_filho->data << endl;

        prefixo += (e_ultimo ? "    " : string() + (char)179 + "   ");

        for(size_t i = 0; i < no_filho->filho.size(); i++){
            mostra_arvore(no_filho->filho[i], prefixo, i == no_filho->filho.size()-1);
        }
    }

    int menor(No* no){
        if(!no) return INT_MAX;

        int min_val = no->data;
        for(int i = 0; i < no->filho.size(); i++){
            int menor_dos_filhos = menor(no->filho[i]);
            if(menor_dos_filhos < min_val){
                min_val = menor_dos_filhos;
            }
        }
        return min_val;
    }

    int altura(No* no){
        if(!no) return -1;

        int h_max = -1;
        for(int i = 0; i < no->filho.size(); i++){
            h_max = max(h_max, altura(no->filho[i]));
        }
        return h_max + 1;
    }

    int soma(No* no){
        if(!no) return 0;

        int total = no->data;
        for(int i = 0; i < no->filho.size(); i++){
            total += soma(no->filho[i]);
        }
        return total;
    }

    void DFS(No* raiz){
        if(!raiz) return;

        stack<No*> pilha;
        pilha.push(raiz);

        while(!pilha.empty()){
            No* atual = pilha.top();
            pilha.pop();

            cout << atual->data << " ";

            for(int i = atual->filho.size()-1; i >= 0; i--){
                pilha.push(atual->filho[i]);
            }
        }
    }

    void BFS(No* raiz){
        if(!raiz) return;

        queue<No*> fila;
        fila.push(raiz);

        while(!fila.empty()){
            No* atual = fila.front();
            fila.pop();

            cout << atual->data << " ";

            for(int i = 0; i < atual->filho.size(); i++){
                fila.push(atual->filho[i]);
            }
        }
    }

    bool busca_DFS(No* no, int valor){
        if(!no) return false;

        if(no->data == valor)
            return true;

        for(int i = 0; i < no->filho.size(); i++){
            if(busca_DFS(no->filho[i], valor))
                return true;
        }

        return false;
    }

    bool busca_BFS(No* raiz, int valor){
        if(!raiz) return false;

        queue<No*> fila;
        fila.push(raiz);

        while(!fila.empty()){
            No* atual = fila.front();
            fila.pop();

            if(atual->data == valor)
                return true;

            for(int i = 0; i < atual->filho.size(); i++){
                fila.push(atual->filho[i]);
            }
        }

        return false;
    }

    // 1) Contagem de folhas
    int contar_folhas(No* no){
        if(!no) return 0;

        if(no->filho.empty())
            return 1;

        int total = 0;
        for(int i = 0; i < no->filho.size(); i++){
            total += contar_folhas(no->filho[i]);
        }

        return total;
    }

    // 2) Maior valor na árvore
    int maior_valor(No* no){
        if(!no) return INT_MIN;

        int maior = no->data;

        for(int i = 0; i < no->filho.size(); i++){
            int maior_filho = maior_valor(no->filho[i]);
            if(maior_filho > maior){
                maior = maior_filho;
            }
        }

        return maior;
    }

    // 3) Contagem de nós em um nível específico
    int contar_nos_nivel(No* raiz, int k){
        if(!raiz) return 0;

        queue<No*> fila;
        fila.push(raiz);

        int nivel_atual = 0;

        while(!fila.empty()){
            int quantidade = fila.size();

            if(nivel_atual == k){
                return quantidade;
            }

            for(int i = 0; i < quantidade; i++){
                No* atual = fila.front();
                fila.pop();

                for(int j = 0; j < atual->filho.size(); j++){
                    fila.push(atual->filho[j]);
                }
            }

            nivel_atual++;
        }

        return 0;
    }

    // auxiliar para apagar subárvore
    void deletar_subarvore(No* no){
        if(!no) return;

        for(int i = 0; i < no->filho.size(); i++){
            deletar_subarvore(no->filho[i]);
        }

        delete no;
    }

    // 4) Remover nó pelo valor
    bool remover(T valor){
        if(!no_raiz) return false;

        // caso especial: remover a raiz
        if(no_raiz->data == valor){
            deletar_subarvore(no_raiz);
            no_raiz = NULL;
            return true;
        }

        queue<No*> fila;
        fila.push(no_raiz);

        while(!fila.empty()){
            No* atual = fila.front();
            fila.pop();

            for(int i = 0; i < atual->filho.size(); i++){
                if(atual->filho[i]->data == valor){
                    deletar_subarvore(atual->filho[i]);
                    atual->filho.erase(atual->filho.begin() + i);
                    return true;
                }
                fila.push(atual->filho[i]);
            }
        }

        return false;
    }

    // 5) Grau da árvore
    int grau_arvore(No* no){
        if(!no) return 0;

        int maior_grau = no->filho.size();

        for(int i = 0; i < no->filho.size(); i++){
            int grau_filho = grau_arvore(no->filho[i]);
            if(grau_filho > maior_grau){
                maior_grau = grau_filho;
            }
        }

        return maior_grau;
    }
};

int main(){
    // criando a árvore
    arvore_generica<int> arvore(100);

    // adicionar nós
    arvore.Add_filho(arvore.no_raiz, -22);
    arvore.Add_filho(arvore.no_raiz, 13);
    arvore.Add_filho(arvore.no_raiz, 41);
    arvore.Add_filho(arvore.no_raiz, 10);

    // adicionando filhos a nós específicos
    arvore.Add_filho(arvore.no_raiz->filho[0], 5);
    arvore.Add_filho(arvore.no_raiz->filho[0], -6);
    arvore.Add_filho(arvore.no_raiz->filho[1], 7);
    arvore.Add_filho(arvore.no_raiz->filho[2], 8);
    arvore.Add_filho(arvore.no_raiz->filho[2]->filho[0], 133);

    cout << "Arvore Generica de Grau N" << endl;
    arvore.mostra_arvore(arvore.no_raiz);

    cout << "\nMenor valor = " << arvore.menor(arvore.no_raiz) << endl;
    cout << "Maior valor = " << arvore.maior_valor(arvore.no_raiz) << endl;
    cout << "Altura = " << arvore.altura(arvore.no_raiz) << endl;
    cout << "Soma = " << arvore.soma(arvore.no_raiz) << endl;

    cout << "Quantidade de folhas = " << arvore.contar_folhas(arvore.no_raiz) << endl;

    cout << "Nos no nivel 0 = " << arvore.contar_nos_nivel(arvore.no_raiz, 0) << endl;
    cout << "Nos no nivel 1 = " << arvore.contar_nos_nivel(arvore.no_raiz, 1) << endl;
    cout << "Nos no nivel 2 = " << arvore.contar_nos_nivel(arvore.no_raiz, 2) << endl;
    cout << "Nos no nivel 3 = " << arvore.contar_nos_nivel(arvore.no_raiz, 3) << endl;

    cout << "Grau da arvore = " << arvore.grau_arvore(arvore.no_raiz) << endl;

    cout << "\nPercurso DFS: ";
    arvore.DFS(arvore.no_raiz);

    cout << "\nPercurso BFS: ";
    arvore.BFS(arvore.no_raiz);

    cout << "\nBusca DFS (18): " << arvore.busca_DFS(arvore.no_raiz, 18) << endl;
    cout << "Busca BFS (-6): " << arvore.busca_BFS(arvore.no_raiz, -6) << endl;

    cout << "\nRemovendo o no 41..." << endl;
    if(arvore.remover(41)){
        cout << "No removido com sucesso!" << endl;
    }else{
        cout << "No nao encontrado!" << endl;
    }

    cout << "\nArvore apos remocao:" << endl;
    arvore.mostra_arvore(arvore.no_raiz);

    return 0;
}

