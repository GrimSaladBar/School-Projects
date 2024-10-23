//Student Name: Caleb Ellis
//Student ID: 400014224

#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int max(int valA, int valB)//Returns the largest of the two values
{
    return (valA > valB) ? valA : valB;
}

class AVLNode
    {
        private:
            int height;
            int clientID;
            string  firstName;
            string surname;
            string destination;
            string payment;
            string booking;
            AVLNode* leftPtr;
            AVLNode* rightPtr;

        public:
            // Constructors
            AVLNode() {height = 0; leftPtr = rightPtr = NULL;} //Default
            AVLNode(int, string, string, string, string, string); //Overloaded

            //Accessor functions
            int getID(){return clientID;}
            int getHeight() {return height;}
            string getRecord();
            string getRecordWithHeight();
            AVLNode* getLeftPtr(){return leftPtr;}
            AVLNode* getRightPtr(){return rightPtr;}

            // Mutator functions
            void setID(int num){clientID = num;}
            void setHeight(int nodeHeight) {height = nodeHeight;}
            void setRecord(string);
            void setLeftPtr(AVLNode* left){leftPtr = left;}
            void setRightPtr(AVLNode* right){rightPtr = right;}
    };

class AVLTree
{
    private:
        AVLNode* root;
        AVLNode* insertHelper(AVLNode*, int, string, string, string, string, string);
        AVLNode* deleteHelper(AVLNode*, int id);
        string inorderHelper(AVLNode*);
        string preorderHelper(AVLNode*);
        string postorderHelper(AVLNode*);

    public:
        //Default Constructor
        AVLTree() {root = NULL;}
        AVLTree(int, string, string, string, string, string);

        void insert(int, string, string, string, string, string);
        void recursiveInsert(int, string, string, string, string, string);
        void deleteNode(int);

        AVLNode* getRoot() {return root;}
        string inorderNode() {return inorderHelper(root);}
        string preorderNode() {return preorderHelper(root);}
        string postorderNode() {return postorderHelper(root);}

        AVLNode* rotateRight(AVLNode*);
        AVLNode* rotateLeft(AVLNode*);
        int calculateHeight(AVLNode*);
        int calculateBalance(AVLNode*);
};

///////////////////////////////////////////
/////////// AVLNode Functions /////////////
///////////////////////////////////////////
AVLNode::AVLNode(int id, string first, string last, string dst, string pay, string book)
    {
        height = 0;
        clientID    = id;
        firstName   = first;
        surname     = last;
        destination = dst;
        payment     = pay;
        booking     = book;
        leftPtr     = NULL;
        rightPtr    = NULL;
    }


string AVLNode::getRecord()
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

string AVLNode::getRecordWithHeight()
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
    str.append(to_string(height));
    str.append(")");
    str.append("\n");
    return str;
}

void AVLNode::setRecord(string record)
{
    string clientIDString;
    istringstream clientRecord(record);
    clientRecord >> clientIDString >> firstName >> surname >> destination >> payment >> booking;
    clientID = stoi(clientIDString);
}

///////////////////////////////////////////
/////////// AVLTree Functions /////////////
///////////////////////////////////////////
AVLTree::AVLTree(int id, string first, string last, string dst, string pay, string book)
{
    AVLNode* node = new AVLNode(id, first, last, dst, pay, book);
    root = node;
}


AVLNode* AVLTree::insertHelper(AVLNode* ptr, int id, string first, string last, string dst, string pay, string book)
{
    if (ptr == NULL)
    {
        ptr = new AVLNode(id, first, last, dst, pay, book);
    }

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

    //Updates Ptr's Height
    ptr->setHeight(1 + max(calculateHeight(ptr->getLeftPtr()), calculateHeight(ptr->getRightPtr())));

    //If Sub-tree of ptr is now too heavy, the sub-tree is balanced
    //Checks if Left sub-tree is too heavy
    if (calculateBalance(ptr) > 1)
    {
        if (id < ptr->getLeftPtr()->getID())
        {
            return rotateRight(ptr);
        }
        else if (id > ptr->getLeftPtr()->getID())
        {
            ptr->setLeftPtr(rotateLeft(ptr->getLeftPtr()));
            return rotateRight(ptr);
        }
    }

    //Checks if Right sub-tree is too heavy
    if(calculateBalance(ptr) < -1)
    {

        if (id < ptr->getRightPtr()->getID())
        {
            return rotateLeft(ptr);
        }
        else if (id > ptr->getRightPtr()->getID())
        {
            ptr->setRightPtr(rotateRight(ptr->getRightPtr()));
            return rotateLeft(ptr);
        }
    }
    return ptr;
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
//  Modified version of the original code
AVLNode* AVLTree::deleteHelper(AVLNode* ptr, int id)
{
    if ( ptr == NULL)           // Node location is empty
        {
            return NULL;
        }

    // Else the tree/subtree is not empty
        AVLNode* successor;

        if( id > ptr->getID() )            // Search in Right sub-tree of ptr for the node
        {
            ptr->setRightPtr(deleteHelper(ptr->getRightPtr(), id));
            if ( calculateBalance(ptr) == 2)        // Subtree is too heavy on the leftPtr of ptr
            {
                if (calculateBalance(ptr->getLeftPtr()) >= 0)
                {
                    return rotateRight(ptr);
                }
                else
                {
                    ptr->setLeftPtr(rotateLeft(ptr->getLeftPtr()));
                    return rotateRight(ptr);
                }
            }
        }
        else
        {
            if( id < ptr->getID() )              // Search the Left sub-tree of ptr for the node
            {
                ptr->setLeftPtr( deleteHelper(ptr->getLeftPtr(), id));
                if( calculateBalance(ptr) == -2 )     // Re-balance: ptr is too heavy on the rightPtr
                {
                    if (calculateBalance(ptr->getRightPtr()) <= 0)
                    {
                        return rotateLeft(ptr);
                    }
                    else
                    {
                        ptr->setRightPtr(rotateRight(ptr->getRightPtr()));
                        return rotateLeft(ptr);
                    }
                }
            }
            else
            {
                //------------------------------------------------------//
                //     Node to to be deleted is found                   //
                //------------------------------------------------------//
                if ( ptr->getRightPtr() != NULL)
                {  //Go right and then deep left
                    successor = ptr->getRightPtr();
                    while ( successor->getLeftPtr() != NULL)
                    {
                        successor = successor->getLeftPtr();
                    }

                    // Copy the data in successor into ptr
                    ptr->setRecord( successor->getRecord() );

                    // Delete the successor node from ptr's right sub-tree
                    ptr->setRightPtr( deleteHelper( ptr->getRightPtr(), ptr->getID() ));

                    if (calculateBalance(ptr) == 2) // Rebalance: ptr is too heavy on the left
                    {
                        if (calculateBalance(ptr->getLeftPtr()) >= 0)
                            ptr = rotateLeft(ptr);
                        else
                            ptr = rotateRight(ptr);
                    }
                }
            else
                return(ptr->getLeftPtr());
            }
        }

    ptr->setHeight(calculateHeight(ptr));
    return(ptr);
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
AVLNode* AVLTree::rotateLeft(AVLNode* ptr)
{
    AVLNode* newParent;

    newParent = ptr->getRightPtr();
    ptr->setRightPtr(newParent->getLeftPtr());
    newParent->setLeftPtr(ptr);
    ptr->setHeight(calculateHeight(ptr));
    newParent->setHeight(calculateHeight(newParent));

    return (newParent);
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
AVLNode*  AVLTree::rotateRight(AVLNode* ptr)
{
    AVLNode* newParent;

    newParent = ptr->getLeftPtr();
    ptr->setLeftPtr( newParent->getRightPtr());
    newParent->setRightPtr(ptr);
    ptr->setHeight(calculateHeight(ptr));
    newParent->setHeight(calculateHeight(newParent));

    return (newParent);
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
int AVLTree::calculateHeight(AVLNode* ptr)
{
    int leftHeight, rightHeight;

    if( ptr == NULL)
        return(0);

    if (ptr->getLeftPtr() == NULL)
        leftHeight = 0;
    else
        leftHeight = 1 + ptr->getLeftPtr()->getHeight();

    if (ptr->getRightPtr() == NULL)
        rightHeight = 0;
    else
        rightHeight = 1 + ptr->getRightPtr()->getHeight();


    if (leftHeight > rightHeight)
        return(leftHeight);

    return(rightHeight);
}

//  Created by Dr. John Charlery on 10/25/2023.
//  Copyright (c) 2023 University of the West Indies. All rights reserved.
int AVLTree::calculateBalance(AVLNode* ptr)
{
    int leftHeight, rightHeight;

    if (ptr == NULL)
        return (0);

    if (ptr->getLeftPtr() == NULL)
        leftHeight = 0;
    else
        leftHeight = 1 + ptr->getLeftPtr()->getHeight();

    if (ptr->getRightPtr() == NULL)
        rightHeight = 0;
    else
        rightHeight = 1 + ptr->getRightPtr()->getHeight();

    return(leftHeight - rightHeight);
}

string AVLTree::inorderHelper(AVLNode* ptr)
{
    string str = "";

    if (ptr != NULL)
    {
        if (ptr->getLeftPtr() != NULL)
        {
            str.append(inorderHelper(ptr->getLeftPtr()));
        }
        str.append(ptr->getRecordWithHeight());
        if(ptr->getRightPtr() != NULL)
        {
            str.append(inorderHelper(ptr->getRightPtr()));
        }

    }
    return str;
}

string AVLTree::preorderHelper(AVLNode* ptr)
{
    string str = "";

    if (ptr != NULL)
    {
        str.append(ptr->getRecordWithHeight());
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


string AVLTree::postorderHelper(AVLNode* ptr)
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
        str.append(ptr->getRecordWithHeight());
    }
    return str;
}

void AVLTree::recursiveInsert(int id, string first, string last, string dst, string pay, string book)
{
    root = insertHelper(root, id, first, last, dst, pay, book);
}

void AVLTree::deleteNode(int id)
{
    root = deleteHelper(root, id);
}
#endif
