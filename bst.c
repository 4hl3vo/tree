#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int val;
	struct Node* left;
	struct Node* right;
} Node;

Node* createNode(int val);
void freeTree(Node* node);
Node* insertNode(Node* node, int val);
void preOrderTraversal(Node* node);
void inOrderTraversal(Node* node);
void postOrderTraversal(Node* node);

int main(void)
{
	int input;
	Node* root;

	do {
		scanf("%d", &input);
		
		if (!input)
			break;

		root = insertNode(root, input);
	} while (input);
	
	printf("\n");
	preOrderTraversal(root);
	printf("\n");
	inOrderTraversal(root);
	printf("\n");
	postOrderTraversal(root);
	printf("\n");

	freeTree(root);

	return 0;
}

Node* createNode(int val)
{
	Node* node = (Node*)malloc(sizeof(Node));
	
	if (node) {
		node->val = val;
		node->left = NULL;
		node->right = NULL;
	}

	return node;
}

void freeTree(Node* node) {
    if (!node)
        return;

    freeTree(node->left);
    freeTree(node->right);
	free(node);
}

Node* insertNode(Node* node, int val) 
{
	if (!node)
		return createNode(val);

	if (val < node->val)
		node->left = insertNode(node->left, val);
	else
		node->right = insertNode(node->right, val);

	return node;
}

void preOrderTraversal(Node* node)
{
    if (!node)
        return;

    printf("%d ", node->val);
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

void inOrderTraversal(Node* node)
{
    if (!node)
        return;

    inOrderTraversal(node->left);
    printf("%d ", node->val);
    inOrderTraversal(node->right);
}

void postOrderTraversal(Node* node)
{
    if (!node)
        return;

    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    printf("%d ", node->val);
}
