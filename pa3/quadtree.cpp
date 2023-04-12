
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */
#include <iostream>
#include <stack>
#include "quadtree.h"
using namespace std;

// Node constructor, given.
quadtree::Node::Node(pair<int, int> ul, int d, RGBAPixel a, double v)
    : upLeft(ul), dim(d), avg(a), var(v), NW(nullptr), NE(nullptr), SE(nullptr), SW(nullptr) {}

// quadtree destructor, given.
quadtree::~quadtree() {
    clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree& other) {
    copy(other);
}
// quadtree assignment operator, given.
quadtree& quadtree::operator=(const quadtree& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

quadtree::quadtree(PNG& imIn) {
    edge = imIn.width();
    int dim = int(log2(edge));
    stats s(imIn);
    root = buildTree(s, make_pair(0,0), dim);
}


quadtree::Node* quadtree::buildTree(stats& s, pair<int, int> ul, int dim) {
    /* Your code here! */
        Node* n =  new Node (ul, dim, s.getAvg(ul,dim), s.getVar(ul,dim));
        if (dim == 0) {
            n->NW = nullptr;
            n->NE = nullptr;
            n->SE = nullptr;
            n->SW = nullptr;
            return n;   
        } else {  
           pair<int,int> NWul = ul;
           pair<int, int> NEul = make_pair(ul.first + pow(2, (dim -1)), ul.second);
           pair<int,int> SWul = make_pair(ul.first, pow(2, (dim - 1)) + ul.second);
           pair<int,int> SEul = make_pair(ul.first + pow(2, (dim -1)), ul.second + pow(2, dim - 1));

           n->NW = buildTree(s, ul, dim - 1);
           n->NE = buildTree(s, NEul, dim - 1);
           n->SE = buildTree(s, SEul, dim - 1);
           n->SW = buildTree(s, SWul, dim - 1);     
           return n;
        }

}


PNG quadtree::render() const {
    /* Your code here! */
    PNG im(edge, edge);
    renderHelper(root, im);
    return im;
    
}

int k = 0;
void quadtree::renderHelper(Node* node, PNG im) const {
    if (!node) {
        cout << "return in render" << endl;
        return;
    }

    if (!node->NW && !node->SE && !node->SW && !node->NE) {
        //cout << k++ << endl;
        int nside = pow(2, node->dim);
        for (int x = node->upLeft.first; x < node->upLeft.first + nside; x++) {
            for (int y = node->upLeft.second; y < node->upLeft.second + nside; y++) {
                *im.getPixel(x,y) = node->avg;
                 return;
            }
        }
    }

    else {
        //cout << k++ << endl;
        renderHelper(node->NW, im);
        renderHelper(node->NE, im);
        renderHelper(node->SW, im);
        renderHelper(node->SE, im);     
    }
}

int quadtree::idealPrune(const int leaves) const {
    /* Your code here! */
    return 0;
}

int quadtree::pruneSize(const int tol) const {
    /* Your code here! */
    return 0;
}

void quadtree::prune(const int tol) {
    /* Your code here! */
}

 void quadtree::clear() {
     /* your code here */
 }



void quadtree::copy(const quadtree& orig) {
    /* your code here */
}






