#ifndef RECORD_H_INCLUDED
#define RECORD_H_INCLUDED
using namespace std;
class record{
    friend class listRecordDict;
    friend class inventory;
    friend class HTrecordDict;
protected:
    //variables that will be part of inventory
    string barcode;
    string name;
    float price;
    int quantity;
public:
    record(string c, string n, float p, int q); //initializes values of variable
    string toString(); //converts data into a string
    float sell(int a); //sell specified amount of item
    string fileString();//converts data into a string
    string getBarcode(); //retrieves barcode without globally changing the value
    //overloading operators
    //compare barcode with record or string and return true or false
    bool operator ==(record);
    bool operator >(record);
    bool operator <(record);
    bool operator ==(string s1);
    bool operator >(string s2);
    bool operator <(string s3);

};


#endif // RECORD_H_INCLUDED
