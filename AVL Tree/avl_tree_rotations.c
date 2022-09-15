#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int max(int a, int b)
{
    return a > b ? a : b;
}

int getHeight(struct Node *node)
{
    if (node == NULL)
        return 0;

    return node->height;
}

struct Node *createNode(int key)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getBalanceFactor(struct Node *node)
{
    if (node == NULL)
        return 0;

    return getHeight(node->left) - getHeight(node->right);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return y;
}

struct Node *insert(struct Node *node, int key)
{
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance_factor = getBalanceFactor(node);

    // Left Left Case
    if (balance_factor > 1 && key < node->left->key)
    {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance_factor < -1 && key > node->right->key)
    {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance_factor > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance_factor < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preorder(struct Node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->key);

    preorder(root->left);
    preorder(root->right);
}

int main()
{
    struct Node *root = NULL;
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 3);
    preorder(root);
    return 0;
}
