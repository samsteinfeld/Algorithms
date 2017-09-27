#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED
#include "container.h"
#include "record.h"

class cell:public container{
    friend class listRecordDict;
    friend class inventory;
    friend class RBtreeNode;
    friend class HTrecordDict;
protected:
    cell *prev; //previous cell
    cell *next; //next cell
public:
    //constructors that initialize values based on what is being inputted
    cell(record *d);
    cell(record *d, cell *p);
    cell(record *d, cell *p, cell *r);
};

#endif // CELL_H_INCLUDED
