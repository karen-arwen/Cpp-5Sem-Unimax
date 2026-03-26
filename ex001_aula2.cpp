/*Preencher uma matriz MxN de dimensões fornecidas via teclado com números
aleatorios inteiros na faixa de 0 a 9.*/
#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;
int main(){
	int lin, col, i, j;
	cout<<"Informe a dimensao linha ";
	cin>>lin;
	cout<<"Informe a dimensao coluna "; 
	cin>>col;
		int mat[lin][col], mat_T[lin][col];
		srand(time(NULL));
		
		for(i=0; j<lin; i++){
			for(j=0; j<col; j++){
				aux = rand()%10; //faixa de 0 a 9;
				if(aux >= 10){
					mat[i][j] = aux;
				}
			}
		}
		for(i=0; i<lin; i++){
			for(j=0; j<col; j++){
				cout<<mat[i][j]<<" ";
			}
			cout<<endl<<endl;
		}
}
