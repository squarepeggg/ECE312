//
// Created by Matthew Olan on 11/27/23.
//
#include <stdlib.h>
#include <iostream>
#include "Parse.h"
#include "exptree.h"
#include "Map.h"
using namespace std;
vector<Node*> stackFrame;
VariableTracker Storage;
// Friend said
// 1.) put all values of prefix expression into a vector object
// 2.) pass vector to experssion tree
// 3.) evaluate (compute) tree


bool operationChecker(string text){
    if(text == "+"){
        return false;
    }else if(text == "-"){
        return false;
    }else if(text == "/"){
        return false;
    }else if(text == "*"){
        return false;
    }else if(text == "&&"){
        return false;
    }else if(text == "||"){
        return false;
    }else if(text == ">"){
        return false;
    }else if(text == "<"){
        return false;
    }else if(text == "=="){
        return false;
    }else if(text == "!="){
        return false;
    }else if(text == ">="){
        return false;
    }else if(text == "<="){
        return false;
    }else if(text == "~"){
        return false;
    }else if(text == "!"){
        return false;
    }
    else{
        return true;
    }
}
string AWPerator(string text){
     if(text == "+"){
        return "+";
    }else if(text == "-"){
        return "-";
    }else if(text == "/"){
        return "/";
    }else if(text == "*"){
        return "*";
    }else if(text == "&&"){
        return "&&";
    }else if(text == "||"){
        return "||";
    }else if(text == ">"){
        return ">";
    }else if(text == "<"){
        return "<";
    }else if(text == "=="){
        return "==";
    }else if(text == "!="){
        return "!=";
    }else if(text == ">="){
        return ">=";
    }else if(text == "<="){
        return "<=";
    }else if(text == "~"){
        return "~";
    }else if(text == "!"){
        return "!";
    }
     return "";
}



void expression(){
    read_next_token();
    string text = next_token();
    Node* node;
    while(next_token_type != END && (next_token_type == NUMBER || next_token_type == SYMBOL || next_token_type == NAME)){
        bool condition = operationChecker(text);
        string awperator = AWPerator(text);
        int newNodeVal = token_number_value;
        if(next_token_type == NAME){
            newNodeVal = Storage.Getter();
        }
            node = new Node(condition,newNodeVal,awperator);
        stackFrame.push_back(node);
        string next = peek_next_token();
        if(next == "text" || next == "var" || next == "output" || next == "//" || next == "set"){
            break;
        }
        read_next_token();
        text = next_token();
    }
    ExpTree expressionTree(stackFrame);
    int result = expressionTree.parse();
    cout << result;
}


void coutFunc(){
    read_next_token();
    string output = next_token();
    cout << output;
}

void varFunc(){
    read_next_token(); // reads x/y/z
    string variable1 = next_token(); // puts x/y/z into variable1
    string varSymbol;
    read_next_token();
    string expr = next_token();    // expression
    Node* node; // node pointer

    while(next_token_type != END && (next_token_type == NUMBER || next_token_type == SYMBOL || next_token_type == NAME)){
        bool condition = operationChecker(expr);   // returns true if number; false if symbol
        string awperator = AWPerator(expr); // return the symbol or ""
        int newNodeVal = token_number_value;
        if(next_token_type == NAME){
            newNodeVal = Storage.Getter();
        }
        node = new Node(condition,newNodeVal,awperator);
        stackFrame.push_back(node); // pushes constructor onto stack
        string next = peek_next_token();
        if(next == "text" || next == "var" || next == "output" || next == "//"){
            break;
        }
        read_next_token();
        expr = next_token();
    }
    ExpTree expressionTree(stackFrame);
    int result = expressionTree.parse();
    Storage.newVar(variable1, result);
}

void setFunc(){
    read_next_token(); // reads variable
    string variable1 = next_token(); // puts variable into variable
    string varSymbol;
    read_next_token();
    string expr = next_token();
    Node* node;
    while(next_token_type != END && (next_token_type == NUMBER || next_token_type == SYMBOL || next_token_type == NAME)){
        bool condition = operationChecker(expr);
        string awperator = AWPerator(expr);
        node = new Node(condition,token_number_value,awperator);
        stackFrame.push_back(node);
        string next = peek_next_token();
        if(next == "text" || next == "var" || next == "output" || next == "//"){
            break;
        }
        read_next_token();
        expr = next_token();
    }
    ExpTree expressionTree(stackFrame);
    int result = expressionTree.parse();
    Storage.set(variable1,result);
}



void run (){
    string Incoming_Text;
    read_next_token();
    while(next_token_type != END){
        Incoming_Text = next_token();
        if(next_token_type == NAME){
            if(Incoming_Text == "output"){
                expression();
            }else if(Incoming_Text == "text"){
                coutFunc();
            }else if(Incoming_Text == "var"){
                varFunc();
            }else if(Incoming_Text == "set"){
                setFunc();
            }
        }
        read_next_token();
    }
    Storage.clear();
}

int main(){
//    cout << "Test 1" << endl;
//    set_input("/Users/matthew/Desktop/ECE312_projects/Project8_starter_files/TestCases/proj8/test1.blip");
//    run();
//    cout << "Test 2" << endl;
//    set_input("/Users/matthew/Desktop/ECE312_projects/Project8_starter_files/TestCases/proj8/test2.blip");
//    run();
//    cout << "Test 3" << endl;
//    set_input("/Users/matthew/Desktop/ECE312_projects/Project8_starter_files/TestCases/proj8/test3.blip");
//    run();
//    cout << "Test 4" << endl;
//    set_input("/Users/matthew/Desktop/ECE312_projects/Project8_starter_files/TestCases/proj8/test4.blip");
//    run();
    set_input("test_grader.blip");
    run();
}


