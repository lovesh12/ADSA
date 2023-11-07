#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int key;
    Node *child;
    Node *sibling;
    Node *parent;
    int degree;

    Node(int key) : key(key), child(NULL), sibling(NULL), parent(NULL), degree(0){};
};

typedef list<Node *> heap;

heap heapUnion(heap h1, heap h2)
{
    heap nheap;
    auto it1 = h1.begin();
    auto it2 = h2.begin();
    while (it1 != h1.end() && it2 != h2.end())
    {
        if ((*it1)->degree <= (*it2)->degree)
        {
            nheap.push_back(*it1);
            it1++;
        }

        else
        {
            nheap.push_back(*it2);
            it2++;
        }
    }

    while (it1 != h1.end())
    {
        nheap.push_back(*it1);
        it1++;
    }

    while (it2 != h2.end())
    {
        nheap.push_back(*it2);
        it2++;
    }

    return nheap;
}

void swap(Node *&a, Node *&b)
{
    Node *t = a;
    a = b;
    b = t;
}

Node *mergeBinomialTrees(Node *t1, Node *t2)
{
    if (t1->key > t2->key)
        swap(t1, t2);

    t2->parent = t1;
    t2->sibling = t1->child;
    t1->child = t2;
    t1->degree++;

    return t1;
}

heap fixHeap(heap h)
{
    if (h.size() <= 1)
        return h;
    auto it1 = h.begin();
    auto it2 = it1;
    auto it3 = it1;

    if (h.size() == 2)
    {
        it2++;
        it3 = h.end();
    }
    else
    {
        it2++;
        for (int i = 0; i < 2; i++)
            it3++;
    }

    while (it1 != h.end())
    {
        if (it2 == h.end())
        {
            it1++;
            break;
        }
        else if ((*it1)->degree < (*it2)->degree)
        {
            it1++;
            it2++;
            if (it3 != h.end())
                it3++;
        }
        // all 3 same
        else if (it3 != h.end() && (*it1)->degree == (*it2)->degree && (*it2)->degree && (*it3)->degree)
        {
            it1++;
            it2++;
            it3++;
        }
        // 2 same
        else if ((*it1)->degree == (*it2)->degree)
        {
            *it1 = mergeBinomialTrees(*it1, *it2);
            h.erase(it2);
            if (it3 != h.end())
                it3++;
        }
        return h;
    }
}

heap insert(heap _heap, int x)
{
    Node *n = new Node(x);
    heap nheap;
    nheap.push_back(n);

    _heap = heapUnion(_heap, nheap);
    return fixHeap(_heap);
}

Node *getMin(heap h)
{
    auto it = h.begin();
    Node *temp = *it;
    while (it != h.end())
    {
        if ((*it)->key < temp->key)
            temp = *it;
        it++;
    }
    return temp;
}

heap removeMinFromTreeReturnHeap(Node *tree)
{
    heap h;
    Node *temp = tree->child;
    Node *lo;

    // making a binomial heap from Binomial Tree
    while (temp)
    {
        lo = temp;
        temp = temp->sibling;
        lo->sibling = NULL;
        h.push_front(lo);
    }
    return h;
}

heap extractMin(heap h)
{
    heap nheap;
    Node *tmin = getMin(h);

    auto it = h.begin();
    while (it != h.end())
    {
        if (*it != tmin)
            nheap.push_back(*it);
        it++;
    }

    auto removedH = removeMinFromTreeReturnHeap(tmin);
    nheap = heapUnion(nheap, removedH);
    nheap = fixHeap(nheap);
    return nheap;
}

// print function for Binomial Tree
void printTree(Node *t)
{
    while (t)
    {
        cout << t->key << " ";
        printTree(t->child);
        t = t->sibling;
    }
}

// print function for binomial heap
void printHeap(heap h)
{
    auto it = h.begin();
    while (it != h.end())
    {
        printTree(*it);
        it++;
    }
}

int main()
{
    heap h;

    h = insert(h, 10);
    h = insert(h, 20);
    h = insert(h, 30);

    cout << "Heap elements after insertion:" << endl;
    printHeap(h);

    cout << "Minimum element of heap: ";
    Node *t = getMin(h);
    cout << t->key << endl;

    h = extractMin(h);
    cout << "Heap elements after extracing minimum:" << endl;
    printHeap(h);
}