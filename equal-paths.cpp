#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
/*int height(Node * root){
    if(root == NULL){
        return 0;
    }
    else {
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + max(leftHeight,rightHeight);
    }
}*/

bool checkEqualPaths(Node * root, int depth, int& leafDepth)
{
    if(root == NULL){
        return true;
    }
    if((root->left == NULL) && (root->right == NULL)) {
        if(leafDepth == -1){
            leafDepth = depth;
        }
        else if(leafDepth!= depth){
            return false;
        }
        return true;   //checking if leaf so then depth and height equal 

    }

    return checkEqualPaths(root->left, depth + 1,leafDepth) && checkEqualPaths(root->right, depth+1, leafDepth);
}

bool equalPaths(Node * root)
{
    int leafDepth = -1;
    return checkEqualPaths(root,0, leafDepth);   
}

