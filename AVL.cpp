#include <iostream>

struct Node
{
    int key;
    Node *left = nullptr;
    Node *right = nullptr;
    int height = 1;
};