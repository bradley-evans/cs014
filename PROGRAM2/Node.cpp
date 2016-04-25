#include "Node.h"

template<typename T>
Node::Node(string data) {
            this->count = 0;
            this->left = 0;
            this->right = 0;
            this->data = data;
}

template<typename T>
void Node<T>::inc() {     // mutator, increments count
    this->count++;
}

template<typename T>
void Node<T>::dec() {     // mutator, decriment count
    this->count--;
}

template<typename T>
int Node<T>::currcount() {              // accessor, returns count
    return this->count;
}