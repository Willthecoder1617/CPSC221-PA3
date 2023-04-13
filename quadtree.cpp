
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

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
    /* Your code here! */
    
    int dim = 0;
    int h = imIn.height();
    while (h > 1){
        dim++;
        h = h/2;
    }
    stats s = stats(imIn);

    pair<int,int> ul1 = pair(0,0);
    pair<int,int> ul2 = pair(imIn.height()/2,0);

    pair<int,int> ul3 = pair(0,imIn.height()/2 );
    pair<int,int> ul4 = pair(imIn.height()/2,imIn.height()/2);



    Node* qTree = new Node(ul1,dim,s.getAvg(ul1,dim), s.getVar(ul1,dim));
    if (root != nullptr){
        clear();
    }
    qTree->NW = buildTree(s,ul1,dim-1);
    qTree->NE = buildTree(s,ul2,dim-1);
    qTree->SW = buildTree(s,ul3,dim-1);
    qTree->SE = buildTree(s,ul4,dim-1);


    root = qTree;

}

quadtree::Node* quadtree::buildTree(stats& s, pair<int, int> ul, int dim) {
    /* Your code here! */
    
    if (dim == 0){
        Node* qTree1 = new Node(ul,dim,s.getAvg(ul,dim), s.getVar(ul,dim));
 
        return qTree1;
    }else{
        Node* qTree2 = new Node(ul,dim,s.getAvg(ul,dim), s.getVar(ul,dim));
        pair<int,int> ul2 = pair((power(2,dim-1)+ul.first),ul.second);
        pair<int,int> ul3 = pair(ul.first,(power(2,dim-1)+ul.second));
        pair<int,int> ul4 = pair((power(2,dim-1)+ul.first),(power(2,dim-1)+ul.second));
        qTree2->NW = buildTree(s,ul,dim-1);
        qTree2->NE = buildTree(s,ul2,dim-1);
        qTree2->SW = buildTree(s,ul3,dim-1);
        qTree2->SE = buildTree(s,ul4,dim-1);
    }
    return nullptr;
}
// help function
int power(int base, int power){
    if (power == 0){
        return 1;
    }
    while(power > 1){
        base = base * base;
    }
    return base;
}

//helper 2
void quadtree::set(PNG& png, Node* node) const{
    stats s = stats(png);

    if (node->NW == nullptr && node->NE == nullptr && node->SW == nullptr && node->SE == nullptr){
        
        RGBAPixel px = RGBAPixel(s.getSum('r',node->upLeft,0),s.getSum('g',node->upLeft,0),s.getSum('b',node->upLeft,0));
        *png.getPixel(node->upLeft.first,node->upLeft.second) = px;
        
    }

}



PNG quadtree::render() const {
    /* Your code here! */
    int di =   root->dim;

    
    int wh =  power(2,di);

    PNG png1 = PNG(wh,wh);
    
    set(png1,root);    
    
    return png1;
}


int quadtree::idealPrune(const int leaves) const {
    /* Your code here! */
    return 0;
}

int quadtree::pruneSize(const int tol) const {
    /* Your code here! */
    int count = 0;
    if (prunable(root->NW,tol)){
        count += prunesizehelper(root->NW,tol);
    }

    if (prunable(root->NE,tol)){
        count += prunesizehelper(root->NE,tol);
    }

    if (prunable(root->SW,tol)){
        count += prunesizehelper(root->SW,tol);
    }

    if (prunable(root->SE,tol)){
        count += prunesizehelper(root->SE,tol);
    }
    return count;
}

int quadtree::prunesizehelper(Node* node,const int tol ) const{
    
    if (node->NW == nullptr && node->NE == nullptr && node->SW == nullptr && node->SE == nullptr)     {
       if (prunable(node,tol)){
        return 0;
       }else{
        return 1;
       }
    }  else {
        int a = prunesizehelper(node->NW,tol) ;
        int b = prunesizehelper(node->NE,tol) ;
        int c = prunesizehelper(node->SW,tol) ;
        int d = prunesizehelper(node->SE,tol) ;

        if (a+b+c+d == 0){
            return 1;
        }else{
            return a+b+c+d;
        }
        
    }
}


void quadtree::prune(const int tol) {
    /* Your code here! */
    
    if (!prunable(root->NW,tol)){
        prunehelper(root->NW,tol);
    }else{
        prunehelper2(root->NW);
        root->NW = nullptr;
    }


    if (!prunable(root->NE,tol)){
        prunehelper(root->NE,tol);
    }else{
        prunehelper2(root->NE);
        root->NE = nullptr;
    }

    if (!prunable(root->SW,tol)){
        prunehelper(root->SW,tol);
    }else{
        prunehelper2(root->SW);
        root->SW = nullptr;
    }

    if (!prunable(root->SE,tol)){
        prunehelper(root->SE,tol);
    }else{
        prunehelper2(root->SE);
        root->SE = nullptr;
    }
    
}

void quadtree::prunehelper(Node* node,const int tol ){
   
       if (prunable(node->NW,tol)){
        prunehelper2(node->NW);
        node->NW = nullptr;

       }

       if (!prunable(node->NE,tol)){
        prunehelper2(node->NE);
        node->NE = nullptr;

       }

       if (!prunable(node->SW,tol)){
        prunehelper2(node->SW);
        node->SW = nullptr;

       }

       if (!prunable(node->SE,tol)){
        prunehelper2(node->SE);
        node->SE = nullptr;

       }
    

 }

void quadtree::prunehelper2(Node* node ){
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
void quadtree::clearhelper(Node* root){
    if (root->NW != nullptr){
        clearhelper(root->NW);
        
    }

     if (root->NE != nullptr){
        clearhelper(root->NE);
    }
    
     if (root->SW != nullptr){
        clearhelper(root->SW);
    } 
    
    if (root->SE != nullptr){
        clearhelper(root->SE);
    }

    delete(root);
    root = nullptr;

}
void quadtree::copy(const quadtree& orig) {
    /* your code here */
    root = copyhelper(root);
}
//helper function 4

quadtree::Node* quadtree::copyhelper(Node* root){
    Node* nod = new Node(root->upLeft,root->dim, root->avg,root->var);
    if (root->NW != nullptr){
        nod->NW = copyhelper(root->NW);
        
    }

     if (root->NE != nullptr){
        nod->NE = copyhelper(root->NE);
    }
    
     if (root->SW != nullptr){
        nod->SW = copyhelper(root->SW);
    } 
    
    if (root->SE != nullptr){
        nod->SE = copyhelper(root->SE);
    }

    return nod;

}
