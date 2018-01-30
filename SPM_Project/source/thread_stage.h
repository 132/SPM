#pragma once

#include <Montecarlo.h>
#include <interval_number.h>
#include <string.h>
#include <fstream>
#include <function.h>

namespace Montecarlo{

    struct stage{
    };
    
    struct readStream: public stage{
        ifstream inputStream;
        int nworker;
        
        readStream(ifstream input, int nw);
        void sendInputStream();
    };
    
    struct randomN: pubic stage{
      interval_number intervalN;
      
      randomN(interval_number N);
      double randomNumber();
    };
    
    struct randomListN: public stage{
      
      double randomNumber(int a, int b);
    };
    
    struct split2Farm: public stage{
        int nworker;
        split2Farm(int n);
        
    };
    
}

