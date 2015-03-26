#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include "SueLinkedList.hpp"
#include "SueLinkNode.hpp"

using namespace std;

//Mergesort our way
// -- number of elements
// -- numbers
// -- letters
// -- string
// - Linked Lists
//

// returns the time the program in seconds.
double getcputime(void){
    struct timeval time;
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    time = ru.ru_utime;
    double temp = (double)time.tv_sec + (double)time.tv_usec / 1000000.0;
    time = ru.ru_stime;
    temp+=(double)time.tv_sec + (double)time.tv_usec / 1000000.0;
    return temp;
}

//String Sample Context
static const char alphanum[] =
        "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

//Length of the string
int stringLength = sizeof(alphanum) - 1;

// Random Character Generator Function that was used in previous assignments
// returns a random character
char genRandomChar(){
    return alphanum[rand() % stringLength]; //character generator and returns a random character
}


string random(int len)
{
    string a = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string r;
    srand(time(NULL));
    for(int i = 0; i < len; i++) r.push_back(a.at(size_t(rand() % 62)));
    return r;
}

//Helper Functions
//Creates & returns random string to user input specified length
string generateRandomStringOfLength(int length){
    string myGeneratedString;
    for (int i = 0; i < length; i ++){
        myGeneratedString += genRandomChar();//Puts random string in specified length
    }
    return myGeneratedString; //returns the random string
}

//Merge Function combines arrayLeft and arrayRight.
// arrayLeft goes from head to the middle and arrayRight goes from middle + 1 to tail
void merge(string arrayList[], int left, int middle, int right){

    int i, j, k;
    int sizeLeft = middle - left + 1;
    int sizeRight =  right - middle;


    string* leftArray = new string[sizeLeft];   //dynamic declaration
    string* rightArray = new string[sizeRight]; //dynamic declaration
    //string leftArray[10000]; //temp arrays    //Static declaration
    //string rightArray[10000]; //temp arrays   //static declaration

    //Copy strings to temp arrays leftArray and rightArray
    for(i = 0; i < sizeLeft; i++) leftArray[i] = arrayList[left + i];
    for(j = 0; j < sizeRight; j++) rightArray[j] = arrayList[middle + 1 + j];

    // Merge the temp left and right arrays back into one arrayList
    i = 0;
    j = 0;
    k = left;
    while (i < sizeLeft && j < sizeRight)
    {

        if (leftArray[i] <= rightArray[j])
        {
            arrayList[k] = leftArray[i];
            i++;
        }
        else
        {
            arrayList[k] = rightArray[j];
            j++;
        }
        k++;
    }

    //Copy, if there are any, the remaining elements of left array
    while (i < sizeLeft){
        arrayList[k] = leftArray[i];
        i++;
        k++;
    }

    //Copy, if there are any, the remaining elements of right array
    while (j < sizeRight){
        arrayList[k] = rightArray[j];
        j++;
        k++;
    }
}

//
void mergeSort(string arrayList[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left)/2;
        mergeSort(arrayList, left, middle);
        mergeSort(arrayList, middle + 1, right);
        merge(arrayList, left, middle, right);
    }
}

////////MergeSortWithLinkedListBookVersion

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
        if(first < second){
            newHead = first;
            first = first->getNext();
            lastSmall = newHead;
        }else{
            newHead = second;
            second = second->getNext();
            lastSmall = newHead;
        }

        while(first != NULL && second != NULL){
            if(first < second){ ///I don't get it
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

void MSBMergeSort(SueLinkedList* linkedList){


    SueLinkNode* first = linkedList->getHead();
    SueLinkNode* last = linkedList->getTail();
    MSBRecMergeSort(first);
    if(first == NULL){
        last = NULL;
    }else{
        last = first;
        while(last->getNext() != NULL){
            last = last->getNext();
        }
    }

    cout << "First " ;
    for (int i = 0; i < linkedList->getSize(); i++){
        cout << first->getData() << " ";
        first = first->getNext();
    }
    cout << endl;

}



void mergeSortTest(){
    int NumStrings = 0; // initialize NumStrings which is the variable for number of strings
    int stringLen = 0; // initialize string length variable to 0
    int printflag = 0; // initialize print flag to 0
    cout << "Enter the number of strings to sort? ";
    cin >> NumStrings;
    string * arrayList = new string[NumStrings];
    cout << "Enter the string length? ";
    cin >> stringLen;
    cout << "Enter 1 if you would like to print the sorted list OR enter any other number to NOT print the list? ";
    cin >> printflag;
    for (int i = 0; i < NumStrings; i+=1) // Loops to set the random strings to the list
        arrayList[i] = generateRandomStringOfLength(stringLen); // builds a linked list that is generated by random strings of length stringlength
    if(printflag == 1){ // if user wants to print list then prints unsorted list
        cout << endl;
        cout << "Unsorted List\n";
        cout << "*****************\n";
        for (int i = 0; i < NumStrings; ++i)
            cout << arrayList[i] << "   ";
        cout << endl;
        cout << endl << "Begin Sort\n";
        cout << "*****************\n";
    }
    double timeStart = getcputime(); // gets initial cpu start time
    mergeSort(arrayList, 0, NumStrings-1);
    double timeEnd = getcputime(); // gets cpu end time
    if(printflag == 1) for (int i = 0; i < NumStrings; i++) cout << arrayList[i] << "   ";
    cout << endl << endl << "Time it took to sort list is: " << timeEnd-timeStart << " seconds" << endl; // prints the time the algorithm took by subtracting the end time and start time

}



void linkedListTest( int NumStrings, int stringLen){

    SueLinkedList* myLinkedList = new SueLinkedList();


    for(int i = 0; i < 10; i++){
       cout << random(stringLen) << " ";
    }
    cout << endl;

    for (int i = 0; i < NumStrings; i+=1) // Loops to set the random strings to the list
        myLinkedList->addNode(random(stringLen));

    cout << "unsorted Linked List: " ;
    for (int i = 0; i < NumStrings; i+=1){
        SueLinkNode* myNode = myLinkedList->getNode(i);
        cout << myNode->getData() << " ";
    }
    cout << endl;

    MSBMergeSort(myLinkedList);


    cout << "Sorted Linked List: " ;
    for (int i = 0; i < myLinkedList->getSize(); i+=1){
        SueLinkNode* myNode = myLinkedList->getNode(i);
        cout << myNode->getData() << " ";
    }
    cout << endl;

}

void linkedListTestComparisonOperators(){

    SueLinkNode* node1 = new SueLinkNode("1");
    SueLinkNode* node2 = new SueLinkNode("2");
    SueLinkNode* node3 = new SueLinkNode("2");
    SueLinkNode* node4 = new SueLinkNode("3");
    if(node1 < node2){
        cout << "Node 1 is less than node 2" << endl;
    }else{
        cout << "Node 1 is not less than node 2" << endl;
    }

    if(node2 < node1){
        cout << "Node 1 is less than node 2" << endl;
    }else{
        cout << "Node 1 is not less than node 2" << endl;
    }

    if(node1 > node2){
        cout << "Node 1 is greater than node 2" << endl;
    }else{
        cout << "Node 1 is not greater than node 2" << endl;
    }
    if(node2 > node1){
        cout << "Node 2 is greater than node 1" << endl;
    }else{
        cout << "Node 1 is not greater than node 2" << endl;
    }

    if(node2 <= node3){
        cout << "Node 2 is less than or equal node 3" << endl;
    }else{
        cout << "Node 2 is not less or equal than node 3" << endl;
    }

    if(node3 <= node2){
        cout << "Node 3 is less than or equal node 2" << endl;
    }else{
        cout << "Node 3 is not less or equal than node 2" << endl;
    }

    if(node2 >= node3){
        cout << "Node 2 is greater than or equal node 3" << endl;
    }else{
        cout << "Node 2 is not greater or equal than node 3" << endl;
    }






}

int main(){
    //mergeSortTest();
    linkedListTest(5,5);
    //linkedListTestComparisonOperators();

    return 0;
}
