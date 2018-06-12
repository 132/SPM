#include "Montecarlo.h"
#include "interval_number.h"
#include <iostream>

namespace Montecarlo{

    interval_number::interval_number(int iid, int aa, int bb, func ff): id(iid), a(aa), b(bb), mainFunc(ff){}
    
    void interval_number::setN(int N){
        N_number = N;
    }
    void interval_number::setListNumber(int * ln){
        listNumber = ln;
    }
    void interval_number::calMonteNumber(){
        double total= 0;
        //std::cout<<"called a calMonteNumber: "<<N_number<<std::endl;
        for(int i=0;i<N_number;i++){
            total += mainFunc(listNumber[i])*(b-a);
            //std::cout<<"total: "<<total<<" from "<<listNumber[i]<<" "<< mainFunc(listNumber[i])<<" * "<<b-a<<std::endl;
        }
        monteNumber = total/N_number;
        //std::cout<<"monteNumber: "<<monteNumber<<std::endl;
    }
    double interval_number::getMonteNumber(){
        return monteNumber;
    }

}
 
