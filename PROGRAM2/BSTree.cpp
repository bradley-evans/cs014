#include "BSTree.h"
using namespace std;



void BinarySearchTree::insert(const string &newdata) {
/* 
Insert an item into the binary search tree. Be sure to keep the binary 
search tree properties. When an item is first inserted into the tree the
count should be set to 1. When adding a duplicate string (case 
sensitive), rather than adding another node, the count variable should 
just be incremented.
*/
    if (root == 0) {
        // the tree is empty, put new node at root.
        root = new Node(newdata);
        root->inc();
        return;
    } else {
        addnode(root,newdata);
    }
}

bool BinarySearchTree::search(const string &searchstr) const {
/*
Search for a string in the binary search tree. It should return true if
the string is in the tree, and false otherwise.
*/

return false;
}

string BinarySearchTree::largest() const {
    return largest_recursive(root);
}
string BinarySearchTree::largest_recursive(Node* node) const {
/* 
Find and return the largest value in the tree. Return an empty string if
the tree is empty.
*/
    if (root == 0) {
        return "";
    }
    if (node->right == 0) {
        return node->data;
    }
    return largest_recursive(node->right);
}
string BinarySearchTree::smallest() const {
    return smallest_recursive(root);
}
string BinarySearchTree::smallest_recursive(Node* node) const {
/*
Find and return the smallest value in the tree. Return an empty string
if the tree is empty.
*/
    if (root == 0) {
        return "";
    }
    if (node->left == 0) {
        return node->data;
    }
    return smallest_recursive(node->left);

}
int BinarySearchTree::height (const string &searchstr) const {
/*
Compute and return the height of a particular string in the tree. The 
height of a leaf node is 0 (count the number of edges on the longest 
path). Return -1 if the string does not exist.
*/

return 0;
}
void BinarySearchTree::remove(const string &searchstr) {
/*
Remove a specified string from the tree. Be sure to maintain all binary
search tree properties. If removing a node with a count greater than 1,
just decrement the count, otherwise, if the count is simply 1, remove 
the node. You MUST follow the remove algorithm shown in the slides and 
discussed in class or else your program will not pass the test 
functions. When removing, if removing a leaf node, simply remove the 
leaf. Otherwise, if the node to remove has a left child, replace the 
node to remove with the largest string value that is smaller than the 
current string to remove (i.e. find the largest value in the left 
subtree of the node to remove). If the node has no left child, replace 
the node to remove with the smallest value larger than the current 
string to remove (i.e. find the smallest value in the right subtree of 
the node to remove).
*/
    if (root == 0) {
        // the tree is empty, nothing to see here.
        // otherwise, move on to the recursive private helper function
    }
    remove_search(root,searchstr);
}
void BinarySearchTree::remove_search(Node* node, const string &string) {
    if (node->data == string) {
        // we found the node for deletion
        remove_node(node);
    } else if (node->data < string) {
        if (node->right == 0) {
            // dead end found
            return;
        } else {
            remove_search(node->right, string);
        }
    } else if (node->data > string) {
        if (node->left == 0) {
            // dead end found
            return;
        } else {
            remove_search(node->left, string);
        }
    }
}
void BinarySearchTree::remove_node(Node* node) { // actually delete a node
    // there are five cases.
    Node *swapNode;
    //case 1: a leaf
    if (node->left == 0 && node->right == 0) {
        if (node->data < node->up->data) {
            // then this is the right child and a leaf
            node->up->right = 0;
            delete node;
        } else {
            // then it must be the left child
            node->up->left = 0;
            delete node;
        }
    }
    // case 2: a node with one left child
    if (node->left != 0 && node->right == 0) {
        swapNode = maxNode(node->left);
        swapNode->up->right = 0;
        node->data = swapNode->data;
        delete swapNode;
    }
    // case 3: a node with one right child
    if (node->left == 0 && node->right != 0) {
        swapNode = minNode(node->right);
        swapNode->up->left = 0;
        node->data = swapNode->data;
        delete swapNode;
    }
    // case 4: a node with two children
    if (node->left != 0 && node->right != 0) {
        // treat it as a node with only a right child
        swapNode = minNode(node->right);
        swapNode->up->left = 0;
        node->data = swapNode->data;
        delete swapNode;
    }
}
Node* BinarySearchTree::minNode(Node* node) {
    if (node->left == 0) {
        return node;
    }
    return minNode(node->left);
}
Node* BinarySearchTree::maxNode(Node* node) {
    if (node->right == 0) {
        return node;
    }
    return maxNode(node->right);
}

void BinarySearchTree::addnode(Node* node, string string) {
    if (node->data < string) {
        if (node->right != 0) {
            addnode(node->right, string);
        } else {
            node->right = new Node(string);
            node->right->up = node;
            node->right->inc();
        }
    } else if (node->data > string) {
        if (node->left != 0) {
            addnode(node->left, string);
        } else {
            node->left = new Node(string);
            node->left->up = node;
            node->left->inc();
        }
    } else {
        node->inc();
    }
}


void BinarySearchTree::preOrder() {
    preOrder_recursive(root);
}
void BinarySearchTree::preOrder_recursive( Node* curr ) {

    if (curr == 0) {
          return;
    }
    cout << curr->data << " (" << curr->currcount() << "), ";
    preOrder_recursive(curr->left);  
    preOrder_recursive(curr->right);

}

void BinarySearchTree::inOrder() {
    inOrder_recursive(root);
}
void BinarySearchTree::inOrder_recursive( Node* curr ) {
    if ( curr == 0 ) {
        return;
    }
    inOrder_recursive(curr->left);
    cout << curr->data << " (" << curr->currcount() << "), ";
    inOrder_recursive(curr->right);
}

void BinarySearchTree::postOrder() {
    postOrder_recursive(root);
}
void BinarySearchTree::postOrder_recursive( Node* curr ) {

    if (curr == 0) {
          return;
    }
    postOrder_recursive(curr->left);  
    postOrder_recursive(curr->right);
    cout << curr->data << " (" << curr->currcount() << "), ";

}

