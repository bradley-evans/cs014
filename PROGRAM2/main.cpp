#include <iostream>
#include <string>
#include "BSTree.h"
using namespace std;

int main() {
    
    BinarySearchTree tree;
    string currstring;
    int i;
    
    for (i=0;i<20;i++) {
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
    cout << "Deleting 'quebec' ..." << endl;
    tree.remove("quebec");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Deleting 'charlie' ..." << endl;
    tree.remove("charlie");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Deleting 'juliet' ..." << endl;
    tree.remove("juliet");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Deleting 'epsilon' ..." << endl;
    tree.remove("epsilon");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    cout << "Deleting 'golf' ..." << endl;
    tree.remove("golf");
    cout << "In Order: ";
    tree.inOrder();
    cout << endl;
    /*
    cout << "Deleting 'alpha' ..." << endl;
    tree.remove("alpha");
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
    cout << "Deleting 'quebec' ..." << endl;
    tree.remove("quebec");
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
    */
    
    
}