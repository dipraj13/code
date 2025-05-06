#include <iostream>
#include <omp.h>
using namespace std;

int sum(int arr[], int n){
    int count = 0;
    #pragma omp parallel for reduction(+:count)
    for(int i = 0;i < n;i++){
        count += arr[i];
    }

    return count;
}

float avg(int arr[], int n){
    int s1 = sum(arr,n);
    return float(s1)/n;
}

int minVal(int arr[],int n){
    int min_val = arr[0];

    #pragma omp parallel for reduction(min:min_val)

    for(int i= 1;i<n;i++){
        if(arr[i] < min_val){
            min_val = arr[i];
        }
    }

    return min_val;
}

int maxVal(int arr[],int n){
    int max_val = arr[0];

    #pragma omp parallel for reduction(max:max_val)

    for(int i= 1;i<n;i++){
        if(arr[i] > max_val){
            max_val = arr[i];
        }
    }

    return max_val;
}

int main(){
    int n;
    cout << "Enter size of array : ";
    cin >> n;

    int arr[n];
    //cout << "Enter " << n << "Elemnets : ";

    for(int i=0;i<n;i++){
        //cin >> arr[i];
        arr[i] = i+1;
    }

    cout << "Max : " << maxVal(arr,n) << endl;
    cout << "Min : " << minVal(arr,n) << endl;
    cout << "Sum : " << sum(arr, n) << endl;
    cout << "Average : " <<  avg(arr, n) << endl;
    return 0;
}