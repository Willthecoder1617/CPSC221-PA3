
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
    if (edge == 0) {
         PNG img(0,0);
         return img;
    }
    
    int dim = int(log2(edge));
    PNG im(pow(2,dim), pow(2,dim));
    cout << "root:" << endl;
 
    renderHelper(root, im);
    return im;
    
}

int k = 0;
void quadtree::renderHelper(Node* node, PNG &im) const {
    if (node == nullptr) {
        cout << "return in render" << endl;
        return;
    }

    if (node->NW == nullptr && node->SE == nullptr && node->SW == nullptr && node->NE == nullptr) {
       //cout << k++ << endl;
        int nside = pow(2, node->dim); 
       for (int x = node->upLeft.first; x < node->upLeft.first + nside; x++) {
        for (int y = node->upLeft.second; y < node->upLeft.second + nside; y++) {
            *im.getPixel(x, y) = node->avg; 
        }

       }           
    }
    
    else {
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
    if (root->NW == nullptr){
        return prunesizehelper(root,tol);
    }
    int count = 0;
    if (prunable(root->NW,tol)){
    
        count++;

    }else{
        count += prunesizehelper(root->NW,tol);

    }

     if (prunable(root->NE,tol)){
    
        count++;

    }else{
        count += prunesizehelper(root->NE,tol);

    }

     if (prunable(root->SW,tol)){
    
        count++;

    }else{
        count += prunesizehelper(root->SW,tol);

    }


     if (prunable(root->SE,tol)){
    
        count++;

    }else{
        count += prunesizehelper(root->SE,tol);

    }

    return count;
}

int quadtree::prunesizehelper(Node* node,const int tol ) const{
    
    if (node->NW == nullptr && node->NE == nullptr && node->SW == nullptr && node->SE == nullptr)     {
       return 1;
    }  else {
         int count = 0;
    if (prunable(node->NW,tol)){
    
        count++;

    }else{
        count += prunesizehelper(node->NW,tol);

    }

     if (prunable(node->NE,tol)){
    
        count++;

    }else{
        count += prunesizehelper(node->NE,tol);

    }

     if (prunable(node->SW,tol)){
    
        count++;

    }else{
        count += prunesizehelper(node->SW,tol);

    }


     if (prunable(node->SE,tol)){
    
        count++;

    }else{
        count += prunesizehelper(node->SE,tol);

    }

       return count;
        
    }
}


void quadtree::prune(const int tol) {
    /* Your code here! */
    if (prunable(root, tol)) {
        clearhelper(root->NE);
        clearhelper(root->NW);
        clearhelper(root->SE);
        clearhelper(root->SW);

 


        root->NE = nullptr;
        root->NW = nullptr;
        root->SW = nullptr;
        root->SE = nullptr;
        
       // prunehelper2(root);
    } else {
        prunehelper(root,tol);

    }
    
    // if (!prunable(root->NW,tol)){
    //     prunehelper(root->NW,tol);
    // }else{
    //     prunehelper2(root->NW);
    //     root->NW = nullptr;
    // }


    // if (!prunable(root->NE,tol)){
    //     prunehelper(root->NE,tol);
    // }else{
    //     prunehelper2(root->NE);
    //     root->NE = nullptr;
    // }

    // if (!prunable(root->SW,tol)){
    //     prunehelper(root->SW,tol);
    // }else{
    //     prunehelper2(root->SW);
    //     root->SW = nullptr;
    // }

    // if (!prunable(root->SE,tol)){
    //     prunehelper(root->SE,tol);
    // }else{
    //     clearhelper(root->SE);
    //     root->SE = nullptr;
    // }
    
}

void quadtree::prunehelper(Node* node,const int tol ){
    if (node == nullptr) {
        return;
    }
   
       if (prunable(node->NW,tol) && node->NW != nullptr){

        clearhelper(node->NW->SE);
        clearhelper(node->NW->NW);
        clearhelper(node->NW->NE);
        clearhelper(node->NW->SW);
        //clearhelper(node->NW);
        node->NW->SE = nullptr;
        node->NW->NW = nullptr;
        node->NW->NE = nullptr;
        node->NW->SW = nullptr;
        

       } else {
        prunehelper(node->NW, tol);
       }

       if (prunable(node->NE,tol) && node->NE != nullptr){
        //clearhelper(node->NE);

        clearhelper(node->NE->SE);
        clearhelper(node->NE->NW);
        clearhelper(node->NE->NE);
        clearhelper(node->NE->SW);

        node->NE->SE = nullptr;
        node->NE->NW = nullptr;
        node->NE->NE = nullptr;
        node->NE->SW = nullptr;
       

       } else {
        prunehelper(node->NE, tol);
       }

       if (prunable(node->SW,tol) && node->SW != nullptr){
        clearhelper(node->SW->SE);
        clearhelper(node->SW->NW);
        clearhelper(node->SW->NE);
        clearhelper(node->SW->SW);
        node->SW->SE = nullptr;
        node->SW->NW = nullptr;
        node->SW->NE = nullptr;
        node->SW->SW = nullptr;

       } else {
        prunehelper(node->SW, tol);

       }

       if (prunable(node->SE,tol) && node->SE != nullptr) {

        clearhelper(node->SE->SE);
        clearhelper(node->SE->NW);
        clearhelper(node->SE->NE);
        clearhelper(node->SE->SW);
        //clearhelper(node->SE);
        node->SE->SE = nullptr;
        node->SE->NW = nullptr;
        node->SE->NE = nullptr;
        node->SE->SW = nullptr;

       } else {
        prunehelper(node->SE, tol);
       }
    

 }

void quadtree::prunehelper2(Node* node ){

    if (node == nullptr) {
        return;
    }
    if (node->NW == nullptr && node->NE == nullptr && node->SW == nullptr && node->SE == nullptr)     {
        delete(node);
    }   else {

        prunehelper2(node->NW);
        prunehelper2(node->NE);
        prunehelper2(node->SW);
        prunehelper2(node->SE);



        delete(node);
    }
}

void quadtree::clear() {
    /* your code here */
    clearhelper(root);
    
    
}

//helper function 3
void quadtree::clearhelper(Node* n){
    if (n == nullptr) {
        return;
    }
    if (n->NW != nullptr){
        clearhelper(n->NW);
        
    }

     if (n->NE != nullptr){
        clearhelper(n->NE);
    }
    
     if (n->SW != nullptr){
        clearhelper(n->SW);
    } 
    
    if (n->SE != nullptr){
        clearhelper(n->SE);
    }

    delete(n);
    n = nullptr;

}
 


void quadtree::copy(const quadtree& orig) {
    /* your code here */
    edge = orig.edge;
    root = copyhelper(orig.root);

}
//helper function 4

int i = 0;
quadtree::Node* quadtree::copyhelper(Node* n){
    if (n == nullptr) {
        return nullptr;
    } 
    //cout << i++ << endl;
     Node* nod = new Node(n->upLeft,n->dim, n->avg,n->var);
        nod->NW = copyhelper(n->NW);
        nod->NE = copyhelper(n->NE);
        nod->SW = copyhelper(n->SW);
        nod->SE = copyhelper(n->SE);
        return nod;

}






