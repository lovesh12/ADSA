#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int data) : data(data)
    {
        left = NULL;
        right = NULL;
    }
};

bool search(Node *root, int x)
{
    if (root == NULL)
        return false;
    while (root)
    {
        if (root->data == x)
            return true;
        else if (root->data < x)
            root = root->right;
        else
            root = root->left;
    }

    return false;
}

bool insert(Node *&root, int x)
{
    if (root == NULL)
    {
        root = new Node(x);
        return true;
    }

    Node *prev = NULL;
    Node *curr = root;
    while (curr)
    {
        prev = curr;
        if (curr->data == x)
            return false;
        else if (curr->data < x)
            curr = curr->right;
        else
            curr = curr->left;
    }

    if (x < prev->data)
        prev->left = new Node(x);
    else
        prev->right = new Node(x);

    return true;
}

Node *getSucc(Node *root)
{
    Node *prev = root;
    while (root)
    {
        prev = root;
        root = root->left;
    }

    return prev;
}

Node *remove(Node *root, int x)
{
    if (root == NULL)
        return NULL;
    if (root->data < x)
        root->right = remove(root->right, x);
    else if (root->data > x)
        root->left = remove(root->left, x);
    else
    {
        if (root->left && root->right)
        {
            Node *succ = getSucc(root->right);
            root->data = succ->data;
            root->right = remove(root->right, succ->data);
        }
        else if (root->right)
        {
            Node *r = root->right;
            delete root;
            return r;
        }
        else if (root->left)
        {
            Node *r = root->left;
            delete root;
            return r;
        }

        else
            return NULL;
    }

    return root;
}

int main()
{
    Node *root = NULL;
    insert(root, 1);
    insert(root, 10);
    insert(root, 5);
    insert(root, 11);
    insert(root, 7);
    insert(root, 6);
    insert(root, 8);
    insert(root, 9);

    cout << search(root, 9) << endl;
    cout << search(root, 11) << endl;
    root = remove(root, 9);
    cout << search(root, 9) << endl;
    cout << search(root, 11) << endl;
}