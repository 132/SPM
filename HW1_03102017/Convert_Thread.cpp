#include<iostream>
#include<thread>
#include<string.h>
using namespace std;

void checkLower(char& in){
	if(islower(in)){
		in = toupper(in);
	}
}
void funcCharacter(char* in){
	thread Char[strlen(in)];
	for(int j=0;j<strlen(in);j++)
		Char[j] = thread(checkLower,ref(in[j]));
	for(int j=0;j<strlen(in);j++)
		Char[j].join();
}
int main(int argc, char* argv[]){
	thread Word[argc-1];
	for(int i = 1;i < argc;i++){
	/*	thread Charac[strlen(argv[i])];
		for(int j=0; j<strlen(argv[i]);j++){
			Charac[j] = thread (checkLower,ref(argv[i][j]));
		}
		for(int j=0;j<strlen(argv[i]);j++)
			Charac[j].join();
	*/
		Word[i-1] = thread(funcCharacter,argv[i]);
	}
	for(int i=1;i<argc;i++)
		Word[i-1].join();
	for(int k=1;k< argc;k++)
		cout<<argv[k]<<" ";
}
