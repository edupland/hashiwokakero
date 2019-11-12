#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct node_s{
	int x;
	int y;
	int degree;
};
typedef struct node_s* node;

node new_node (int x, int y, int required_degree){
	node node = malloc(sizeof(node));
	node->x = x;
	node->y = y;
	node->degree = required_degree;
	return node;
}

void delete_node (node n){
	free(n);
}

int get_x (node n){
	return n->x;
}

int get_y (node n){
	return n->y;
}

int get_required_degree (node n){
	return n->degree;
}