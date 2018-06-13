#include "function.h"
#include <math.h>
#include <iostream>

namespace Montecarlo {

func::func(int p, double * lp)
        : power(p), listPara(lp)
{}

double func::operator()(int x) {
    double out = 0;
    for(int i=power;i>=0;i--){
//	std::cout<< i << " "<< std::endl;
        out += pow(x,i) * listPara[abs(i-power)];
//        std::cout<<" x: "<<x<<" i: "<<i<<" pow(x,i): "<<pow(x,i)<<" [abs(i-power)]: "<<abs(i-power)<<" listPara[abs(i-power)]: "<<listPara[abs(i-power)]<<std::endl;
    }
    return out;
}
}
