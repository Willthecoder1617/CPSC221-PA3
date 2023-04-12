
#include "stats.h"
#include <cmath>
#include <utility>
#include <vector>
#include <iostream>

using namespace cs221util;



stats::stats(PNG& im) {
    sumRed.resize(im.width());
    sumBlue.resize(im.width());
    sumGreen.resize(im.width());

    sumsqRed.resize(im.width());
    sumsqBlue.resize(im.width());
    sumsqGreen.resize(im.width());


    for (int x = 0; x < im.width(); x++) {
        
        sumRed[x].resize(im.height());
        sumBlue[x].resize(im.height());
        sumGreen[x].resize(im.height());

        sumsqRed[x].resize(im.height());
        sumsqBlue[x].resize(im.height());
        sumsqGreen[x].resize(im.height());


        for (int y = 0; y < im.height(); y++) {

            // very first iteratioj
            if (x == 0 && y == 0) {
                sumRed[x][y] = im.getPixel(0,0)->r;
                sumBlue[x][y] = im.getPixel(0,0)->b;
                sumGreen[x][y] = im.getPixel(0,0)->g;

                sumsqRed[x][y] = pow(im.getPixel(0,0)->r,2);
                sumsqBlue[x][y] = pow(im.getPixel(0,0)->b, 2);
                sumsqGreen[x][y] = pow(im.getPixel(0,0)->g, 2);

            }

             else if (x == 0) {
                sumRed[x][y] = sumRed[x][y-1] + im.getPixel(x,y)->r;
                sumBlue[x][y] = sumBlue[x][y-1] + im.getPixel(x,y)->b;
                sumGreen[x][y] = sumGreen[x][y-1] + im.getPixel(x,y)->g;

                sumsqRed[x][y] = sumsqRed[x][y-1] + pow(im.getPixel(x,y)->r, 2);
                sumsqBlue[x][y] = sumsqBlue[x][y-1] + pow(im.getPixel(x,y)->b, 2);
                sumsqGreen[x][y] = sumsqGreen[x][y-1] + pow(im.getPixel(x,y)->g, 2);
            }

             else if (y == 0) {
                sumRed[x][y] = sumRed[x-1][y] + im.getPixel(x,y)->r;
                sumBlue[x][y] = sumBlue[x-1][y] + im.getPixel(x,y)->b;
                sumGreen[x][y] = sumGreen[x-1][y] + im.getPixel(x,y)->g;

                sumsqRed[x][y] = sumsqRed[x-1][y] + pow(im.getPixel(x,y)->r, 2);
                sumsqBlue[x][y] = sumsqBlue[x-1][y] + pow(im.getPixel(x,y)->b, 2);
                sumsqGreen[x][y] = sumsqGreen[x-1][y] + pow(im.getPixel(x,y)->g, 2);

            } else {
                sumRed[x][y] = sumRed[x][y-1] + sumRed[x-1][y] + im.getPixel(x,y)->r - sumRed[x-1][y-1];
                sumGreen[x][y] = sumGreen[x][y-1] + sumGreen[x-1][y] + im.getPixel(x,y)->g - sumGreen[x-1][y-1];
                sumBlue[x][y] = sumBlue[x][y-1] + sumBlue[x-1][y] + im.getPixel(x,y)->b - sumBlue[x-1][y-1];

                sumsqRed[x][y] = sumsqRed[x][y-1] + sumsqRed[x-1][y] + pow(im.getPixel(x,y)->r, 2) - sumsqRed[x-1][y-1];
                sumsqGreen[x][y] = sumsqGreen[x][y-1] + sumsqGreen[x-1][y] + pow(im.getPixel(x,y)->g, 2) - sumsqGreen[x-1][y-1];
                sumsqBlue[x][y] = sumsqBlue[x][y-1] + sumsqBlue[x-1][y] + pow(im.getPixel(x,y)->b, 2) - sumsqBlue[x-1][y-1];

            }

            // long sumr = 0;
            // long sumb = 0;
            // long sumg = 0;

            // long sumsqr = 0;
            // long sumsqb = 0;
            // long sumsqg = 0;

      
            // //cout << x << endl;
            // for (int i = 0; i <= x; i++) {
            //     //cout << "4th loop" << endl;
            //     for (int k = 0; k <= y; k++) {
            //         RGBAPixel* p = im.getPixel(i,k);
            //         sumr = sumr + p->r;
            //         sumb = sumb + p->b;
            //         sumg = sumg + p->g;

            //         sumsqr = sumsqr + pow(p->r, 2);
            //         sumsqb = sumsqb + pow(p->b, 2);
            //         sumsqg = sumsqg + pow(p->g, 2);
            //     }
            //     //cout << "exit 4th" << endl;

            // }
            // //cout << "exit 3rd loop" << endl;

            // sumRed[x][y] = sumr;
            // sumBlue[x][y] = sumb;
            // sumGreen[x][y] = sumg;

            // sumsqRed[x][y] = sumsqr;
            // sumsqBlue[x][y] = sumsqb;
            // sumsqGreen[x][y] = sumsqg;


        }
       
    }
   

}

// sum over
long stats::getSum(char channel, pair<int, int> ul, int dim) {

    /* Your code here!! */
     if (channel =='r') {
        if (ul.first == 0 && ul.second == 0) {
            return sumRed[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumRed[pow(2,dim) - 1][pow(2,dim) - 1 + ul.second] -
            sumRed[pow(2,dim) - 1][ul.second - 1];
        } else if (ul.second == 0) {

            return sumRed[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1] -
            sumRed[ul.first - 1][pow(2,dim) - 1];
        } else {
            return sumRed[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumRed[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumRed[pow(2,dim) - 1 + ul.first][ul.second - 1];
        }
    } else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            return sumGreen[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumGreen[pow(2,dim) - 1][pow(2,dim) - 1 + ul.second] -
            sumGreen[pow(2,dim) - 1][ul.second - 1];
        } else if (ul.second == 0) {
            return sumGreen[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1] -
            sumGreen[ul.first - 1][pow(2,dim) - 1];
        } else {
            return sumGreen[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumGreen[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumGreen[pow(2,dim) - 1 + ul.first][ul.second - 1];
        }
        
    }  else if (channel == 'b') {
            if (ul.first == 0 && ul.second == 0) {
            return sumBlue[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumBlue[pow(2,dim) - 1][pow(2,dim) - 1 + ul.second] -
            sumBlue[pow(2,dim) - 1][ul.second - 1];
        } else if (ul.second == 0) {
            return sumBlue[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1] -
            sumBlue[ul.first - 1][pow(2,dim) - 1];
        } else {
            return sumBlue[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumBlue[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumBlue[pow(2,dim) - 1 + ul.first][ul.second - 1];
        }
        
    }
    return 0; 
}



long stats::getSumSq(char channel, pair<int, int> ul, int dim) {
         if (channel =='r') {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqRed[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumsqRed[pow(2,dim) - 1][pow(2,dim) - 1 + ul.second] -
            sumsqRed[pow(2,dim) - 1][ul.second - 1];
        } else if (ul.second == 0) {
            return sumsqRed[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1] -
            sumsqRed[ul.first - 1][pow(2,dim) - 1];
        } else {
             return sumsqRed[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumsqRed[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumsqRed[pow(2,dim) - 1 + ul.first][ul.second - 1];
        }
    } else if (channel == 'g') {
        if (ul.first == 0 && ul.second == 0) {
            return sumsqGreen[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumsqGreen[pow(2,dim) - 1][pow(2,dim) - 1 + ul.second] -
            sumsqGreen[pow(2,dim) - 1][ul.second - 1];
        } else if (ul.second == 0) {
            return sumsqGreen[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1] -
            sumsqGreen[ul.first - 1][pow(2,dim) - 1];
        } else {
            return
            sumsqGreen[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumsqGreen[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumsqGreen[pow(2,dim) - 1 + ul.first][ul.second - 1];
        }
        
    }  else if (channel == 'b') {
            if (ul.first == 0 && ul.second == 0) {
            return sumsqBlue[pow(2,dim) - 1][pow(2,dim) - 1];
        } else if (ul.first == 0) {
            return sumsqBlue[pow(2,dim) - 1][pow(2,dim) - 1 + ul.second] -
            sumsqBlue[pow(2,dim) - 1][ul.second - 1];
        } else if (ul.second == 0) {
            return
            sumsqBlue[pow(2,dim) - 1 + ul.first][pow(2,dim) - 1] -
            sumsqBlue[ul.first - 1][pow(2,dim) - 1];
        } else {
            return
            sumsqBlue[ul.first + pow(2,dim) - 1][ul.second + pow(2,dim) -1] -
            sumsqBlue[ul.first -1][pow(2,dim) - 1 + ul.second] -
            sumsqBlue[pow(2,dim) - 1 + ul.first][ul.second - 1];
        }
        
    }

    return 0; 
}

long stats::rectArea(int dim) {
    /* Your code here!! */
    int ans = pow(2, dim) * pow(2,dim);
    
    return ans;


    // assuming that its log 2

}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int dim) {
    /* Your code here!! */
    long summatationsq = getSumSq('r', ul, dim) + getSumSq('g', ul, dim) + getSumSq('b', ul, dim);
    long sumsqaured = pow(getSum('r', ul, dim), 2) + pow(getSum('g', ul, dim), 2) + pow(getSum('b', ul, dim), 2);
    long area = rectArea(dim);

    return summatationsq - (sumsqaured / area);
}

RGBAPixel stats::getAvg(pair<int, int> ul, int dim) {
    /* Your code here!! */
    long r = getSum('r', ul, dim);
    long g = getSum('g', ul, dim);
    long b = getSum('b', ul, dim);

    long total = r + g + b;

    RGBAPixel pixel = RGBAPixel();

    pixel.r = r / rectArea(dim);
    pixel.b = b / rectArea(dim);
    pixel.g = g / rectArea(dim);

    return pixel;
}
