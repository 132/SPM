#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <chrono>
#include <mutex>
#include <atomic>
#include <thread>
#include <fstream>
#include <queue> 
#include <condition_variable>

#include <function.h>
#include <interval_number.h>
#include <Montecarlo.h>

using namespace Montecarlo;

std::mutex mutex_readS;
std::mutex mutex_random_n;
std::mutex mutex_to_farm;

std::queue<interval_number* > readQ;
std::queue<interval_number* > randomN_randomListNQ;
std::queue<interval_number* > toFarmQ;

std::condition_variable cond_read_randomN;
std::condition_variable cond_randomN_randomListN;
std::condition_variable cond_randomListN_farm;

bool read_ready = true;
bool randomNumber_ready = false;
bool randomList_ready = false;
bool startFarm_ready = false;

/*
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
*/

void calMonteNumberThread(interval_number * intervalN){
    
    intervalN->calMonteNumber();
    std::cout<<"calculate Monte: "<<intervalN->a<< " : "<< intervalN->monteNumber<<std::endl;
    
}

int randomNumberN(interval_number * intervalN){
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(intervalN->b-intervalN->a,5*(intervalN->b-intervalN->a)); // distribution in range [1, 6]
    //std::cout << "random N: "<<dist6(rng) << " of "<<intervalN->a<< " "<<intervalN->b<<std::endl;
    return dist6(rng);
}

void randomListNumberN(interval_number * intervalN){
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
}

void readStream(std::ifstream &inputStream, func gf){
    int a,b;
    int id =0;
    std::cout<<"creat readStream Thread"<<std::endl;
    while(inputStream >> a >> b){

        std::lock_guard<std::mutex> lk(mutex_readS);
         
        std::cout<<"result of readStream: "<<a<<" "<<b<<std::endl;
        interval_number * interval_temp = new interval_number(id,a,b,gf);
        id++;
        std::cout<<"result of readStream: "<<interval_temp->a << " " << interval_temp->b<<std::endl;
    
        readQ.push(interval_temp);
    
        std::cout<<"from Q: "<<readQ.front()->a<< " " << readQ.front()->b<<std::endl;
    
        randomNumber_ready = true;

        cond_read_randomN.notify_one();
    }
}

void randomNumber(){
    std::cout<<"randomNumber: Q: "<<readQ.empty()<<std::endl;
    
    do{
        std::unique_lock<std::mutex> lk(mutex_readS);
        cond_read_randomN.wait(lk, []{return randomNumber_ready;});
        
            std::lock_guard<std::mutex> lkrandomN(mutex_random_n);
            
                auto interval_temp = readQ.front();
                readQ.pop();
                std::cout<<"randomNumber: "<<interval_temp->a<<std::endl;
                interval_temp->setN(randomNumberN(interval_temp));
                randomN_randomListNQ.push(interval_temp);
                randomList_ready = true;
                
            cond_randomN_randomListN.notify_one();
            
        lk.unlock();
        cond_read_randomN.notify_one();
        
    }while(!readQ.empty());
}

void randomListNumber(){
    
    do{
        std::unique_lock<std::mutex> lkrandomN(mutex_random_n);
        cond_randomN_randomListN.wait(lkrandomN, []{return randomList_ready;});
            
            std::lock_guard<std::mutex> lktoFarm(mutex_to_farm);
            
                auto interval_temp = randomN_randomListNQ.front();
                randomN_randomListNQ.pop();
                std::cout<<"in randomListNumber: "<<interval_temp->a<<std::endl;
                randomListNumberN(interval_temp);
                toFarmQ.push(interval_temp);
                startFarm_ready = true;
                //mutex_list_n.unlock();
                
            cond_randomListN_farm.notify_one();
            
        lkrandomN.unlock();
        cond_randomN_randomListN.notify_one();
    }while(!randomN_randomListNQ.empty());
}

void farmStage(int nworker){
    std::thread run[nworker];
    std::cout<<"number of worker: "<<nworker<<std::endl;
    do{   
        std::cout<<"goto FarmStage:" << std::endl;
        for(int i=0; i<nworker;i++){
            std::unique_lock<std::mutex> lk2farm(mutex_to_farm);
            cond_randomListN_farm.wait(lk2farm, []{return startFarm_ready;});
            if(!toFarmQ.empty()){
                auto intervao_temp = toFarmQ.front();
                toFarmQ.pop();
                run[i] = std::thread(calMonteNumberThread, intervao_temp);
            } else {
                break;
            }
            lk2farm.unlock();
            cond_randomListN_farm.notify_one();
        }
        for(int i=0;i<nworker;i++)
            run[i].join();
    }while(!toFarmQ.empty());
}

int main(int argc, char * argv[]) {
// take the arguments from the command line
    int nworker = atoi(argv[1]);
    
    int pow = atoi(argv[2]);
    double * listPara = new double [pow+1];
    for(int i=0;i<pow+1;i++)
        listPara[i] = atof(argv[i+3]);
    func givenFunc(pow, listPara);
    
    std::ifstream streamInterval;
    streamInterval.open("../input/Input.txt");

    if(argc != pow + 4)
        std::cout<<"Error: Lack of Parameter"<<std::endl;
    
    auto start = std::chrono::system_clock::now();
    
    std::thread readS(readStream, std::ref(streamInterval), givenFunc);                // read stream and create Q
    std::thread generateRandomN(randomNumber);    // a random number stage
    std::thread generateListN(randomListNumber);      // a list of random number 
    
    //call a farm
    farmStage(nworker-3);

    readS.join();
    generateRandomN.join();
    generateListN.join();
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Workers: "<< nworker << " PowerOfFunc: " << pow << " TimeThread: " << elapsed_seconds.count() <<std::endl;

    delete listPara;
    return 0;
}
    
    /*
     *     
    //std::unique_lock<std::mutex> lk(mutex_readS);
    //cond_randomN_randomListN.wait(lk, []{return !readQ.empty();});  
    //std::cout<<"readQ empty: "<<readQ.empty()<<std::endl;
    //std::cout<<"result after streaming: "<<readQ.front()->a<<std::endl;

    //lk.unlock();
    //lk.unlock();
    //cond_randomN_randomListN.notify_one();
    
   // std::thread generateRandomN(randomNumber, readQ, randomN_randomListNQ);    // a random number stage
 std::lock_guard<std::mutex> lk(m
    std::thread generateListN(randomListNumber, randomN_randomListNQ, toFarmQ);      // a list of random number 
    std::thread run[nworker];       // farm stage
    
    do{
        for(int i=0; i<nworker;i++){
            if(!toFarmQ.empty()){
                auto intervao_temp = toFarmQ.front();
                toFarmQ.pop();
                run[i] = std::thread(calMonteNumberThread, intervao_temp);
            } else {
                break;
            }
        }
        for(int i=0;i<nworker;i++)
            run[i].join();
    }while(!toFarmQ.empty());
    
    
    
    generateListN.join();

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
    */
 //   for(int i=0;i<pow+1;i++)
 //       std::cout<<listPara[i]<<std::endl;
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
