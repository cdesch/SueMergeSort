//
// Created by cj on 3/25/15.
//

#ifndef _SUEMERGESORT_SUELINKNODE_HPP_
#define _SUEMERGESORT_SUELINKNODE_HPP_
#include <string>

using namespace std;

class SueLinkNode{
private:
    string data;
    SueLinkNode* next;
public:

    SueLinkNode(){
        this->data = "";
        this->next = NULL;
    }
    SueLinkNode(string data){
        this->data = data;
        this->next = NULL;
    }
    SueLinkNode(string data, SueLinkNode* next){
        this->data = data;
        this->next = next;
    }

    ~SueLinkNode(){
        //TODO: tell the next node it is going to be deleted
        this->next->prepareForDeletion();
        delete this->next;
        this->prepareForDeletion();
    }

    //Setters and Getters
    void setData(string data){
        this->data = data;
    }
    string getData(){
        return this->data;
    }
    void setNext(SueLinkNode* next){
        this->next = next;
    }

    SueLinkNode* getNext(){
        return this->next;
    }

    //Helpers
    void setNextToNull(){
        this->next = NULL;
    }

    void prepareForDeletion(){
        this->setNextToNull();
    }

    friend bool operator> (SueLinkNode &node1, SueLinkNode &node2);
    friend bool operator<= (SueLinkNode &node1, SueLinkNode &node2);

    friend bool operator< (SueLinkNode &node1, SueLinkNode &node2);
    friend bool operator>= (SueLinkNode &node1, SueLinkNode &node2);

    //Operators



};

bool operator > (SueLinkNode &node1, SueLinkNode &node2)
{
    return node1.getData().compare(node2.getData()) == 1 ? true : false ;
}

bool operator<= (SueLinkNode &node1, SueLinkNode &node2)
{
    return node1.getData().compare(node2.getData()) <= 0 ? true : false ;
}

bool operator< (SueLinkNode &node1, SueLinkNode &node2)
{
    return node1.getData().compare(node2.getData()) < 0 ? true : false ;
}

bool operator>= (SueLinkNode &node1, SueLinkNode &node2)
{
    return node1.getData().compare(node2.getData()) >= 0 ? true : false ;
}
#endif //_SUEMERGESORT_SUELINKNODE_HPP_
