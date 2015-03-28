#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include "SueLinkedList.hpp"
#include "SueLinkNode.hpp"
#include <sys/time.h>
#include <sys/resource.h>
using namespace std;

//Mergesort our way
// -- number of elements
// -- numbers
// -- letters
// -- string
// - Linked Lists
//

/*
Folder - zip
 - The alogrithm code. your final merge
 - Word Document Analysis
 - All the workcode
 */
class list
{
protected:


public:
    list();
    void print();
};

//struct Link
struct Link{
    Link * next; //Pointer to next node
    string dataItem; // declares item as a string
    Link(string data, Link * nextNode){
        dataItem = data; //sets a string in the list to variable item
        next = nextNode; // pointer to next item
    }
};

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
static char const alphanum[] =
        "0123456789";
        //        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        //        "abcdefghijklmnopqrstuvwxyz";

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

void print(Link * list){ //prints the list of items
    while (list != NULL){ //continues until the end of the list is reached
        cout << list-> dataItem << " "; // list the string and separate with spaces
        list = list->next; // Move along one node, list points to the node coming after the node it was previously pointing to set up for priting item
    }
    cout << endl;
}

void splitList(Link * list, Link * &subListOne, Link * &subListTwo){ // splits one list into two sublists
    if (list == NULL) return; // if list is empty return
    // To split the list requires to traverse the list with two pointers, Node1 and Node2.
    Link* Node1; // Declares Node1
    Node1 = list; // Makes Node1 pointer identical to list pointer. The pointer Node1 is initialized to the first node of the list
    list = list->next; // Moves along one node, list points to the node coming after the node it was previously pointing to
    Node1->next = NULL; // Next pointer of the Node1 points to null
    subListOne = Node1; // Makes subLisOne pointer identical to Node1 pointer

    Link* Node2; // Declares Node2
    Node2 = list; // Makes Node2 pointer identical to list pointer. Since list has already traversed in the above code, Node2 starts at the third node.
    list = list->next; // Moves along another node, list points to the node coming after the node it was previously pointing to
    Node2->next = NULL; // Next pointer of the Node2 points to null
    subListTwo = Node2; // Makes subListTwo pointer identical to Node2 pointer

    if (list == NULL) return; // if list pointer points to Null then return

    while (list != NULL){ // while the list is not empty
        // while will end when Node2 becomes Null then Node1 will point to middle of list, which will be the last node of subList.
        Node1->next = list; // Node1 moves along one node. Sets pointer from the last node of list to the node just added to Node1.
        Node1 = list; // Makes Node1 pointer identical to list pointer
        list = list->next; // Move to next link in chain, list points to the node coming after the node it was previously pointing to
        Node1->next = NULL; // Next pointer of the Node1 points to null

        if (list == NULL) break; // Break if list pointer is pointing to Null
        // Node2 moves along two nodes everytime Node1 moves one node.
        Node2->next = list; // Sets pointer from the last node of list to the node just added
        Node2 = list; // Makes Node2 pointer identical to list pointer
        list = list->next; // Moves to next link in chain, list points to the node coming after the node it was previously pointing to
        Node2->next = NULL; // Next pointer of the Node2 list points to null
    }
}

Link * mergesTwoLists(Link * subListOne, Link * subListTwo, int printflag){ // merges two sublists to one sorted list
    Link * head = NULL; // Declares head pointer to Null
    Link * headSecondList = NULL; // Declares head of second sublist to Null
    while (subListOne != NULL && subListTwo != NULL){ // While there are items in both sublists then do the following until hit end both lists are empty
        Link * tempList; // Declares a temporary pointer.
        if (subListOne->dataItem <= subListTwo->dataItem){ // compare the nodes and checks to see if item in sublistOne is less than or equal to item in sublistTwo
            tempList = subListOne; // When subListTwo data item is less than or equal to subListOne data item then Make templist pointer identical to subListOne pointer
            subListOne = subListOne->next; // Moves to next link in chain, subListOne points to the node coming after the node it was previously pointing to
        }
        else{
            tempList = subListTwo; // When subListOne data item is less than subListTwo data item then Make templist pointer identical to subListTwo pointer
            subListTwo = subListTwo->next; // Moves to next link in chain, subListTwo points to the node coming after the node it was previously pointing to
        }
        if (head == NULL) // if head pointer is null
            head = tempList; // Makes head pointer identical to templist pointer
        else
            headSecondList->next = tempList; // Sets pointer from the last node of templist to the node just added to head of second sublist.
        headSecondList = tempList; // Makes head pointer of second sublist identical to templist pointer
        headSecondList->next = NULL; // Next pointer of the head of second sublist points to null
    }// end while

    if (subListOne != NULL) headSecondList->next = subListOne; // Copy into combined list if there are any remaining elements of subListOne
    else if (subListTwo != NULL) // Copy into combined list if there are any remaining elements of subListTwo
        headSecondList->next = subListTwo; // set pointer from the last node of subListTwo to the node just added to head of second sublist.

    if(printflag == 1) { // prints list if user requested to print list
        print(head); // calls print function to print sorted list
        cout<< endl;
    } // end if
    return head; //return sorted list
}


Link * recursiveMergeSort(Link  * list, int printflag){ // splits the list, sorts the separate lists, and merges sublists to one sorted list,
    if (list == NULL) return list;// if list pointer is null, then no items in list and return
    if (list->next == NULL){ // if there is only one item in list
        if(printflag == 1) { // prints list if user requested
            print(list); // calls print function to print list with one item
            cout<< endl;
        }
        return list;//if next pointer of list is null then return
    }
    Link * ListOne; // Declares ListOne pointer
    Link * ListTwo; // Declares ListTwo pointer
    splitList(list, ListOne, ListTwo); // calls function splitlist to split the list into two sublists - ListOne and ListTwo
    ListOne = recursiveMergeSort(ListOne, 0); // sorts sublist ListOne, recursively calls sort
    ListTwo = recursiveMergeSort(ListTwo, 0); // sorts sublist ListTwo, recursively calls sort
    list = mergesTwoLists(ListOne, ListTwo, printflag);// merges two sublists to one list
    return list; // return one sorted list
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


double mergeSortTest(int NumStrings, int stringLen, int printflag){

    string * arrayList = new string[NumStrings];

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
    if(printflag == 1){
        for (int i = 0; i < NumStrings; i++) cout << arrayList[i] << "   ";
        cout << endl << endl << "Time it took to sort list is: " << timeEnd-timeStart << " seconds" << endl; // prints the time the algorithm took by subtracting the end time and start time

    }
    return timeEnd - timeStart;
}



double SueLinkedListTest(int NumStrings, int stringLen, int printflag){

    SueLinkedList* myLinkedList = new SueLinkedList();


    for (int i = 0; i < NumStrings; i+=1) // Loops to set the random strings to the list
        myLinkedList->addNode(generateRandomStringOfLength(stringLen));

    if(printflag == 1){ // if user wants to print list then prints unsorted list
        cout << "unsorted Linked List: " ;
        for (int i = 0; i < NumStrings; i+=1){
            SueLinkNode* myNode = myLinkedList->getNode(i);
            cout << myNode->getData() << " ";
        }
        cout << endl;
    }

    double timeStart = getcputime(); // gets initial cpu start time
    myLinkedList->MSBMergeSort();
    double timeEnd = getcputime(); // gets cpu end time


    if(printflag == 1){ // if user wants to print list then prints unsorted list
        cout << std::fixed << "Time to sort list is: " << timeEnd-timeStart << " seconds" << endl; // prints the time the algorithm took by subtracting the end time and start time


        cout << "Sorted Linked List: " ;
        for (int i = 0; i < myLinkedList->getSize(); i+=1){
            SueLinkNode* myNode = myLinkedList->getNode(i);
            cout << myNode->getData() << " ";
        }
        cout << endl;
    }

    return timeEnd-timeStart;

}


double RecursiveMergeSortTest(int NumStrings, int stringLen, int printflag){


    Link * list = NULL; // initalize list pointerto Null


    for (int i = 0; i < NumStrings; i+=1) // Loops to set the random strings to the list
        list = new Link(generateRandomStringOfLength(stringLen), list); // builds a linked list that is generated by random strings of length stringlength
    if(printflag == 1){ // if user wants to print list then prints unsorted list
        cout << endl;
        cout << "Unsorted List\n";
        cout << "*************\n";
        print(list); // prints unsorted list
        cout << endl;
        cout << "Sorted List\n";
        cout << "***********\n";
    }
    double timeStart = getcputime(); // gets initial cpu start time
    recursiveMergeSort(list, printflag); // starts the sorting algorithm
    double timeEnd = getcputime(); // gets cpu end time

    if (printflag==1){
        cout << std::fixed << "Time to sort list is: " << timeEnd-timeStart << " seconds" << endl; // prints the time the algorithm took by subtracting the end time and start time
    }
    return timeEnd-timeStart;
}

void timeTrials(){

    //TODO: nextTime Copy SueLinkedList into a Template Based one
    int stringLen = 3;
    int NumStrings [12] = { 10, 50, 100, 200, 300, 500, 750, 1000, 2000, 5000, 10000, 20000 };
    int printflag = 0;

    cout << "Time Trials: " << endl;
    //TODO: Rename - Sue to Book version .... RecursiveTime to My2ndVersion..... mergeSort1stVersion
    cout << "Elements , \t SueLinkedListTime , \t RecursiveTime , \t MergeSort"  << endl;
    for (int i = 0; i < 10; i++){
        double sueLinkedListTrialTime =  SueLinkedListTest(NumStrings[i], stringLen, printflag);
        double recursiveMergeSortTrialTime = RecursiveMergeSortTest(NumStrings[i],stringLen, printflag);
        double mergeSortTrialTime = mergeSortTest(NumStrings[i],stringLen, printflag);
        cout << std::fixed << NumStrings[i] <<" \t" << sueLinkedListTrialTime << " \t" << recursiveMergeSortTrialTime << " \t "<< mergeSortTrialTime <<  endl;
    }
}

int main(){

    int timeTrialInputSelect;
    cout << "Time Trials? (select #1)" ;
    cin >> timeTrialInputSelect;

    if(timeTrialInputSelect == 1){
        timeTrials();
    }else{


        //TODO Ask user 1,2 or 3 for which one to run
        int NumStrings = 0; // initialize NumStrings which is the variable for number of strings
        int stringLen = 0; // initialize string length variable to 0
        int printflag = 0; // initialize print flag to 0
        Link * list = NULL; // initalize list pointerto Null
        cout << "Enter the number of strings to sort? ";
        cin >> NumStrings;
        cout << "Enter the string length? ";
        cin >> stringLen;
        cout << "Enter 1 if you would like to print the sorted list OR enter any other number to NOT print the list? ";
        cin >> printflag;

        //User input

        //mergeSortTest(NumStrings, stringLen, printflag);
        SueLinkedListTest(NumStrings, stringLen, printflag);
        RecursiveMergeSortTest(NumStrings,stringLen, printflag);

        //linkedListTestComparisonOperators();

    }




    return 0;
}
