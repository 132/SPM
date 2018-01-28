#include <iostream>
#include <fstream>
#include <ff/farm.hpp>
#include <ff/pipeline.hpp>
#include <string.h>
#include <random>
#include <Montecarlo.h>
#include <function.h>
#include <vector>
#include <stage.h>

using namespace Montecarlo;

int main(int argc, char * argv[]) {
// take the arguments from the command line
    int pow = atoi(argv[1]);
    double * listPara = new double [pow+1];
    for(int i=0;i<pow+1;i++)
        listPara[i] = atof(argv[i+2]);
   
    if(argc-3 != pow)
        std::cout<<"Error: Lack of Parameter"<<std::endl;
    
    func givenFunc(pow, listPara);
    std::ifstream streamInterval;
    streamInterval.open("../input/Input.txt");
    int a, b;
    streamInterval >> a >> b;
    std::cout<<"From input: "<<a << " "<<b<<std::endl;

    
    while (streamInterval >> a >> b){
        std::cout<<"From input: "<<a << " "<<b<<std::endl;
        // first stage in pipeline
        
        // second stage in pipeline
        
        // third stage is farm with n worker
    }

    for(int i=0;i<pow+1;i++)
        std::cout<<listPara[i]<<std::endl;
    //if(argc < )
    //    std::cout<<"Error: pow 
    delete listPara;
    
    // random a number
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

    std::cout << dist6(rng) << std::endl;
    
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
    
    initStage initS();
    randomStage randomS;
    //finalStage finalS;
    /////////////////////////////
    //int nworkers = atoi(argv[pow+3]);
    int nworkers = 10;
    std::vector<ff_node *> listWorkers;
    for(int i=0;i < nworkers; i++);
        listWorkers.push_back(new worker_farm);
    //ff_Farm<double> farm(std::move(listWorkers), true);
    
    ff_farm <> intervalFarm(listWorkers);
    
    ff_Pipe <> pipe(randomS, intervalFarm);//, finalS);
    
    if(pipe.run_and_wait_end() < 0) error("running Pipe");
    return 0;
}
