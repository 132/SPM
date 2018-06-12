#include <fstream>
#include <iostream>
#include <random>

int main(int argc, char* argv[]){
    if(argc != 4){
        std::cout<<"Lack of parameters, Dude"<<std::endl;
        return 1;
    }
    int nInterval = atoi(argv[1]);
    int rangA = atoi(argv[2]);
    int rangB = atoi(argv[3]);
    if(rangA > rangB){
        std::cout<<"Second Para < Third Para"<<std::endl;
        return 1;
    }
    int *a = new int[nInterval];
    int *b = new int[nInterval];
    
    std::ofstream ofs;
    ofs.open("../input/Input.txt", std::ofstream::out | std::ofstream::trunc);
    
    int seed = time(NULL);
    srand(seed);
    
    for(int i=0;i<nInterval;i++){
        a[i] = rand() % rangA + 1;
        b[i] = rand() % rangB + a[i];
        ofs<<a[i]<<" "<<b[i]<<" ";
    }
    
    delete a;
    delete b;
    ofs.close();
    
    return 0;
}
