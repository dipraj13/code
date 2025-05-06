#include <iostream>
#include <omp.h>
using namespace std;

void printArray(int a[], int n){
    for(int i = 0;i < n;i++){
        cout << a[i] << " " ;
    }
    cout << endl;
}

void merge(int a[], int left , int mid,int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // int arr1[n1];
    // int arr2[n2];
    int* arr1 = new int[n1];
    int* arr2 = new int[n2];

    for(int i = 0;i < n1;i++){
        arr1[i] = a[left + i]; 
    }

    for(int i = 0;i < n2;i++){
        arr2[i] = a[mid + i + 1]; 
    }

    int i = 0, j = 0;
    int k = left;
    while(i < n1 && j < n2){
        if(arr1[i] <= arr2[j]){
            a[k++] = arr1[i++];
        }
        else{
            a[k++] = arr2[j++];
        }
    }

    while(i < n1){
        a[k++] = arr1[i++]; 
    }

    while(j < n2){
        a[k++] = arr2[j++];
    }

    delete[] arr1;
    delete[] arr2;

}

void mergeSort(int a[],int left, int right, int depth = 0){
    if(left < right){
        int mid = (left + right) / 2;

        // mergeSort(a,left , mid);
        // mergeSort(a, mid + 1, right);
        
        if(depth <= 1000){
            #pragma omp parallel sections
            {
            #pragma omp section
            mergeSort(a,left, mid,depth + 1);
            #pragma omp section
            mergeSort(a,mid+1,right,depth +1);
            }
        }
        else{
            mergeSort(a,left, mid,depth + 1);
            mergeSort(a,mid+1,right, depth+1);
        }

        merge(a, left,mid,right);
    }
}



int main(){
    // int array[] = {
    //     34, 7, 23, 32, 5, 62, 78, 21, 56, 90,
    //     12, 11, 13, 5, 6, 7, 99, 45, 27, 67,
    //     88, 43, 76, 18, 29, 39, 2, 8, 1, 55,
    //     60, 70, 19, 84, 3, 16, 31, 22, 50, 42,
    //     35, 28, 91, 74, 33, 61, 25, 4, 14, 10
    // };
    
    int n = 10000000;
    int *array = new int[n];
    for(int i = 0;i < n; i++){
        array[i] = n-i;
    }
    double start = omp_get_wtime();
    mergeSort(array,0,sizeof(array)/sizeof(array[0])-1);
    double end = omp_get_wtime();
    cout << "Time : "<<((end - start)* 1e6)<<endl;
    //printArray(array,sizeof(array)/sizeof(array[0]));
}