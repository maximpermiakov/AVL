#include <iostream>

struct Node
{
    int key;
    Node *left = nullptr;
    Node *right = nullptr;
    int height = 1;
};

int height(Node *node)
{
    if (node == nullptr)
        return 0;
    return std::max(height(node->left), height(node->right)) + 1;
}

int bfactor(Node *node)
{
    return height(node->right) - height(node->left);
}

void fixheight(Node *node)
{
    if (node == nullptr)
        return;
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

Node *rotate_right(Node *p)
{
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

Node *rotate_left(Node *p)
{
    Node *q = p->right;
    p->right = q->left;
    q->left = p;
    fixheight(p);
    fixheight(q);
    return q;
}

Node *balance(Node *p)
{
    fixheight(p);
    if (bfactor(p) == 2)
    {
        if (bfactor(p->right) < 0)
        {
            p->right = rotate_right(p->right);
        }
        return rotate_left(p);
    }
    if (bfactor(p) == -2)
    {
        if (bfactor(p->left) > 0)
        {
            p->left = rotate_left(p->left);
        }
        return rotate_right(p);
    }
    return p;
}

Node *push(Node *root, int new_key)
{
    if (root == nullptr)
    {
        root = new Node;
        root->key = new_key;
        return root;
    }
    if (new_key > root->key)
    {
        root->right = push(root->right, new_key);
    }
    else
    {
        root->left = push(root->left, new_key);
    }
    return balance(root);
}

Node *findmin(Node *p)
{
    if (p->left == nullptr)
        return p;
    return findmin(p->left);
}

Node *removemin(Node *p)
{
    if (p->left == nullptr)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

Node *pop(Node *root, int key)
{
    if (root == nullptr)
        return nullptr;
    if (key > root->key)
    {
        root->right = pop(root->right, key);
    }
    else if (key < root->key)
    {
        root->left = pop(root->left, key);
    }
    else
    {
        Node *left = root->left;
        Node *right = root->right;
        delete root;
        if (right == nullptr)
            return left;
        Node *min = findmin(right);
        min->right = removemin(right);
        min->left = left;
        return balance(min);
    }
    return balance(root);
}

Node *find(Node *root, int key)
{
    if (root == nullptr or root->key == key)
        return root;
    if (root->key > key)
        return find(root->left, key);
    if (root->key < key)
        return find(root->right, key);
}

void destroy_tree(Node *root)
{
    if (root->left != nullptr)
        destroy_tree(root->left);
    if (root->right != nullptr)
        destroy_tree(root->right);
    delete root;
}

void preorder(Node *root)
{
    if (root == nullptr)
        return;
    std::cout << root->key << std::endl;
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    std::cout << root->key << std::endl;
    inorder(root->right);
}

void postorder(Node *root)
{
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->key << std::endl;
}