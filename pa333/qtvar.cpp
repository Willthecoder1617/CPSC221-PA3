
#include "qtvar.h"

bool qtvar::prunable(Node* node, const int tol) const {
    /* Your code here! */
    if (node == nullptr) {
        return false;
    }
    if (node->var <= tol){
        return true;
    }
    return false;
}

