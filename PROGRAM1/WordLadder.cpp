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
            if (word.size() != 5) {
                cout << "Error: Word longer than 5 characters detected in dictionary." << endl;
                return;
            }
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
        cout << "Opening output file failed." << endl;
        return;
    }
    if (start == end) {
        outfile << start;
        return;
    }
    
    // set up the stuff
    queue< stack<string> > queue;
    stack< string > tempstack;

    string word;
    list<string>::iterator it;
    
    
    tempstack.push(start);
    queue.push(tempstack);
    
   
    // find the first word, delete it
    dict.remove(start);
    while(!queue.empty()) {
        // get the word off of the top of the front stack
        word = queue.front().top();
        for (it=dict.begin();it!=dict.end();++it) {
            if (wordcompare(word,*it)) {
                if (*it == end) {
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
                tempstack.push(*it);
                queue.push(tempstack);
                it = dict.erase(it);
            }
        }
        queue.pop();
    }
    // if a word ladder is not found, then do this
    if (outfile.is_open()) {
        outfile << "No Word Ladder Found!!";
    }
}

bool WordLadder::wordcompare(string word, string dictword) {
    int hits = 0;
    for (int i=0; i<5; i++) {
        if (word[i] == dictword[i]) { hits++; }
    }
    if (hits == 4) {
        return true;
    } else {
        return false;
    }
}

void WordLadder::printstack(stack<string> stack, ofstream &outfile) {
    
    int i = 0;
    vector<string> ladder;
    while (!stack.empty()) {
        ladder.push_back(stack.top());
        stack.pop();
        i++;
    }
    
    if (outfile.is_open()) {
        while (i!=0) {
            i--;
            outfile << ladder.at(i);
            cout << ladder.at(i);
            if (i!=0) {
                outfile << " ";
                cout << " ";
            }
        }
        cout << endl;
    }
    // if (outfile.is_open()) {
    //     while (!stack.empty()) {
            
    //         outfile << stack.top();
    //         cout << stack.top();
    //         stack.pop();
    //         if (!stack.empty()) {
    //             outfile << " ";
    //             cout << " ";
    //         }
    //     }
    // }
    //cout << endl;
}