#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include"inventory.h"
#include "cell.h"
#include "listRecordDict.h"
#include "recordDict.h"
#include "container.h"
#include "RBRecordDict.h"
#include "HTrecordDict.h"
#include "record.h"
using namespace std;

//Sam Steinfeld

const int MAX = 10000;//Max size of hash table
inventory::inventory(recordDict *rd){
    dict = rd;
}

inventory::~inventory(){
    delete dict;
}

void inventory::search(string s){
    container *searchResult;

    searchResult = dict->search(s);

    if (searchResult == NULL)
        cout << "Barcode not found"<<endl;
    else
        cout << searchResult->data->toString()<<endl;

}

void inventory::sell(string s, int a){
    container *searchResult;
    float itemSold; //item we are selling
    searchResult = dict->search(s);
    itemSold =  searchResult->data->sell(a);
    if (searchResult == NULL)
        cout << "Barcode not found";
    else {
        if (itemSold == 0){
            cout << "That quantity of item " << searchResult->data->barcode <<" sold, zero remain."<<endl;
        }
        else //tells you how many you sold and the amount that remain
            cout << a << " of item "<< searchResult->data->barcode << " sold, " << searchResult->data->quantity << " remain."<<endl;
    }
}

void inventory::add(record *rec){
    dict->insert(rec);
}

void inventory::remove(string s){
    dict->remove(s);
}

void inventory::readFile(string filename){
    ifstream myfile;
    myfile.open(filename.c_str());
    record *rec;
    string barcode, name;
    float price;
    int quantity;

    myfile >> barcode;
    while(!myfile.eof()){
        myfile >> name;

        myfile >> price;

        myfile >> quantity;

        rec = new record(barcode, name, price, quantity); //initialize values using constructor
        add(rec); //add record to inventory
        myfile >> barcode;
    }
    myfile.close();
}

void inventory::toFile(string filename){
    dict->toFile(filename);
}

int main(){
    int type = 0; //method of accomplishing tasks for updating/adding/removing inventory
    cout << "Enter (1) if you'd like to use a linked list" << endl << "(2) for a red-black tree"<< endl << "(3) for a hash table" << endl;
    cin >> type;
    inventory *myinv; //inventory created depending on what method is being used
    int size = MAX; //max size for hash table

    //initialize constructor depending on method chosen
    if(type==1)
        myinv = new inventory(new listRecordDict);
    if(type==2)
        myinv = new inventory(new RBRecordDict);
    if(type==3){
        myinv = new inventory(new HTrecordDict(size));
    }

    string filename;
    int num = -1;
    string c, n; //barcode and name respectively
    float p; //price
    int q; //quantity
    record *rec; //needed to get values for barcode, name, price, and quantity

    while(num !=0){
        cout << "Would you like to:"<<endl<<"(1) Read a file"<<endl<< "(2) Manually add an entry"<<endl;
        cout<<"(3) Enter barcode to search for"<<endl<<"(4) Sell an item"<<endl<<"(5) Remove barcode from inventory"<<endl;
        cout<< "(6) Write inventory to file"<<endl<<"(0) Delete inventory and end program"<<endl;
        cin >> num;

        if(num == 1){ //transfer inventory from file to method being used
            cout << "Please enter file name to read:" << endl;
            cin >> filename;
            myinv->readFile(filename);
        }

        else if (num == 2){ //add data to inventory
            cout << "Please enter barcode, name, price, and quantity to add:" << endl;
            cin>>c;
            cin>>n;
            cin>>p;
            cin>>q;
            rec = new record(c,n,p,q);
            myinv->add(rec);

        }

        else if (num == 3){ //search for an item based on barcode
            cout << "Please enter a barcode to search for:"<<endl;
            cin >> c;
            myinv->search(c);
            cout << endl;
        }

        else if (num == 4){ //remove specified quantity of item from inventory
            cout << "Please enter a barcode and a quantity to sell:"<<endl;
            cin >> c;
            cin >> q;
            myinv->sell(c, q);
            cout << endl;
        }

        else if (num == 5){ //remove specified item from item from inventory
            cout << "Please enter a barcode to remove:"<<endl;
            cin>>c;
            myinv->remove(c);
        }
        else if (num == 6){ //create specified file name
            cout << "Please enter a filename to create:"<<endl;
            cin >> filename;
            myinv->toFile(filename);
        }

        else if(num == 0)//delete inventory
            delete myinv;

        else
            cout << "Sorry, option not recognized, please try again" << endl;
    }

    return 0;
}
