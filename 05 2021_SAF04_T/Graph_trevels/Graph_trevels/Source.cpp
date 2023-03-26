#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

/* структура, представляющая вершину */
typedef struct Vertex {
    int data;
    struct Vertex* next;
} Vertex;

/* структура, представляющая список смежности */
typedef struct AdjacencyList {
    Vertex* head;
} AdjacencyList;

/* массив списков смежности */
AdjacencyList graph[MAX_VERTICES];

/* функция для добавления вершины в список смежности */
void add_vertex(int source, int destination) {

    // функция сначала выделяет память под новый элемент списка
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));

    // заполняет поле data этого элемента значением destination
    vertex->data = destination;

    // поле next устанавливает равным указателю на текущий головной элемент списка смежности у вершины source
    vertex->next = graph[source].head;

    // головным элементом списка смежности у вершины source устанавливается созданный элемент.
    graph[source].head = vertex;
}

/* функция для считывания графа из файла */
void read_graph_from_file(const char* filename) {
        
    int num_vertices, num_edges;
    int source, destination;

    FILE* file = fopen(filename, "r");

    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }

    /* считываем количество вершин и ребер */
    fscanf(file, "%d %d", &num_vertices, &num_edges);

    /* инициализируем списки смежности */
    for (int i = 0; i < num_vertices; i++) {
        graph[i].head = NULL;
    }

    /* считываем ребра */
    for (int i = 0; i < num_edges; i++) {
        fscanf(file, "%d%d", &source, &destination);
        add_vertex(source, destination);
    }

    fclose(file);
}

Vertex* depth_first_search(int start, int value) {

    if (start == value) {
        printf("start and value are the same");
        return 0;
    }

    printf("The way to search: \n");

    // массив, используемый для отслеживания того, посещалась ли вершина
    int visited[MAX_VERTICES] = { 0 };

    // создаем стек, используемый для отслеживания пути поиска
    int stack[MAX_VERTICES];
    int top = -1;

    // помещаем вершину start в стек и отмечаем ее как посещенную
    stack[++top] = start;
    visited[start] = 1;

    // пока стек не пустой
    while (top >= 0) {

        // извлекаем вершину из стека
        int current = stack[top--];
        Vertex* vertex = graph[current].head;

        // печатаем ее значение
        printf("%d ", current);

        // перебираем список смежности текущей вершины
        while (vertex != NULL) {

            // Проверяем искомая это вершина или нет
            if (vertex->data == value) {
                return vertex;
            }

            int destination = vertex->data;

            // если вершина не посещена, добавляем ее в стек и отмечаем как посещенную
            if (!visited[destination]) {
                stack[++top] = destination;
                visited[destination] = 1;
            }

            vertex = vertex->next;
        }
    }

    return NULL;
}

Vertex* breadth_first_search(int start, int value) {

    if (start == value) {
        printf("start and value are the same");
        return 0;
    }

    printf("The way to search: \n");

    // массив, используемый для отслеживания того, посещалась ли вершина
    int visited[MAX_VERTICES] = { 0 };

    // создаем очередь, используемую для отслеживания пути поиска
    int queue[MAX_VERTICES];
    int front = 0, rear = -1;

    // помещаем вершину start в очередь и отмечаем ее как посещенную
    queue[++rear] = start;
    visited[start] = 1;

    // пока очередь не пустая
    while (rear >= front) {

        // извлекаем вершину из очереди
        int current = queue[front++];
        Vertex* vertex = graph[current].head;

        // печатаем ее значение
        printf("%d ", current);

        // Проверяем, остались ли еще вершины для поиска
        if (vertex == NULL) {
            return NULL;
        }

        // Проверяем искомая это вершина или нет
        if (vertex->data == value) {
            return vertex;
        }

        // перебираем список смежности текущей вершины
        while (vertex != NULL) {

            int destination = vertex->data;

            // если вершина не посещена, добавляем ее в очередь и отмечаем как посещенную
            if (!visited[destination]) {
                queue[++rear] = destination;
                visited[destination] = 1;
            }

            vertex = vertex->next;
        }
    }

    return NULL;
}

int main() {

    int value;
    int start;

    const char* filename = "test.txt";

    read_graph_from_file(filename);

    printf("Enter the value to search\n");
    scanf("%d", &value);

    printf("Enter the vertex to start from\n");
    scanf("%d", &start);

    Vertex* result = depth_first_search(start, value);

    if (result != NULL) {
        printf("\nVertex with number %d was finded at %p\n", value, result);
    }

    else {
        printf("\nThe value wasnt finded!\n");
    }

    result = breadth_first_search(start, value);

    if (result != NULL) {
        printf("\nVertex with number %d was finded at %p\n", value, result);
    }

    else {
        printf("\nThe value wasnt finded!\n");
    }

    return 0;
}