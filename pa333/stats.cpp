
#include "stats.h"
#include <cmath>
#include <utility>
#include <vector>
#include <iostream>

using namespace cs221util;
stats::stats(PNG& im) {
    // std::cout<<"STATS CALLED"<<std::endl;
    // Initialize the private vectors so that, for each color, entry
    // (x,y) is the cumulative sum of the the color values in the rectangle from (0,0)
    // to (x,y). Similarly, the sumSq vectors are the cumulative
    // sum of squares in the rectangle from (0,0) to (x,y).

    int width = im.width();
    int height = im.height();

    // Resize
    sumRed.resize(width, vector<long>(height));
    sumGreen.resize(width, vector<long>(height));
    sumBlue.resize(width, vector<long>(height));
    sumsqRed.resize(width, vector<long>(height));
    sumsqGreen.resize(width, vector<long>(height));
    sumsqBlue.resize(width, vector<long>(height));

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            RGBAPixel* p = im.getPixel(x, y);

            sumRed[x][y] = p->r;
            sumGreen[x][y] = p->g;
            sumBlue[x][y] = p->b;
            sumsqRed[x][y] = pow(p->r, 2);
            sumsqGreen[x][y] = pow(p->g, 2);
            sumsqBlue[x][y] = pow(p->b, 2);

            if (x > 0) {
                sumRed[x][y] += sumRed[x - 1][y];
                sumGreen[x][y] += sumGreen[x - 1][y];
                sumBlue[x][y] += sumBlue[x - 1][y];
                sumsqRed[x][y] += sumsqRed[x - 1][y];
                sumsqGreen[x][y] += sumsqGreen[x - 1][y];
                sumsqBlue[x][y] += sumsqBlue[x - 1][y];
            }

            if (y > 0) {
                sumRed[x][y] += sumRed[x][y - 1];
                sumGreen[x][y] += sumGreen[x][y - 1];
                sumBlue[x][y] += sumBlue[x][y - 1];
                sumsqRed[x][y] += sumsqRed[x][y - 1];
                sumsqGreen[x][y] += sumsqGreen[x][y - 1];
                sumsqBlue[x][y] += sumsqBlue[x][y - 1];
            }

            if (x > 0 && y > 0) {
                sumRed[x][y] -= sumRed[x - 1][y - 1];
                sumGreen[x][y] -= sumGreen[x - 1][y - 1];
                sumBlue[x][y] -= sumBlue[x - 1][y - 1];
                sumsqRed[x][y] -= sumsqRed[x - 1][y - 1];
                sumsqGreen[x][y] -= sumsqGreen[x - 1][y - 1];
                sumsqBlue[x][y] -= sumsqBlue[x - 1][y - 1];
            }
        }
    }
}




 
long stats::getSumSq(char channel, pair<int, int> ul, int dim) {

    /* Your code here!! */
     if (channel =='r') {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqRed[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumsqRed[ul.first + pow(2,dim) - 1][pow(2,dim) - 1 + ul.second] -
            sumsqRed[ul.first + pow(2,dim) - 1][ul.second - 1];
        } else if (ul.second == 0) {

            return sumsqRed[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumsqRed[ul.first - 1][pow(2,dim) - 1 + ul.second];
        } else {
            return sumsqRed[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumsqRed[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumsqRed[pow(2,dim) - 1 + ul.first][ul.second - 1] +
            sumsqRed[ul.first -1][ul.second -1];
        }
    } else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqGreen[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumsqGreen[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumGreen[pow(2,dim) - 1 + ul.first][ul.second - 1];
        } else if (ul.second == 0) {
            return sumsqGreen[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumsqGreen[ul.first - 1][pow(2,dim) - 1 + ul.second];
        } else {
            return sumsqGreen[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumsqGreen[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumsqGreen[pow(2,dim) - 1 + ul.first][ul.second - 1] +
            sumsqGreen[ul.first - 1][ul.second - 1];
        }
        
    }  else if (channel == 'b') {
            if (ul.first == 0 && ul.second == 0) {
            return sumsqBlue[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumsqBlue[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumsqBlue[pow(2,dim) - 1 + ul.first][ul.second - 1];
        } else if (ul.second == 0) {
            return sumsqBlue[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumsqBlue[ul.first - 1][pow(2,dim) - 1 + ul.second];
        } else {
            return sumsqBlue[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumsqBlue[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumsqBlue[pow(2,dim) - 1 + ul.first][ul.second - 1] +
            sumsqBlue[ul.first - 1][ul.second - 1];
        }
        
    }
    return 0; 
}


long stats::rectArea(int dim) {
    return pow(2, dim) * pow(2, dim); //may need to replace
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int dim) {
     long summatationsq = getSumSq('r', ul, dim) + getSumSq('g', ul, dim) + getSumSq('b', ul, dim);
     int area = rectArea(dim);
    long sumsqaured = pow(getSum('r', ul, dim), 2) / area + pow(getSum('g', ul, dim), 2) / area + pow(getSum('b', ul, dim), 2) / area;
    

    return summatationsq - sumsqaured;

    

    // if (dim == 0) return 0;

    // long area = rectArea(dim);
    // long sumR = getSum('r', ul, dim);
    // long sumG = getSum('g', ul, dim);
    // long sumB = getSum('b', ul, dim);

    // long sumSqR = getSumSq('r', ul, dim);
    // long sumSqG = getSumSq('g', ul, dim);
    // long sumSqB = getSumSq('b', ul, dim);

    // double varR = (double)sumSqR - (double)pow(sumR, 2)/area;
    // double varG = (double)sumSqG - (double)pow(sumG, 2)/area;
    // double varB = (double)sumSqB - (double)pow(sumB, 2)/area;

    // return varR + varG + varB;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int dim) {
    
    long area = rectArea(dim);
    long avgR = getSum('r', ul, dim) / area;
    
    long avgG = getSum('g', ul, dim) / area;
    long avgB = getSum('b', ul, dim) / area;
    
    return RGBAPixel(avgR, avgG, avgB);
}




long stats::getSum(char channel, pair<int, int> ul, int dim) {

    /* Your code here!! */
     if (channel =='r') {
        if (ul.first == 0 && ul.second == 0) {
            return sumRed[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumRed[ul.first + pow(2,dim) - 1][pow(2,dim) - 1 + ul.second] -
            sumRed[ul.first + pow(2,dim) - 1][ul.second - 1];
        } else if (ul.second == 0) {

            return sumRed[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumRed[ul.first - 1][pow(2,dim) - 1 + ul.second];
        } else {
            return sumRed[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumRed[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumRed[pow(2,dim) - 1 + ul.first][ul.second - 1] +
            sumRed[ul.first -1][ul.second -1];
        }
    } else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            return sumGreen[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumGreen[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumGreen[pow(2,dim) - 1 + ul.first][ul.second - 1];
        } else if (ul.second == 0) {
            return sumGreen[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumGreen[ul.first - 1][pow(2,dim) - 1 + ul.second];
        } else {
            return sumGreen[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumGreen[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumGreen[pow(2,dim) - 1 + ul.first][ul.second - 1] +
            sumGreen[ul.first - 1][ul.second - 1];
        }
        
    }  else if (channel == 'b') {
            if (ul.first == 0 && ul.second == 0) {
            return sumBlue[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumBlue[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumBlue[pow(2,dim) - 1 + ul.first][ul.second - 1];
        } else if (ul.second == 0) {
            return sumBlue[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1 + ul.second] -
            sumBlue[ul.first - 1][pow(2,dim) - 1 + ul.second];
        } else {
            return sumBlue[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumBlue[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumBlue[pow(2,dim) - 1 + ul.first][ul.second - 1] +
            sumBlue[ul.first - 1][ul.second - 1];
        }
        
    }
    return 0; 
}




