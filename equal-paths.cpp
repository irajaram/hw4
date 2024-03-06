#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int height(Node * root){
    if(root == NULL){
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + max(leftHeight,rightHeight);
}

bool equalPaths(Node * root)
{
    if(root == NULL){
        return true;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if(leftHeight != rightHeight) {
        return false;
    }
    
    return (equalPaths(root->left) == equalPaths(root->right));
    
}

