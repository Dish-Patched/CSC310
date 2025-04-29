#include "binomialHeap.h"

binomialNode::binomialNode(Edge e) 
{ 
    edge = e;
    degree = 0; 
    parent = nullptr; 
    child = nullptr; 
    sibling = nullptr;
}

BinomialHeap::BinomialHeap()
{
    head = nullptr;
}

binomialNode* BinomialHeap::mergeTrees(binomialNode* tree1, binomialNode* tree2) {
    if (tree1->edge.weight > tree2->edge.weight)
        swap(tree1, tree2);
    tree2->parent = tree1;
    tree2->sibling = tree1->child;
    tree1->child = tree2;
    tree1->degree++;
    return tree1;
}

binomialNode* BinomialHeap::unionHeaps(binomialNode* heap1, binomialNode* heap2) {
    if (!heap1) return heap2;
    if (!heap2) return heap1;

    binomialNode* newHead = nullptr;
    binomialNode** pos = &newHead;

    while (heap1 && heap2) {
        if (heap1->degree <= heap2->degree) {
            *pos = heap1;
            heap1 = heap1->sibling;
        } else {
            *pos = heap2;
            heap2 = heap2->sibling;
        }
        pos = &(*pos)->sibling;
    }

    *pos = heap1 ? heap1 : heap2;
    return newHead;
}

void BinomialHeap::linkTrees(binomialNode*& prev, binomialNode*& curr, binomialNode*& next) {
    if (curr->edge.weight <= next->edge.weight) {
        curr->sibling = next->sibling;
        mergeTrees(curr, next);
    } else {
        if (prev)
            prev->sibling = next;
        else
            head = next;
        mergeTrees(next, curr);
        curr = next;
    }
}

void BinomialHeap::insert(Edge edge) {
    BinomialHeap tempHeap;
    tempHeap.head = new binomialNode(edge);
    merge(tempHeap);
}

void BinomialHeap::merge(BinomialHeap& other) {
    head = unionHeaps(head, other.head);
    if (!head) return;

    binomialNode* prev = nullptr;
    binomialNode* curr = head;
    binomialNode* next = curr->sibling;

    while (next) {
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            linkTrees(prev, curr, next);
        }
        next = curr->sibling;
    }
}

Edge BinomialHeap::findMin() {
    if (!head) throw runtime_error("Heap is empty");

    binomialNode* y = nullptr;
    binomialNode* x = head;
    Edge minEdge = x->edge;

    while (x) {
        if (x->edge.weight < minEdge.weight) {
            minEdge = x->edge;
            y = x;
        }
        x = x->sibling;
    }

    return minEdge;
}

void BinomialHeap::deleteMin() {
    if (!head) return;

    binomialNode* prevMin = nullptr;
    binomialNode* minNode = head;
    binomialNode* prev = nullptr;
    Edge minEdge = minNode->edge;

    for (binomialNode* curr = head; curr; curr = curr->sibling) {
        if (curr->edge.weight < minEdge.weight) {
            minEdge = curr->edge;
            prevMin = prev;
            minNode = curr;
        }
        prev = curr;
    }

    if (prevMin)
        prevMin->sibling = minNode->sibling;
    else
        head = minNode->sibling;

    binomialNode* childReversed = reverseList(minNode->child);
    BinomialHeap tempHeap;
    tempHeap.head = childReversed;
    merge(tempHeap);

    delete minNode;
}

binomialNode* BinomialHeap::reverseList(binomialNode* node) {
    binomialNode* prev = nullptr;
    while (node) {
        binomialNode* next = node->sibling;
        node->sibling = prev;
        node->parent = nullptr;
        prev = node;
        node = next;
    }
    return prev;
}

void BinomialHeap::decreaseKey(Edge oldEdge, Edge newEdge) {
    binomialNode* node = findNode(head, oldEdge);
    if (!node || newEdge.weight > node->edge.weight)
        return;

    node->edge = newEdge;
    binomialNode* y = node;
    binomialNode* z = y->parent;

    while (z && y->edge.weight < z->edge.weight) {
        swap(y->edge, z->edge);
        y = z;
        z = y->parent;
    }
}

void BinomialHeap::deleteKey(Edge edge) {
    Edge minusInfEdge = edge;
    minusInfEdge.weight = INT_MIN;
    decreaseKey(edge, minusInfEdge);
    deleteMin();
}

binomialNode* BinomialHeap::findNode(binomialNode* node, Edge edge) {
    if (!node)
        return nullptr;
    if (node->edge.src == edge.src && node->edge.dest == edge.dest && node->edge.weight == edge.weight)
        return node;

    binomialNode* res = findNode(node->child, edge);
    if (res)
        return res;

    return findNode(node->sibling, edge);
}

void BinomialHeap::printHeap() {
    cout << "Binomial Heap:\n";
    binomialNode* temp = head;
    while (temp) {
        cout << "B" << temp->degree << ":\n";
        printTree(temp, 0);
        temp = temp->sibling;
    }
}

void BinomialHeap::printTree(binomialNode* node, int space) {
    if (!node)
        return;

    space += 5;
    printTree(node->sibling, space);

    cout << setw(space) << " " << "(" << node->edge.src << ", " << node->edge.dest << ", " << node->edge.weight << ")\n";

    printTree(node->child, space);
}
