#ifndef RBRECORDDICT_H_INCLUDED
#define RBRECORDDICT_H_INCLUDED
#include "recordDict.h"
#include "RBtreeNode.h"
class RBRecordDict:public recordDict{
protected:
    RBtreeNode *root; //root
public:
    RBRecordDict(); //sets root to NULL
    ~RBRecordDict(); //calls destroy_tree()
    void insert(record *in); //inserts record in tree
    RBtreeNode *search(string key); //searches for barcode in tree
    void remove(string r); //removes barcode from tree
    void toFile(string filename); //writes inventory to a file
protected:
    void destroy_tree(RBtreeNode *leaf); //deletes all leaves in tree
    void insert_h(RBtreeNode *n, record *in); //he;per function for insert()
    void insert_fixup(RBtreeNode *n); //helper function for insert()
    RBtreeNode *grandparent(RBtreeNode *n); //creates grandparent node
    RBtreeNode *uncle(RBtreeNode *n); //creates uncle node
    RBtreeNode *sibling(RBtreeNode *n); //creates sibling node
    RBtreeNode *color(RBtreeNode *n); //creates color node
    void rotate_right(RBtreeNode *n); //rotates tree to the right on given pivot point
    void rotate_left(RBtreeNode *n);  //rotates tree to left on given pivot point
    RBtreeNode *search_help(string key, RBtreeNode *leaf); //helper function for search()
    void inOrderTraversal(); //traverses inventory in order
    void inOrder_help(RBtreeNode *leaf); //helper function for inOrderTraversal()
    RBtreeNode *successor(RBtreeNode *c); //successor node
    void remove_fixup(RBtreeNode *n); //helper function for remove()
    RBcolor Color(RBtreeNode *n); //returns Color of node and checks to see if node is NULL
    ofstream myfile; //creates myfile globally so it can be used by multiple functions
    void postOrderTraversal(); //traverses inventory in post order
    void preOrderTraversal(); //traverses inventory in pre order
    void preOrder_help(RBtreeNode *leaf); //helper function for preOrderTraversal()
    void postOrder_help(RBtreeNode *leaf); //helper function for postOrderTraversal()
};


#endif // RBRECORDDICT_H_INCLUDED
