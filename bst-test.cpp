#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    // BinarySearchTree<char,int> bt;
    // bt.insert(std::make_pair('a',1));
    // bt.insert(std::make_pair('b',2));
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // bt.clear();

    BinarySearchTree<uint16_t, uint16_t> testTree;

    testTree.insert(std::make_pair(5, 5));
      //testTree.print();



    testTree.insert(std::make_pair(3, 3));
      // testTree.print();

    testTree.insert(std::make_pair(1, 1));
      // testTree.print();
    
    
    testTree.insert(std::make_pair(10, 10));
    for(BinarySearchTree<uint16_t, uint16_t>::iterator it = testTree.begin(); it != testTree.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    testTree.print();

      // testTree.print();
    // testTree.insert(std::make_pair(15, 15));

    // testTree.insert(std::make_pair(2, 2));
    // testTree.insert(std::make_pair(4, 4));

    


  	// verifyBST(testTree, std::set<std::string>({"Hello World"}));
    
    /*cout << "Erasing b" << endl;
    bt.remove('b');

    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');*/

    return 0;
}
