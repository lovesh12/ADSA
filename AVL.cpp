#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    int height;
    Node *left;
    Node *right;

    Node(int data) : data(data)
    {
        left = NULL;
        right = NULL;
        height = 1;
    }
};

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

int height(Node *root)
{
    if (!root)
        return 0;
    return root->height;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

Node *rightRotate(Node *x)
{
    Node *y = x->left;
    Node *t = y->right;

    y->right = x;
    x->left = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

Node *insert(Node *root, int x)
{
    Node *n = new Node(x);
    if (!root)
        return n;

    if (root->data < x)
        root->right = insert(root->right, x);
    else if (root->data > x)
        root->left = insert(root->left, x);
    else
        return root;
    root->height = 1 + max(height(root->left), height(root->right));

    int balf = (height(root->left) - height(root->right));
    if (abs(balf) <= 1)
        return root;

    if (balf > 1)
    {
        if (x < root->left->data) // LL
            return rightRotate(root);

        else if (x > root->left->data) // LR
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    else if (balf < -1)
    {
        if (x > root->right->data) // RR
            return leftRotate(root);

        else if (x < root->right->data) // RL
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

Node *remove(Node *&root, int x)
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
            *root = *r;
            delete r;
        }
        else if (root->left)
        {
            Node *r = root->left;
            *root = *r;
            delete r;
        }
        else
            return NULL;
    }
    root->height = 1 + max(height(root->left), height(root->right));

    int balf = (height(root->left) - height(root->right));
    if (abs(balf) <= 1)
        return root;

    if (balf > 1)
    {
        if (x < root->left->data) // LL
            return rightRotate(root);

        else if (x > root->left->data) // LR
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    else if (balf < -1)
    {
        if (x > root->right->data) // RR
            return leftRotate(root);

        else if (x < root->right->data) // RL
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

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

void bfs(Node *root)
{
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();
    }
}

int main()
{
    Node *root = NULL;

    root = insert(root, 1);
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 11);
    root = insert(root, 7);
    root = insert(root, 6);
    root = insert(root, 8);
    root = insert(root, 9);

    cout << search(root, 9) << endl;
    cout << search(root, 11) << endl;
    root = remove(root, 9);
    cout << search(root, 9) << endl;
    cout << search(root, 11) << endl;
}