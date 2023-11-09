#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 5 // Number of cities

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printSolution(int dist, char* cities[], int parent[], int src, int dest) {
    if (dest == src) {
        printf("%s -> ", cities[src]);
        return;
    }
    printSolution(dist, cities, parent, src, parent[dest]);
    printf("%s -> ", cities[dest]);
}

void dijkstra(int graph[V][V], int src, int dest, char* cities[]) {
    int dist[V];
    int parent[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && (dist[u] + graph[u][v] < dist[v])) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Shortest path: ");
    printSolution(dist[dest], cities, parent, src, dest);
    printf("\n");
    printf("Shortest distance: %d km\n", dist[dest]);
}

int main() {
    int graph[V][V] = {
        {0, 347, 626, 730, 1335},
        {347, 0, 575, 0, 940},
        {626, 575, 0, 1313, 710},
        {730, 0, 1313, 0, 1726},
        {1335, 940, 710, 1726, 0}
    };

    char* cities[V] = {"Chennai", "Bangalore", "Hyderabad", "Thiruvananthapuram", "Mumbai"};

    int source, destination;
    printf("Enter the source city (0-Chennai, 1-Bangalore, 2-Hyderabad, 3-Thiruvananthapuram, 4-Mumbai): ");
    scanf("%d", &source);
    printf("Enter the destination city (0-Chennai, 1-Bangalore, 2-Hyderabad, 3-Thiruvananthapuram, 4-Mumbai): ");
    scanf("%d", &destination);

    dijkstra(graph, source, destination, cities);

    return 0;
}
4