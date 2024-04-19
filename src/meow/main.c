#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int cnt = 0;
bool visited[MAX];
int tin[MAX];
int up[MAX];

void dfs(int v, int p, int n, int G[MAX][MAX]){
    cnt++;
    tin[v] = up[v] = cnt;
    visited[v] = true;
    int count = 0;

    for (int u = 0; u < n; u++){
        if (G[v][u] == 1) {
            if (u == p) continue;
            if (visited[u]){
                up[v] = up[v] < tin[v] ? up[v] : tin[v];
            } else {
                dfs(u, v, n, G);
                count++;
                up[v] = up[v] < up[u] ? up[v] : up[u];
                if (p != -1 && up[u] >= tin[v]) {
                    printf("Vertex %d is a cutpoint\n", v);
                }
            }
        }
    }

    if (p == -1 && count >= 2) {
        printf("Vertex %d is a cutpoint\n", v);
    }
}