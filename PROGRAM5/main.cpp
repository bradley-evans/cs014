/*
Program by: Bradley Evans, 861236473
bevan006

June 2nd, 2016
*/

#include <iostream>
#include <string>
#include "Jug.h"

using namespace std;

int main() {
    string solution;
    /* Take in some input. Make the new jug object */
    int inputs[9];
    for (int i=0;i<9;i++) {
        cin >> inputs[i];
    }
    Jug head(   inputs[0], inputs[1], inputs[2], inputs[3], 
             inputs[4], inputs[5], inputs[6], inputs[7], 
             inputs[8]);
    if (head.solve(solution) == 0) {
        // the output is empty
        cout << solution << endl;
    } else if (head.solve(solution) == -1) {
        // the output is erroneous
        cout << "Error 3" << endl;
    } else if (head.solve(solution) == 1) {
        // the solution is good.
        cout << solution << endl;
    }
    
    
    //cout << "Run complete." << endl;
}


/* helper function definitions */