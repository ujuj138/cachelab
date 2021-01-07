/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"
int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{	
	int i, j, x, y;
	int tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
	if(M == 32){
		for(x = 0; x < N; x = x + (256/M)){
			for(y = 0; y < M; y = y + (256/M)){
				for(i = x; i < x + (256/M); i++){
					for(j = y; j < y + (256/M); j++){
						if(i != j){
							B[j][i] = A[i][j];
						}else{
							tmp0 = A[i][i];
							tmp1 = i;
						}						
					}
					if(x == y){
						B[tmp1][tmp1] = tmp0;
					}
				} 
			}
		}
	}else if(M == 64){
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
	}else{
		for(x = 0; x < N; x = x + 16){
			for(y = 0; y < M; y = y + 16){
				for(i = x; i < x + 16 && i < N; i++){
					for(j = y; j < y + 16 && j < M; j++){
						if(i != j){
							B[j][i] = A[i][j];
						}else{
							tmp0 = A[i][i];
							tmp1 = i;
						}						
					}
					if(x == y){
						B[tmp1][tmp1] = tmp0;
					}
				} 
			}
		}
	} 
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

