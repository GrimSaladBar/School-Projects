//Student Name: Caleb Ellis
//Student ID: 400014224

#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include <string>
#include <sstream>

class SplayNode
{
    private:
        int clientID;
        string  firstName;
        string surname;
        string destination;
        string payment;
        string booking;
        SplayNode* leftPtr;
        SplayNode* rightPtr;

    public:
        //Constructors
        SplayNode() {leftPtr = rightPtr = NULL;} //Default Constructors
        SplayNode(int, string, string, string, string, string); //Overloaded Constructor

        //Accessor Functions
        int getID() {return clientID;}
        string getRecord();
        SplayNode* getLeftPtr() {return leftPtr;}
        SplayNode* getRightPtr() {return rightPtr;}

        //Mutator Functions
        void setID(int id) {clientID = id;}
        void setRecord(string);
        void setLeftPtr(SplayNode* left) {leftPtr = left;}
        void setRightPtr(SplayNode* right) {rightPtr = right;}
};

class SplayTree
{

    private:
        SplayNode* root;

        //Utility Functions
        SplayNode* rightRotate(SplayNode*);
        SplayNode* leftRotate(SplayNode*);
        SplayNode* splay(int, SplayNode*);
        SplayNode* insertHelper(SplayNode*, int, string, string, string, string, string);
        string inorderHelper(SplayNode*);
        string preorderHelper(SplayNode*);
        string postorderHelper(SplayNode*);
        void deleteSplayNode( SplayNode* );
        SplayNode* findSplayNode( int );
        SplayNode* getSuccessor(SplayNode* );
        SplayNode* getParent(SplayNode* );
        SplayNode* getMinimum( SplayNode* );


    public:
        SplayTree(){ root = 0; };
        SplayTree(int, string, string, string, string, string);
        SplayNode* getRoot(){return root;}
        void recursiveInsert(int, string, string, string, string, string);
        string inorderNode(){ return inorderHelper(root);}
        string preorderNode(){ return preorderHelper(root);}
        string postorderNode(){ return postorderHelper(root);}
        void deleteNode(int);
};

///////////////////////////////////////////
/////////// SplayNode Functions ///////////
///////////////////////////////////////////
SplayNode::SplayNode(int id, string first, string last, string dst, string pay, string book)
{
    clientID    = id;
    firstName   = first;
    surname     = last;
    destination = dst;
    payment     = pay;
    booking     = book;
    leftPtr     = NULL;
    rightPtr    = NULL;
}

string SplayNode::getRecord()
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
    str.append("\n");
    return str;
}

void SplayNode::setRecord(string record)
{
    string clientIDString;
    istringstream clientRecord(record);
    clientRecord >> clientIDString >> firstName >> surname >> destination >> payment >> booking;
    clientID = stoi(clientIDString);
}

///////////////////////////////////////////
/////////// SplayTree Functions ///////////
///////////////////////////////////////////

SplayTree::SplayTree(int id, string first, string last, string dst, string pay, string book)
{
    SplayNode* node = new SplayNode(id, first, last, dst, pay, book);
    root = node;
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
//  Modified version of the original code
SplayNode* SplayTree::splay(int id, SplayNode* root) {
    if (root == NULL)
        return NULL;

    SplayNode header;  // Use a local variable instead of dynamically allocating a header node
    SplayNode* leftTreeMax = &header;
    SplayNode* rightTreeMin = &header;

    /* loop until root->left == NULL || root->right == NULL; then break!
         The zig/zag mode would only happen when cannot find key and will reach
         null on one side after RR or LL Rotation.
         */
    while (true) {
        if (id < root->getID()) {
            if (root->getLeftPtr() == NULL)
                break;

            if (id < root->getLeftPtr()->getID()) {
                root = rightRotate(root);
                if (root->getLeftPtr() == NULL)
                    break;
            }

            rightTreeMin->setLeftPtr(root);
            rightTreeMin = rightTreeMin->getLeftPtr();
            root = root->getLeftPtr();
            rightTreeMin->setLeftPtr(NULL);
        } else if (id > root->getID()) {
            if (root->getRightPtr() == NULL)
                break;

            if (id > root->getRightPtr()->getID()) {
                root = leftRotate(root);
                if (root->getRightPtr() == NULL)
                    break;
            }

            leftTreeMax->setRightPtr(root);
            leftTreeMax = leftTreeMax->getRightPtr();
            root = root->getRightPtr();
            leftTreeMax->setRightPtr(NULL);
        } else {
            break;
        }
    }

    leftTreeMax->setRightPtr(root->getLeftPtr());
    rightTreeMin->setLeftPtr(root->getRightPtr());
    root->setLeftPtr(header.getRightPtr());
    root->setRightPtr(header.getLeftPtr());

    return root;
}


SplayNode* SplayTree::findSplayNode(int id)
{
    SplayNode* ptr = root;

    while (ptr != NULL)
    {
        if (ptr->getID() == id) //Id is found
            return ptr;

        if (id < ptr->getID())
            ptr = ptr->getLeftPtr();
        else if (id > ptr->getID())
            ptr = ptr->getRightPtr();
    }
    return NULL; //Tree is empty or id was not found
}

SplayNode* SplayTree::getParent(SplayNode* ptr)
{
    if (ptr == NULL)
        return NULL;

    if (ptr == root)
        return NULL;

    SplayNode* current = root;
    while (current != NULL)
    {
        if (current->getLeftPtr() == ptr || current->getRightPtr() == ptr) //Ptr is found
            return current;
        else
        {
            if (ptr->getID() < current->getID())
                current = current->getLeftPtr();
            else if (ptr->getID() > current->getID())
                current = current->getRightPtr();
        }
    }
    return current;
}


//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
SplayNode* SplayTree::getSuccessor(SplayNode* ptr)
{
    if (ptr->getRightPtr() == NULL)
        return ptr->getLeftPtr();
    else
        return (getMinimum(ptr->getRightPtr()));
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
SplayNode* SplayTree::getMinimum(SplayNode *ptr)
{
    while(ptr->getLeftPtr() != NULL)
        ptr = ptr->getLeftPtr();

    return ptr;
}

SplayNode* SplayTree::insertHelper(SplayNode* root, int id, string first, string last, string dst, string pay, string book)
{
    SplayNode* node = new SplayNode(id, first, last, dst, pay, book);

    if (root == NULL)
        return node;

    SplayNode* parentTemp = new SplayNode();
    SplayNode* temp = root;

    while (temp != NULL)
    {
        parentTemp = temp;

        if(id < temp->getID())
            temp = temp->getLeftPtr();
        else if (id > temp->getID())
            temp = temp->getRightPtr();
    }

    if (id < parentTemp->getID())
        parentTemp->setLeftPtr(node);
    else if (id > parentTemp->getID())
        parentTemp->setRightPtr(node);

    //root = splay(id, root);
    return root;
}

void SplayTree::recursiveInsert(int id, string first, string last, string dst, string pay, string book)
{
    root = insertHelper(root, id, first, last, dst, pay, book);
}

void SplayTree::deleteSplayNode(SplayNode* node)
{
    if (node == NULL)
        return;
    else
    {
        SplayNode *successor, *successorChild, *parent;

        if (node->getLeftPtr() == NULL || node->getRightPtr() == NULL)
            successor = node;
        else
            successor = getSuccessor(node);

        successorChild = successor->getRightPtr();
        parent = getParent(successor);

        //Transfer data from successor to node
        node->setRecord(successor->getRecord());

        if (parent == NULL)
            root = successorChild;
        else if (successor == parent->getLeftPtr())
            parent->setLeftPtr(successorChild);
        else
            parent->setRightPtr(successorChild);

        if (successor != node)
            node->setRecord(successor->getRecord());

        delete successor;
    }
}

void SplayTree::deleteNode(int id)
{
    SplayNode* node = findSplayNode(id);
    deleteSplayNode(node);
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
//  Modified version of the original code
SplayNode* SplayTree::leftRotate(SplayNode* ptr)
{
    SplayNode* newParent = ptr->getRightPtr();
    ptr->setRightPtr(newParent->getLeftPtr());
    newParent->setLeftPtr(ptr);
    return (newParent);
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
//  Modified version of the original code
SplayNode*  SplayTree::rightRotate(SplayNode* ptr)
{
    SplayNode* newParent = ptr->getLeftPtr();
    ptr->setLeftPtr(newParent->getRightPtr());
    newParent->setRightPtr(ptr);
    return (newParent);
}

string SplayTree::inorderHelper(SplayNode* ptr)
{
    string str = "";

    if (ptr != NULL)
    {
        if (ptr->getLeftPtr() != NULL)
        {
            str.append(inorderHelper(ptr->getLeftPtr()));
        }
        str.append(ptr->getRecord());
        if(ptr->getRightPtr() != NULL)
        {
            str.append(inorderHelper(ptr->getRightPtr()));
        }
    }
    return str;
}

string SplayTree::preorderHelper(SplayNode* ptr)
{
    string str = "";

    if (ptr != NULL)
    {
        str.append(ptr->getRecord());
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


string SplayTree::postorderHelper(SplayNode* ptr)
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
        str.append(ptr->getRecord());
    }
    return str;
}
#endif
