#ifndef UF_H
#define UF_H

#include<iostream>
using namespace std;

class weightedQuickUnion
{
    private:
        int* parent;
        int* size;
        int n;

    public:
        weightedQuickUnion(int n);
        ~weightedQuickUnion();

        int find(int p);
        void Union(int p, int q);
        bool connected(int p, int q);

        void print();
};

#endif