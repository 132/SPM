#include <iostream>
#include <fstream>
#include <string.h>
#include <random>
#include <ctime>
#include <chrono>
#include "function.h"
#include "interval_number.h"
#include "Montecarlo.h"
#include <chrono>

using namespace Montecarlo;

int main(int argc, char * argv[]) {
// take the arguments from the command line
    std::string fileName = argv[1];

std::vector<std::chrono::system_clock::time_point> timeline;

    int pow = atoi(argv[2]);
    double * listPara = new double [pow+1];
    for(int i=0;i<pow+1;i++){
        listPara[i] = atof(argv[i+3]);
//	std::cout<<listPara[i]<<std::endl;
	}
   
    if(argc != pow +4)
        std::cout<<"Error: Lack of Parameter"<<std::endl;
    
    func givenFunc(pow, listPara);

    int a, b;
//    streamInterval >> a >> b;
//    std::cout<<"From input: "<<a << " "<<b<<std::endl;

    std::ifstream streamInterval;
    streamInterval.open(fileName);

    std::ofstream ofs;
    ofs.open("Output_Seq.txt", std::ofstream::out | std::ofstream::trunc);
//    ofs.close();
 
    int id = 0;
	
    auto start = std::chrono::system_clock::now();
    while (streamInterval >> a >> b){
	if(a == b)	b = a * 100;
        interval_number * interval_temp = new interval_number(id,a,b,givenFunc);

        // first stage in pipeline
	int gap = interval_temp->b - interval_temp->a;

	srand(id);
	int randomN = rand()%gap + gap;
//	std::cout<< randomN <<std::endl;
	interval_temp->setN(randomN);
	
        // second stage in pipeline
//        int elemRandomNumber = new int 
	int * elemRandomNumber = new int [interval_temp->N_number];

	double total = 0;
	for(int i=0;i<randomN;i++){
		srand(id+i);
		elemRandomNumber[i] = rand()%b + a;
//		timeline.push_back(std::chrono::system_clock::now());
//		total+= givenFunc(elemRandomNumber)*gap;
	}
	interval_temp->setListNumber(elemRandomNumber);
        // third stage is farm with n worker
	timeline.push_back(std::chrono::system_clock::now());
	interval_temp->calMonteNumber();
	timeline.push_back(std::chrono::system_clock::now());

//	interval_temp->monteNumber = total/randomN;
	
//	std::cout<<"MonteNumber: "<<interval_temp->monteNumber<<std::endl;
	// write to a file
	ofs<<interval_temp->monteNumber<<" ";
	id++;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

	auto min = timeline.front();
	auto max = timeline.back();
	std::chrono::duration<double> duringFarm_ = max - min;

    std::cout<< duringFarm_.count() <<" PowerOfFunc: "<< pow <<" TimeSeq: "<< elapsed_seconds.count() << std::endl;
    delete listPara;
    ofs.close();

//    for(int i=0;i<pow+1;i++)
//        std::cout<<listPara[i]<<std::endl;
    //if(argc < )
    // random a number

//    std::mt19937 rng;
//    rng.seed(0);
//    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,99999); // distribution in range [1, 6]
//    std::cout << dist6(rng) << std::endl;

//    int seed = time(NULL);
//    srand(0);
//    std::cout<<rand()%10000<<std::endl;
//    std::cout<<rand() % (intervalN->b - intervalN->a)*5 +  (intervalN->b - intervalN->a)<<std::endl;
    
    //if(pipe.run_and_wait_end() < 0) error("running pipe");
    
    // farm
    
    // int nworkers = atoi(argv[1]);
    // std::vector<ff_node *> workers;
    // for (int i -> workers)
    //      workers.push_back(new Worker)
    // ff_farm <> myFarm(Workers);
    // if (myFarm.run_and_wait_end() < 0) error("running myFarm");
    return 0;
}
