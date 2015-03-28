//
// Created by cj on 3/25/15.
//

#ifndef _SUEMERGESORT_SUELINKEDLIST_HPP_
#define _SUEMERGESORT_SUELINKEDLIST_HPP_

#include "SueLinkNode.hpp"
#include <string>
#include <iostream>


using namespace std;




class SueLinkedList{

private:
    SueLinkNode* head;
    SueLinkNode* tail;
    int numNodes;

public:
    SueLinkedList(){
        this->head = NULL;
        this->tail = NULL;
        this->numNodes = 0;
    }

    SueLinkedList(SueLinkNode* head){
        this->head = head;
        this->tail = this->getUnknownTail(head);
    }


    SueLinkedList(SueLinkNode* head, SueLinkNode *tail, int numNodes){
        this->head = head;
        this->tail = tail;
        this->numNodes = numNodes;
    }

    ~SueLinkedList(){
        //this->head-
        cout << __PRETTY_FUNCTION__ << endl;
        this->head->prepareForDeletion();
        delete this->head;
        this->head = NULL;
        this->tail = NULL;
        this->numNodes = 0;
    }

    //Helper Functions
    void addNode(string data){
        SueLinkNode* newNode = new SueLinkNode(data);
        this->addNode(newNode);
    }

    void addNode(SueLinkNode* node){
        //what if this is the first node to be added?
        if(this->head == NULL){
            //If head is ==  to NULL, it is the first node

            this->setHead(node);
            this->setTail(node);
        }else{
            //If it is not the first song, we can assume it needs to go on to the end
            //Check to see if the tail is equal to null
            if(this->tail == NULL){
                cout << "ERROR: Tail is empty :: Do something" << endl;
            }

            //Get the last SueLinkNode
            SueLinkNode* lastNode = this->getTail();
            lastNode->setNext(node); //Set the newLastNode to next
            this->setTail(node); // New last node
        }
        this->numNodes++;
    }

    //Setters and Getters
    void setHead(SueLinkNode* node){
        this->head = node;
    }
    SueLinkNode* getHead(){
        return this->head;
    }
    void setTail(SueLinkNode* node){
        this->tail = node;
    }
    SueLinkNode* getTail(){
        return this->tail;
    }

    SueLinkNode* getNode(int index){
        //check if index it out of bounds
        if(index >= this->numNodes || index < 0){
            cout << "ERROR: Index is out of bounds" << endl;
            return NULL;
        }

        //Check to see if the index is at the beginning or at the end.
        if(index == 0 ){
            return this->head;
        }else if (index == this->numNodes-1){
            return this->tail;
        }

        SueLinkNode* currentNode = this->head;
        for (int i = 0; i < this->numNodes; i++) {
            if (index == i) {
                return currentNode;
            } else {
                currentNode = currentNode->getNext();
            }
        }

        //it will never run this line
        return currentNode;
    }

    int getSize(){
        return this->numNodes;
    }

    //Swap Nodes

    //Compares Nodes
    // returns -1 if A is less than B; 0 if Equal; 1 if A greater than B
    int compareNodes(SueLinkNode* nodeA, SueLinkNode* nodeB ){
        return this->compareNodes(nodeA->getData(), nodeB->getData());
    }

    // returns -1 if A is less than B; 0 if Equal; 1 if A greater than B
    int compareNodes(string stringA, string stringB){
        return stringA.compare(stringB);
    }

    SueLinkNode* getUnknownTail(SueLinkNode* node){
        int i = 0;
        while(node->getNext() != NULL){
            node = node->getNext();
            i++;
        }
        this->numNodes = i; //Reset our number of nodes since we didn't know what it was.
        return node;
    }

    void MSBDivide(SueLinkNode* first, SueLinkNode* &second ){
        SueLinkNode* middle;
        SueLinkNode* current;

        //Check for empty list
        if(first == NULL){
            second = NULL;
        }else if (first->getNext() == NULL){
            second = NULL;
        }else{
            middle = first;
            current = first->getNext();
            if(current != NULL){
                current = current->getNext();
            }
            while(current != NULL){
                middle = middle->getNext();
                current = current->getNext();
                if(current != NULL){
                    current = current->getNext();
                }
            }
            second = middle->getNext();
            middle->setNext(NULL);
        }
    }

    SueLinkNode* MSBMergeList(SueLinkNode* first, SueLinkNode* second){
        SueLinkNode* lastSmall;
        SueLinkNode* newHead;

        if(first == NULL){
            return second;
        }else if(second == NULL){
            return first;
        }else{
            if(first->getData() < second->getData()){
                newHead = first;
                first = first->getNext();
                lastSmall = newHead;
            }else{
                newHead = second;
                second = second->getNext();
                lastSmall = newHead;
            }

            while(first != NULL && second != NULL){
                if(first->getData() < second->getData()){
                    lastSmall->setNext(first);
                    lastSmall = lastSmall->getNext();
                    first = first->getNext();
                }else{
                    lastSmall->setNext(second);
                    lastSmall = lastSmall->getNext();
                    second = second->getNext();
                }
            }

            if(first == NULL){
                lastSmall->setNext(second);
            }else{
                lastSmall->setNext(first);
            }

            return newHead;

        }

    }

    void MSBRecMergeSort(SueLinkNode* & head){
        SueLinkNode* otherHead;
        if(head != NULL){
            if (head->getNext() != NULL){
                MSBDivide(head,otherHead);
                MSBRecMergeSort(head);
                MSBRecMergeSort(otherHead);
                head = MSBMergeList(head,otherHead);
            }
        }


    }

    void MSBMergeSort(){
        MSBRecMergeSort(this->head);
        if(this->head == NULL){
            this->tail = NULL;
        }else{
            this->tail = this->head;
            while(this->tail->getNext() != NULL){
                this->tail = this->tail->getNext();
            }
        }

    }



};

#endif //_SUEMERGESORT_SUELINKEDLIST_HPP_
