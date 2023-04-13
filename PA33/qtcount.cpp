#include "qtcount.h"

bool qtcount::prunable(Node* node, const int tol) const {
    /* Your code here */
        
    
    return prunableHelper(node,node,tol);

}
//helper
bool qtcount::prunableHelper(Node* root, Node* curr, const int tol) const{
    
    if (curr->NW == nullptr && curr->NE == nullptr && curr->SW == nullptr && curr->SE == nullptr){
       int dist = pow((root->avg.r - curr->avg.r),2) +pow((root->avg.g - curr->avg.g),2) + pow((root->avg.b - curr->avg.b),2);
       
       if (abs(dist) <= tol ){
        return true;
       }else{
        return false;
       }
    }else {
       
       bool a = prunableHelper(root, curr->NW, tol);

       bool b = prunableHelper(root, curr->NE, tol);
       bool c = prunableHelper(root, curr->SW, tol);
       bool d = prunableHelper(root, curr->SE, tol);
      
        if (a && b && c && d){
            return true;
        }else{
            return false;
        }

      
    }
}
