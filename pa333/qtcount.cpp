#include "qtcount.h"

#include "qtcount.h"

bool qtcount::prunable(Node* node, const int tol) const {

    /* Your code here */
            if (node == nullptr) {
        return false;
    }
    
    return prunableHelper(node,node,tol);

}
//helper
bool qtcount::prunableHelper(Node* node, Node* curr, const int tol) const{
    
    if (curr->NW == nullptr && curr->NE == nullptr && curr->SW == nullptr && curr->SE == nullptr) {
        if (curr && pow((curr->avg.r - node->avg.r), 2) + pow((curr->avg.g - node->avg.g), 2) +
        pow((curr->avg.b - node->avg.b), 2) > tol) {
            return false;
        } else {
            return true;
        }

        
    } else {
        bool a = prunableHelper(node, curr->NW, tol);
        bool b = prunableHelper(node, curr->NE, tol);
        bool c = prunableHelper(node, curr->SW, tol);
        bool d = prunableHelper(node, curr->SE, tol);
      
        bool k = a && b && c && d;
        return k;



    }
       



        

}
