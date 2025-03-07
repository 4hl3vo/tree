# tree

## preorder traversal
* visit the root
* traverse the left subtree
* traverse the right subtree
```c
void preOrderTraversal(Node* n)
{
    if (!n)
        return;

    printf("%d\n", n->val);
    preOrderTraversal(n->left);
    preOrderTraversal(n->right);
}
```
## inorder traversal
* traverse the left subtree
* visit the root
* traverse the right subtree
```c
void inOrderTraversal(Node* n)
{
    if (!n)
        return;


    inOrderTraversal(n->left);
    printf("%d\n", n->val);
    inOrderTraversal(n->right);
}
```

## postorder traversal
* traverse the left subtree
* traverse the right subtree
* visit the root
```c
void postOrderTraversal(Node* n)
{
    if (!n)
        return;

    postOrderTraversal(n->left);
    postOrderTraversal(n->right);
    printf("%d\n", n->val);
}
```
## insert in a BST
```c
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
```

## AVL

* Adel'son-Vel'skii & Landis , 1962
* Fator de Balanceamento (FB)
* FB(node) = altura(node->left) - altura(node->right)
* balanceada = o fator de balanceamento de todos os nós está no intervalo:
> -1 <=FB <= 1

### altura
```c 
int height(Node* node)
{
    int hLeft, hRight;

    if (!node)
        return 0;

    hLeft = height(node->left);
    hRight = height(node->right);

    if (hLeft > hRight)
        return hLeft + 1;
    else
        return hRight + 1;
}
```
