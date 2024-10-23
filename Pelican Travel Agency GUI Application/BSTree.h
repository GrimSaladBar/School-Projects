//Student Name: Caleb Ellis
//Student ID: 400014224

#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class BSTNode
{
    private:
        int clientID;
        string  firstName;
        string surname;
        string destination;
        string payment;
        string booking;
        BSTNode* leftPtr;
        BSTNode* rightPtr;

    public:
        // Constructors
        BSTNode() {leftPtr = rightPtr = NULL;} //Default Constructor
        BSTNode(int, string, string, string, string, string); //Overloaded Constructor

        //Accessor functions
        int getID(){return clientID;}
        string getRecord();
        BSTNode* getLeftPtr(){return leftPtr;}
        BSTNode* getRightPtr(){return rightPtr;}

        // Mutator functions
        void setID(int id){clientID = id;}
        void setRecord(string);
        void setLeftPtr(BSTNode* left){leftPtr = left;}
        void setRightPtr(BSTNode* right){rightPtr = right;}
};

class BSTree
{
    private:
        BSTNode* root;
        BSTNode* insertHelper(BSTNode*, int, string, string, string, string, string);
        BSTNode* deleteHelper(BSTNode*, int id);
        string inorderHelper(BSTNode*);
        string preorderHelper(BSTNode*);
        string postorderHelper(BSTNode*);

    public:
        //Default Constructor
        BSTree() {root = NULL;}
        BSTree(int, string, string, string, string, string);

        void insert(int, string, string, string, string, string);
        void recursiveInsert(int, string, string, string, string, string);
        void deleteNode(int);

        BSTNode* getRoot() {return root;}
        string inorderNode() {return inorderHelper(root);}
        string preorderNode() {return preorderHelper(root);}
        string postorderNode() {return postorderHelper(root);}
};

///////////////////////////////////////////
/////////// BSTNode Functions /////////////
///////////////////////////////////////////
BSTNode::BSTNode(int id, string first, string last, string dst, string pay, string book)
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


string BSTNode::getRecord()
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

void BSTNode::setRecord(string record)
{
    string clientIDString;
    istringstream clientRecord(record);
    clientRecord >> clientIDString >> firstName >> surname >> destination >> payment >> booking;
    clientID = stoi(clientIDString);
}

///////////////////////////////////////////
/////////// BSTree Functions //////////////
///////////////////////////////////////////
BSTree::BSTree(int id, string first, string last, string dst, string pay, string book)
{
    BSTNode* node = new BSTNode(id, first, last, dst, pay, book);
    root = node;
}

BSTNode* BSTree::insertHelper(BSTNode* ptr, int id, string first, string last, string dst, string pay, string book)
{
    if (ptr == NULL)
    {
        ptr = new BSTNode(id, first, last, dst, pay, book);
    }
    else
    {
        if (id < ptr->getID())//If id is less than, put into the left sub-tree
        {
            ptr->setLeftPtr(insertHelper(ptr->getLeftPtr(), id, first, last, dst, pay, book));
        }
        else if (id > ptr->getID())//If id is greater than, put into the right sub-tree
        {
            ptr->setRightPtr(insertHelper(ptr->getRightPtr(), id, first, last, dst, pay, book));
        }
        else
            return ptr;
    }
    return ptr;
}

BSTNode* BSTree::deleteHelper(BSTNode* ptr, int id)
{
    //Base Case - If ptr is NULL, return message
    if (ptr == NULL)
        return NULL;

    //Implied Else - ptr is not NULL

    if (ptr->getID() > id)//If id is less than, the node must be in the left sub-tree
    {
        ptr->setLeftPtr(deleteHelper(ptr->getLeftPtr(), id));
    }
    else if (ptr->getID() < id)//If id is greater than, the node must be in the right sub-tree
    {
        ptr->setRightPtr(deleteHelper(ptr->getRightPtr(), id));
    }
    else //For if the exact node with the id is found
    {
        if (ptr->getRightPtr() != NULL)//If the node has a right child
        {
            BSTNode* cycleThrough = ptr->getRightPtr();

            //Cycle through each node in the left sub-tree
            while (cycleThrough->getLeftPtr() != NULL)
            {
                cycleThrough = cycleThrough->getLeftPtr();
            }

            //Replace data in ptr with the to-be-deleted node's data
            ptr->setRecord(cycleThrough->getRecord());

            //Delete the node
             ptr->setRightPtr(deleteHelper(ptr->getRightPtr(), cycleThrough->getID()));
        }
        else //ptr has no left child, so just replace it with what's in the left subtree
        {
            return ptr->getLeftPtr();
        }
    }

    return ptr;
}

string BSTree::inorderHelper(BSTNode* ptr)
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

string BSTree::preorderHelper(BSTNode* ptr)
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


string BSTree::postorderHelper(BSTNode* ptr)
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

void BSTree::recursiveInsert(int id, string first, string last, string dst, string pay, string book)
{
    root = insertHelper(root, id, first, last, dst, pay, book);
}

//Iterative Insert
/*void BSTree::insert(int id, string first, string last, string dst, string pay, string book)
{
    //Create the new node
    BSTNode* node = new BSTNode(id, first, last, dst, pay, book);

    //If tree is empty, make the new node the root of the tree
    if (root == NULL)
    {
        root = node;
        return;
    }

    //Else
    BSTNode* parent = NULL;
    BSTNode* current = root;

    while (current != NULL)
    {
        parent = current;
        if (parent->getID() > node->getID())
            current = parent->getLeftPtr();
        else if(parent->getID() < node->getID())
            current = parent->getRightPtr();
        else
            return; //BSTNode is already in the tree
    }

    if (node->getID() < parent->getID())
    {
        parent->setLeftPtr(node);
    }
    else
    {
        parent->setRightPtr(node);
    }

}*/

void BSTree::deleteNode(int id)
{
    root = deleteHelper(root, id);
}
#endif
