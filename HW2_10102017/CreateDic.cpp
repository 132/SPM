// g++ -std=c++0x -lpthread CreateDic.cpp

#include<iostream>
#include<fstream>
#include<thread>
#include<string.h>
#include<vector>
#include<sstream>
#include<functional>
#include<chrono>
#include <mutex>
#include <atomic>

using namespace std;

mutex m;
vector<unsigned long> HashTable;
vector<string> Terms;
vector<int> Frequency;
/*
*/
unsigned long hashFunction(string in){
	hash<string> str_hash;
//	cout<<str_hash(in)<< " :hash String"<<endl;
	return str_hash(in);
 }
/*
 * void buildDic(vector<unsigned long>& HashList, vector<string>& Terms, vector<int>& Fre, string in){
	unsigned long check = hashFunction(in);
	for(int i=0;i<HashTale.size();i++){
		if(check == HashList.at(i)){
	//		cout<<in<<" "<<Fre.at(i)<<" in IF in buildDic"<<endl;
	//		m.lock();
			Frequency.at(i) = Frequency.at(i) + 1;
	//		m.unlock();
			return;
		}
	}
	//cout<<in<<" input of buildDic"<< endl;
	// not find 
	HashList.push_back(hashFunction(in));
	Terms.push_back(in);
	Fre.push_back(1);
}
*/

//void readDic(char *Dic,vector<unsigned long>& HashList, vector<string>& Terms, vector<int>& Fre){
void readDic(char *Dic){
	ifstream rDic(Dic);
	string line;
	while(getline(rDic,line)){
		istringstream is(line);
		string part;
		int count =1;
		while(getline(is,part,' ')){
			if(count==1){
				unsigned long npart;
				stringstream(part) >> npart;
				HashTable.push_back(npart);
				count++;
			}
			else if(count==2){
				Terms.push_back(part);
				count++;
			}else if(count==3){
				Frequency.push_back(stoi(part));
				count =1;
			}
		}
	}
}
void add2Vector(vector<unsigned long> HT, vector<string> T, vector<int> F){
	for(int i=0;i<HT.size();i++){
		int check = 0; // non existing
		for(int j=0;j<HashTable.size();j++){
			if(HT.at(i) == HashTable.at(j)){
				Frequency.at(i) += F.at(i);
				check =1; 	// existing
				cout<<T.at(i)<<" add2Vector"<<endl;
				break;
			}
		}
		if(check == 0){
			HashTable.push_back(HT.at(i));
			Terms.push_back(T.at(i));
			Frequency.push_back(F.at(i));
		}
	}
}
//void countWords(string line,vector<unsigned long>& HashList, vector<string>& Terms, vector<int>& Fre){
void countWords(string line){
	// TOKENIZER
	for(int i=0;i<=sizeof(line);i++)			// convert special symbol to space
		if(int(line[i])<65 || (int(line[i])<90 && 97<int(line[i])) || int(line[i])>122)	// mistake about ASCII check it later
				line[i] = ' ';
	cout<<line<< ": line TOKENIZER"<<endl;
	istringstream is(line);
	string parts;
	// Change to tokenizer -> buildDic
	
	// Assignment Vector
	vector<unsigned long> HashList;
	vector<string> nTerms;
	vector<int> Fre;
	//
	while(getline(is,parts, ' ')){
		if(parts.empty() || parts == " ")
			continue;
		else{
//			build Dic moved to here
			unsigned long check = hashFunction(parts);
			cout<<parts<<" Need to check this parts"<<endl;
			int existW = 0;
 			for(int i=0;i<HashTable.size();i++){
				 if(check == HashTable.at(i)){
					for(int j=0;j<HashList.size();j++){
				 		if(HashList.at(j)==check){
							cout<<Terms.at(i)<<" Existing in the same line"<<endl;
							Fre.at(Fre.at(j)+1);
							existW = 1;
							break;
						}else{
							cout<<Terms.at(i)<<" non Existing before in this line"<<endl;
							HashList.push_back(HashTable.at(i));
							nTerms.push_back(parts);
							Fre.push_back(1);
							existW = 1;
							break;
						}
				 	}
					break;
 				}
			}
			if(existW ==0){
	 			HashList.push_back(check);
				nTerms.push_back(parts);
				Fre.push_back(1);
			}
		}
	}
	m.lock();
	//add2Vector(HashList,nTerms,Fre);
	
	for(int i=0;i<HashList.size();i++){
		int check = 0; // non existing
		cout<<nTerms.at(i)<<" nTerms_ in add2Vector"<<endl;

		for(int j=0;j<HashTable.size();j++){
			if(HashList.at(i) == HashTable.at(j)){
				Frequency.at(j) += Fre.at(i);
				check =1;       // existing
				cout<<nTerms.at(i)<<" add2Vector "<<Frequency.at(j)<<endl;
				break;
			}
		}
		if(check == 0){
			HashTable.push_back(HashList.at(i));
			Terms.push_back(nTerms.at(i));
			Frequency.push_back(Fre.at(i));
		}
	}
	cout<<"........................Complete CountWords"<<endl;
	
	m.unlock();
}

void writeDic(char *Dic){//,vector<unsigned long> hashList, vector<string> Terms, vector<int> Fre){
	ofstream writeDic(Dic);
	for(int i=0;i<HashTable.size();i++)
		writeDic<< HashTable.at(i)<< " "<< Terms.at(i)<<" "<<Frequency.at(i)<< endl;
}

/*
*/

int main(int argc, char** argv){
	if (argc != 4) {
		cout << "Usage: " << argv[0] << " <File_Name> <File_Dictrionary> <The_Number_of_Threads> " << endl;
		return EXIT_FAILURE;
    	}
	//char *NoThread = argv[3];
	//int NumberOfThread = (int) *NoThread;
	int NumberOfThread = atoi(argv[3]);
	
	char *FileName = argv[1];
	ifstream readFile(FileName);
	
	// File Dic Hash-Term-Frequency
	
	// Vetors
	
//	vector<unsigned long> HashTable;
//	vector<string> Terms;
//	vector<int> Frequency;
	//
	char *FileDic = argv[2];
	readDic(FileDic);//FileDic,HashTable,Terms,Frequency);
	string line;
//	while(getline(readFile,line)){
//		countWords(line,HashTable, Terms, Frequency);
//		//thread t(countWords, line,ref( HashTable), ref(Terms), ref(Frequency));
//	}
	thread run[NumberOfThread];
	auto start = std::chrono::system_clock::now();
	cout<<NumberOfThread<< " :NumberOfThread"<<endl;
	int EndOfFile = NumberOfThread;
	do{
		for(int i=0; i<NumberOfThread;i++){
			if(getline(readFile,line)){
				cout<<i<<" # Thread"<<endl;
				
				run[i] = thread(countWords,line);//,ref(HashTable),ref(Terms),ref(Frequency));
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
	auto end = std::chrono::system_clock::now();
 	std::chrono::duration<double> elapsed_seconds = end-start;
	
	cout<<"Elapsed secounds: "<<elapsed_seconds.count()<<endl;
	writeDic(FileDic);//,HashTable,Terms,Frequency);

	cout<<"Thread"<<'\t'<<"Input_File"<<'\t'<<"Dictionary"<<'\t'<<"Elapsed_Seconds"<<endl;
	cout<<NumberOfThread<<'\t'<<FileName<<'\t'<<FileDic<<'\t'<<elapsed_seconds.count()<<endl;
/*	
*/
}
