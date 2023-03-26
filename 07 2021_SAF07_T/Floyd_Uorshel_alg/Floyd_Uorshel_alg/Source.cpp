#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// Колличество вершин графа в файле test.txt
#define VERTICES 11

#define MAX_VERTICES 100
#define NOT_VISITED -1

void read_file_to_matrix(char* file_name, int matrix[][MAX_VERTICES], int vertices) {

    FILE* file;
    file = fopen(file_name, "r");

    int source, destination, weight;

    while (fscanf(file, "%d %d %d", &source, &destination, &weight) != EOF) {
        matrix[source][destination] = weight;
    }

    fclose(file);
}

void print_matrix(int matrix[][MAX_VERTICES], int vertices) {

    printf("Weighted Adjacency Matrix:\n");

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void restorePath(int path[][MAX_VERTICES], int start_vertex, int end_vertex) {

    if (path[start_vertex][end_vertex] == 0) {
        printf("%d ", start_vertex);
        if (start_vertex != end_vertex) {
            printf("%d ", end_vertex);
        }

    }

    else {
        restorePath(path, start_vertex, path[start_vertex][end_vertex]);
        printf("%d ", end_vertex);
    }
}

void FU_alg(int matrix[][MAX_VERTICES], int vertices) {

    int path[MAX_VERTICES][MAX_VERTICES] = { 0 };
    int dist[MAX_VERTICES][MAX_VERTICES];
    int i, j, k;

    // Инициализируем матрицу расстояний dist так, чтобы она соответствовала матрице смежности (0 заменяем на INT_MAX)
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            dist[i][j] = matrix[i][j];
            if (dist[i][j] == 0) dist[i][j] = INT_MAX;
        }
    }

    // Выполняем алгоритм Флойда-Уоршелла
    for (k = 0; k < vertices; k++) {
        for (i = 0; i < vertices; i++) {
            for (j = 0; j < vertices; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;
                }
            }
        }
    }

    // Выводим кратчайшие расстояния и пути между всеми парами вершин
    printf("\nShortest distances between all pairs of vertices:\n");
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            if (dist[i][j] == INT_MAX) {
                printf("INF ");
            }
            else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nShortest paths between all pairs of vertices:\n");
    for (i = 0; i < vertices; i++) {
        for (j = 0; j < vertices; j++) {
            if (i != j) {
                printf("Shortest path from vertex %d to vertex %d: \n", i, j);
                restorePath(path, i, j);
                printf("\n");
            }
        }
    }
}




int main() {

    int matrix[MAX_VERTICES][MAX_VERTICES] = { 0 };

    read_file_to_matrix((char*)"test.txt", matrix, VERTICES);
    print_matrix(matrix, VERTICES);

    FU_alg(matrix, VERTICES);


    return 0;
}