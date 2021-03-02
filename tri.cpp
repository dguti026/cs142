#include <iostream>
#include <ctime>
#include "get_time.h"
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
using namespace std;
int main(){
    int n = 1024;

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
    cilk_for (int i = 0; i < n; i++)
    {
        cilk_for (int j = 0; j < n; j++)
        {
          for (int k = 0; k < n; k++){
               	
		C[i][j] += A[i][k] * B[k][j];
		 if(i == 10 && j == 20){
                        cout << "C[10][20]" << " "<< C[i][j] << endl;
                } 
                
            }
            
        }
        
    }
    t.stop();
    cout << "elapsed time: " << t.get_total() << std::endl;
    
    return 0;
}
