#ifndef RBTREE_H
#define RBTREE_H


// Definindo dado do tipo Color //
typedef enum Color{
	RED,
	BLACK
}Color;


// Estrutura de um no da arvore rubro-negra //
typedef struct Node{
	int val;
	Color color;
	struct Node* left;
	struct Node* right;
	struct Node* parent;	
}Node;


// Funcao que efetua uma rotacao a direita //
// Recebe um ponteiro do tipo Node que causa violacao //
void rightRotate(Node *node);


// Funcao que efetua uma rotacao a esquerda //
// Recebe um ponteiro do tipo Node que causa violacao //
void leftRotate(Node *node);


#endif
