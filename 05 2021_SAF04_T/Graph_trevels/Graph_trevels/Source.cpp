#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

/* ���������, �������������� ������� */
typedef struct Vertex {
    int data;
    struct Vertex* next;
} Vertex;

/* ���������, �������������� ������ ��������� */
typedef struct AdjacencyList {
    Vertex* head;
} AdjacencyList;

/* ������ ������� ��������� */
AdjacencyList graph[MAX_VERTICES];

/* ������� ��� ���������� ������� � ������ ��������� */
void add_vertex(int source, int destination) {

    // ������� ������� �������� ������ ��� ����� ������� ������
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));

    // ��������� ���� data ����� �������� ��������� destination
    vertex->data = destination;

    // ���� next ������������� ������ ��������� �� ������� �������� ������� ������ ��������� � ������� source
    vertex->next = graph[source].head;

    // �������� ��������� ������ ��������� � ������� source ��������������� ��������� �������.
    graph[source].head = vertex;
}

/* ������� ��� ���������� ����� �� ����� */
void read_graph_from_file(const char* filename) {
        
    int num_vertices, num_edges;
    int source, destination;

    FILE* file = fopen(filename, "r");

    if (!file) {
        printf("Error opening file\n");
        exit(1);
    }

    /* ��������� ���������� ������ � ����� */
    fscanf(file, "%d %d", &num_vertices, &num_edges);

    /* �������������� ������ ��������� */
    for (int i = 0; i < num_vertices; i++) {
        graph[i].head = NULL;
    }

    /* ��������� ����� */
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

    // ������, ������������ ��� ������������ ����, ���������� �� �������
    int visited[MAX_VERTICES] = { 0 };

    // ������� ����, ������������ ��� ������������ ���� ������
    int stack[MAX_VERTICES];
    int top = -1;

    // �������� ������� start � ���� � �������� �� ��� ����������
    stack[++top] = start;
    visited[start] = 1;

    // ���� ���� �� ������
    while (top >= 0) {

        // ��������� ������� �� �����
        int current = stack[top--];
        Vertex* vertex = graph[current].head;

        // �������� �� ��������
        printf("%d ", current);

        // ���������� ������ ��������� ������� �������
        while (vertex != NULL) {

            // ��������� ������� ��� ������� ��� ���
            if (vertex->data == value) {
                return vertex;
            }

            int destination = vertex->data;

            // ���� ������� �� ��������, ��������� �� � ���� � �������� ��� ����������
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

    // ������, ������������ ��� ������������ ����, ���������� �� �������
    int visited[MAX_VERTICES] = { 0 };

    // ������� �������, ������������ ��� ������������ ���� ������
    int queue[MAX_VERTICES];
    int front = 0, rear = -1;

    // �������� ������� start � ������� � �������� �� ��� ����������
    queue[++rear] = start;
    visited[start] = 1;

    // ���� ������� �� ������
    while (rear >= front) {

        // ��������� ������� �� �������
        int current = queue[front++];
        Vertex* vertex = graph[current].head;

        // �������� �� ��������
        printf("%d ", current);

        // ���������, �������� �� ��� ������� ��� ������
        if (vertex == NULL) {
            return NULL;
        }

        // ��������� ������� ��� ������� ��� ���
        if (vertex->data == value) {
            return vertex;
        }

        // ���������� ������ ��������� ������� �������
        while (vertex != NULL) {

            int destination = vertex->data;

            // ���� ������� �� ��������, ��������� �� � ������� � �������� ��� ����������
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