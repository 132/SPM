#include <iostream>
#include <fstream>
#include <ff/farm.hpp>
#include <ff/pipeline.hpp>
#include <string.h>
#include <random>


#include <vector>

#include <chrono>
#include <mutex>
#include <atomic>

#include "Montecarlo.h"
#include "stage.h"
#include "interval_number.h"
#include "function.h"
using namespace Montecarlo;
std::mutex m;

int main(int argc, char * argv[]) {
// take the arguments from the command line
    
    int nworkers = atoi(argv[1])-5;
// take parameters and power of given function
    std::string fileName = argv[2];
    
    int pow = atoi(argv[3]);
    if(argc != pow + 5){
        std::cout<<"Error: not correct the number of Prameters"<<std::endl;
        return 1;
    }
    double * listPara = new double [pow+1];
    for(int i=0;i<pow+1;i++){
        listPara[i] = atof(argv[i+4]);
//std::cout<<listPara[i]<< " ";
}

    std::ofstream ofs;
    ofs.open("Output_ff.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    
    //std::cout<<"############################- Start stages -#########################################"<<std::endl;
    func givenFunc(pow, listPara);
    
    auto start = std::chrono::system_clock::now();
    readStream readS(fileName, givenFunc);
    ff_node_F<interval_number> randomN(randomNumber);
    ff_node_F<interval_number> randomListN(randomListNumber);
    //ff_node_F<interval_number> calMontecarlo(calculateMonte);
    
    writer_lastStage write_last_stage;
    
    std::vector<ff_node *> listWorkers;
    for(int i=0;i < nworkers; i++);
        listWorkers.push_back(new worker_farm);
    
    ff_farm <> intervalFarm(listWorkers);
    intervalFarm.remove_collector();
    
    ff_Pipe<> pipe(readS, randomN, randomListN, intervalFarm, write_last_stage);
    
    
    if(pipe.run_and_wait_end() < 0) error("running Pipe");
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    
    //std::cout<<"Time of FF: "<<elapsed_seconds.count()<<std::endl;
    std::cout<<"Workers: "<< nworkers << " PowerOfFunc: " << pow << " TimeFF: " << elapsed_seconds.count() <<std::endl;
    delete listPara;

    return 0;
}
