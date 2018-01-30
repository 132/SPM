#include <ff/pipeline.hpp>
#include <ff/farm.hpp>
#include <stage.h>
#include <Montecarlo.h>
#include <iostream>
#include <random>
#include <string.h>
#include <fstream>
#include <function.h>

using namespace ff;
namespace Montecarlo{
// first stage read a stream and send an interval to next stage    
    readStream::readStream(std::string f, func ffunc): mainFunc(ffunc){
        readStreamFile.open(f);
        //mainFunc = mainF;
    }
    
    
    interval_number * readStream::svc(interval_number *){
        int a, b;
        while (readStreamFile >> a >> b){
            ff_send_out(new interval_number(a, b, mainFunc));
        }
        return EOS;
    }
 // second stage ff_node_F<interval_number>
    interval_number * randomNumber(interval_number *intervalN, ff_node *const){
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(intervalN->b-intervalN->a,5*(intervalN->b-intervalN->a)); // distribution in range [1, 6]

        //std::cout << "random N: "<<dist6(rng) << " of "<<intervalN->a<< " "<<intervalN->b<<std::endl;
        intervalN->setN(dist6(rng));
        return intervalN;
    }
// third stage ff_node<interval_number
    interval_number * randomListNumber(interval_number *intervalN, ff_node *const){
        int * temp = new int [intervalN->N_number];
        
        for(int i=0; i<intervalN->N_number; i++){
            std::mt19937 rng;
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(intervalN->a,intervalN->b);
            //std::cout << "random in N: "<<dist6(rng)<<std::endl;
            temp[i] = dist6(rng);
        }
        //std::cout<<"complete .. "<<std::endl;
        intervalN->setListNumber(temp);
        return intervalN;
    }

// main Task
    interval_number * calculateMonte(interval_number * intervalN, ff_node *const){
        intervalN->calMonteNumber();
        
        return intervalN;
    }
    

    worker_farm::worker_farm(){
        //std::cout<<"worker from a Farm"<<std::endl;
    }
    
    interval_number * worker_farm::svc(interval_number * intervalN){
        intervalN->calMonteNumber();
        return intervalN;
    }
}
/*    
// summary result
    interval_number * summaryResult::svc(interval_number * intervalN){
        return intervalN;
    }

// Go to FARM
    interval_number * emittor_farm::svc(interval_number * intervalN){ // emittor of farm stage
        for(int i=0;i<intervalN->N_number;i++){
            ff_send_out(new worker_farm);
        }
        return EOS;
    }
    
 //   void * worker_farm::svc(void * task){    // worker of farm stage
       // return 0;
 //   }

    
    interval_number * collector_farm::svc(interval_number *intervalN){   // collector of farm stage
        return 0;
    }
}

    void finalStage::svc_end(){
        std::cout<<"Complete the Cycle of stages."<<std::endl;
    }
    void * initStage::svc(void * task){
        std::cout<<"Hello, starting the Cycle of stages project! Are you ready?"<<std::endl;
        //return 0;
    }
*/
