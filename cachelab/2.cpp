#include<stdio.h>

int main(){
	int A[64][64], B[64][64];	
	int i, j, x, y;
	int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
	FILE * fp = fopen("trans2.txt", "r");
	for(i = 0; i < 64; i++){
		for(j = 0; j < 64; j++){
			A[i][j] = 0;
			B[i][j] = 0;
		}
	}
	
	for(i = 0; i < 64; i++){
		for(j = 0; j < 64; j++){
			fscanf(fp, "%d", &A[i][j]);
		}
	}
	
		for(i = 0; i < 64; i = i + 8){
			for(j = 0; j < 64; j = j + 8){
				for(x = j; x < j + 4; x++){
					tmp0 = A[x][i];
					tmp1 = A[x][i + 1];
					tmp2 = A[x][i + 2];
					tmp3 = A[x][i + 3];
					tmp4 = A[x][i + 4];
					tmp5 = A[x][i + 5];
					tmp6 = A[x][i + 6];
					tmp7 = A[x][i + 7];
					B[i][x] = tmp0;
					B[i][x + 4] = tmp4;
					B[i + 1][x] = tmp1;
					B[i + 1][x + 4] = tmp5;
					B[i + 2][x] = tmp2;
					B[i + 2][x + 4] = tmp6;
					B[i + 3][x] = tmp3;
					B[i + 3][x + 4] = tmp7;
				}
				for(x = i; x < i + 4; x++){
					tmp0 = B[x][j + 4];
					tmp1 = B[x][j + 5];
					tmp2 = B[x][j + 6];
					tmp3 = B[x][j + 7];
					tmp4 = A[j + 4][x];
					tmp5 = A[j + 5][x];
					tmp6 = A[j + 6][x];
					tmp7 = A[j + 7][x];
					B[x][j + 4] = tmp4;
					B[x][j + 5] = tmp5;
					B[x][j + 6] = tmp6;
					B[x][j + 7] = tmp7;
					B[x + 4][j] = tmp0;
					B[x + 4][j + 1] =  tmp1;
					B[x + 4][j + 2] =  tmp2;
					B[x + 4][j + 3] =  tmp3;
				}
				for(x = i + 4; x < i + 8; x++){
					tmp0 = A[j + 4][x];
					tmp1 = A[j + 5][x];
					tmp2 = A[j + 6][x];
					tmp3 = A[j + 7][x];
					B[x][j + 4] = tmp0;
					B[x][j + 5] = tmp1;
					B[x][j + 6] = tmp2;
					B[x][j + 7] = tmp3;
				}
			}
		}
	for(i = 0; i < 64; i++){
		for(j = 0; j < 64; j++){
			printf("%d ", B[i][j]);
		}
		printf("\n\n");
	}

	
	fclose(fp);
} 
