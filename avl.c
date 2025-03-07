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
int height(Node* node);
int balance_factor(Node* node);
Node* left_rotation(Node* node);
Node* right_rotation(Node* node);
int balance_left(Node* node);
int balance_right(Node* node);
int balance(Node* node);
int is_avl(Node* node);

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
		
	is_avl(root) ? printf("eh avl\n") : printf("nn eh avl\n");
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

    int bf = balance_factor(node);

    if (bf > 1 && val < node->left->val)
        return right_rotation(node);

    if (bf < -1 && val > node->right->val)
        return left_rotation(node);

    if (bf > 1 && val > node->left->val) {
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }

    if (bf < -1 && val < node->right->val) {
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }

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

int height(Node* node)
{
    int h_left, h_right;

    if (!node)
        return 0;

    h_left = height(node->left);
    h_right = height(node->right);

    if (h_left > h_right)
        return h_left + 1;
    else
        return h_right + 1;
}

int balance_factor(Node* node)
{
	return node ? height(node->left) - height(node->right) : 0;
}

Node* left_rotation(Node* node)
{
	Node *temp;

	temp = node->right;
	node->right = node->left;
	temp->left = node;

	return temp;
}

Node* right_rotation(Node* node)
{
	Node *temp;

	temp = node->left;
	node->left = node->right;
	temp->right = node;

	return temp;
}

int balance_left(Node* node)
{
	int bf_left = balance_factor(node->left);

	if (bf_left > 0) {
		right_rotation(node);
		return 1;
	} else if (bf_left < 0) {
		left_rotation(node->left);
		right_rotation(node);
		return 1;
	}
	return 0;
}

int balance_right(Node* node)
{
	int bf_right = balance_factor(node->right);

	if (bf_right > 0) {
		left_rotation(node);
		return 1;
	} else if (bf_right < 0) {
		right_rotation(node->left);
		left_rotation(node);
		return 1;
	}
	return 0;
}

int balance(Node* node)
{
	int bf = balance_factor(node);

	if (bf > 1)
		return balance_left(node);
	else if (bf < -1)
		return balance_right(node);
	else
		return 0;
}

int is_avl(Node* node)
{
	int bf;

	if (!node)
		return 1;

	if (!is_avl(node->left))
		return 0;
	if (!is_avl(node->right))
		return 0;

	bf = balance_factor(node);

	if ( (bf > 1) || (bf < -1) )
		return 0;
	else 
		return 1;
}
