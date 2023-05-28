#include<iostream>
#include<omp.h>
using namespace std;

void merge(int *,int,int,int);

void merge_sort(int *arr,int low,int high){
    int mid;
    if(low<high){
        mid=(low+high)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                merge_sort(arr,low,mid);
            }
            #pragma omp section
            {
                merge_sort(arr,mid+1,high);
            }
        }
        
        
        merge(arr,low,mid,high);
    }
}

void merge(int *arr,int low,int mid,int high){
    int i,j,k,c[50];
    i=k=low;
    j=mid+1;

    while(i<=mid && j<=high){
        if(arr[i]<arr[j]){
            c[k]=arr[i];
            i++;
            k++;
        }
        else{
            c[k]=arr[j];
            k++;
            j++;
        }
    }
    while(i<=mid){
        c[k]=arr[i];
        k++;
        i++;
    }
    while(j<=high){
        c[k]=arr[j];
        j++;
        k++;
    }

    for(int i=low;i<k;i++){
        arr[i]=c[i];
    }

}

int main(){
    omp_set_num_threads(4);
    int n;
    cout<<"\nEnter how many element you want to enter:";
    cin>>n;
    int arr[n];
    cout<<"\nEnter the Elements:";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    merge_sort(arr,0,n-1);
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    
    return 0;
}