#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>

using namespace std;

vector<bool> v;
vector<vector<int>> g;

void bfsTraversal(int b) {
    queue<int> q;
    q.push(b);
    v[b] = true;

    cout << "\nThe BFS Traversal is: ";

    double start = omp_get_wtime();
    while (!q.empty()) {
        int a = q.front();
        q.pop();

        #pragma omp parallel for
        for (int j = 0; j < g[a].size(); j++) {
            int neighbor = g[a][j];
            if (!v[neighbor]) {
                #pragma omp critical
                {
                    v[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << a << " ";
    }
    double end = omp_get_wtime();
    double time = end - start;
    cout << "\n\nTime taken => " << time << endl;
}

void makeEdge(int a, int b) {
    g[a].push_back(b);
}

int main() {
    omp_set_num_threads(4);
    int n, e;
    cout << "Consider first vertex => 0" << endl;
    cout << "\nEnter the number of vertices: ";
    cin >> n;
    cout << "\nEnter the number of edges: ";
    cin >> e;
    v.assign(n, false);
    g.resize(n);
    int a, b, i;
    cout << "\nEnter the edges with source and target vertex: " << endl;
    for (i = 0; i < e; i++) {
        cin >> a >> b;
        makeEdge(a, b);
    }
    for (i = 0; i < n; i++) {
        if (!v[i]) {
            bfsTraversal(i);
        }
    }
    return 0;
}
