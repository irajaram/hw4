#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* currParent, AVLNode<Key,Value>* currNode);
    void rotateLeft(AVLNode<Key,Value>* node);
    void rotateRight(AVLNode<Key,Value>* node);
    void removeFix(AVLNode<Key,Value>* node, int diff);


};


/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
  
  if(this->root_ == NULL){
    AVLNode<Key, Value>* current = new AVLNode<Key, Value> (new_item.first, new_item.second, nullptr);
    this->root_ = current;
    //this->root_->setBalance(0);
    return;
  }
  AVLNode <Key, Value>* temp = static_cast<AVLNode<Key,Value>*>(this->root_);
  AVLNode <Key, Value>* parent = nullptr;
  while(temp!=NULL){
      parent = temp;
      if(new_item.first< temp->getKey()){
        temp = temp ->getLeft();
      }
      else if(new_item.first > temp->getKey()){
        temp = temp->getRight();
      }
      else{
        temp->setValue(new_item.second);
        return;
      }
  }
  //current->setParent(parent);
  //insert currentNode
  AVLNode<Key,Value>* newNode = new AVLNode<Key, Value> (new_item.first, new_item.second, parent);
  if(new_item.first < parent->getKey()){
    parent->setLeft(newNode);           
  }
  else if(new_item.first > parent ->getKey()){
    parent->setRight(newNode);
  }
  
  
  if(parent->getBalance()==-1){
    parent->setBalance(0);
  }   
  else if(parent->getBalance() == 1){
    parent->setBalance(0);
  } 
  else if(parent->getBalance() == 0){
    if(parent->getLeft() == newNode){
      parent->setBalance(-1);
    }
    else{
      parent->setBalance(1);
    }
    insertFix(parent,newNode);
  }      
  

}
template<class Key, class Value>
void AVLTree<Key,Value>::insertFix(AVLNode<Key,Value>* currParent,AVLNode<Key,Value>* currNode)
{   
    AVLNode<Key,Value>* currGrand = currParent->getParent();
    if(currParent == NULL || currGrand == NULL){
        return;
    }
    
    else{
        // bool zigzig = false;
        // bool zigzag = false;

        bool isLeftParent = currGrand->getLeft()==currParent;
        bool isRightParent = currGrand->getRight()==currParent;
        bool isLeftNode = currParent->getLeft() == currNode;
        bool isRightNode = currParent->getRight() == currNode;
        
        if(isLeftParent) {
            currGrand->updateBalance(-1);
            if(currGrand->getBalance()==0){
                return;
            }
            else if(currGrand->getBalance() == -1){
                insertFix(currGrand,currParent);
            }

            else if(currGrand->getBalance()== -2){
                if(isLeftNode){ //zig-zig
                    rotateRight(currGrand);
                    currGrand->setBalance(0);
                    currParent->setBalance(0);
                }
                else  { //zig zag
                    rotateLeft(currParent);
                    rotateRight(currGrand);
                    if(currNode->getBalance() == -1){
                        currParent->setBalance(0);
                        currGrand->setBalance(1);
                        currNode->setBalance(0);
                    }
                    else if(currNode->getBalance() == 0){
                        currParent->setBalance(0);
                        currGrand->setBalance(0);
                        currNode->setBalance(0);
                    }
                    else if(currNode->getBalance()== 1){
                        currParent->setBalance(-1);
                        currGrand->setBalance(0);
                        currNode->setBalance(0);
                    }
                }
            }
        }

        else if(isRightParent) {
            currGrand->updateBalance(1);
            if(currGrand->getBalance()==0){
                return;
            }
            else if(currGrand->getBalance() == 1){
                insertFix(currGrand,currParent);
            }

            else if(currGrand->getBalance()== 2){
                if(isRightNode){ //zig-zig
                    rotateLeft(currGrand);
                    currGrand->setBalance(0);
                    currParent->setBalance(0);
                }
                else  { //zig zag
                    rotateRight(currParent);
                    rotateLeft(currGrand);
                    if(currNode->getBalance() == 1){
                        currParent ->setBalance(0);
                        currGrand->setBalance(-1);
                        currNode->setBalance(0);
                    }
                    else if(currNode->getBalance() == 0){
                        currParent->setBalance(0);
                        currGrand->setBalance(0);
                        currNode->setBalance(0);
                    }
                    else if(currNode->getBalance()== -1){
                        currParent->setBalance(1);
                        currGrand->setBalance(0);
                        currNode->setBalance(0);
                    }
                }
            }
        }
        

    }

}
template<class Key, class Value>
void AVLTree<Key,Value>::rotateLeft(AVLNode<Key,Value>* node)
{
    /*while(node!=NULL){
        node->updateBalance(balanceDiff());
        if(node->getBalance>1)
    }*/

    //AVLNode<Key,Value>* p = node->getParent();
    AVLNode<Key,Value>* y= node->getRight(); //want to get right subtree
    AVLNode<Key,Value>* b = y->getLeft(); //get left child because that has to become right subchild of x which is getting rotated
    AVLNode<Key,Value>* parent= node->getParent();

        y->setLeft(node);
        node->setRight(b);
        
        y->setParent(parent);

        if(b!= NULL){
            b->setParent(node);
        }

        if(parent ==NULL){
            this->root_ = y;
        }
        else if (node == parent->getLeft()) { //if original node was left child of parent y replaces original node as left child of parent
           parent->setLeft(y);
        }
        else { //if original node was right child of parent y replaces original node as right child of parent
            parent->setRight(y);
        }
        node->setParent(y);
        
        
        

    

    
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* node)
{
    /*while(node!=NULL){
        node->updateBalance(balanceDiff());
        if(node->getBalance>1)
    }*/

    //AVLNode<Key,Value>* p = node->getParent();
    AVLNode<Key,Value>* y= node->getLeft(); //want to get right subtree
    AVLNode<Key,Value>* b = y->getRight(); //get left child because that has to become right subchild of x which is getting rotated
    AVLNode<Key,Value>* parent = node->getParent();
        y->setRight(node);
        node->setLeft(b);
        
        y->setParent(parent);

         if(b!= NULL){
            b->setParent(node);
        }

        if(parent ==NULL){
            this->root_ = y;
        }
        else if (node == parent->getLeft()) { //if original node was left child of parent y replaces original node as left child of parent
            parent->setLeft(y);
        }
        else { //if original node was right child of parent y replaces original node as right child of parent
            parent->setRight(y);
        }
        node->setParent(y);
        
        
       
    

    
}
/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key,Value>* removeNode = static_cast<AVLNode<Key,Value>*>(this->internalFind(key));
    if(removeNode== nullptr){
        return;
    }
    else if((removeNode->getLeft()!= nullptr) && (removeNode->getRight()!=nullptr)){ // 2 child case
      AVLNode <Key,Value>* pred = static_cast <AVLNode<Key,Value>*> (this->predecessor(removeNode));
      nodeSwap(pred, removeNode);
    }

    AVLNode<Key,Value>* parent = removeNode->getParent();
    int diff = 0;
    if(parent!= nullptr){
        if(parent->getLeft() == removeNode){
            diff = 1;
        }
        else if ( parent->getRight()== removeNode){
            diff = -1;
        }        
    }
    //case 1 : leaf node
    if ((removeNode -> getLeft() == NULL) && removeNode -> getRight() == NULL) {
      if (removeNode -> getParent() == NULL) { //check if root
        //delete root_;
        this->root_ = NULL;
      } else {
       
        if (parent -> getLeft() == removeNode) /*checking if left child*/ {
          parent -> setLeft(NULL);
        } else if (parent -> getRight() == removeNode) /*checking if right child*/ {
          parent -> setRight(NULL);
        }
        //delete removeNode;
      }
      delete removeNode;
    }

    //case 2: 1 child
    else if ((removeNode -> getLeft() != NULL) || (removeNode -> getRight() != NULL)) {
      Node < Key, Value > * childNode = NULL;
      if (removeNode -> getLeft() != NULL) { //checking if parent will be point to left child of removed
        childNode = removeNode -> getLeft();
      } else if (removeNode -> getRight() != NULL) { // checking if parent will be point to right child of removed
        childNode = removeNode -> getRight();
      }
      if (removeNode == this->root_) /*checking if node is a root*/ {
        this->root_ = childNode;
        this->root_ -> setParent(NULL);
      } else {
        if (parent -> getLeft() == removeNode) { //checking if removed is to right of parent if so setting child to the right of parent
          parent -> setLeft(childNode);
          childNode -> setParent(parent);
        } else if (parent -> getRight() == removeNode) { //checking if removed is to left of parent if so setting child to the left of parent
          parent -> setRight(childNode);
          childNode -> setParent(parent);
        }
      }
      delete removeNode;
    }
    //delete removeNode;
    removeFix(parent,diff);   
}

template<class Key, class Value>
void AVLTree<Key, Value>:: removeFix(AVLNode<Key,Value>* node, int diff){
 if (node==NULL){
    return;
 } 
 AVLNode<Key,Value>* p = node->getParent();
 int ndiff;
 if(p!=NULL){
    if(p->getLeft() == node){
        ndiff = 1;
    }
    else{
        ndiff= -1;
    }
 }

 if(diff== -1){
    if(node->getBalance() + diff == -2){ //case 1
        AVLNode<Key,Value>* c = node->getLeft();
        if(c->getBalance() ==-1){ //zig zig //case 1a
            rotateRight(node);
            node->setBalance(0);
            c->setBalance(0);
            removeFix(p,ndiff);
        }
        else if(c->getBalance() ==0){ //zig zig //case 1b
            rotateRight(node);
            node->setBalance(-1);
            c->setBalance(1);
        }
        else if(c->getBalance()==1){ //zig zag //case1c
            AVLNode<Key,Value>* g = c->getRight();
            rotateLeft(c);
            rotateRight(node);
            if(g->getBalance()==1){
                node->setBalance(0);
                c->setBalance(-1);
                g->setBalance(0);
            }
            else if(g->getBalance() == 0){
                node->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }
            else if(g->getBalance() == -1){
                node->setBalance(1);
                c->setBalance(0);
                g->setBalance(0);
            }
            removeFix(p,ndiff);
        }
    }
    else if(node->getBalance() + diff == -1){ //case 2
        node->setBalance(-1);
    }

    else if(node->getBalance() + diff == 0){ //case 3
        node->setBalance(0);
        removeFix(p,ndiff);
    }
    
 } 

 else if(diff == 1){
    if(node->getBalance() + diff == 2){ //case 1
        AVLNode<Key,Value>* c = node->getRight();
        if(c->getBalance() ==1){ //zig zig //case 1a
            rotateLeft(node);
            node->setBalance(0);
            c->setBalance(0);
            removeFix(p,ndiff);
        }
        else if(c->getBalance() ==0){ //zig zig //case 1b
            rotateLeft(node);
            node->setBalance(1);
            c->setBalance(-1);
        }
        else if(c->getBalance()==-1){ //zig zag //case1c
            AVLNode<Key,Value>* g = c->getLeft();
            rotateRight(c);
            rotateLeft(node);
            if(g->getBalance()==-1){
                node->setBalance(0);
                c->setBalance(1);
                g->setBalance(0);
            }
            else if(g->getBalance() == 0){
                node->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            }
            else if(g->getBalance() == 1){
                node->setBalance(-1);
                c->setBalance(0);
                g->setBalance(0);
            }
            removeFix(p,ndiff);
        }
    }
    else if(node->getBalance() + diff == 1){ //case 2
        node->setBalance(1);
    }

    else if(node->getBalance() + diff == 0){ //case 3
        node->setBalance(0);
        removeFix(p,ndiff);
    }
    
    
 }

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
