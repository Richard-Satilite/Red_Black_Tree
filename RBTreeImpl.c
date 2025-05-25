#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"

Node *genNode(int val){
	Node *node = (Node *) malloc(sizeof(Node));

	if(node == NULL)
		return NULL;
	node->val = val;
	node->color = RED;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;

	return node;
}

void leftRotation(Node **root, Node *x){
	Node* y = x->right;
	x->right = y->left;

	if (y->left != NULL)
		y->left->parent = x;
	

	y->parent = x->parent;

	if (x->parent == NULL)
		*root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	
	y->left = x;
	x->parent = y;
}

void rightRotate(Node **root, Node *y){
	Node* x = y->left;
	y->left = x->right;

	if (x->right != NULL)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == NULL)
		*root = x;
	else if (y == y->parent->right)
		y->parent->right = x;
	else
		y->parent->left = x;

	x->right = y;
	y->parent = x;
}

Bool searchRB(Node *root, int val){

	while(root != NULL){
		if(val < root->val)
			root = root->left;
		else if(val > root->val)
			root = root->right;
		else
			return true;
	}

	return false;
}


void insertRB(Node **root, int val){
	Node *z = genNode(val);

	if(z == NULL || searchRB(*root, val))
		return;
	
	Node *y = NULL;
	Node *x = *root;

	while(x != NULL){
		y = x;
		if(val < x->val)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;

	if(y == NULL)
		*root = z;
	else if(z->val < y->val)
		y->left = z;
	else
		y->right = z;

	//Funcao de correcao
}
