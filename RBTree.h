#ifndef RBTREE_H
#define RBTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
bool searchRB(Node *root, int val);


// Funcao que realiza a busca de um valor na arvore e retorna o no //
// Recebe um ponteiro que aponta para a raiz da arvore e o valor a ser buscado //
Node *searchRBNode(Node *root, int val);


// Funcao que realiza a troca entre os nos da arvore //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore, um ponteiro para o no que sera substituido e um ponteiro para o no que ira assumir o lugar //
void swapNodes(Node **root, Node *out, Node *in);


// Funcao que efetua correcao de violacoes causadas pela insercao //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore e um ponteiro do no que foi inserido //
void insertFix(Node **root, Node *z);


// Funcao que efetua correcao de violacoes causadas pela remocao //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore, um ponteiro do no que substituiu o no removido e um ponteiro para o seu pai //
void removeFix(Node **root, Node *x, Node *xParent);


// Funcao que imprime a arvore em formato pre-ordem //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore //
void printPreOrder(Node **root);


// Funcao que imprime a arvore em formato Em ordem //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore //
void printInOrder(Node **root);


// Funcao que imprime a arvore em formato Pos-ordem //
// Recebe um ponteiro que aponta para o ponteiro da raiz da arvore //
void printPosOrder(Node **root);


// Funcao que gera uma arvore rubro-negra inicial //
Node *initialRBTree();


// Funcao que inicializa o programa //
void startProgram();


#endif
