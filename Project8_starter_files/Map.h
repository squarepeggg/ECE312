//
// Created by Matthew Olan on 11/28/23.
//

#ifndef PROJECT8_STARTER_FILES_MAP_H
#define PROJECT8_STARTER_FILES_MAP_H



#include <map>
#include <sstream>
#include <iostream>
#include <string>
#include "Parse.h"
#include <fstream>
using namespace std;

class VariableTracker
{

private:
    map<string, int> variables;

public:
    ~VariableTracker() { variables.clear(); }
    void print() {
        for (auto s : variables) {
            cout << "Variable " << s.first << ": " << s.second << endl;
        }
    }

    void newVar(string& var, int value){
        if(!variables.count(var)) {
            variables.emplace(var, value);
//            cout << "Key " << var <<":" << value << " is added to map." << endl;
//        } else {
//            cout << "Key " << var << " exists." << endl;
//        }
        }
    }

    void clear(){
        variables.clear();
    }

    void set(string& var, int value){
        if(variables.count(var)){
            variables.at(var) = value;
            cout << "Var is now " << value << endl;
        } else {
            cout << "variable " << var << " is not declared." << endl;
        }

    }

    int Getter(){
        return variables.at(next_token());
    }
    int Getter(const string& variableName){
        return variables.at(variableName);
    }
    // You need to write at least two functions:
    /*

    1)  Add a new variable to the list of variables
            - you should be able to provide a value



    2)  Update a variable's existing value
            - if the variable doesn't exist, print some error

    Bonus: implement functionality to set one variable's value to another variable's value!

    */

};

#endif //PROJECT8_STARTER_FILES_MAP_H
