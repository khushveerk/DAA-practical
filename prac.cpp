// # insertionsot 
#include <iostream>
#include <algorithm>
using namespace std;

void insertionSort(int arr[],int n){
    for(int i =1;i<n;i++){
        int key = arr[i];
        int j = i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}
int main() {
     int arr[] = {31,41,59,26,41,58};
     int n = sizeof(arr)/ sizeof(arr[0]);
     cout<<"before :";
     for(int i =0;i<n;i++) {

        cout<<arr[i]<<" ";
     }
     cout<< endl;

    insertionSort(arr,n);
     cout<< "After";
     for(int i =0;i<n;i++){
        cout<<arr[i]<<" ";
     }

     cout<< endl;
}
-----------------------------------------------------------------------------------------------------------
  
