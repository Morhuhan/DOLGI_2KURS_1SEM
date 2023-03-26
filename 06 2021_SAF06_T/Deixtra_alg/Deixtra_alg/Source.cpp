#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

//  олличество вершин графа в файле test.txt
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

int restorePath(int* previous, int start_vertex, int end_vertex) {

    if (previous[end_vertex] != -1) {
        restorePath(previous, start_vertex, previous[end_vertex]);
        printf(" -> %d", end_vertex);
    }

    else {
        return NULL;
    }

    return 1;

}

void dijkstra(int matrix[][MAX_VERTICES], int vertices, int start_vertex) {

    //  аждый элемент previous[i] хранит информацию о предыдущей вершине на пути от стартовой вершины до вершины j
    int previous[MAX_VERTICES];

    // »нициализаци€ массива previous
    for (int i = 0; i < vertices; i++) {
        previous[i] = -1;
    }

    // содержит рассто€ни€ от стартовой вершины до каждой другой вершины
    int distances[MAX_VERTICES];

    // хранит информацию о том, была ли вершина посещена
    int visited[MAX_VERTICES];

    // »нициализаци€ массивов
    for (int i = 0; i < vertices; i++) {
        distances[i] = INT_MAX;
        visited[i] = NOT_VISITED;
    }

    // ƒистанци€ до стартовой вершины устанавливаетс€ 0
    distances[start_vertex] = 0;

    for (int i = 0; i < vertices; i++) {

        // ¬ершина, до которой дистанци€ минимальна 
        int min_distance_vertex = NOT_VISITED;

        // “екуща€ минимальна€ дистанци€
        int min_distance = INT_MAX;

        // —мотрим, в какую вершину лучше перейти на данном шаге
        for (int j = 0; j < vertices; j++) {

            // ≈сли текуща€ вершина не посещалась ранее и рассто€ние до нее в массиве дистанций меньше min_distance
            if (visited[j] == NOT_VISITED && distances[j] < min_distance) {

                // ћинимальна€ дистанци€ теперь станвитс€ равной дистанции до этой вершины
                min_distance = distances[j];

                // Ќова€ вершина, до которой дистанци€ минимальна
                min_distance_vertex = j;    
            }
        }

        if (min_distance_vertex == NOT_VISITED) {
            break;
        }

        // ѕереходим в оптимальную вершину
        visited[min_distance_vertex] = 1;

        // перебор всех путей из min_distance_vertex вершины
        for (int j = 0; j < vertices; j++) {

            // ≈сли:
            // ¬ матрице смежности есть путь в j-ую вершину из текущей (min_distance_vertex)
            // Ёта j-а€ вершина еще не посещалась
            // ƒистанци€ до текущей вершины + вес ребра < дистанци€ до j-ой вершины
            if (matrix[min_distance_vertex][j] && visited[j] == NOT_VISITED && distances[min_distance_vertex] + matrix[min_distance_vertex][j] < distances[j]) {
                
                // ≈сли рассто€ние, полученное путем сложени€, меньше текущего значени€ рассто€ни€, то текущее значение рассто€ни€ обновл€етс€
                distances[j] = distances[min_distance_vertex] + matrix[min_distance_vertex][j];
                
                // ќбновл€ем информацию в массиве previous
                previous[j] = min_distance_vertex;
            }
        }
    }

    printf("Distances from the start vertex %d:\n", start_vertex);

    for (int i = 0; i < vertices; i++) {
        printf("%d ", distances[i]);
    }

    printf("\n");

    for (int i = 1; i < vertices; i++) {
        
        printf("Shortest path from vertex 0 to vertex %d: ", vertices - i);

        // если путь в i-ую вершину определен, то он выведетс€
        int result = restorePath(previous, start_vertex, vertices - i);

        printf("\n");
    }
}


int main() {

    int start_vertex;
    printf("Enter the start_vertex: \n");
    scanf("%d", &start_vertex);

    int matrix[MAX_VERTICES][MAX_VERTICES] = { 0 };

    read_file_to_matrix((char*)"test.txt", matrix, VERTICES);
    print_matrix(matrix, VERTICES);

    dijkstra(matrix, VERTICES, start_vertex);

    return 0;
}