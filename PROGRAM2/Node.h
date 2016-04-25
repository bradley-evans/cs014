class Node {
    private:
        string data;         // the data held in this node
        Node *left;  // next node
        Node *right; // previous node
        Node *up;    // parent node
        int count;      // counts existance of duplicates
        
    public:
        void inc();     // mutator, increments count
        void dec();     // mutator, decriment count
        int currcount();// accessor, returns count
        Node() {        // default constructor
            this->count = 0;
            this->left = 0;
            this->right = 0;
        }
        Node(string data);
       
};
/*  Leaving some templates intact.
template <class A_Type> A_Type calc<A_Type>::multiply(A_Type x,A_Type y)
{
  return x*y;
}
template <class A_Type> A_Type calc<A_Type>::add(A_Type x, A_Type y)
{
  return x+y;
}
*/