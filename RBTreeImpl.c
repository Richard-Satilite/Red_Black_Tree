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

void printPreOrder(Node **root) {
	if (*root != NULL) {
		printf("%d -> ", (*root)->val);
		printPreOrder(&((*root)->left));
		printPreOrder(&((*root)->right));
	}
}

void printInOrder(Node **root) {
	if (*root != NULL) {
		printInOrder(&((*root)->left));
		printf("%d -> ", (*root)->val);
		printInOrder(&((*root)->right));
	}
}

void printPosOrder(Node **root) {
	if (*root != NULL) {
		printPosOrder(&((*root)->left));
		printPosOrder(&((*root)->right));
		printf("%d -> ", (*root)->val);
	}
}

Node **initialRBTree(){

	// raiz da arvore
    Node *root = genNode(13), **finalRoot;
    root->color = BLACK;

    root->left = genNode(8);
    

    root->left->left = genNode(1);
    root->left->left->color = BLACK;
    
    root->left->left->right = genNode(6);

    root->left->right = genNode(11);
    root->left->right->color = BLACK;

    root->right = genNode(17);

    root->right->left = genNode(15);
    root->right->left->color = BLACK;

    root->right->right = genNode(25);
    root->right->right->color = BLACK;

    root->right->right->left = genNode(22);

    root->right->right->right = genNode(27);

	/*
		Arvore gerada
          13(B)
         /    \
      8(R)    17(R)
     /  \     /   \
   1(B) 11(B)15(B) 25(B)
   /  \           /   \
     6(R)      22(R) 27(R)
	*/

	finalRoot = &root;

    return finalRoot;
} 

void startProgram(){
	Node **root = initialRBTree();
	int option, val;

	printf("\nVISUALIZACAO DA ARVORE RUBRO-NEGRA\n\nARVORE INICIAL:\n\n");
	printInOrder(root);

	do{
		printf("\nDIGITE A OPCAO DA OPERACAO QUE DESEJA REALIZAR\n[1] - VISUALIZAR ARVORE\n[2] - ADICIONAR ELEMENTO NA ARVORE\n[3] - REMOVER ELEMENTO DA ARVORE\n[4] - ENCERRAR PROGRAMA");
		scanf("%d", &option);

		switch(option){
			case 1:
				printf("\n\nVISUALIZACAO DA ARVORE NAS TRES TRAVESSIAS:\n\n");
				printf("\n\nEM PRE-ORDEM:\n");
				printPreOrder(root);
				printf("\n\nEM ORDEM:\n");
				printInOrder(root);
				printf("\n\nEM POS-ORDEM:\n");
				printPosOrder(root);
				putchar('\n');
			break;
			case 2:
				printf("\n\nDIGITE O VALOR QUE DESEJA ADICIONAR NA ARVORE: ");
				scanf("%d", &val);
				
				insertRB(root, val);
				if(searchRB(*root, val))
					printf("\nVALOR %d INSERIDO!\n\n", val);
			break;
			case 3:
				printf("\n\nDIGITE O VALOR QUE DESEJA REMOVER DA ARVORE: ");
				scanf("%d", &val);

				removeRB(root, val);
				if(!searchRB(*root, val))
					printf("\n\nVALOR %d REMOVIDO!\\n\n", val);

			break;
			case 4:
				printf("\n\nATE MAIS!\n\n");
			break;
			default:
				printf("\nOPCAO INVALIDA!\n\n");
			break;
		}
	}while(option != 4);
}
