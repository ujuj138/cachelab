#include<stdio.h>

int main(){
	int i, j, count = 0;
	for(i = 0; i < 64; i++){
		for(j = 0; j < 64; j++){
			printf("%d ", count);
			count++;
		}
		printf("\n");
	}
} 
