#include <iostream>
#include <string>
#include <random>

#include <vector>

#include <chrono>
#include <mutex>
#include <atomic>
#include <thread>
#include <fstream>

#include <function.h>
#include <interval_number.h>
#include <Montecarlo.h>

using namespace Montecarlo;
std::mutex m;

void calMonteNumberThread(interval_number * intervalN, func givenFunc){
    intervalN->calMonteNumber();
}


void randomListNumber(interval_number * intervalN, func givenFunc){
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
    //std::thread(calMonteNumberThread, std::ref(intervalN), givenFunc);
    calMonteNumberThread(std::ref(intervalN), givenFunc);
}


void randomNumberN(interval_number * intervalN, func givenFunc){
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(intervalN->b-intervalN->a,5*(intervalN->b-intervalN->a)); // distribution in range [1, 6]
    //std::cout << "random N: "<<dist6(rng) << " of "<<intervalN->a<< " "<<intervalN->b<<std::endl;
    intervalN->setN(dist6(rng));
    //std::thread(randomListNumber, std::ref(intervalN), givenFunc);
    //std::cout << "random N2: "<<dist6(rng) << " of "<<intervalN->a<< " "<<intervalN->b<<std::endl;
    randomListNumber(intervalN, givenFunc);
}

int main(int argc, char * argv[]) {
// take the arguments from the command line
    int nworker = atoi(argv[1]);
    //std::cout<<nworker<< " :NumberOfThread"<<std::endl;
    
    int pow = atoi(argv[2]);
    double * listPara = new double [pow+1];
    for(int i=0;i<pow+1;i++)
        listPara[i] = atof(argv[i+3]);
    func givenFunc(pow, listPara);
    
    std::ifstream streamInterval;
    streamInterval.open("../input/Input.txt");

    if(argc != pow + 4)
        std::cout<<"Error: Lack of Parameter"<<std::endl;
    
    int a, b;
    int EndOfFile = 0;
    int numberInterval = 0;
    auto start = std::chrono::system_clock::now();
    std::thread run[nworker];
    do{
        for(int i=0;i<nworker;i++){
            if (streamInterval >> a >> b){
                //std::cout<<"Worker: "<< i <<std::endl;
                //interval_number interval_temp(a,b,givenFunc);
                
                run[i] = std::thread(randomNumberN, new interval_number(a,b,givenFunc), givenFunc);
                numberInterval ++;
                //run[i] = thread(randomNumber,ref(interval_temp));
                //run[i] = thread(randomListNumber, ref(interval_temp));
                //run[i] = thread(calMonteNumber, ref(interval_temp), givenFunc);
            } else {
                // end of stream
                EndOfFile = 1;
                break;
            }
        }
        for(int i=0;i<nworker;i++)
            run[i].join();
    }while(EndOfFile ==1);

 //   for(int i=0;i<pow+1;i++)
 //       std::cout<<listPara[i]<<std::endl;

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Workers: "<< nworker << " PowerOfFunc: " << pow << " TimeThread: " << elapsed_seconds.count() <<std::endl;

    delete listPara;
    return 0;
}
    
    /*
	do{
		for(int i=0; i<nworker;i++){
			if(getline(readFile,line)){
				cout<<i<<" # Thread"<<endl;
				
				run[i] = thread(countWords,line);   // countWords is the function
			}else{
				EndOfFile = i;
				EndOfFile = false;
				cout<<"End Of File"<<endl;
				break;
			}
		}
		for(int i=0;i<EndOfFile;i++){
			run[i].join();
		}
		cout<<"...........Complete 2 Threads"<<endl;
	}while(EndOfFile>0);
    */
/*
 // random a number
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

    std::cout << dist6(rng) << std::endl;
    */
