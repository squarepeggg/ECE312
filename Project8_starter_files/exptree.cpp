//
// Created by Matthew Olan on 11/27/23.
//

#include "exptree.h"
using namespace std;
#define DEBUG true
ExpTree::ExpTree(vector<Node*>& expr) { // construct from expression vector
    overallRoot = add(overallRoot, expr);
//    add(overallRoot, expr);
}
// void ExpTree::add(Node* root, vector<Node*>& expr) { // passing expr as a reference
// private method
Node* ExpTree::add(Node* root, vector<Node*>& expr) { // passing expr as a reference
    int flag = 0;
        Node* first = expr[0]; // store the first element
expr.erase(expr.begin()); // remove the first element
root = first; // root points to the first token Node
if(first->optr == "!"){
    root->left = add(root->left,expr);
    flag = 1;
}
if(first->optr == "~"){
        root->left = add(root->left,expr);
        flag = 1;
}
if(flag == 0){
    if (!(first->isOperand)) { // if first is an operator, add 2 operands
        root->left = add(root->left, expr);
        root->right = add(root->right, expr);
    }
}
return root; // return the new sub-tree
}
void ExpTree::printTree() {
    printTree(overallRoot, 0); // call helper method
}
void ExpTree::printSpaces(int level) { // print 4 spaces per level, for indentation
    for (int i = 0; i < level*4; i++) {
        cout << ' ';
    }
}
// private recursive helper method
void ExpTree::printTree(Node* root, int level) {
    if (root == nullptr) return;
    printTree(root->right, level+1); // print the right sub-tree
    printSpaces(level); // print the indentation for the root of sub-tree
    root->print(); // print the root
    printTree(root->left, level+1); // print the left sub-tree
}
int ExpTree::parse() {
    return parse(overallRoot);
}
int ExpTree::parse(Node* root) {
    if (root->isOperand) return root->operand;
    int arg1 = 0;
    int arg2 = 0;
    if(root->left){
        arg1 = parse(root->left);
    }
    if(root->right){
        arg2 = parse(root->right);
    }
    if (root->optr == "+") {
        return arg1 + arg2;
    } else if(root->optr == "*"){
        return arg1 * arg2;
    }else if(root->optr == "/"){
        return arg1 / arg2;
    }else if (root->optr == "-") {
        return arg1 - arg2;
    } else if (root->optr == "&&") {
        return arg1 && arg2;
    } else if (root->optr == "||") {
        return arg1 || arg2;
    } else if (root->optr == ">") {
        return arg1 > arg2;
    } else if (root->optr == "<") {
        return arg1 < arg2;
    } else if (root->optr == "==") {
        return arg1 == arg2;
    } else if (root->optr == "!=") {
        return arg1 != arg2;
    } else if (root->optr == ">=") {
        return arg1 >= arg2;
    } else if (root->optr == "<=") {
        return arg1 <= arg2;
    } else if (root->optr == "!") {
        return !arg1;
    } else if (root->optr == "~") {
        return -arg1;
    } else if (root->optr == "%"){
        return arg1 % arg2;
    }
    return 0;
}
// copy constructor, assignment operator, destructor
Node* ExpTree::copy(const Node* that) {
    if (that == 0) return nullptr;
    Node* n = new Node(that->isOperand, that->operand, that->optr );
    if (that->left != nullptr)
        n->left = copy(that->left);
    if (that->right != nullptr)
        n->right = copy(that->right);
    return n;
}
ExpTree::ExpTree(const ExpTree& that) {
    overallRoot = copy(that.overallRoot);
}
ExpTree& ExpTree::operator=(const ExpTree& that) {
    if (this != &that) {
        destroy(overallRoot);
        overallRoot = copy(that.overallRoot);
    }
    return *this;
}
ExpTree::~ExpTree() {
    destroy(overallRoot);
}
void ExpTree::destroy(Node* n) {
    if (n == nullptr)
        return;
    if(n->left){
        destroy(n->left);
    }
    if(n->right){
        destroy(n->right);
    }
    delete n;
    n = nullptr;
}