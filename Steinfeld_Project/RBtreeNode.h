#ifndef RBTREENODE_H_INCLUDED
#define RBTREENODE_H_INCLUDED
#include "container.h"
#include "record.h"
#include "cell.h"
enum RBcolor{Red, Black}; //colors of nodes
class RBtreeNode:public container{
    friend class RBRecordDict;
public:
    RBtreeNode(record *d); //initializes variable
    RBtreeNode(record *d, RBtreeNode *p); //initializes variables
protected:
    RBtreeNode *parent, *left, *right; //types of nodes
    RBcolor color; //color of node
};

#endif // RBTREENODE_H_INCLUDED
