#pragma once
#include <Montecarlo.h>

// ax^2 + bx + c
namespace Montecarlo{
class func{
public:
    int power;
    double * listPara;
    func(int p, double *lp);
    double cal(int a, int b, int n, int list_n);
    // operator in class functor
    double operator()(int x); 
};
}
//int power;
//int[] listParamerter;
//func(int p, int lp:)
//cal(int a, int b);


