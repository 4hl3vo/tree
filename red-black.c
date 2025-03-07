#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int val;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

Node* createNode(int val, Color color, Node* parent);
void freeTree(Node* node);
void preOrderTraversal(Node* node);
Node* grandparent(Node* node);
Node* uncle(Node* node);
void insert_case1(Node* node);
void insert_case2(Node* node);
void insert_case3(Node* node);
void insert_case4(Node* node);
void insert_case5(Node* node);
void left_rotate(Node* node);
void right_rotate(Node* node);
Node* insertNode(Node* root, int val);

int main(void) {
    int input;
    Node* root = NULL;

    do {
        scanf("%d", &input);
        if (!input)
            break;
        root = insertNode(root, input);
    } while (input);

    printf("\n");
    preOrderTraversal(root);
    printf("\n");

    freeTree(root);
    return 0;
}

Node* createNode(int val, Color color, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node) {
        node->val = val;
        node->color = color;
        node->parent = parent;
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

void preOrderTraversal(Node* node) {
    if (!node)
        return;
    printf("%d ", node->val);
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

Node* grandparent(Node* node) {
    if (node && node->parent)
        return node->parent->parent;
    return NULL;
}

Node* uncle(Node* node) {
    Node* g = grandparent(node);
    if (!g)
        return NULL;
    return (node->parent == g->left) ? g->right : g->left;
}

void left_rotate(Node* node) {
    Node* right_child = node->right;
    Node* parent = node->parent;

    node->right = right_child->left;
    if (node->right)
        node->right->parent = node;

    right_child->parent = parent;
    if (parent) {
        if (node == parent->left)
            parent->left = right_child;
        else
            parent->right = right_child;
    }

    right_child->left = node;
    node->parent = right_child;
}

void right_rotate(Node* node) {
    Node* left_child = node->left;
    Node* parent = node->parent;

    node->left = left_child->right;
    if (node->left)
        node->left->parent = node;

    left_child->parent = parent;
    if (parent) {
        if (node == parent->left)
            parent->left = left_child;
        else
            parent->right = left_child;
    }

    left_child->right = node;
    node->parent = left_child;
}

void insert_case1(Node* node) {
    if (!node->parent) {
        node->color = BLACK;
    } else {
        insert_case2(node);
    }
}

void insert_case2(Node* node) {
    if (node->parent->color == BLACK)
        return;
    else
        insert_case3(node);
}

void insert_case3(Node* node) {
    Node* u = uncle(node);
    Node* g = grandparent(node);

    if (u && u->color == RED) {
        node->parent->color = BLACK;
        u->color = BLACK;
        g->color = RED;
        insert_case1(g);
    } else {
        insert_case4(node);
    }
}

void insert_case4(Node* node) {
    Node* g = grandparent(node);

    if (node == node->parent->right && node->parent == g->left) {
        left_rotate(node->parent);
        node = node->left;
    } else if (node == node->parent->left && node->parent == g->right) {
        right_rotate(node->parent);
        node = node->right;
    }

    insert_case5(node);
}

void insert_case5(Node* node) {
    Node* g = grandparent(node);

    node->parent->color = BLACK;
    g->color = RED;

    if (node == node->parent->left && node->parent == g->left) {
        right_rotate(g);
    } else {
        left_rotate(g);
    }
}

Node* insertNode(Node* root, int val) {
    Node** current = &root;
    Node* parent = NULL;

    while (*current) {
        parent = *current;
        if (val < (*current)->val)
            current = &(*current)->left;
        else
            current = &(*current)->right;
    }

    *current = createNode(val, RED, parent);
    insert_case1(*current);

    Node* newRoot = *current;
    while (newRoot->parent)
        newRoot = newRoot->parent;

    return newRoot;
}
