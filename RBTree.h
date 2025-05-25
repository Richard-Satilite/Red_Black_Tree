#ifndef RBTREE_H
#define RBTREE_H


// Definindo dado do tipo Color //
typedef enum Color{
	RED,
	BLACK
}Color;


// Definindo dado do tipo Bool //
typedef enum {
	false,
	true
}Bool;


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
Node *genNode(int val);


// Funcao que efetua uma rotacao a esquerda //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore e um ponteiro do no que causa violacao //
void leftRotate(Node **root, Node *x);


// Funcao que efetua uma rotacao a direita //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore e um ponteiro do no que causa violacao //
void rightRotate(Node **root, Node *y);


// Funcao que efetua uma insercao na arvore //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore e o valor a ser inserido //
void insertRB(Node **root, int val);


// Funcao que efetua a remocao de um no na arvore //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore e o valor do no a ser removido //
void removeRB(Node **root, int val);


// Funcao que realiza a busca de um valor na arvore //
// Recebe um ponteiro que aponta para a raiz da arvore e o valor a ser buscado //
Bool searchRB(Node *root, int val);


// Funcao que realiza a busca de um valor na arvore e retorna o no //
// Recebe um ponteiro que aponta para a raiz da arvore e o valor a ser buscado //
Node *seachRBNode(Node *root, int val);


// Funcao que realiza a troca entre os nos da arvore //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore, um ponteiro para o no que sera substituido e um ponteiro para o no que ira assumir o lugar //
void swapNodes(Node **root, Node *out, Node *in);


// Funcao que efetua correcao de violacoes causadas pela insercao //
// Recebe um pornteiro que aponta para o ponteiro da raiz da arovre e um ponteiro do no que foi inserido //
void insertFix(Node **root, Node *z);

#endif
