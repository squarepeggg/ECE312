// CRM in C++ <filename.cpp>
// EE 312 Project 7 submission by
// <Your Name Here>
// <Your EID>
// Slip days used: <0>
// Summer 2022
#include <iostream>
#include <cassert>
#include "UTString.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;


Customer::Customer(UTString name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) { // done, please do not edit
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}



void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](UTString name) { // not done, your effort goes here
    // if customer is in data base return pointer
    for(int i = 0; i < this->length; i++){
        if(this->data[i].name == name) {
            return this->data[i];
        }
    }
    // if customer is not in data base
        // if length == capacity then we double capacity
    if(this->length == this->capacity){
        Customer* temp = new Customer [this->capacity * 2];
        for(int i = 0; i < this->length; i++){
            temp[i] = this->data[i];      // 1 to 1 transfer of data
        }
        delete[] this->data;
        this->data = temp;
        this->capacity *= 2;
        this->data[this->length] = Customer(name);
        this->length++;
    } else{
        this->data[this->length] = Customer(name);
        this->length++;
    }
    return this->data[this->length - 1];
}

bool CustomerDB::isMember(UTString name) { // not done, your effort goes here
    for(int i = 0; i < this->length; i++){
        if(name == this->data[i].name){
            return true;
        }
    }
    return false;
}
