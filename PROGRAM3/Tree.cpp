#include "Tree.h"

using namespace std;


// PRIVATE FUNCTIONS


void Tree::preOrder(Node *node) {
    
    if (node == 0) {
        return;
    }
    cout << node->small << ", ";
    if (node->left != 0) {
        preOrder(node->left);
    }
    if (node->middle != 0) {
        preOrder(node->middle);
    }
    if (!node->large.empty()) {
        cout << node->large << ", ";
    }
    if (node->right != 0) {
        preOrder(node->right);
    }
    return;
}
void Tree::inOrder(Node *node) {
    
    if (node == 0) {
        return;
    }
    if (node->left != 0) {
        inOrder(node->left);
    }
    cout << node->small << ", ";
    if (node->middle != 0) {
        inOrder(node->middle);
        
    }
    if (!node->large.empty()) {
        cout << node->large << ", ";
        
    }
    if (node->right != 0) {inOrder(node->right);}
    return;
}
void Tree::postOrder(Node *node) {
    
    if (node == 0) {
        return;
    }
    postOrder(node->left);
    if (!node->large.empty()) { cout << node->small << ", "; }
    postOrder(node->middle);
    postOrder(node->right);
    if ( node->large.empty()) { cout << node->small << ", "; }
    if (!node->large.empty()) { cout << node->large << ", "; }
}
void Tree::search(const string &, Node *) {
  
}
Node* Tree::locateLeaf(Node *node, string string) {
    // cout << "Finding leaf node...";
    if (root == 0) {
        // cout << "This is the root node!...";
        // this will be inserted into a root node
        return root;
    }
    if ((string == node->small) || (string == node->large)) {
        // cout << "Match found...";
        // then we have a data match
        return node;
    }
    if (node->left == 0 && node->right == 0) {
        // cout << "Leaf with SMALL[" << node->small << "] LARGE [" << node->large << "] found...";
        // we found a leaf! Wonderful.
        return node;
    }
    if (node->left != 0 || node->right != 0) {
        // then this node isn't a leaf, and things get complicated
        if (!node->small.empty() && node->large.empty()) {
            // cout << "Two node with children...";
            // then we are in a two-node with children
            if (string < node->small && node->left != 0) {
                // cout << "Checking left child...";
                // the string is smaller than the two node's value and a left child exists
                return locateLeaf(node->left, string);
            }
            if (string > node->small && node->right != 0) {
                // cout << "Checking right child...";
                // the string is larger than the two-node's value and a right child exists
                return locateLeaf(node->right, string);
            }
            // cout << "Something went wrong! two-node findNode";
            return 0;
        }
        if (!node->small.empty() && !node->large.empty()) {
            // cout << "Three node with children...";
            // then we are in a three node with children
            if (string < node->small && node->left != 0) {
                // cout << "Checking left child...";
                // the string is smaller than the three node's small value and a left child exists
                return locateLeaf(node->left, string);
            }
            if (string > node->large && node->right != 0) {
                // cout << "Checking right child...";
                // the string is larger than the two-node's large value and a right child exists
                return locateLeaf(node->right, string);
            }
            if (string > node->small && string < node->large && node->middle != 0) {
                // cout << "Checking middle child...";
                // the string is in between the three node's values and a middle child exists
                return locateLeaf(node->middle, string);
            }
            // cout << "Something went wrong! three-node findNode";
            return 0;
        }
    }
    return 0;
}
void Tree::addnode(Node *target, string string) {
    // simplest cases
    if (root == 0) {
        // cout << "Inserting at root node." << endl;
        // then this is a root node
        root = new Node(string);
        return;
    }
    if (target->small == string) {
        // cout << "Incrementing." << endl;
        // data match
        target->small_count++;
        return;
    }
    if (target->large == string) {
        // cout << "Incrementing." << endl;
        // data match
        target->large_count++;
        return;
    }
    // more complex cases
    if (!target->small.empty() && target->large.empty()) {
        // cout << "Inserting into a two-node...";
        // case: a two node
        if (string > target->small) {
            // cout << "Inserting case: new string larger than existing string in node...";
            // case: a two-node where the new string is larger than the existing data
            target->large = string;
            // cout << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
            return;
        } 
        if (string < target->small) {
            // cout << "Inserting case: new string smaller than existing string in node...";
            // case: a two node where the new string is smaller than the existing data
            target->large = target->small;
            target->small = string;
            // cout << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
            return;
        }
    }
    if (!target->small.empty() && !target->large.empty()) {
        // case: a three node
        if (target->parent == 0) {
             // cout << "A root three-node was detected, splitting root...";
             splitRoot(string);
             return;
        } else if (target->parent->isTwoNode()) {
        // cout << "Inserting into a three node...";
            // case: parent is a two node
            if (string < target->small) {
                // promote the small node and split
                // cout << "Inserting and promoting " << target->small << "...";
                addnode(target->parent, target->small);
                target->small = string;
                if (target->parent->middle == 0) {
                    // cout << "Creating a middle node...";
                    target->parent->middle = new Node(target->large);
                    target->parent->middle->parent = target->parent;
                } else if (target->parent->middle != 0) {
                    addnode(target->parent->middle, target->large);
                }
                target->large.clear();
                // cout << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
                return;
            }
            if (string > target->large) {
                // promote the large node and split
                // cout << "Inserting and promoting " << target->large << "...";
                addnode(target->parent, target->large);
                target->large = string;
                if (target->parent->middle == 0) {
                    // cout << "Creating a middle node...";
                    target->parent->middle = new Node(target->small);
                    target->parent->middle->parent = target->parent;
                } else if (target->parent->middle != 0) {
                    addnode(target->parent->middle, target->small);
                }
                target->small = string;
                target->large.clear();
                // cout << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
                return;
            }
            if (string > target->small && string < target->large) {
                // promote the new node and split
                // cout << "Promoting " << string << "...";
                addnode(target->parent, string);
                if (target->parent->middle == 0) {
                    // cout << "Creating a middle node...";
                    target->parent->middle = new Node(target->large);
                    target->parent->middle->parent = target->parent;
                } else if (target->parent->middle != 0) {
                    addnode(target->parent->middle, target->large);
                }
                target->large.clear();
                // cout << "Node is now [" << target->small << "] [" << target->large << "]" << endl;
                return;
            }
        }
        if (target->parent->isThreeNode()) {
            // cout << "Parent is a three node, splitting...";
            if (string < target->small) {
                // cout << "Promoting small...";
                addnode(target->parent, target->small);
                if (target->parent->middle == 0) {
                    target->parent->middle = new Node(target->large);
                    target->parent->middle->parent = target->parent;
                    // cout << "Adding " << string << "...";
                    target->small = string;
                    target->large.clear();   
                } else {
                    addnode(target->parent->middle,target->large);
                    target->small = string;
                    target->large.clear();
                }
                return;
            }
            if (string > target->large) {
                addnode(target->parent, target->large);
                if (target->parent->middle == 0) {
                    target->parent->middle = new Node(target->small);
                    target->parent->middle->parent = target->parent;
                    target->small = string;
                    target->large.clear();   
                } else {
                    addnode(target->parent->middle,target->large);
                    target->large.clear();
                }
                return;
            }    
            if (string > target->small && string < target->large) {
                
            }
        }
    }
}
void Tree::splitRoot(string string) {
    if (string < root->small) {
        // promote small to root
        // cout << "splitting root case: string less than root small...";
        root->parent = new Node(root->small);
        root->parent->left = root;
        root->parent->right = new Node(root->large);
        root->parent->right->parent = root->parent;
        root->small = string;
        root->large.clear();
        root = root->parent;
        // cout << "Root successfully split." << endl;
        return;
    }
    if (string > root->large) {
        // promote large to root
        // cout << "splitting root case: string greater than root large...";
        root->parent = new Node(root->large);
        root->parent->right = root;
        root->parent->left = new Node(root->small);
        root->parent->left->parent = root->parent;
        root->small = string;
        root->large.clear();
        root = root->parent;
        // cout << "Root successfully split with " << root->small << " as root." << endl;
        return;
    }
    if (string > root->small && string < root->large) {
        // promote new string to root
        // cout << "splitting root case: new string is middle value...";
        root->parent = new Node(string);
        root->parent->left = root;
        root->parent->right = new Node(root->large);
        root->parent->right->parent = root->parent;
        root->large.clear();
        root = root->parent;
        // cout << "Root successfully split with " << root->small << " as root." << endl;
        return;
    }
}

// PUBLIC FUNCTIONS
Tree::Tree() {
    root = 0;
}
Tree::~Tree() {

}
void Tree::insert(const string &string) {
    Node *target = 0;
    // cout << "Inserting [" << string << "]...";
    target = locateLeaf(root, string);
    addnode(target,string);
}
void Tree::preOrder( ) {
    preOrder(root);
}
void Tree::inOrder( ) {
    inOrder(root);
}
void Tree::postOrder( ) {
    postOrder(root);
}
void Tree::remove(const string &) {
  
}
bool Tree::search(const string &) {
  return false;
}