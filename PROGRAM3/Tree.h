#ifndef __TREE_H
#define __TREE_H

#include <string>
#include <iostream>

#include "Node.h"

class Tree {
private:
  Node *root;
  void preOrder(Node *node);
  void inOrder(Node *node);
  void postOrder(Node *node);
  void search(const std::string &, Node *);
  Node* locateLeaf(Node *, std::string);
  void addnode(Node*, std::string);
  void splitRoot(std::string);

public:
  Tree( );
  ~Tree( );
  void insert(const std::string &);
  void preOrder( );
  void inOrder( );
  void postOrder( );
  void remove(const std::string &);
  bool search (const std::string &);

private:
  // Add additional functions/variables here
    
};

#endif
