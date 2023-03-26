#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

#define QSIZE 20

typedef struct node {
	int info;
	struct node* llink;
	struct node* rlink;
} node;

node* queue[QSIZE];
int rear = -1;
int front = -1;

node* create_node(int info) {
	node* new_node = (node*)malloc(sizeof(node));
	new_node->info = info;
	new_node->llink = NULL;
	new_node->rlink = NULL;
	return new_node;
}

int is_empty() {
	if (front == rear) {
		return 1;
	}
	else {
		return 0;
	}
}

void enqueue(node* new_node) {
	rear++;
	if (rear == (QSIZE)) {
		rear = 0;
	}
	queue[rear] = new_node;
}

node* dequeue() {
	front++;
	if (front == QSIZE) {
		front = 0;
	}
	return queue[front];
}




void push(node** root, int info) {

	node* new_node = create_node(info);
	node* tmp = *root;

	// ≈сли дерево пустое - нова€ нода становитс€ рутом
	if (*root == NULL) {
		*root = new_node;
	}

	// ≈сли дерево не пустое, а поступивша€ info < чем в текущем tmp
	else if (info < tmp->info) {

		// ѕровер€ем, дошли ли мы до !левого! кра€ и пытаемс€ вставить новый элемент
		if (tmp->llink == NULL) {
			tmp->llink = new_node;
		}

		// ≈сли не дошли до кра€, то углубл€емс€
		else {
			push(&(tmp->llink), info);
		}
	}

	// ≈сли дерево не пустое, а поступивша€ info > чем в текущем tmp
	else if (info > tmp->info) {

		if (tmp->rlink == NULL) {
			tmp->rlink = new_node;
		}

		else {
			push(&(tmp->rlink), info);
		}
	}


}

void input_numbers(node** root) {
	int n;
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	int i, info;
	for (i = 0; i < n; i++) {
		printf("Enter element %d: ", i + 1);
		scanf("%d", &info);
		push(root, info);
	}
}

node* search_binary_tree(node* root, int value) {

	if (root == NULL) {
		return NULL;
	}

	if (root->info == value) {
		return root;
	}

	node* left_search = search_binary_tree(root->llink, value);
	if (left_search != NULL) {
		return left_search;
	}

	node* right_search = search_binary_tree(root->rlink, value);
	if (right_search != NULL) {
		return right_search;
	}

	return NULL;
}


int main() {

	node* root = NULL;

	input_numbers(&root);

	int value;
	printf("Enter the value to search\n");
	scanf("%d", &value);

	node* result = search_binary_tree(root, value);

	if (result != NULL) {
		printf("The valu was finded in node with adress %p\n", result);
	}

	else {
		printf("The value wasnt finded in this tree\n");
	}

	return 0;
}