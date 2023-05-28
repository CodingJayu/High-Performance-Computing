#include<iostream>
#include<omp.h>
using namespace std;

void min_val(int *arr,int n){
    int min_val=1000;
    #pragma omp parallel for reduction(min:min_val)
    for(int i=0;i<n;i++){
        if(min_val>arr[i]){
            min_val=arr[i];
        }
        // cout<<"\nthread:"<<omp_get_thread_num()<<" iteration:"<<i;
    }
    cout<<"\nMin val:"<<min_val;
}

void max_val(int *arr,int n){
    int max_val=-1;
    #pragma omp parallel for reduction(max:max_val)
    for(int i=0;i<n;i++){
        if(max_val<arr[i]){
            max_val=arr[i];
        }
        // cout<<"\nThread :"<<omp_get_thread_num()<<"Iteration :"<<i;
    }
    cout<<"\nMax val:"<<max_val;

}

void sum_val(int *arr,int n){
    int sum_val=0;
    #pragma omp parallel for reduction(+:sum_val)
    for(int i=0;i<n;i++){
        sum_val=sum_val+arr[i];
        // cout<<"\nThread:"<<omp_get_thread_num()<<" Iteration"<<i;
    }
    
    cout<<"\nsum val:"<<sum_val;
}

void avg_val(int *arr,int n){
    double sum_val=0;
    #pragma omp parallel for reduction(+:sum_val)
    for(int i=0;i<n;i++){
        sum_val=sum_val+arr[i];
        // cout<<"\nThread:"<<omp_get_thread_num()<<" Iteration"<<i;
    }
    cout<<"\nAvg val:"<<sum_val/n;
}


int main(){
    omp_set_num_threads(4);
    int n;
    cout<<"\nEnter Size of Array:";
    cin>>n;
    int arr[n];
    cout<<"\nEnter Values:";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    min_val(arr,n);
    max_val(arr,n);
    sum_val(arr,n);
    avg_val(arr,n);
    return 0;
}