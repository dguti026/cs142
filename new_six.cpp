#include <iostream>
#include <ctime>
#include "get_time.h"
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
using namespace std;
int main(){
    int n = 32;

    int** A;
    A = new int*[n];
    int** B;
    B = new int*[n];
    int** C;
    C = new int*[n];

    for (int i = 0; i < n; i++)
    {
        A[i] = new int[n];
        B[i] = new int[n];
        C[i] = new int[n];
        for(int j = 0; j < n; ++j){
            A[i][j] = 0;
            B[i][j] = 0;
            C[i][j] = 0;
        }
    }


    cout << " here" << endl;
    cilk_for(int i = 0; i < n; ++i ){
        for(int j = 0; j < n; ++j){
            A[i][j] = i +j;
            B[i][j] = i+2*j;
            C[i][j] = 0;
        }
    }
   timer t;	
   int s = 8;
   cilk_for(int i_1 = 0; i_1 <n; i_1+=s){ 
 	
  	cilk_for(int j_1 = 0; j_1 < n; j_1 +=s){

		for(int k_1 = 0; k_1 < n; k_1 +=s){

			for(int i = i_1; i < i_1+s; ++i){

				for(int j = j_1; j < j_1+s; ++j){

					for(int k = k_1;k < k_1+s; ++k){

						C[i][j] += A[i][k] * B[k][j];
                				 if(i == 10 && j == 20){
                       					 cout << "C[10][20]" << " "<< C[i][j] << endl;
               					  }		
					}
				}
			}
		}
	}
   }
    
    t.stop();
    cout << "elapsed time: " << t.get_total() << std::endl;

    return 0;
}

