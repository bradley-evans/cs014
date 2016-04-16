

#include "WordLadder.h"

WordLadder::WordLadder(const string &file) {
    string word;
    ifstream infile;
    infile.open(file.c_str());
    if (infile.is_open()) {
        while (!infile.eof()) {
            getline(infile,word);
            /*
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
        cout << "Error opening input file" << endl;
        return;
    }
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    
    // set up the stuff
    queue< stack<string> > queue;
    stack< string > stack, tempstack;
    vector<string> nextwords,used;
    unsigned i;
    string word;
    bool startgood = false;
    bool endgood = false;
    
    ofstream outfile;
    outfile.open(outputFile.c_str());
    
    if (start == end) {
        outfile << start;
        return;
    }
    
    stack.push(start);
    queue.push(stack);
    
    // are the start and end words in the dictionary?
    for (list<string>::iterator it=dict.begin();it!=dict.end();++it) {
        if (*it == start) {
            startgood = true;
        } else if (*it == end) {
            endgood = true;
        }
    }
    if (!endgood || !startgood) {
        if (outfile.is_open()) {
            outfile << "Error. Start or end words are not in the dictionary.";
        }
        return;
    }          
    
    // find the first word, delete it
    dict.remove(start);
    
    while(!queue.empty()) {
        
        stack = queue.front();
        word = stack.top();
        
        // find one-off matches
        findnext(nextwords,used,word);
        
        // lets do other stuff?
        
        for (i=0;i<nextwords.size(); i++) {
            if (nextwords.at(i)==end) {
                // match found
                stack.push(end);
                //print the stack
                //cout << "Match found.";
                printstack(stack,outfile);
                return;
            } else {
                tempstack = stack;
                tempstack.push(nextwords.at(i));
                queue.push(tempstack);
            }
        }
        nextwords.clear();
        queue.pop();
    }
    // if a word ladder is not found, then do this
    if (outfile.is_open()) {
        outfile << "No Word Ladder Found!!";
        outfile.close();
    }
}

bool WordLadder::vectorcontains(vector<string> vec, string word) {
    unsigned i = 0;
    for (i=0;i<vec.size();++i) {
        if (vec.at(i)==word) {
            return true;
        }
    }
    return false;
}

void WordLadder::findnext(vector<string> &nextwords, vector<string> &used, string word) {

    string nextword;
    //int interrupt=0;
    unsigned i;
    char ltr;
    
    for (i=0;i<word.length();++i) {
        nextword = word;
        for (ltr = 'a'; ltr <= 'z'; ++ltr) {
            nextword[i]=ltr;
            for (list<string>::iterator it=dict.begin();it!=dict.end();++it) {
                if (*it == nextword && !vectorcontains(used,nextword)) {
                    nextwords.push_back(nextword);
                    used.push_back(nextword);
                }
            }
        }
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