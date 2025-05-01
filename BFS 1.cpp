#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

void BFS(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " "; 

        // Parallelize the exploration of neighbors
        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); i++) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
}

int main() {
    int vertices, edges;
    cout << "Enter number of vertices: ";
    cin >> vertices;
    cout << "Enter number of edges: ";
    cin >> edges;

    vector<vector<int>> adj(vertices);
    vector<bool> visited(vertices, false); 

    cout << "Enter the edges (u v) where u and v are connected:\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }

    int startNode;
    cout << "Enter the starting node: ";
    cin >> startNode;

    cout << "BFS Traversal: ";
    BFS(startNode, adj, visited);
    cout << endl;

    return 0;
}

