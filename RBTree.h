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


// Funcao que gera cria um no e retorna o seu ponteiro //
// Recebe um valor inteiro //
Node *genNode(int val){



// Funcao que efetua uma rotacao a esquerda //
// Recebe o ponteiro que aponta para a raiz da arvore e um ponteiro do no que causa violacao //
void leftRotate(Node **root, Node *x);


// Funcao que efetua uma rotacao a direita //
// Recebe o ponteiro que aponta para a raiz da arvore e um ponteiro do no que causa violacao //
void rightRotate(Node **root, Node *y);


#endif
