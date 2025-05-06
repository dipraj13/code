#include <iostream>
#include <omp.h>
using namespace std;


void printArray(int arr[], int n){
    for(int i=0;i<n;i++){
        cout<<arr[i] << " ";
    }
    cout<<endl;
}

void seqBubble(int arr[], int n){

    for(int i = 0;i<n-1;i++){
        for(int j = 0;j<n-i;j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void paraBubble(int arr[],int n){
    for(int i =0; i<n;i++){
        #pragma omp parallel for
        for(int j=0;j<n-1;j+=2){
            if(arr[j] > arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }

        #pragma omp parallel for
        for(int j = 1;j<n-1;j+=2){
            if(arr[j] > arr[j+1]){
                swap(arr[j],arr[j+1]);
            }   
        }
    }
}

int main(){
    int n= 100000;
    int arr[n], arr1[n];

    for(int i =n ;i>0;i--){
        arr[i] = arr1[i] = i;
    }

    double start = omp_get_wtime();
    seqBubble(arr,n);
    double end = omp_get_wtime();
    cout << "The time seq : " << end -start<<endl;

    start = omp_get_wtime();
    paraBubble(arr1,n);
    end = omp_get_wtime();
    cout << "The time para : "<<end-start << endl;

    return 0;
}