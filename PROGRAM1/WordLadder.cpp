#include "WordLadder.h"

WordLadder::WordLadder(const string &file) {
    string word;
    ifstream infile;
    infile.open(file.c_str());
    if (infile.is_open()) {
        while (!infile.eof()) {
            getline(infile,word);
            /* This code is causing problems with zyBooks
            if (word.length() != 5) {
                cout << "Word not exactly five characters detected!" << endl;
                return;
            }
            */
            dict.push_back(word.c_str());
        }
        infile.close();
        return;
    } else {
        cout << "Error opening input file." << endl;
        return;
    }
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    
    ofstream outfile;
    outfile.open(outputFile.c_str());
    if (!outfile.is_open()) {
        cout << "Opening output file failed.";
        return;
    }
    if (start == end) {
        outfile << start;
        return;
    }
    
    // set up the stuff
    queue< stack<string> > queue;
    stack< string > tempstack;
    unsigned i;
    string word;
    string nextword;
    list<string>::iterator it;
    char ltr;
    
    tempstack.push(start);
    queue.push(tempstack);
    
   
    // find the first word, delete it
    dict.remove(start);
    while(!queue.empty()) {
        // get the word off of the top of the front stack
        word = queue.front().top();
        for (i=0;i<5;++i) {
            nextword = word;
            for (ltr = 'a'; ltr <= 'z'; ++ltr) {
                // Change one letter in nextword.
                nextword[i]=ltr;
                for (it=dict.begin();it!=dict.end();++it) {
                    if (*it == nextword) {
                        if ( *it == end) {
                            // if the off by one word is the last word 
                            // the ladder contains the entire stack -- output and return.
                            queue.front().push(end);
                            //print the stack
                            printstack(queue.front(),outfile);
                            //cout << "Operations: " << opers << endl << endl;
                            return;
                        } 
                        // otherwise, create a copy of the front stack and push the
                        // off by one word from dictionary
                        tempstack = queue.front();
                        tempstack.push(nextword);
                        queue.push(tempstack);
                        it = dict.erase(it);
                    }
                }
            }
        }
        queue.pop();
    }
    // if a word ladder is not found, then do this
    if (outfile.is_open()) {
        outfile << "No Word Ladder Found!!";
    }
}


void WordLadder::printstack(stack<string> stack, ofstream &outfile) {
    
    if (outfile.is_open()) {
        while (!stack.empty()) {
            outfile << stack.top();
            stack.pop();
            if (!stack.empty()) {
                outfile << " ";
            }
        }
    }
    //cout << endl;
}