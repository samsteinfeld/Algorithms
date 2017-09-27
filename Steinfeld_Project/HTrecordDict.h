#ifndef HTRECORDDICT_H_INCLUDED
#define HTRECORDDICT_H_INCLUDED
#include "recordDict.h"
#include "cell.h"
#include "record.h"

class HTrecordDict:public recordDict{
protected:
    int size; //size of hash table
    int a, b; //random numbers
    cell **H; //hashtable
    int generateRandomKey(); //generates a random number, which will be the key
    int hash(string s); //hashes the inputted string
    string toString(int x); //converts current int into a string
public:
    HTrecordDict(int length); //sets all values in hashtable to null and sets a and b to random keys
    ~HTrecordDict(); //deletes all data from hastable
    void insert(record *in); //inserts record in linked list in an index of hashtable
    cell *search(string w); //searches for barcode in linked list in an index of hashtable
    void remove(string w); //searches from barcode in linked list in an index of hashtable
    void toFile(string filename); //writes inventory to file
};


#endif // HTRECORDDICT_H_INCLUDED
