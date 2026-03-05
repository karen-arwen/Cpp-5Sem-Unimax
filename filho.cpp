#include<iostream>
#include<vector>
using namespace std;
//estrutura do nó da arvore generica
class No{
public:
    int data;
    vector<No*> filho;
    // vetor para armazenar filhos do nó
    No(int val){
        data = val;
    }
};

template <typename T>
class arvore_generica
public:
    No* no_raiz;
    arvore_generica(T Valor_raiz){
        no_raiz = new No(Valor_raiz);
    }

    //metodo para add um filho a um no
    void Add_filho(No* pai, T Valor_filho){
        No*  no_filho = new No(Valor_filho);
        pai->filho.push_back(no_filho);
    }

    void mostra_arvore(No* no_filho, string prefixo="", cool e_ultimo=true){
        if(!no_filho) return;
        cout<<prefixo;
        cout<<(e_ultimo) ?
        string() + (char)192 + (char)196 + (char)196 + " ";
        string() + (char)195 + (char)196 + (char)196 + " ";
        cout<<no_filho -> data<<endl;
        prefixo+=(e_ultimo ? " ":string()+(char)179 + " ")
        for(int i=0; i<no_filho->filho.size(); i++){
            mostra_arvore(no_filho->filho[i],prefixo,i==no_filho->filho.size());
        }
    }
}

int main(){
    //criar a arvore
    arvore_generica<int> arvore(1);
    //adicionando os nós
    arvore:Add_filho(arvore.no_raiz, 2);
    arvore:Add_filho(arvore.no_raiz, 3);
    arvore:Add_filho(arvore.no_raiz, 4);

    //adicionar filhos em um nó especifico
    arvore.Add_filho(arvore.no_raiz->filho[0], 5);
    arvore.Add_filho(arvore.no_raiz->filho[0], 6);
    arvore.Add_filho(arvore.no_raiz->filho[0], 7);
    arvore.Add_filho(arvore.no_raiz->filho[0], 5);



}