#pragma once
#include "Montecarlo.h"
#include "function.h"
#include <chrono>
namespace Montecarlo{
class interval_number{
public:
    int id;
    int a;
    int b;
    int N_number;
    int * listNumber = new int [N_number];
    func mainFunc;
    double monteNumber;


//	std::chrono::duration<double> timeExec; 
    
    interval_number(int iid, int aa, int bb, func f);
    void setN(int N);
    void setListNumber(int * ln);
    
    void calMonteNumber();
    double getMonteNumber();
    
};
}
 
