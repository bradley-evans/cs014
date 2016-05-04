#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;
  void preOrder(Node *node);
  void inOrder(Node *node);
  void postOrder(Node *node);
  void search(const string &, Node *);

public:
  Tree( );
  ~Tree( );
  void insert(const string &);
  void preOrder( );
  void inOrder( );
  void postOrder( );
  void remove(const string &);
  bool search (const string &);

private:
  // Add additional functions/variables here
    
};

#endif
