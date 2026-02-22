#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_NODES = 1e5 + 9;

// Global adjacency list
vector<int> adj[MAX_NODES];

int main() {
    // Faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int nodes, edges;
    if (!(cin >> nodes >> edges)) return 0;

    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // dist stores the shortest path length, parent tracks the path
    vector<int> dist(nodes + 1, INF);
    vector<int> parent(nodes + 1, 0);
    queue<int> task_queue;

    // Start BFS from the first computer
    dist[1] = 0;
    task_queue.push(1);

    while (!task_queue.empty()) {
        int current = task_queue.front();
        task_queue.pop();

        for (int neighbor : adj[current]) {
            // If we found a shorter way to reach the neighbor
            if (dist[current] + 1 < dist[neighbor]) {
                dist[neighbor] = dist[current] + 1;
                parent[neighbor] = current;
                task_queue.push(neighbor);
            }
        }
    }

    // Check if the destination is reachable
    if (dist[nodes] == INF) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        // Output path length (number of computers)
        cout << dist[nodes] + 1 << "\n";

        // Backtrack to reconstruct the route
        vector<int> route;
        for (int v = nodes; v != 0; v = parent[v]) {
            route.push_back(v);
        }
        reverse(route.begin(), route.end());

        for (int i = 0; i < route.size(); ++i) {
            cout << route[i] << (i == route.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }

    return 0;
}