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
#include <ctime>

#include "function.h"
#include "interval_number.h"
#include "Montecarlo.h"

using namespace Montecarlo;

std::mutex mutex_readS;
std::mutex mutex_random_n;
std::mutex mutex_to_farm;
std::mutex mutex_calMonte;
std::mutex mutex_write2File;

std::queue<interval_number* > readQ;
std::queue<interval_number* > randomN_randomListNQ;
std::queue<interval_number* > toFarmQ;
std::queue<interval_number* > write2FileQ;

std::queue<bool> emittorQ;

std::condition_variable cond_read_randomN;
std::condition_variable cond_randomN_randomListN;
std::condition_variable cond_randomListN_farm;
std::condition_variable cond_divide2Farm;
std::condition_variable cond_write2File;

//bool read_ready = true;
bool endOfStream = false;
bool endOfrandomNumber = false;
bool endOfrandomList = false;
bool endOfFarm = false;
int endOfWorker = 0;

int randomNumberN(interval_number * intervalN){

//    int seed = time(NULL);
//    srand(seed);
	srand(intervalN->id);
	return rand() % (intervalN->b - intervalN->a) +  (intervalN->b - intervalN->a);
//	srand(intervalN->id);
//	return rand() % intervalN->b + intervalN->a;
}

void randomListNumberN(interval_number * intervalN){
    int * temp = new int [intervalN->N_number];
//    int seed = time(NULL);
//    srand(seed);
    for(int i=0; i<intervalN->N_number; i++){

	srand(intervalN->id+i);

        temp[i] = rand() % intervalN->b + intervalN->a;
    }
    intervalN->setListNumber(temp);
}

void readStream(std::ifstream &inputStream, func gf){
    int a,b;
    int id =1;
    while(inputStream >> a >> b){
        if(a == b)
            b = a * 100;
        std::lock_guard<std::mutex> lk(mutex_readS);
        interval_number * interval_temp = new interval_number(id,a,b,gf);
        id++;
        readQ.push(interval_temp);
        cond_read_randomN.notify_one();
    }
    endOfStream = true;
    cond_read_randomN.notify_one();
}

void randomNumber(){
    do{
        std::unique_lock<std::mutex> lk(mutex_readS);
        cond_read_randomN.wait(lk, []{return (!readQ.empty() || endOfStream);});
            if (readQ.empty() && endOfStream)
                break;
            std::lock_guard<std::mutex> lkrandomN(mutex_random_n);
                auto interval_temp = readQ.front();
                readQ.pop();
                //std::cout<<"randomNumber: "<<interval_temp->a<<std::endl;
                interval_temp->setN(randomNumberN(interval_temp));
                randomN_randomListNQ.push(interval_temp);
            cond_randomN_randomListN.notify_one();
        lk.unlock();
        cond_read_randomN.notify_one();
    }while(true);
    endOfrandomNumber = true;
    cond_randomN_randomListN.notify_one();
}

void randomListNumber(){    
    do{
        std::unique_lock<std::mutex> lkrandomN(mutex_random_n);
        cond_randomN_randomListN.wait(lkrandomN, []{return (!randomN_randomListNQ.empty() || endOfrandomNumber);});
        if(endOfrandomNumber && randomN_randomListNQ.empty())
            break;
            
            std::lock_guard<std::mutex> lktoFarm(mutex_to_farm);
                auto interval_temp = randomN_randomListNQ.front();
                randomN_randomListNQ.pop();
                //std::cout<<"in randomListNumber: "<<interval_temp->a<<std::endl;
                randomListNumberN(interval_temp);
                toFarmQ.push(interval_temp);
            cond_randomListN_farm.notify_one();
        lkrandomN.unlock();
        cond_randomN_randomListN.notify_one();
    }while(true);
    endOfrandomList = true;
    cond_randomListN_farm.notify_one();
}

void calMonteNumberThread(){
    do{
    std::unique_lock<std::mutex> lk2Monte(mutex_calMonte);
    cond_divide2Farm.wait(lk2Monte, []{return (!emittorQ.empty() || endOfFarm);});
    if((endOfrandomList && endOfFarm) || toFarmQ.empty()){
        endOfWorker++;
        break;
    }
 //           if(toFarmQ.size()==1)
 //           {
 //               auto temp = toFarmQ.front();
 //           }
        std::lock_guard<std::mutex> lk(mutex_write2File);
            
            emittorQ.pop();
            auto intervao_temp = toFarmQ.front();
            toFarmQ.pop();
            intervao_temp->calMonteNumber();
            write2FileQ.push(intervao_temp);
            
        cond_write2File.notify_one();
    lk2Monte.unlock();
    cond_divide2Farm.notify_one();
    }while(true);
}

void farmStage(int nworker){
    std::thread run[nworker];
        int number_farm = 0;
        do{            
            run[number_farm] = std::thread(calMonteNumberThread);//, std::ref(ready[number_farm]));
            number_farm++;
        } while (number_farm < nworker);
        do{
            int gap = nworker - emittorQ.size();// - collectorQ.size();
            std::unique_lock<std::mutex> lk2farm(mutex_to_farm);
            cond_randomListN_farm.wait(lk2farm, [gap, nworker]{
                if((!toFarmQ.empty()) || (endOfrandomList)){
                    return true;
                } else return false;
                
            });
            if(toFarmQ.size()==1){
                auto temp = toFarmQ.front();
            }
            if((endOfrandomList && toFarmQ.empty()) || endOfWorker == nworker)
                break;
            {
                std::lock_guard<std::mutex> lk2Monte(mutex_calMonte);
                if(gap > toFarmQ.size()){
                    gap = toFarmQ.size();
                } 
                for(int i=0; i < gap ; i++){
                    if(!toFarmQ.empty())
                        emittorQ.push(true);
                    else 
                        break;
                    cond_divide2Farm.notify_one();
                }
                if(emittorQ.size() > nworker){
                    break;
                }
            }    
            cond_divide2Farm.notify_all();
            lk2farm.unlock();
            cond_randomListN_farm.notify_one();
        }while(true);
        endOfFarm = true;
        cond_divide2Farm.notify_all();
        cond_write2File.notify_one();
        
        for(int i=0;i<nworker;i++){
            run[i].join();
        }
}

void writeFile(){
    std::ofstream outFile("Output_thread.txt", std::ios_base::app);
    std::queue<interval_number* > tempQ;
    int position = 1;
    do{
    std::unique_lock<std::mutex> lk2File(mutex_write2File);
    cond_write2File.wait(lk2File, []{
        return (!write2FileQ.empty() || endOfFarm);
    });
    if(endOfFarm && write2FileQ.empty())
        break;

        auto intervalN = write2FileQ.front();
        write2FileQ.pop();
        
        if(intervalN->id == position){
            outFile<<intervalN->monteNumber<<" ";
            position++;
            if(!tempQ.empty()){
                for(int i=0;i<tempQ.size();i++){
                    auto temp_interval = tempQ.front();
                    tempQ.pop();
                    if(temp_interval->id == position){
                        outFile<<temp_interval->monteNumber<<" ";
                        position++;
                    } else 
                        tempQ.push(temp_interval);
                }
            }
        } else {
            tempQ.push(intervalN);
        }

    lk2File.unlock();
    cond_write2File.notify_one();
    
    }while(true);
}


int main(int argc, char * argv[]) {
    int nworker = atoi(argv[1]);
    std::string fileName = argv[2];
    
    int pow = atoi(argv[3]);
    if(argc != pow + 5){
        std::cout<<"Error: not correct the number of Prameters"<<std::endl;
        return 1;
    }

    double * listPara = new double [pow+1];
    for(int i=0;i<pow+1;i++)
        listPara[i] = atof(argv[i+3]);
    func givenFunc(pow, listPara);
    
    std::ifstream streamInterval;
    streamInterval.open(fileName);

    std::ofstream ofs;
    ofs.open("Output_thread.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    
    auto start = std::chrono::system_clock::now();
    
    std::thread readS(readStream, std::ref(streamInterval), givenFunc);                // read stream and create Q
    std::thread generateRandomN(randomNumber);    // a random number stage
    std::thread generateListN(randomListNumber);      // a list of random number 
    
    std::thread generateFarm(farmStage, nworker-5);   //call a farm
    std::thread write2File(writeFile);

    readS.join();
    generateRandomN.join();
    generateListN.join();
    generateFarm.join();
    write2File.join();
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout<<"Workers: "<< nworker-5 << " PowerOfFunc: " << pow << " TimeThread: " << elapsed_seconds.count() <<std::endl;
    delete listPara;
    return 0;
}
