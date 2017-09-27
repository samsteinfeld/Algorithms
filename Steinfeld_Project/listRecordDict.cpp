#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<string>
#include "record.h"
#include "container.h"
#include "recordDict.h"
#include "cell.h"
#include "listRecordDict.h"

using namespace std;

listRecordDict::listRecordDict(){
    first = NULL;
    last = NULL;
}

void listRecordDict::insert(record *in){
    cell *newCell;
    newCell = new cell(in);

    if (first == NULL)
    {
        first = newCell;
        last = newCell;
    }
    else
    {
        last -> next = newCell;
        newCell -> prev = last;
        last = newCell;
    }
}
cell* listRecordDict::search(string w){
    cell *c;
    c = first;

    while(c != NULL){
        if ( c->data->operator==(w) ){
            return c;
        }
        else
            c = c->next;
    }
    return NULL;
}

void listRecordDict::remove(string w){
    cell *todelete;
    todelete = search(w);
    while(todelete != NULL){
        if ( todelete->data->operator==(w) ){
            delete todelete;
        }
        else if (todelete == first && first == last){
            first = NULL;
            last = NULL;
            delete todelete;
        }
        else if(todelete == first && first->data!=NULL){
           first = first->next;
           first->prev = NULL;
           delete todelete;
        }

        else if(todelete == last && first->data!=NULL){
            last = last->prev;
            last->prev = NULL;
            delete todelete;
        }
        else{
            todelete -> prev ->next = todelete->next;
            todelete->next ->prev = todelete->prev;
            delete todelete;
        }
    }
}

void listRecordDict::toFile(string filename){
    ofstream myfile;
    myfile.open(filename.c_str());
    cell *c = first;

    while(c != NULL){
        myfile << (c->data)->fileString() <<endl;
        c = c->next;
    }
    myfile.close();
}

listRecordDict::~listRecordDict(){
    cell *temp;
    while (first != NULL)
    {
        temp = first;
        first = first->next;
        delete temp;
    }
    last = NULL;
}


