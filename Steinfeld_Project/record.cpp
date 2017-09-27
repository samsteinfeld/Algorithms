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


record::record(string c, string n, float p, int q){
    barcode = c;
    name = n;
    price = p;
    quantity = q;
}

string record::toString(){
    stringstream convert;
    string s;

    convert  << "Barcode: " << barcode << " Name: " << name << " Price: " << price << " Quantity: " << quantity;
    s = convert.str();
    return s;
}

float record::sell(int a){
    if ((quantity - a) > 0){
        quantity = quantity - a;
        return (a * price);
    }
    else
        return 0;
}

bool record::operator ==(record rec){
    if (barcode == rec.barcode)
        return true;
    else
        return false;
}

bool record::operator >(record rec){
    if (barcode > rec.barcode)
        return true;
    else
        return false;
}

bool record::operator <(record rec){
    if (barcode < rec.barcode)
        return true;
    else
        return false;
}

bool record::operator == (string s){
    if (barcode == s)
        return true;
    else
        return false;
}

bool record::operator >(string s){
    if (barcode > s)
        return true;
    else
        return false;
}

bool record::operator <(string s){
    if (barcode < s)
        return true;
    else
        return false;
}

string record::fileString(){
    stringstream convert;
    string s;

    convert <<  barcode << " " << name << " " << price << " " << quantity;
    s = convert.str();
    return s;
}

string record::getBarcode(){
    return barcode;
}


