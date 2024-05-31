#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int min(int a, int b) {
    return a < b ? a : b;
}

int n, edgeCount;
int adjMatrix[MAX][MAX];
int ids[MAX];
int low[MAX];
bool visited[MAX];
int id = 0;

void findCutVertices(int node, int parent) {
    visited[node] = true;
    ids[node] = low[node] = id++;

    for (int i = 0; i < n; i++) {
        if (adjMatrix[node][i]) {
            if (!visited[i]) {
                findCutVertices(i, node);
                low[node] = min(low[node], low[i]);
                if (ids[node] < low[i]) {
                    printf("Шарнир: %d - %d\n", node, i);
                }
            } else if (i != parent) {
                low[node] = min(low[node], ids[i]);
            }
        }
    }
}

int main() {
    printf("Введите количество вершин графа: ");
    scanf("%d", &n);
    printf("Введите матрицу смежности %d x %d:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adjMatrix[i][j]);
            if (adjMatrix[i][j] == 1) {
                edgeCount++;
            }
        }
    }

    printf("Шарниры графа:\n");
    findCutVertices(0, -1);

    return 0;
}
