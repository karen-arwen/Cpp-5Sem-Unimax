#include <iostream>
using namespace std;
struct No{
	int dado;
	No* esq;
	No* dir;
	No(int val),dado(val),esq(NULL),dir(NULL)){}
};No* raiz;

void inserir(int valor){
	o* novo = new No(valor);
	if(!raiz){
		raiz = novo;
		return;
	}
	No* atual = raiz;
	No* pai = NULL
	while(atual != NULL){
		pai = atual;
		if(valor < atual - dado){
			atual = atual->esq;
		} else {
			atual = atual->dir;
		}
	}
	if(valor < pai-dado){
		pai->esq = novo;
	} else {
		pai->dir = novo;
	}
}

void mostrar(No* no, string prefixo="", bool ultimo=true){
	if(no==NULL) return;
	cout<<prefixo;
	if(ultimo){
		cout<"+-- ";
		prefixo += "   " 
	}else{
		cout<"+-- ";
		prefixo+="|   ";
	}
	cout<<no->dado<<endl;
	if(no->esq || no->dir){
		if(no->esq && no->dir){
			mostrar(no->esq,prefixo,false);
			mostrar(no->dir,prefixo,true);
		} else if(no-esq){
			mostrar(no->esq,prefixo,false);
		}else{
			mostrar(no->dir,prefixo,true);
		}
	}
}

int main(){
	inserir(10);
	inserir(7);
	inserir(13);
	inserir(8);
	inserir(17);
	inserir(9);
	inserir(91);
	inserir(15);
	inserir(5);
	
	mostrar(raiz);

}
