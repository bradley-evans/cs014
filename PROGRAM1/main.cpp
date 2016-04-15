#include <iostream>
#include <string>

#include "WordLadder.h"

using namespace std;



int main() {
    
    string filename,leadword,endword,output; // defines a word dictionary
    //cout << "Select dictionary file: "; 
    cin >> filename;
    WordLadder wordladder(filename); // create a word ladder
    
    //cout << "First word: ";
    cin >> leadword;
    //cout << endl;
    //cout << "Second word: ";
    cin >> endword;
    //cout << endl;
    //cout << "Output file: ";
    cin >> output;
    wordladder.outputLadder(leadword,endword,output);
    //cout << endl;
    
    //wordladder.outputLadder()
    
    //cout << "Successful end." << endl;
}