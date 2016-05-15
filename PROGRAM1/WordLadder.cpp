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
    stack< string > stack, tempstack;
    vector<string> nextwords;
    unsigned i;
    string word;
    bool startgood = false;
    bool endgood = false;
    

    
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
        // get the word off of the top of the front stack
        word = stack.top();
        
        // find one-off matches
        findnext(nextwords,word,end);
        //cout << "One off matches for " << word << ": ";
        if (nextwords.size() != 0) {
            for (i=0;i<nextwords.size(); i++) {
                //cout << nextwords.at(i) << " ";
                if (nextwords.at(i)==end) {
                    // if the off by one word is the last word in the dictionary
                    // the ladder contains the entire stack -- complete and return.
                    stack.push(end);
                    //print the stack
                    //cout << "Match found.";
                    printstack(stack,outfile);
                    //cout << endl << "Complete!" << endl;
                    return;
                } else {
                    // otherwise, create a copy of the front stack and push the
                    // off by one word from dictionary
                    tempstack = stack;
                    tempstack.push(nextwords.at(i));
                    queue.push(tempstack);
                }
            }
            cout << endl;
        } else if (nextwords.size() == 0) {
            cout << endl;
        }
        nextwords.clear();
        // dequeue the front stack
        queue.pop();
    }
    // if a word ladder is not found, then do this
    if (outfile.is_open()) {
        outfile << "No Word Ladder Found!!";
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

void WordLadder::findnext(vector<string> &nextwords, string word, string end) {

    string nextword;
    list<string>::iterator it;
    unsigned i;
    char ltr;
    
    for (i=0;i<5;++i) {
        // Nextword is the word being manipulated.
        // Word is the original word we are looking for one-off matches for.
        nextword = word;
        for (ltr = 'a'; ltr <= 'z'; ++ltr) {
            // Change one letter in nextword.
            nextword[i]=ltr;
            for (it=dict.begin();it!=dict.end();++it) {
                // Check the modified nextword against the dictionary.
                if (*it == nextword) {
                    it = dict.erase(it);
                    nextwords.push_back(nextword);
                    if (nextword == end) {
                        return;
                    }
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