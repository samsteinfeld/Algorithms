#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include<random>
#include<stdlib.h>
#include "recordDict.h"
#include "listRecordDict.h"
#include "cell.h"
#include "HTrecordDict.h"
#include "record.h"
using namespace std;

int HTrecordDict::generateRandomKey(){
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1,size);
    return distribution(generator);
}

HTrecordDict::HTrecordDict(int length){
    size = length;
    cell **A = new cell*[size];
    H = A; //create copy of hash table
    for (int i = 0; i < size; i++)
        H[i] = NULL;
    a = generateRandomKey();
    b = generateRandomKey();
}

HTrecordDict::~HTrecordDict(){
    cell *temp; //delete all data from hashtable using temporary variable
    for (int i = 0; i<size; i++){
        temp = H[i];
        while (temp!=NULL){
            delete temp;
            temp = temp->next;
        }
    }
    delete H;
}

int HTrecordDict::hash(string s){
    int h=b;
    for (int i = 0; i < s.length(); i++)
        h = h + int(s[i]);
    return  h % size;
}

string HTrecordDict::toString(int x){
    stringstream convert;
    string s;
    convert << x;
    s = convert.str();
    return s;
}

void HTrecordDict::insert(record *in){
    int h = hash(in->getBarcode()); //hash barcode
    cell *newCell;
    newCell = new cell(in);
    if(H[h]==NULL){
        H[h] = newCell;
    }

    else{
        H[h]->next = newCell;
        newCell -> prev = H[h];
        H[h] = newCell;
    }
}

cell* HTrecordDict::search(string w){
    int h = hash(w);
    cell *c;
    c = H[h];

    while(c != NULL){
        if ( c->data->operator==(w) ){
            return c;
        }
        else
            c = c->next;
    }
    return NULL;
}

void HTrecordDict::remove(string w){
    int h = hash(w); //hash string(barcode)
    cell *todelete; //create temporary variable to delete
    todelete = H[h];
    while (todelete!=NULL){
        if(todelete->data->operator==(w))
            delete todelete;
        else
            todelete = todelete->next;
    }
}

void HTrecordDict::toFile(string filename){
    ofstream myfile;
    myfile.open(filename.c_str());
    cell *temp;

    for (int i = 0; i<size; i++){
        temp = H[i];
        while (temp!=NULL){
            myfile << (temp->data)->fileString() <<endl;
            temp = temp->next;
        }
    }
    myfile.close();
}

