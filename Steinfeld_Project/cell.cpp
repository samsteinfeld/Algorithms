#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include "record.h"
#include "container.h"
#include "recordDict.h"
#include "cell.h"

using namespace std;
//constructors initialize variables to respective inputted values, or NULL if not inputted
cell::cell(record *d){
    data = d;
    prev = NULL;
    next = NULL;
}

cell::cell(record *d, cell *p){
    data = d;
    prev = p;
    next = NULL;
}

cell::cell(record *d, cell *p, cell *r){
    data = d;
    prev = p;
    next = r;
}

