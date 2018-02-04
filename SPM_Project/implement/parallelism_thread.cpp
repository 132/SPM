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
std::mutex mutex_calMonte;
std::mutex mutex_write2File;

//std::mutex mutex_worker = new std::mutex[255];

std::queue<interval_number* > readQ;
std::queue<interval_number* > randomN_randomListNQ;
std::queue<interval_number* > toFarmQ;
std::queue<interval_number* > write2FileQ;

std::queue<bool> emittorQ;
std::queue<bool> collectorQ;

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

bool randomList_ready = false;
bool startFarm_ready = false;
bool calMonte_ready = false;
bool write2File_ready = false;
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
    int id =1;
    std::cout<<"creat readStream Thread"<<std::endl;
    while(inputStream >> a >> b){

        std::lock_guard<std::mutex> lk(mutex_readS);
         
        interval_number * interval_temp = new interval_number(id,a,b,gf);
        id++;
        readQ.push(interval_temp);
        

        cond_read_randomN.notify_one();
    }
    
    //interval_number * interval_temp = new interval_number(0,0,0,gf);
    //readQ.push(interval_temp);
    
    endOfStream = true;
    cond_read_randomN.notify_one();
}

void randomNumber(){
   // std::cout<<"randomNumber: Q: "<<readQ.empty()<<std::endl;
    
    do{
        std::unique_lock<std::mutex> lk(mutex_readS);
        cond_read_randomN.wait(lk, []{return (!readQ.empty() || endOfStream);});
        if (readQ.empty() && endOfStream)
            break;
        
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
                std::cout<<"in randomListNumber: "<<interval_temp->a<<std::endl;
                randomListNumberN(interval_temp);
                toFarmQ.push(interval_temp);
                startFarm_ready = true;
                //mutex_list_n.unlock();
                
            cond_randomListN_farm.notify_one();
            
        lkrandomN.unlock();
        cond_randomN_randomListN.notify_one();
    }while(true);
    
    endOfrandomList = true;
    cond_randomListN_farm.notify_one();
}

void calMonteNumberThread(){
    
    do{
    //std::cout<<"ready: "<<emittorQ.empty()<<std::endl;
    std::unique_lock<std::mutex> lk2Monte(mutex_calMonte);
    cond_divide2Farm.wait(lk2Monte, []{return (!emittorQ.empty() || endOfFarm);});
    
    //|| (endOfrandomList && endOfFarm) || (!toFarmQ.empty() && endOfrandomList));}); //|| !toFarmQ.empty())
    //std::cout<<"in side MoteCal -> ready = 0"<<std::endl;
    //std::cout<<"emittorQ size in Monte: "<<emittorQ.size()<<std::endl;
    std::cout<<"emittorQ.size(): "<<emittorQ.size()<<" emittorQ.empty: "<<emittorQ.empty()<<" endOfList: "<<endOfrandomList<<" toFarmQ: "<<toFarmQ.empty()<<" endOfFarm: "<<endOfFarm<<"  +++++++++++++++++"<<std::endl;
    
    //if(emittorQ.empty() && endOfrandomList && endOfFarm){
    
    if((endOfrandomList && endOfFarm) || toFarmQ.empty()){
        std::cout<<"end of worker========================"<<std::endl;
        endOfWorker++;
        
        break;
    }
    
    /*
    auto tempCheckEnd = toFarmQ.front();
    std::cout<<"id lasts: "<<tempCheckEnd->id<<std::endl;
    if(tempCheckEnd->id == 0){
        do{
            emittorQ.pop();
        }while(!emittorQ.empty());
        std::cout<<"end of worker in case of End of Interval========================"<<std::endl;
        endOfWorker = true;
        cond_divide2Farm.notify_all();
        break;
    }
    
    if(endOfWorker)
        break;
    
    */
    
            if(toFarmQ.size()==1)
            {
                auto temp = toFarmQ.front();
                std::cout<<"in CalMote last thing: "<<temp->a<<std::endl;
            }
        std::lock_guard<std::mutex> lk(mutex_write2File);
            
            emittorQ.pop();
            //std::cout<<"emittorQ size after POP in Monte: "<<emittorQ.size()<<std::endl;
            auto intervao_temp = toFarmQ.front();
            
            toFarmQ.pop();
    
            intervao_temp->calMonteNumber();
            
            std::cout<<"calculate Monte: "<<intervao_temp->a<< " : "<< intervao_temp->monteNumber<<std::endl;

            write2FileQ.push(intervao_temp);
            
            collectorQ.push(true);
            //cond_divide2Farm.notify_one();
            std::cout<<"size of collectorQ: "<<collectorQ.size()<<std::endl;
            
        cond_write2File.notify_one();
        
    lk2Monte.unlock();
    cond_divide2Farm.notify_one();
    
    
    }while(true);
    //cond_divide2Farm.notify_all();
    //lk2farm.unlock();
    //cond_randomListN_farm.notify_one();
}

void farmStage(int nworker){
    std::thread run[nworker];
 
    
        //std::cout<<"goto FarmStage:" << std::endl;
        //std::cout<<"number of worker: "<<nworker<<std::endl;
        int number_farm = 0;
        
        do{            
            std::cout<<"create a thread farm"<<std::endl;
            run[number_farm] = std::thread(calMonteNumberThread);//, std::ref(ready[number_farm]));
            number_farm++;
            //std::cout<<"Number of farm: "<<number_farm<<std::endl;
        } while (number_farm < nworker);
            
        
        do{
            //std::cout<<"startFarm_ready: "<<startFarm_ready<<std::endl;
            
           // if(nworker < t
            
                int gap = nworker - emittorQ.size();// - collectorQ.size();
                
                
            //std::cout<<"NUmber gap: "<<gap<<std::endl;
            
            std::unique_lock<std::mutex> lk2farm(mutex_to_farm);
            cond_randomListN_farm.wait(lk2farm, [gap, nworker]{
                
                std::cout<<"Check before add emittorQ "<<std::endl;
                std::cout<<"toFarmQ.empty() "<<toFarmQ.empty()<<" gap: "<<gap<<" endOfrandomList: "<<endOfrandomList<<std::endl;
                //if((!toFarmQ.empty() && gap > 0 && emittorQ.size()+collectorQ.size() <= nworker) || (endOfrandomList && gap > 0)) return true; 
                
                if((!toFarmQ.empty()) || (endOfrandomList)) 
                { std::cout<<"check truen in farm"<<std::endl;return true; }
                else return false;});
                std::cout<<"Check after add emittorQ "<<std::endl;
            
            std::cout<<"endOfrandomList: "<<endOfrandomList<<" toFarmQ.size(): "<<toFarmQ.size()<<std::endl;
            if(toFarmQ.size()==1)
            {
                auto temp = toFarmQ.front();
                std::cout<<"last thing: "<<temp->a<<std::endl;
            }
            if((endOfrandomList && toFarmQ.empty()) || endOfWorker == nworker){
                std::cout<<"end of Farm============================"<<std::endl;
                std::cout<<"number of emittorQ.size(): "<<emittorQ.size()<<" +++++++++++++++++"<<std::endl;
                break;
            }
            //std::cout<<"startFarm_ready is true"<<std::endl;
            {
                std::lock_guard<std::mutex> lk2Monte(mutex_calMonte);
                
                std::cout<<"emittorQ: "<<emittorQ.size()<<" gap: "<<gap<<" toFarmQ.size(): "<<toFarmQ.size()<<std::endl;
                
                //emittorQ.push(true);
               
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
                std::cout<<"Afer push new emittorQ: "<<emittorQ.size()<<" gap: "<<gap<<" toFarmQ.size(): "<<toFarmQ.size()<<std::endl;
                if(emittorQ.size() > nworker){
                    std::cout<<"greater than nworker"<<std::endl;
                    break;
                }
            }    
            cond_divide2Farm.notify_all();
           // cond_divide2Farm.notify_all();
            
         /*   {
                std::unique_lock<std::mutex> lk2Monte(mutex_calMonte);
                cond_divide2Farm.wait(lk2Monte, [nworker, gap]{
                    std::cout<<"check for after processing "<<collectorQ.size()<< " and "<<gap<<"----------------------------"<<std::endl;
                    //if(collectorQ.size() > 0 && collectorQ.size()<= nworker){
                    if(collectorQ.size() > 0 || (endOfrandomList && toFarmQ.empty()) || (gap > 0)){
                        do{
                            collectorQ.pop(); 
                        }while(!collectorQ.empty());
                     
                        std::cout<<"return true in after processing"<<std::endl; 
                        return true;
                    } else return false;});
                
                //std::cout<<"after processed emittorQ size: "<<emittorQ.size()<<std::endl;
                //std::cout<<"complete process"<<std::endl;
            }
            */
            
            lk2farm.unlock();
            cond_randomListN_farm.notify_one();
            
        }while(true);
        
        std::cout<<"out sisde Farm ========================================"<<std::endl;
        endOfFarm = true;
        cond_divide2Farm.notify_all();
        cond_write2File.notify_one();
        
        
        for(int i=0;i<nworker;i++){
            
            run[i].join();
            std::cout<<"Join Total Worker======"<<std::endl;
        }
}



void writeFile(){
    std::cout<<"create Write: ##########################"<<std::endl;
    
    do{
    //std::cout<<"Write2FileQ: "<<write2FileQ.empty()<<std::endl;
    std::unique_lock<std::mutex> lk2File(mutex_write2File);
    cond_write2File.wait(lk2File, []{
        std::cout<<"writeFile() checking "<<std::endl;
        return (!write2FileQ.empty() || endOfFarm);});
    
    if(endOfFarm && write2FileQ.empty())
        break;
    
        //std::cout<<"after checking Write2FileQ: "<<write2FileQ.empty()<<std::endl;
        std::ofstream outFile("../input/Output_thread.txt", std::ios_base::app);
        auto intervalN = write2FileQ.front();
        write2FileQ.pop();
        
        outFile<<intervalN->monteNumber<<" ";
        std::cout<<"write 2 file: "<<intervalN->monteNumber<<" with: "<<intervalN->a<<std::endl;
        
    lk2File.unlock();
    cond_write2File.notify_one();
    
    }while(true);
    
    std::cout<<"complete write 2 FIle"<<std::endl;
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

    std::ofstream ofs;
    ofs.open("../input/Output_thread.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    
    if(argc != pow + 4)
        std::cout<<"Error: Lack of Parameter"<<std::endl;
    
    auto start = std::chrono::system_clock::now();
    
    std::thread readS(readStream, std::ref(streamInterval), givenFunc);                // read stream and create Q
    std::thread generateRandomN(randomNumber);    // a random number stage
    std::thread generateListN(randomListNumber);      // a list of random number 
    
    std::thread generateFarm(farmStage, nworker-4);   //call a farm
    std::thread write2File(writeFile);
    

    readS.join();
    generateRandomN.join();
    generateListN.join();
    
    generateFarm.join();
    write2File.join();
    
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
