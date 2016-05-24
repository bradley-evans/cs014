#include <iostream>
#include <fstream>

using namespace std;

int main () {
    ifstream file;
    string string;
    file.open("input1");
    while (!file.eof()) {
        file >> string;
        cout << string << endl;
    }
}