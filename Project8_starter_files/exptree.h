//
// Created by Matthew Olan on 11/27/23.
//

#ifndef PROJECT8_STARTER_FILES_EXPTREE_H
#define PROJECT8_STARTER_FILES_EXPTREE_H
using namespace std;

#include <vector>
#include <iostream>
using namespace std;
class Node {
public:
    bool isOperand;
    int operand;
    string optr;
    Node* left;
    Node* right;

    Node(bool isOperand, int operand, string optr) {
        left = nullptr;
        right = nullptr;
        this->isOperand = isOperand;
        this->operand = operand;
        this->optr = optr;
    }

    void print() {
        if (isOperand) {
            cout << operand << endl;
        } else {
            cout << optr << endl;
        }
    }
};
class ExpTree {
private:
    const int spaces_per_level = 4;
    Node* overallRoot;
    Node* add(Node* root, vector<Node*>&);
    void printTree(Node*, int);
    void printSpaces(int);
    int parse(Node*);
    Node* copy(const Node* that);
    void destroy(Node*);
public:
    int parse();
    ExpTree(vector<Node*>& expr); // constructor
    void printTree();
    ExpTree(const ExpTree& that);
    ExpTree& operator=(const ExpTree& that);
    ~ExpTree();
};


#endif //PROJECT8_STARTER_FILES_EXPTREE_H
