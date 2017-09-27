#ifndef LISTRECORDDICT_H_INCLUDED
#define LISTRECORDDICT_H_INCLUDED
#include "recordDict.h"
#include "cell.h"
#include "record.h"
using namespace std;
class listRecordDict:public recordDict{
friend class inventory;
friend class HTrecordDict;
protected:
    cell *first; //first cell in linked list
    cell *last; //last cell
public:
    listRecordDict(); //sets first and last to NULL
    void insert(record *in); //inserts record in linked list
    cell* search(string w); //searches for barcode in inventory
    void remove(string w); //removes item by looking for barcode in inventory
    void toFile(string filename); //writes inventory to a file
    ~listRecordDict(); //deletes linked list
};

#endif // LISTRECORDDICT_H_INCLUDED
