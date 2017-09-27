#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED
#include "recordDict.h"


class inventory{
protected:
    recordDict *dict;
public:
    inventory(recordDict *rd); //constructor that sets record *dict, a protected member, equal to recordDict *rd
    ~inventory(); //destructor that deletes inventory
    void search(string s); //looks to see if requested barcode is in inventory
    void sell(string s2, int a); //sells specified quantity of item
    void add(record *rec); //inserts new record into inventory
    void remove(string s3); //removes record from inventory
    void readFile(string filename); //reads inventory from a file
    void toFile(string filename); //converts current inventory into a file
};


#endif // INVENTORY_H_INCLUDED
