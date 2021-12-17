#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"
using namespace std;
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
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_; 
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent):
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
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
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
    virtual void insert(const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateRight(AVLNode<Key, Value>* older, AVLNode<Key, Value>* younger);
    void rotateLeft (AVLNode<Key, Value>* older, AVLNode<Key, Value>* younger);
    void insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value>* kid);
    void removeFix(AVLNode<Key, Value> *n, int diff);

};

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* older, AVLNode<Key, Value>* younger){

    //ensure parent doesn't cause segfault
    if(older->getParent() != nullptr){
    	if(older->getParent()->getRight() == older){
    		older->getParent()->setRight(younger);
    	}
    	else older->getParent()->setLeft(younger);
    }
    else{
    	this->root_ = younger;
    }

    younger->setParent(older->getParent());
    older->setParent(younger);
    older->setLeft(younger->getRight());
    if(younger->getRight() != nullptr){
    	younger->getRight()->setParent(older);
    }
    younger->setRight(older);
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key, Value>* older, AVLNode<Key, Value>* younger){
	if(older->getParent() != nullptr){
    	if(older->getParent()->getRight() == older){
    		older->getParent()->setRight(younger);
    	}
    	else older->getParent()->setLeft(younger);
    }
    else{
    	this->root_ = younger;
    }

    younger->setParent(older->getParent());
    older->setParent(younger);
    older->setRight(younger->getLeft());
    if(younger->getLeft() != nullptr){
    	younger->getLeft()->setParent(older);
    }
    younger->setLeft(older);
}
//impelementation used from slides
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value> *parent, AVLNode<Key, Value>* kid){

	if(parent == nullptr or parent->getParent() == nullptr) return;

	AVLNode<Key, Value>* g = parent->getParent();

	if(g->getLeft() == parent){
		g->updateBalance(-1);
		if(g->getBalance() == 0) return;
		if(g->getBalance() == -1) insertFix(g, parent);
		if(g->getBalance() == -2){
			//zig-zig
			if(parent->getLeft() == kid){
				rotateRight(g, parent);
				g->setBalance(0);
				parent->setBalance(0);
			}
			//zig-zag
			else if(parent->getRight() == kid){
				rotateLeft(parent, kid);
				rotateRight(g, kid);
				if(kid->getBalance() == -1){
					parent->setBalance(0);
					g->setBalance(1);
					kid->setBalance(0);
				}
				else if(kid->getBalance() == 0){
					parent->setBalance(0);
					g->setBalance(0);
					kid->setBalance(0);
				}
				else if(kid->getBalance() == 1){
					parent->setBalance(-1);
					g->setBalance(0);
					kid->setBalance((0));
				}
			}
		}
	}
	//if parent is right child of grandparent
	else{
		g->updateBalance(1);
		if(g->getBalance() == 0) return;
		if(g->getBalance() == 1) insertFix(g, parent);
		if(g->getBalance() == 2){
			//zig-zig
			if(parent->getRight() == kid){
				rotateLeft(g, parent);
				g->setBalance(0);
				parent->setBalance(0);
			}
			//zig-zag
			else if(parent->getLeft() == kid){
				rotateRight(parent, kid);
				rotateLeft(g, kid);
				if(kid->getBalance() == 1){
					parent->setBalance(0);
					g->setBalance(-1);
					kid->setBalance(0);
				}
				else if(kid->getBalance() == 0){
					parent->setBalance(0);
					g->setBalance(0);
					kid->setBalance(0);
				}
				else if(kid->getBalance() == -1){
					parent->setBalance(1);
					g->setBalance(0);
					kid->setBalance(0);
				}
			}
		}
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    if(this->root_ == NULL){
        AVLNode<Key, Value>* newRoot = new AVLNode<Key, Value>(new_item.first, 
        												new_item.second, NULL);
        this->root_ = newRoot;
        //newRoot->setBalance(0);
        //newRoot->setRight(NULL);
        //newRoot->setLeft(NULL);
        return;
    }
    AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, 
    													new_item.second, NULL);
    AVLNode<Key, Value>* traverse = static_cast<AVLNode<Key,Value>*>(this->root_);
    Key insert = newNode->getKey();
    while(traverse != NULL){
        Key current = traverse->getKey();
        if(insert > current){
            if(traverse->getRight() == nullptr){
               	traverse->setRight(newNode);
               	newNode->setParent(traverse);
                newNode->setValue(new_item.second);
               	break;
            }
            else{
            	traverse = traverse->getRight();
        	}
        }
        else if(insert < current){
            if(traverse->getLeft() == nullptr){
                traverse->setLeft(newNode);
                newNode->setParent(traverse);
                newNode->setValue(new_item.second);
                break;
            }
            else traverse = traverse->getLeft();
        }
        //if they're equal, update value
        else if(insert == current){
            traverse->setValue(new_item.second);
            //delete newNode; //since the created node is no longer needed
            return; 
        }
    }
    newNode->setBalance(0);
    if(traverse->getBalance() == -1 or traverse->getBalance() == 1){
    	traverse->setBalance(0);
    }
    else{
    	if(traverse->getRight() == newNode){
    		traverse->setBalance(1);
    	}
    	else{
    		traverse->setBalance(-1);
    	}
    	insertFix(traverse, newNode);
    }
}

//implementation from slides

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value> *node, int diff){
    if(node == NULL) return;
    if(this->root_ == nullptr){
        return;
    }

	AVLNode<Key, Value>* parent = node->getParent();
	int nextDiff;
	if(parent != nullptr){
		if(parent->getLeft() == node){
			nextDiff = 1;
		}
		else if(parent->getRight() == node){
			nextDiff = -1;
		}
	}
	else return;

	if(diff == -1){
	//left child is taller... balance isn't same thing as height, need to change
		if(node->getBalance() + diff == -2){
			AVLNode<Key, Value>* tallerChild;
			if(node->getRight()->getBalance() < node->getLeft()->getBalance()){
				tallerChild = node->getLeft();
			}
			else{
				tallerChild = node->getRight();
			}

			if(tallerChild->getBalance() == -1 or tallerChild->getBalance() == 0){
				char oldBal = tallerChild->getBalance();
				rotateRight(node, tallerChild);
				if(oldBal == -1){
					node->updateBalance(0);
					tallerChild->updateBalance(-1);
					removeFix(parent, nextDiff);
				}
				if(oldBal == 0){
					node->updateBalance(-1);
					tallerChild->updateBalance(1);
				}
			}
			else if(tallerChild->getBalance() == 1){
				AVLNode<Key, Value>* grandChild = tallerChild->getRight();
				char grandBal = grandChild->getBalance();
				rotateLeft(tallerChild, grandChild);
				rotateRight(node, grandChild);
				if(grandBal == 1){
					node->updateBalance(0);
					tallerChild->updateBalance(-1);
					grandChild->updateBalance(0);
				}
				if(grandBal == 0){
					node->updateBalance(0);
					tallerChild->updateBalance(0);
					grandChild->updateBalance(0);
				}
				if(grandBal == -1){
					node->updateBalance(1);
					tallerChild->updateBalance(0);
					grandChild->updateBalance(0);
				}
				removeFix(parent, nextDiff);
			}
		}
		else if(node->getBalance() == -1){
			node->updateBalance(-1);
			return;
		}
		else if(node->getBalance() == 0){
			node->updateBalance(0);
			removeFix(parent, nextDiff);
		}
	}
	else if(diff == 1){
		if(node->getBalance() + diff == 2){
			AVLNode<Key, Value>* tallerChild;
			if(node->getRight()->getBalance() < node->getLeft()->getBalance()){
				tallerChild = node->getLeft();
			}
			else{
				tallerChild = node->getRight();
			}

			if(tallerChild->getBalance() == 1 or tallerChild->getBalance() == 0){
				char oldBal = tallerChild->getBalance();
				rotateLeft(node, tallerChild);
				if(oldBal == 1){
					node->updateBalance(0);
					tallerChild->updateBalance(1);
					removeFix(parent, nextDiff);
				}
				if(oldBal == 0){
					node->updateBalance(1);
					tallerChild->updateBalance(-1);
				}
			}
			else if(tallerChild->getBalance() == -1){
				AVLNode<Key, Value>* grandChild = tallerChild->getLeft();
				char grandBal = grandChild->getBalance();
				rotateRight(tallerChild, grandChild);
				rotateLeft(node, grandChild);
				if(grandBal == -1){
					node->updateBalance(0);
					tallerChild->updateBalance(1);
					grandChild->updateBalance(0);
				}
				if(grandBal == 0){
					node->updateBalance(0);
					tallerChild->updateBalance(0);
					grandChild->updateBalance(0);
				}
				if(grandBal == 1){
					node->updateBalance(-1);
					tallerChild->updateBalance(0);
					grandChild->updateBalance(0);
				}
				removeFix(parent, nextDiff);
			}
		}
		else if(node->getBalance() == 1){
			node->updateBalance(1);
			return;
		}
		else if(node->getBalance() == 0){
			node->updateBalance(0);
			removeFix(parent, nextDiff);
		}
	}
}
template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    // TODO
    int diff = 0;
    bool rightChild = false;
    AVLNode<Key, Value>* traverse = static_cast<AVLNode<Key,Value>*>(this->root_);
    //find node
    if(static_cast<AVLNode<Key,Value>*>(this->root_) == NULL){
        return;
    } 

    if(this->internalFind(key) == NULL){
    	return;
    } 

    while(traverse->getRight() != nullptr or traverse->getLeft() != nullptr){
    	Key current = traverse->getKey();
    	if(key == current){
    		break;
    	}
        if(key > current){
            rightChild = true;
            traverse = traverse->getRight();
        }
        else{
            traverse = traverse->getLeft();
            rightChild = false;
        }
    }
    //if two children
    if(traverse == this->root_ and traverse->getRight() == nullptr and 
    								traverse->getLeft() == nullptr){
    	this->root_ = nullptr;
    	delete traverse;
    	return;
    }
    if(traverse->getRight() != nullptr and traverse->getLeft() != nullptr){
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key,Value>*>(this->predecessor(traverse)); 
        nodeSwap(traverse, pred);
        if(traverse->getParent()->getRight() == traverse){
            rightChild = true;
        }
        else{
            rightChild = false;
        }
    }
    //if leaf node
    if(traverse->getRight() == nullptr and traverse->getLeft() == nullptr){
        if(rightChild){
            traverse->getParent()->setRight(nullptr);
            diff = -1;
            delete traverse;
        }
        else{
            traverse->getParent()->setLeft(nullptr);
            diff = 1;
            delete traverse;
        }
    } 
    //has one child
    else if(traverse->getRight() != nullptr or traverse->getLeft() != nullptr){
        //set right child to the grandparent's right child
        if(rightChild and traverse->getRight() != nullptr and traverse->getLeft() == nullptr){
            nodeSwap(traverse, traverse->getRight());
            traverse->getParent()->setRight(nullptr);
            diff = -1;
            removeFix(traverse->getParent(), diff);
            delete traverse;
            return;
        }
        //set left child to the grandparent's right child
        else if(rightChild and traverse->getRight() == nullptr and traverse->getLeft() != nullptr){
            nodeSwap(traverse, traverse->getLeft());
            traverse->getParent()->setLeft(nullptr);
            diff = -1;
            removeFix(traverse->getParent(), diff);
            delete traverse;
            return;
        }
        //set right child as the grandparent's left child
        else if(!rightChild and traverse->getRight() != nullptr and traverse->getLeft() == nullptr){
            nodeSwap(traverse, traverse->getRight());
            traverse->getParent()->setRight(nullptr);
            diff = 1;
            removeFix(traverse->getParent(), diff);
            delete traverse;
            return;
        }
        //set the left child as the grandparent's left child
        else if(!rightChild and traverse->getRight() == nullptr and traverse->getLeft() != nullptr){
            nodeSwap(traverse, traverse->getLeft());
            traverse->getParent()->setLeft(nullptr);
            traverse->setParent(nullptr); //is this needed to delete? 
            diff = 1;
            removeFix(traverse->getParent(), diff);
            delete traverse;
            return;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif