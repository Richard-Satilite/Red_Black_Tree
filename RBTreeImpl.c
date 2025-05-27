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

void leftRotate(Node **root, Node *x){
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

Node *searchRBNode(Node *root, int val){
	while(root != NULL){
		if(val < root->val)
			root = root->left;
		else if(val > root->val)
			root = root->right;
		else
			return root;
	}

	return NULL;
}

void insertFix(Node **root, Node *z) {
	while(z != *root && z->parent->color == RED){
		Node *y;

		if(z->parent == z->parent->parent->left){
			y = z->parent->parent->right; //Tio a direita

			if(y != NULL && y->color == RED){
				// Violacao 1: Pai e tio vermelhos

				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else{
				// Violacao 2 e 3: Tio e preto

				if(z == z->parent->right){
					// Violacao 2: filho a direita - rotacao esquerda no pai
					z = z->parent;
					leftRotate(root, z);
				}

				// Violacao 3: z eh filho a esquerda - rotacao direita no avo
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				rightRotate(root, z->parent->parent);
			}

		} else{
			y = z->parent->parent->left; // Tio a esquerda

			if(y != NULL && y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			} else{
				if(z == z->parent->left){
					// Violacao 2

					z = z->parent;
					rightRotate(root, z);
				}

				//Violacao 3

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				leftRotate(root, z->parent->parent);
			}
		}
	}

	// Raiz sempre preta
	(*root)->color = BLACK;
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
	insertFix(root, z);
}

void swapNodes(Node **root, Node *out, Node *in){
	if(out->parent == NULL)
		*root = in;
	else if(out == out->parent->left)
		out->parent->left = in;
	else
		out->parent->right = in;

	if(in != NULL)
		in->parent = out->parent;
}

void removeFix(Node **root, Node *x){
	while (x != *root && (x == NULL || x->color == BLACK)) {
		if (x == x->parent->left) {
			Node *w = x->parent->right;  // irmão

			// Caso 1: w eh vermelho
			if (w != NULL && w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				leftRotate(root, x->parent);
				w = x->parent->right;
			}

			// Caso 2: w eh preto e os dois filhos de w são pretos
			if ((w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK)) {
				w->color = RED;
				x = x->parent;
		
			} else {
			
				// Caso 3: w eh preto, w.left é vermelho e w.right é preto
				if (w->right == NULL || w->right->color == BLACK) {
					if (w->left != NULL)
						w->left->color = BLACK;
					w->color = RED;
					rightRotate(root, w);
					w = x->parent->right;
				}

				// Caso 4: w.right eh vermelho
				w->color = x->parent->color;
				x->parent->color = BLACK;
				if (w->right != NULL)
					w->right->color = BLACK;
				leftRotate(root, x->parent);
				x = *root;
			}

        	} else {

			// Simetrico ao caso acima (x eh filho da direita)
			Node *w = x->parent->left;

			if (w != NULL && w->color == RED) {
				w->color = BLACK;
				x->parent->color = RED;
				rightRotate(root, x->parent);
				w = x->parent->left;
			}

			if ((w->right == NULL || w->right->color == BLACK) && (w->left == NULL || w->left->color == BLACK)) {
				w->color = RED;
				x = x->parent;
			} else {
				if (w->left == NULL || w->left->color == BLACK) {
					if (w->right != NULL)
						w->right->color = BLACK;
					w->color = RED;
					leftRotate(root, w);
					w = x->parent->left;
				}

				w->color = x->parent->color;
				x->parent->color = BLACK;
				if (w->left != NULL)
					w->left->color = BLACK;
				rightRotate(root, x->parent);
				x = *root;
			}
		}
	}

	if (x != NULL)
	x->color = BLACK;
}

void removeRB(Node **root, int val){
	Node *z = searchRBNode(*root, val);

	if(z == NULL)
		return;

	Node *y = z;
	Color yOriginalColor = y->color;
	Node *x;

	// Caso 1: Z so tem no maximo um filho a direita
	if(z->left == NULL){
		x = z->right;
		swapNodes(root, z, z->right);
	}

	// Caso 2: Z so tem no maximo um filho a esquerda
	else if(z->right == NULL){
		x = z->left;
		swapNodes(root, z, z->left);
	}

	// Case 3: Z tem os dois filhos
	else{
		// Assume o menor da subarvore a direita
		y = z->right;
		while(y->left != NULL)
			y = y->left;

		yOriginalColor = y->color;
		x = y->right;

		if(y->parent == z){
			if(x != NULL)
				x->parent = y;
		} else{
			swapNodes(root, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}


		swapNodes(root, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	free(z);

	
	// Se y era preto, pode ter ocorrido violacao
	if(yOriginalColor == BLACK)
		removeFix(root, x);
}
