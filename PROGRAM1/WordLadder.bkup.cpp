#include "WordLadder.h"


WordLadder::WordLadder(const string &file) {
    string word;
    ifstream infile;
    infile.open(file.c_str());
    if (infile.is_open()) {
        while (!infile.eof()) {
            getline(infile,word);
            dict.push_back(word.c_str());
        }
    }
    infile.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
    
    ofstream outfile;
    
    outfile.open(outputFile.c_str());
    
    // set up the stuff
    queue< stack<string> > queue;
    stack< string > stack, tempstack;
    list<string>::const_iterator it;
    vector<string> oneoffmatches;
    vector<string> used;
    unsigned i,interrupt;
    string word;
    char ltr;
    
    stack.push(start);
    queue.push(stack);
    
    // find the first word, delete it
    dict.remove(start);
    
    while(!queue.empty()) {
        stack = queue.front();
        queue.pop();
        word = stack.top();
        
        // find one-off matches
        
                interrupt = 0;
        for (i=0;i<word.length();++i) {
            word = stack.top();
            for (ltr = 'a'; ltr <= 'z'; ++ltr) {
                word[i]=ltr;
                for (it=dict.begin(); it!=dict.end(); it++) {
                    cout << "it=" << *it << " ";
                    interrupt++;
                    if (interrupt>4000) { 
                        cout << "Interrupting." << endl;
                        break;
                    }
                    if (it==dict.end()) {
                        cout << "\n\n\n\n\n\n\n\n\n\n\n\nEnd detected." << endl;
                    }
                    if (*it==word && !vectorcontains(used,word)) {
                        
                        oneoffmatches.insert(oneoffmatches.end(),word);
                        used.insert(used.end(),word);
                        // need a way to delete the word here
                    }
                }
            }
        }
        
        // lets do other stuff?
        
        for (i=0;i<oneoffmatches.size(); i++) {
            if (oneoffmatches.at(i)==end) {
                // match found
                stack.push(end);
                //print the stack
            } else {
                tempstack = stack;
                tempstack.push(oneoffmatches.at(i));
                queue.push(tempstack);
            }
        }
     
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