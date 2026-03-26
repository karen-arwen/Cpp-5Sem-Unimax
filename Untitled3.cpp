#include <iostream>
#include <ctime>
#include <cstdlib>
int main(){
	int ord, i, j;
	cout<<"Informe a ordem da matriz ";
	cin>>ord;
	int mat[ord][ord];
	srand(time(NULL));
	for(i=0;i<ord;i++){
		for(j=0;j<ord;j++){
			if(i==j){
				cout<<mat[i][j]<<" ";
			}
		}
	}
	for(i=0; i)
}
