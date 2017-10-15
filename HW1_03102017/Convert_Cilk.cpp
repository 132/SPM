// g++ test_cilk.cpp -fcilkplus -lcilkrts
// g++ -std=c++11 your_file.cpp -o your_program
#include<iostream>
#include<cilk/cilk.h>
#include<string.h>
//using namespace std;

void checkLower(char& a){
	if(islower(a)){
        	a = toupper(a);
        }
}

int main(int argc,char* argv[]){
//	std::cout<<"Trideptrai! an Com"<<endl;
//	std::cout<<"The length of String: "<<endl;
//	std::cout<<argc<<" The number of String"<<endl;
	//cilk_spawn cout<<"trideptrai"<<endl;
	cilk_for(int i=1;i<argc;i++)
		cilk_for(int j=0; j<strlen(argv[i]);j++)
			checkLower(argv[i][j]);
//			cilk_spawn checkLower(argv[i][j]);
//	cilk_spawn count++;
//	cilk_sync;
	for(int k=1; k<argc;k++)
		std::cout<<argv[k]<<" ";
}
