#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <sys/stat.h>
#include "sha256.h"

using namespace std;

	bool exists (const string& name) {//------------------finding file
	struct stat buffer;   
	return (stat (name.c_str(), &buffer) == 0); }

size_t getFilesize(const string& filename) {//-----------file size
    struct stat st;
    if(stat(filename.c_str(), &st) != 0) {
        return 0;
    }
    return st.st_size;   
}
	
int main()//--------------------------------------------program start
{	
	int fileNo=1;
	ofstream newBlock;
	
	while (exists("Block " + to_string(fileNo) + ".txt")==1){
	cout<<"SKIP THIS FILE: "<<fileNo<<endl;
	fileNo++;}
	//the code for locating the last block goes here
	//the code for the NET consensus should go here
	//the code for reaching 1 MB goes here
	fileNo--;
	for (fileNo;fileNo<=100;fileNo++){
	ifstream lastBlock("Block " + to_string(fileNo) + ".txt");//-------read to buffer the last block
	stringstream buffer;
	buffer << lastBlock.rdbuf();
	string hash = sha256(buffer.str());
	
	while (getFilesize("Block " + to_string(fileNo) + ".txt")<=262144){ //--- FIle Size 
	newBlock.open("Block " + to_string(fileNo) + ".txt", ios_base::app);//---writing data to the new block
	newBlock<<"Just a filler until 256kb"<<endl;//the code for bringing Transaction data to last block goes here
	newBlock.close();
	}
	newBlock.open("Block " + to_string(fileNo) + ".txt", ios_base::app);//------------------chain the last block
	newBlock << hash <<endl;
	newBlock.close();
	fileNo++;
	newBlock.open("Block " + to_string(fileNo) + ".txt");//------the next block will have the hash of the previous
	newBlock << hash <<endl;
	newBlock.close();
	fileNo--;
	}
	
	cout << "Program Ended. Check Output files for results."<<endl;
    return 0;
}


