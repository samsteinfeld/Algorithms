#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include "RBtreeNode.h"
#include "container.h"
#include "cell.h"
using namespace std;

//constructors initialize appropriate values to variables

RBtreeNode::RBtreeNode(record *d){
    data = d;
    parent = NULL;
    left = NULL;
    right = NULL;
    color = Red;
}

RBtreeNode::RBtreeNode(record *d, RBtreeNode *p){
    data = d;
    parent = p;
    left = NULL;
    right = NULL;
    color = Red;
}




