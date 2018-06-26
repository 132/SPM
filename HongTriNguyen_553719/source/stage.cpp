#include <ff/pipeline.hpp>
#include <ff/farm.hpp>

#include <iostream>
#include <random>
#include <string.h>
#include <fstream>
#include <queue> 
#include <ctime>

#include "stage.h"
#include "Montecarlo.h"
#include "function.h"

using namespace ff;
namespace Montecarlo{
// first stage read a stream and send an interval to next stage    
    readStream::readStream(std::string f, func ffunc): mainFunc(ffunc){
        readStreamFile.open(f);
        //mainFunc = mainF;
    }
    
    interval_number * readStream::svc(interval_number *){
        int a, b;
        int id=1;
        while (readStreamFile >> a >> b){
            if (a==b)
		b = a * 100;

//		std::cout<<"a and b: "<< a << ", "<< b<< std::endl;
            ff_send_out(new interval_number(id ,a, b, mainFunc));
            id++;
        }
        return EOS;
    }
 // second stage ff_node_F<interval_number>
    interval_number * randomNumber(interval_number *intervalN, ff_node *const){
        /*
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(intervalN->b-intervalN->a,5*(intervalN->b-intervalN->a)); // distribution in range [1, 6]

        //std::cout << "random N: "<<dist6(rng) << " of "<<intervalN->a<< " "<<intervalN->b<<std::endl;
        intervalN->setN(dist6(rng));
        return intervalN;
        */
//        int seed = time(NULL);
        srand(intervalN->id);
        intervalN->setN(rand() % (intervalN->b-intervalN->a) + (intervalN->b-intervalN->a));
        return intervalN;
    }
// third stage ff_node<interval_number
    interval_number * randomListNumber(interval_number *intervalN, ff_node *const){
        int * temp = new int [intervalN->N_number];
//        int seed = time(NULL);
//        srand(seed);
        for(int i=0; i<intervalN->N_number; i++){
            /*
            std::mt19937 rng;
            rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(intervalN->a,intervalN->b);
            //std::cout << "random in N: "<<dist6(rng)<<std::endl;
            temp[i] = dist6(rng);
            */
	    srand(intervalN->id+i);
            temp[i] = rand() % intervalN->b + intervalN->a;
        }
        //std::cout<<"complete .. "<<std::endl;
        intervalN->setListNumber(temp);
	delete temp;
        return intervalN;
    }

// main Task
//    interval_number * calculateMonte(interval_number * intervalN, ff_node *const){
//        intervalN->calMonteNumber();
//        return intervalN;
//    }
    
    worker_farm::worker_farm(){
    }
    
    interval_number * worker_farm::svc(interval_number * intervalN){
//	std::cout<<"cal: "<<intervalN->id<<std::endl;
        intervalN->calMonteNumber();
        return intervalN;
    }
    
    interval_number * write_stage(interval_number * intervalN, ff_node * const){
        std::ofstream outStream;
        std::queue<interval_number* > tempQ;
        int position = 1;
//        outStream.open("Output.txt", std::ios_base::app);
	 outStream.open("Output_ff.txt", std::ios_base::app);

        outStream << intervalN->monteNumber<<" ";
        delete intervalN;
        return (interval_number *)GO_ON;
    }
     
    interval_number * writer_lastStage::svc(interval_number * intervalN){
        return write_stage(intervalN, this);
    }

}
