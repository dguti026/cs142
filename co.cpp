#include <iostream>
#include <ctime>
#include <stdio.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#ifdef USE_RESTRICT
#else
#define __restrict
#endif
using namespace std;
/*
void mm_base(int *__restrict C, int n_C, int *__restrict A, int n_A, int *__restrict  B, int n_B, int n){
	cout << "here2";
	for(int i = 0; i < n; i++){
		for(int k = 0; k < n; k++){
			for(int j = 0; j < n; j++){
					//cout << i; 
				 C[i*n_C+j] += A[i*n_A+k] * B[k*n_B+j];
					//cout << C[i*n_C+j] << endl;
					 if(i == 10 && j == 20){
                                		cout << "C[10][20]" << " " << C[i*n_C+j] << endl;
                        
                                }
			}
		}
	}

} 
void mm_dac(int *__restrict C, int n_C, int *__restrict A, int n_A, int *__restrict B, int n_B, int n){

	assert((n &(-n)) ==n);
	if(n <= 32){
		mm_base(C, n_C, A, n_A ,B, n_B, n);
	}
	else{
		#define X(M,r,c) (M + (r*(n_ ## M) +c)* (n/2))
		cilk_spawn mm_dac(X(C,0,0), n_C, X(A,0,0), n_A, X(B,0,0), n_B, n/2);
		cilk_spawn mm_dac(X(C,0,1), n_C, X(A,0,0), n_A, X(B,0,1), n_B, n/2);
		cilk_spawn mm_dac(X(C,1,0), n_C, X(A,1,0), n_A, X(B,0,0), n_B, n/2);
		 mm_dac(X(C,1,1), n_C, X(A,1,0), n_A, X(B,0,1), n_B, n/2);
		cilk_sync;
		cilk_spawn mm_dac(X(C,0,0), n_C, X(A,0,1), n_A, X(B,1,0), n_B, n/2);
		cilk_spawn mm_dac(X(C,0,1), n_C, X(A,0,1), n_A, X(B,1,1), n_B, n/2);
		cilk_spawn mm_dac(X(C,1,0), n_C, X(A,1,1), n_A, X(B,1,0), n_B, n/2);
		 mm_dac(X(C,1,1), n_C, X(A,1,1), n_A, X(B,1,1), n_B, n/2);
		cilk_sync;
	}

}
*/
void Rec_Mult(int *__restrict C, int *__restrict A, int *__restrict B, int n, int rowsize){
	if(n <= 32){
	  int r = rowsize;
	  for(int i = 0; i < n; ++i){
		for(int k = 0; k < n; ++k){
			for(int j = 0; j < n; ++j){
				int a = A[i*r+k] * B[k*r+j];
				C[i*r+j] += a;
				if(i == 10 && j == 20){
					cout << "C[10][20]" << " " << C[i*r+j] << endl;
				}
			}
		}
	  }
	}
	else{
		int d11 = 0;
		int d12 = n/2;
		int d21 = (n/2) * rowsize;
		int d22 = (n/2) * (rowsize +1);

		Rec_Mult( C + d11, A + d11, B + d11, n/2, rowsize);
		Rec_Mult( C + d11, A + d12, B + d21, n/2, rowsize);
		Rec_Mult( C + d12, A + d11, B + d12, n/2, rowsize);
		Rec_Mult( C + d12, A + d12, B + d22, n/2, rowsize);
			

		Rec_Mult( C + d21, A + d21, B + d11, n/2, rowsize);
		Rec_Mult( C + d21, A + d22, B + d21, n/2, rowsize);
		Rec_Mult( C + d22, A + d21, B + d12, n/2, rowsize);
		Rec_Mult( C + d22, A + d22, B + d22, n/2, rowsize);
		
	}
}


int main(){
    int n = 1024;
    int** A;
    A = new int*[n];
    int** B;
    B = new int*[n];
    int**  C;
    C = new int*[n];

    for (int i = 0; i < n; i++)
    {
        A[i] = new int[n];
        B[i] = new int[n];
        C[i] = new int[n];
    }
    int m = 1048576;
    int* new_A;
	new_A = new int[m];
    int* new_B;
	new_B = new int[m];
    int* new_C;
	new_C = new int[m];

    cout << " here" << endl;
    int k = 0;
    for(int i = 0; i < n; i++ ){
        for(int j = 0; j < n; j++){
            A[i][j] = i +j;
            B[i][j] = i+2*j;
            C[i][j] = 0;
	
	    new_A[k] = A[i][j];
	    new_B[k] = B[i][j];
	    new_C[k] = C[i][j];
	    ++k;
	   	    
        }
    }
	
	Rec_Mult(new_C, new_A, new_B, n, m);

    return 0;
}
