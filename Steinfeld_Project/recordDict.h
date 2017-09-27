#ifndef RECORDDICT_H_INCLUDED
#define RECORDDICT_H_INCLUDED
#include "record.h"
#include "container.h"
using namespace std;

class recordDict{
public:
    //functions needed in all derived classes of recordDict
    virtual void insert(record *rec)=0; //inserts record
    virtual container* search(string s1){}; //searches for barcode
    virtual void remove(string s2)=0; //removes barcode
    virtual void toFile(string s3)=0; //writes info to file
    virtual ~recordDict(){}; //destructor
};

#endif // RECORDDICT_H_INCLUDED
