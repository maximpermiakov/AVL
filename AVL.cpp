#include <iostream>

struct Node
{
    int key;
    Node *left = nullptr;
    Node *right = nullptr;
    int height = 1;
};

struct Tree
{
    Node *ROOT;
    Node *NIL;
};

Tree *create_empty_tree()
{
    Tree *tree = new Tree;
    Node *NIL = new Node;
    tree->NIL = NIL;
    tree->ROOT = NIL;
    return tree;
}
