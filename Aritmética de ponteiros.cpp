#include <stdio.h>

int main(){
	
	int vetor[2];
	
	vetor[0] = 9;
	vetor[1] = 10;
	
	printf("%d\n", *vetor);
	printf("%d\n", *(vetor + 1));
	
	return 0;
}