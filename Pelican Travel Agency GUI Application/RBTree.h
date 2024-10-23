//Student Name: Caleb Ellis
//Student ID: 400014224

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <string>
#include <sstream>

class RBNode
{
    private:
        string colour;
        int clientID;
        string  firstName;
        string surname;
        string destination;
        string payment;
        string booking;
        RBNode* leftPtr;
        RBNode* rightPtr;
        RBNode* parent;

    public:
        // Constructors
        RBNode() {colour = "RED"; parent = leftPtr = rightPtr = NULL;} //Default Constructor
        RBNode(int, string, string, string, string, string); //Overloaded Constructor

         //Accessor functions
        int getID(){return clientID;}
        string getColour() {return colour;}
        string getRecord();
        string getRecordWithColour();
        RBNode* getLeftPtr(){return leftPtr;}
        RBNode* getRightPtr(){return rightPtr;}
        RBNode* getParent() {return parent;}

        // Mutator functions
        void setID(int num){clientID = num;}
        void setColour(string nodeColour) {colour = nodeColour;}
        void setRecord(string);
        void setLeftPtr(RBNode* left){leftPtr = left;}
        void setRightPtr(RBNode* right){rightPtr = right;}
        void setParent(RBNode* parentNode) {parent = parentNode;}
};

class RBTree
{
    private:
        RBNode* root;

        //Utility Functions
        RBNode* insertHelper(RBNode*, int, string, string, string, string, string);
        void deleteHelper(RBNode*);
        string inorderHelper(RBNode*);
        string preorderHelper(RBNode*);
        string postorderHelper(RBNode*);
        RBNode* findNode(int);
        RBNode* getMinimum(RBNode*);
        RBNode* getSuccessor(RBNode*);

    public:
        RBTree() {root = NULL;} //Default Constructor
        RBTree(int, string, string, string, string, string);

        void insert(int, string, string, string, string, string);
        void deleteNode(int);

        RBNode* getRoot() {return root;}
        string inorderNode() {return inorderHelper(root);}
        string preorderNode() {return preorderHelper(root);}
        string postorderNode() {return postorderHelper(root);}

        void rotateRight(RBNode*);
        void rotateLeft(RBNode*);
        void fixTree(RBNode*);
};

///////////////////////////////////////////
/////////// RBNode Functions //////////////
///////////////////////////////////////////
RBNode::RBNode(int id, string first, string last, string dst, string pay, string book)
{
    colour = "RED";
    clientID    = id;
    firstName   = first;
    surname     = last;
    destination = dst;
    payment     = pay;
    booking     = book;
    leftPtr     = NULL;
    rightPtr    = NULL;
    parent = NULL;
}

string RBNode::getRecord()
{
    string str = to_string(clientID);
    str.append("\t");
    str.append(firstName);
    str.append("\t");
    str.append(surname);
    str.append("\t");
    str.append(destination);
    str.append("\t");
    str.append(payment);
    str.append("\t");
    str.append(booking);

    return str;
}

string RBNode::getRecordWithColour()
{
    string str = to_string(clientID);
    str.append("\t");
    str.append(firstName);
    str.append("\t");
    str.append(surname);
    str.append("\t");
    str.append(destination);
    str.append("\t");
    str.append(payment);
    str.append("\t");
    str.append(booking);
    str.append("\t");
    str.append("(");
    if (colour == "RED")
        str.append("R");
    else if (colour == "BLACK")
        str.append("B");
    str.append(")");
    str.append("\n");
    return str;
}


void RBNode::setRecord(string record)
{
    string clientIDString;
    istringstream clientRecord(record);
    clientRecord >> clientIDString >> firstName >> surname >> destination >> payment >> booking;
    clientID = stoi(clientIDString);
}

///////////////////////////////////////////
/////////// RBTree Functions //////////////
///////////////////////////////////////////
RBTree::RBTree(int id, string first, string last, string dst, string pay, string book)
{
    RBNode* node = new RBNode(id, first, last, dst, pay, book);
    root = node;
}

void RBTree::insert(int id, string first, string last, string dst, string pay, string book)
{
    RBNode* node = new RBNode(id, first, last, dst, pay, book);

    if (root == NULL)
    {
        node->setColour("BLACK");
        root = node;
        return;
    }
    else
    {
        RBNode* ancestor = NULL;
        RBNode* current = root;

        while (current != NULL)
        {
            ancestor = current;

            if (node->getID() < current->getID())
                current = current->getLeftPtr();
            else
                current = current->getRightPtr();
        }

        node->setParent(ancestor);
        if (node->getID() < ancestor->getID())
            ancestor->setLeftPtr(node);
        else
            ancestor->setRightPtr(node);

        fixTree(node);
    }
}

//  Created by Dr. John Charlery on 10/25/2021.
//  Copyright (c) 2021 University of the West Indies. All rights reserved.
//  Modified version of the original code
void RBTree::fixTree( RBNode *ptr )
    {
        RBNode *ptrsUncle = NULL;

        while ( ptr != root && ptr->getParent()->getColour() == "RED" )
            {
                if ( ptr->getParent() == ptr->getParent()->getParent()->getLeftPtr() )
                    {       // ptr's parent is a LEFT child
                        ptrsUncle = ptr->getParent()->getParent()->getRightPtr();

                        if (  ptrsUncle != NULL && ptrsUncle->getColour() == "RED" )
                            {
                                ptr->getParent()->setColour("BLACK");
                                ptrsUncle->setColour("BLACK");
                                ptr->getParent()->getParent()->setColour("RED");
                                ptr = ptr->getParent()->getParent();
                            }
                        else
                            {
                                if ( ptr == ptr->getParent()->getRightPtr() )
                                    {
                                        ptr = ptr->getParent();
                                        rotateLeft( ptr );
                                    }

                                ptr->getParent()->setColour("BLACK");
                                ptr->getParent()->getParent()->setColour("RED");
                                rotateRight( ptr->getParent()->getParent() );
                            }
                    }
                else            // ptr's parent is a RIGHT child
                    {
                        ptrsUncle = ptr->getParent()->getParent()->getLeftPtr();

                        if ( ptrsUncle != NULL && ptrsUncle->getColour() == "RED" )
                            {
                                ptr->getParent()->setColour("BLACK");
                                ptrsUncle->setColour("BLACK");
                                ptr->getParent()->getParent()->setColour("RED");
                                ptr = ptr->getParent()->getParent();
                            }
                        else
                            {
                                if ( ptr == ptr->getParent()->getLeftPtr() )
                                    {
                                        ptr = ptr->getParent();
                                        rotateRight( ptr );
                                    }
                                ptr->getParent()->setColour("BLACK");
                                ptr->getParent()->getParent()->setColour("RED");
                                rotateLeft( ptr->getParent()->getParent() );
                            }
                    }
            }

        root->setColour("BLACK");

        ptrsUncle = NULL;
    }

//  Created by Dr. John Charlery on 10/25/2021.
//  Copyright (c) 2021 University of the West Indies. All rights reserved.
//  Modified version of the original code
void RBTree::deleteHelper(RBNode* node)
{
    if (node == NULL)
        return;
    else
    {
        RBNode *successor, *successorChild;
        successor = node;

        if (node->getLeftPtr() == NULL || node->getRightPtr() == NULL)
            successor = node;
        else
            successor = getSuccessor(node);

        if (successor->getLeftPtr() == NULL)
            successorChild = successor->getRightPtr();
        else
            successorChild = successor->getRightPtr();

        if (successorChild != NULL)
            successorChild->setParent(successor->getParent());

        if (successor->getParent() == NULL)
            root = successorChild;
        else if (successor == successor->getParent()->getLeftPtr())
            successor->getParent()->setLeftPtr(successorChild);
        else
            successor->getParent()->setRightPtr(successorChild);

        if (successor != node)
            node->setRecord(successor->getRecord());

        if (successor->getColour() == "BLACK" && successorChild != NULL)
            fixTree(successorChild);
    }
}


//  Created by Dr. John Charlery on 10/25/2021.
//  Copyright (c) 2021 University of the West Indies. All rights reserved.
//  Modified version of the original code
RBNode* RBTree::getSuccessor(RBNode* ptr)
{
    if (ptr->getRightPtr() == NULL)
        return ptr->getLeftPtr();
    else
        return (getMinimum(ptr->getRightPtr()));
}


//  Created by Dr. John Charlery on 10/25/2021.
//  Copyright (c) 2021 University of the West Indies. All rights reserved.
//  Modified version of the original code
RBNode* RBTree::getMinimum(RBNode* ptr)
{
    while (ptr->getLeftPtr() != NULL)
        ptr = ptr->getLeftPtr();

    return ptr;
}

//  Created by Dr. John Charlery on 10/25/2021.
//  Copyright (c) 2021 University of the West Indies. All rights reserved.
//  Modified version of the original code
RBNode* RBTree::findNode(int id)
{
    RBNode* ptr = root;

    while (ptr != NULL)
    {
        if (ptr->getID() == id)
            return ptr;

        if (id < ptr->getID())
            ptr = ptr->getLeftPtr();
        else if (id > ptr->getID())
            ptr = ptr->getRightPtr();
    }

    return NULL; //Tree is empty OR id was not found
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
void RBTree::rotateLeft( RBNode* ptr )
	{
        RBNode* rightChild = ptr->getRightPtr();
        ptr->setRightPtr(rightChild->getLeftPtr());

        if (rightChild->getLeftPtr() != NULL)
            rightChild->getLeftPtr()->setParent(ptr);

        rightChild->setParent(ptr->getParent());

        if (ptr == root)
            root = rightChild;
        else
            {
                if( ptr == ptr->getParent()->getLeftPtr())
                    ptr->getParent()->setLeftPtr(rightChild);
                 else
                    ptr->getParent()->setRightPtr(rightChild);
            }

        rightChild->setLeftPtr(ptr);
        ptr->setParent(rightChild);
 	}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
void RBTree::rotateRight(RBNode* ptr)
{
    RBNode* leftChild = ptr->getLeftPtr();
    ptr->setLeftPtr(leftChild->getRightPtr());

    if (leftChild->getRightPtr() != NULL)
        leftChild->getRightPtr()->setParent(ptr);

    leftChild->setParent(ptr->getParent());

    if (ptr == root)
        root = leftChild;
    else
        {
            if( ptr == ptr->getParent()->getRightPtr())
                ptr->getParent()->setRightPtr(leftChild);
            else
                ptr->getParent()->setLeftPtr(leftChild);
        }

    leftChild->setRightPtr(ptr);
    ptr->setParent(leftChild);
}


string RBTree::inorderHelper(RBNode* ptr)
{
    string str = "";

    if (ptr != NULL)
    {
        if (ptr->getLeftPtr() != NULL)
        {
            str.append(inorderHelper(ptr->getLeftPtr()));
        }
        str.append(ptr->getRecordWithColour());
        if(ptr->getRightPtr() != NULL)
        {
            str.append(inorderHelper(ptr->getRightPtr()));
        }

    }
    return str;
}

string RBTree::preorderHelper(RBNode* ptr)
{
    string str = "";

    if (ptr != NULL)
    {
        str.append(ptr->getRecordWithColour());
        if (ptr->getLeftPtr() != NULL)
        {
            str.append(preorderHelper(ptr->getLeftPtr()));
        }
        if(ptr->getRightPtr() != NULL)
        {
            str.append(preorderHelper(ptr->getRightPtr()));
        }
    }
    return str;
}


string RBTree::postorderHelper(RBNode* ptr)
{
    string str = "";

    if (ptr != NULL)
    {
        if (ptr->getLeftPtr() != NULL)
        {
            str.append(postorderHelper(ptr->getLeftPtr()));
        }
        if(ptr->getRightPtr() != NULL)
        {
            str.append(postorderHelper(ptr->getRightPtr()));
        }
        str.append(ptr->getRecordWithColour());
    }
    return str;
}

void RBTree::deleteNode(int id)
{
    RBNode* deletedNode = findNode(id);
    deleteHelper(deletedNode);
}
#endif
