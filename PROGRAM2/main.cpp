#include <iostream>
#include <string>
#include "BSTree.h"
using namespace std;

int main() {
    
    BinarySearchTree tree;
    string currstring;
    int i;
    
    for (i=0;i<15;i++) {
        cin >> currstring;
        tree.insert(currstring);
        cout << "Added " << currstring << " to tree." << endl;
    }
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Pre Order: ";
    tree.preOrder();
    cout << endl;
    cout << "Post Order: ";
    tree.postOrder();
    cout << endl;
    cout << "Largest item in tree: ";
    cout << tree.largest() << endl;
    cout << "Smallest item in tree: ";
    cout << tree.smallest() << endl;
    cout << "Deleting 'juliet' ..." << endl;
    tree.remove("juliet");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Pre Order: ";
    tree.preOrder();
    cout << endl;
    cout << "Post Order: ";
    tree.postOrder();
    cout << endl;
    cout << "Largest item in tree: ";
    cout << tree.largest() << endl;
    cout << "Smallest item in tree: ";
    cout << tree.smallest() << endl;
    
    
}