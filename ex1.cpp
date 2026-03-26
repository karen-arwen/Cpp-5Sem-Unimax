#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main (){
	int v[10], i;
	srand(time(NULL));
	
	for(i=0; i<10; i++){
		v[i]= rand()%20; //faixa de calores de 0 a 19
	}
	
	cout <<endl;
	for(i=0; i<10; i++){
		cout<<"V["<<i<<"] = "<<v[i]<<endl;
	}
	
	return 0;
}
