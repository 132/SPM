#pragma once
#include "Montecarlo.h"

// ax^2 + bx + c
namespace Montecarlo{
class func{
public:
    int power;
    double * listPara;
    func(int p, double *lp);
    // operator in class functor
    double operator()(int x); 
};
}


