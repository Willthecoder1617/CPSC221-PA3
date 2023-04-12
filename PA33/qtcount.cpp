#include "qtcount.h"

bool qtcount::prunable(Node* node, const int tol) const {
    /* Your code here */
    bool prunableNW;  
    bool prunableNE;    
    bool prunableSW;    
    bool prunableSE;    
    stats 
    // int count = 0;
    // if (node->NW != nullptr){
    //      prunableNW = prunable(node->NW,tol);
    //     count++;
    // }

    //  if (node->NE != nullptr){
    //     prunableNE = prunable(node->NE,tol);
    //     count++;
    //  }
    
    //  if (node->SW != nullptr){
    //     prunableSW = prunable(node->SW,tol);
    //     count++;

    // } 
    
    // if (node->SE != nullptr){
    //     prunableSE = prunable(node->SE,tol);
    //     count++;

    // }
    // if (count == 0){
    //     stat s = stat()
    // }

    return false;
}
//helper
bool qtcount::prunableHelper(Node* root, Node* curr, const int tol){
    if (curr->NW == nullptr && curr->NE == nullptr && curr->SW == nullptr && curr->SE == nullptr){
        
        ()
    }

}
