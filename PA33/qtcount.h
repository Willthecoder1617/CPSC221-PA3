#ifndef _QTCOUNT_H_
#define _QTCOUNT_H_

#include <cmath>
#include <utility>

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "quadtree.h"
#include "stats.h"

using namespace std;
using namespace cs221util;

class qtcount : public quadtree {
public:
    qtcount(PNG& im) : quadtree(im) {}

    bool prunableHelper(Node* root, Node* curr, const int tol) const;

private:
    bool prunable(Node* node, const int tol) const;
};

#endif
