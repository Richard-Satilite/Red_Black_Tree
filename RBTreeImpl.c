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

bool searchRB(Node *root, int val){

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

	// Raiz eh sempre preta
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

void removeFix(Node **root, Node *x, Node *xParent){
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (xParent != NULL && x == xParent->left) {
            Node *w = xParent->right;  // irmao

            // Caso 1: irmao w eh vermelho
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                leftRotate(root, xParent);
                w = xParent->right;
            }

            // Caso 2: irmao w eh preto e ambos filhos de w sao pretos (ou NULL)
            if ((w == NULL) || 
                ((w->left == NULL || w->left->color == BLACK) && 
                 (w->right == NULL || w->right->color == BLACK))) {
                if(w != NULL)
                    w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                // Caso 3: irmao w eh preto, filho esquerdo eh vermelho, filho direito eh preto
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = xParent->right;
                }

                // Caso 4: irmao w eh preto e filho direito eh vermelho
                if(w != NULL){
                    w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->right != NULL)
                        w->right->color = BLACK;
                    leftRotate(root, xParent);
                }
                x = *root;
            }

        } else if (xParent != NULL) {
            // Caso: x eh filho da direita
            Node *w = xParent->left;  // irmao a esquerda

            // Caso 1: irmao w eh vermelho
            if (w != NULL && w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                rightRotate(root, xParent);
                w = xParent->left;
            }

            // Caso 2: irmao w eh preto e ambos filhos sao pretos
            if ((w == NULL) || 
                ((w->right == NULL || w->right->color == BLACK) && 
                 (w->left == NULL || w->left->color == BLACK))) {
                if(w != NULL)
                    w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                // Caso 3: irmao w eh preto, filho direito eh vermelho, filho esquerdo eh preto
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = xParent->left;
                }
                
                // Caso 4: irmao w eh preto e filho esquerdo eh vermelho
                if(w != NULL){
                    w->color = xParent->color;
                    xParent->color = BLACK;
                    if (w->left != NULL)
                        w->left->color = BLACK;
                    rightRotate(root, xParent);
                }
                x = *root;  // terminar o loop
            }
        } else {
            break;
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
    Node *x = NULL;
    Node *xParent = NULL;

    // Caso 1: Z tem no maximo filho a direita
    if(z->left == NULL){
        x = z->right;
        xParent = z->parent;
        swapNodes(root, z, z->right);
    }
    // Caso 2: Z tem no maximo filho a esquerda
    else if(z->right == NULL){
        x = z->left;
        xParent = z->parent;
        swapNodes(root, z, z->left);
    }
    // Caso 3: Z tem ambos os filhos
    else{
        // Encontrar sucessor (menor da subárvore direita)
        y = z->right;
        while(y->left != NULL)
            y = y->left;

        yOriginalColor = y->color;
        x = y->right;
        
        if(y->parent == z){
            xParent = y;
        } else {
            xParent = y->parent;
            swapNodes(root, y, y->right);
            y->right = z->right;
            if(y->right != NULL)
                y->right->parent = y;
        }

        swapNodes(root, z, y);
        y->left = z->left;
        if(y->left != NULL)
            y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    // Se o no removido era preto, pode ter ocorrido violacao
    if(yOriginalColor == BLACK)
        removeFix(root, x, xParent);
}

void printPreOrder(Node **root) {
	if (*root != NULL) {
		printf("%d (%c) -> ", (*root)->val, (*root)->color == RED ? 'R' : 'B');
		printPreOrder(&((*root)->left));
		printPreOrder(&((*root)->right));
	}
}

void printInOrder(Node **root) {
	if (*root != NULL) {
		printInOrder(&((*root)->left));
		printf("%d (%c) -> ", (*root)->val, (*root)->color == RED ? 'R' : 'B');
		printInOrder(&((*root)->right));
	}
}

void printPosOrder(Node **root) {
	if (*root != NULL) {
		printPosOrder(&((*root)->left));
		printPosOrder(&((*root)->right));
		printf("%d (%c) -> ", (*root)->val, (*root)->color == RED ? 'R' : 'B');
	}
}


Node *initialRBTree(){
    Node *root = NULL;

    insertRB(&root, 13);
    insertRB(&root, 8);
    insertRB(&root, 17);
    insertRB(&root, 1);
    insertRB(&root, 11);
    insertRB(&root, 15);
    insertRB(&root, 25);
    insertRB(&root, 6);
    insertRB(&root, 22);
    insertRB(&root, 27);

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

    return root;
}

void startProgram(){
	Node *root = initialRBTree();
	int option, val;

	printf("\nVISUALIZACAO DA ARVORE RUBRO-NEGRA\n\nARVORE INICIAL (RAIZ: %d):\n\n", root->val);
	printInOrder(&root);

	do{
		printf("\nDIGITE A OPCAO DA OPERACAO QUE DESEJA REALIZAR\n[1] - VISUALIZAR ARVORE\n[2] - ADICIONAR ELEMENTO NA ARVORE\n[3] - REMOVER ELEMENTO DA ARVORE\n[4] - ENCERRAR PROGRAMA\n");
		scanf("%d", &option);

		switch(option){
			case 1:
				printf("\n\nVISUALIZACAO DA ARVORE NAS TRES TRAVESSIAS:\n\n");
				printf("\nRAIZ = %d\n\n", root->val);
				printf("\n\nEM PRE-ORDEM:\n");
				printPreOrder(&root);
				printf("\n\nEM ORDEM:\n");
				printInOrder(&root);
				printf("\n\nEM POS-ORDEM:\n");
				printPosOrder(&root);
				putchar('\n');
			break;
			case 2:
				printf("\n\nDIGITE O VALOR QUE DESEJA ADICIONAR NA ARVORE: ");
				scanf("%d", &val);
				
				if(searchRB(root, val))
					printf("\nO VALOR %d JA EXISTE NA ARVORE!\n\n", val);
				else{
					insertRB(&root, val);
					printf("\nVALOR %d INSERIDO!\n\n", val);
				}


			break;
			case 3:
				printf("\n\nDIGITE O VALOR QUE DESEJA REMOVER DA ARVORE: ");
				scanf("%d", &val);

				if(searchRB(root, val)){
					removeRB(&root, val);
					printf("\n\nVALOR %d REMOVIDO!\n\n", val);
				} else
					printf("\n\nO VALOR  %d NAO EXISTE NA ARVORE", val);
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
