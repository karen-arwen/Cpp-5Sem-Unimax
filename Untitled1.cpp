#include <stdio.h>

int main (){
	int i, n;//v[10];
	
	printf("Digite o valor de N:");
	scanf("%d", &n);
	
	int v[n];
	
	
	for(i=0, i<=n-1, i++){
		prinf("Informe o valor da posicao %d: ", i);
		scanf("%d", &v[i]);
	}
	
	for(i=0, i<=n-1, i++){
		prinf("v[%d] = %d\n", i, v[i]);
	}
}
