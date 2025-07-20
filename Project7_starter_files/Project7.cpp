// CRM in C++ <filename.cpp>
// EE 312 Project 7 submission by
// <Your Name Here>
// <Your EID>
// Slip days used: <0>
// Summer 2022
#include <stdio.h>
#include "UTString.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>
using namespace std;

void readString(UTString&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;
int customer = 0;
/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
    customer = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(UTString word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(UTString word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(UTString type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void TypeChecker(UTString* s, const int* quantity){
    if(*s == "Diapers"){
        if(*quantity >= 0){
            num_diapers += *quantity;    // update stores inventory of diapers
        }
    }
    if(*s == "Bottles"){
        if(*quantity >= 0){
            num_bottles += *quantity;    // update stores inventory of botltes
        }
    }
    if(*s == "Rattles"){
        if(*quantity >= 0){
            num_rattles += *quantity;    // updates stores inventory of rattles
        }
    }
}



void customerPurchase(UTString* name, UTString* typeOfItem, const int* quantityPurchased){
    if(*typeOfItem == "Bottles" ){
        if(*quantityPurchased <= num_bottles){
            database.operator[](*name).bottles += *quantityPurchased;
            num_bottles -= *quantityPurchased;
        }  else
        {
            cout << "Sorry " << name->c_str() << ", we only have " << num_bottles << " Bottles" << endl;
        }
    }
    if(*typeOfItem == "Rattles"){
        if(*quantityPurchased <= num_rattles){
            database.operator[](*name).rattles += *quantityPurchased;
            num_rattles -= *quantityPurchased;
        }else
        {
            cout << "Sorry " << name->c_str() << ", we only have " << num_rattles << " Rattles" << endl;
        }
    }
    if(*typeOfItem == "Diapers"){
        if(*quantityPurchased <= num_diapers){
            database.operator[](*name).diapers += *quantityPurchased;
            num_diapers -= *quantityPurchased;
        }else
        {
            cout << "Sorry " << name->c_str() << ", we only have " << num_diapers << " Diapers" << endl;
        }
    }
}
void isValidCustomer(int* quantity, UTString* name, UTString* typeOfItem){
    int *inventoryCount = selectInventItem(*typeOfItem);
    if(inventoryCount != nullptr && *quantity > 0 && *inventoryCount >= *quantity){
        if(!database.isMember(*name)){ // if customer is not in database
            customer++;
            database.operator[](*name);
        }
    }
    customerPurchase(name,typeOfItem, quantity);

}


void processPurchase() {
    UTString name;
    readString(name);
    UTString typeOfItem;
    readString(typeOfItem);
    int quantity;
    readNum(quantity);
    isValidCustomer(&quantity,&name,&typeOfItem);
}

void processSummarize() {
    Customer botMax;
    cout << "There are " << num_bottles << " Bottles, " << num_diapers << " Diapers and " << num_rattles << " Rattles in inventory" << endl;
    cout << "we have had a total of " << customer << " different customers" << endl;

    if(findMax("Bottles") != nullptr){
        botMax = database.operator[](findMax("Bottles")->name);
    }
    if(findMax("Bottles") != nullptr){
        cout << findMax("Bottles")->name.c_str() << " has purchased the most Bottles (" << botMax.bottles << ")" << endl;
    } else {
        cout << "no one has purchased any Bottles" << endl;
    }
    if(findMax("Diapers") != nullptr){
        botMax = database.operator[](findMax("Diapers")->name);
    }
    if(findMax("Diapers") != nullptr){
        cout << findMax("Diapers")->name.c_str() << " has purchased the most Diapers (" << botMax.diapers << ")" << endl;
    } else {
        cout << "no one has purchased any Diapers" << endl;
    }
    if(findMax("Rattles") != nullptr){
        botMax = database.operator[](findMax("Rattles")->name);
    }
    if(findMax("Rattles") != nullptr){
        cout << findMax("Rattles")->name.c_str() << " has purchased the most Rattles (" << botMax.rattles << ")" << endl;
    } else {
        cout << "no one has purchased any Rattles" << endl;
    }

}

void processInventory() {
    UTString typeOfItem;
    readString(typeOfItem);
    int quantity;
    readNum(quantity);
    TypeChecker(&typeOfItem,&quantity);
}



