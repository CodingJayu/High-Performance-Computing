#include<iostream>
#include<omp.h>
#include<vector>
#include<queue>
using namespace std;

vector<bool> v;
vector<vector<int>> g;

void makeedge(int a,int b){
    g[a].push_back(b);
}

void bfs(int b){
    queue<int> q;
    q.push(b);
    v[b]=true;
    double start=omp_get_wtime();
    while(!q.empty()){
        int a=q.front();
        q.pop();
        #pragma omp parallel for
        for (int i=0;i<g[a].size();i++){
            int neigh=g[a][i];
            if(!v[neigh])
            #pragma omp critical
            {
                v[neigh]=true;
                q.push(neigh);
            }
        }
        cout<<a<<" ";
    }
    cout<<"\n"<<omp_get_wtime()-start;
}

int main(){
    omp_set_num_threads(4);
    int n,e;
    cout<<"\nEnter Number of Vertex:";
    cin>>n;
    cout<<"\nEnter the Number of edges:";
    cin>>e;
    v.assign(n,false);
    g.resize(n);
    int a,b;
    for(int i=0;i<e;i++){
        cin>>a>>b;
        makeedge(a,b);
    }

    for (int i=0;i<n;i++){
        if(!v[i]){
            bfs(i);
        }
    }

    return 0;

}