#include <Montecarlo.h>
#include <interval_number.h>
#include <string.h>
#include <fstream>
#include <thread>
#include <function.h>
#include <thread_stage.h>

namespace Montecarlo{
    readStream::readStream(ifstream input, int nw):inputStream(input), nworker(nw){
        std::thread(sendInputStream);
    }
    
    void readStream::sendInputStream(){
        int a,b;
        while(inputStream >> a >> b){
            
        }
    }
    
    randomN(interval_number N):intervalN(N){}
    
    
}
