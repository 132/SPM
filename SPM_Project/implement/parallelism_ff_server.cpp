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
    
    //std::cout<<"name file: "<<fileName<<std::endl;
    int pow = atoi(argv[3]);
    if(argc != pow + 5){
        std::cout<<"Error: not correct the number of Prameters"<<std::endl;
        return 1;
    }
    double * listPara = new double [pow+1];
    for(int i=0;i<pow+1;i++)
        listPara[i] = atof(argv[i+3]);
    
    //std::cout<<"number of argument: "<<argc<<std::endl;
    
// chec is it enough parameters
    
    
    //std::string fileName = "../input/Input.txt";
    //std::string outFile = "../input/Output.txt";
    std::ofstream ofs;
    ofs.open("../input/Output.txt", std::ofstream::out | std::ofstream::trunc);
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
    
    // main for pipe + farm
    
    // runing pipe
    //firstStage _1;
    //secondStage _2;
    //thidrdStage _3;
    
    //ff_Pipe <> pipe(_1,_2,_3);
    //if(pipe.run_and_wait_end() < 0) error("running pipe");
    
    // farm
    
    // int nworkers = atoi(argv[1]);
    // std::vector<ff_node *> workers;
    // for (int i -> workers)
    //      workers.push_back(new Worker)
    // ff_farm <> myFarm(Workers);
    // if (myFarm.run_and_wait_end() < 0) error("running myFarm");

    //finalStage finalS;
    /////////////////////////////
    //int nworkers = atoi(argv[pow+3]);
 /*   
  * std::ifstream streamInterval;
    
    streamInterval.open("../input/Input.txt");
    
    int a, b;
    streamInterval >> a >> b;
    std::cout<<"From input: "<<a << " "<<b<<std::endl;

    for(int i=0;i<pow+1;i++)
        std::cout<<listPara[i]<<std::endl;

    // random a number
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

    std::cout << dist6(rng) << std::endl;

    
    std::vector<ff_node *> listWorkers;
    for(int i=0;i < nworkers; i++);
        listWorkers.push_back(new worker_farm);
    //ff_Farm<double> farm(std::move(listWorkers), true);
    
    ff_farm <> intervalFarm(listWorkers);
    
    //ff_Pipe <> pipe(randomS, intervalFarm);//, finalS);
*/
