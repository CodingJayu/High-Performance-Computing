#include<iostream>
#include<omp.h>
using namespace std;

void bub_sort(int *arr,int n){
    int a;
    double start=omp_get_wtime();
    for(int i=0;i<n;i++){
        #pragma omp parallel
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                a=arr[j];
                arr[j]=arr[i];
                arr[i]=a;
            }
        }
    }
    double end=omp_get_wtime();
    cout<<"\nTime"<<start-end;
}

int main(){
    omp_set_num_threads(4);
    int n;
    cout<<"\nEnter the no of Element:";
    cin>>n;
    int arr[n];
    cout<<"Enter the Elements:";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    bub_sort(arr,n);

    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;

}