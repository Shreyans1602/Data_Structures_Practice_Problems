/**
 * @brief: A1_1.cpp.
 * 
 * @paragraph: Code Description - This code is used to demonstrate ascending order sorting of a random un-ordered single linked list by the selective sorting algorithm such that we un-link and re-link the nodes and swap them rather than swapping just the data values of two nodes.
 * 
 * @paragraph: Problem Statement - Make a single linked list of integers. There should be at least 15 nodes. The list should not be sorted. Traverse the list. Now sort the list using selection sort. Do not use any other sorting algorithm. The list should be sorted such that your program unlinks the nodes and relinks them so that they are sorted. (DO NOT SWAP THE VALUES IN THE NODES). Use selection sort. Traverse the list again. Submit the complete code.
 * 
 * @author: Shreyans Patel (SSP210009)
 */

#include <iostream>
#include <stdlib.h>

//Number of nodes. Change this to change the number of nodes you need for creating the single linked list.
#define NODE_MAX 15

//Node of the linked list. Each node has an integer value and a pointer of type "Node".
struct Node
{
    int val;        //val: Variable with integer value.
    Node *next;     //next: Pointer to Node (Holds address of a Node).
    
    //Initializing structure members with default values.
    Node()
    {
        val = 0;
        next = NULL;
    }
};

//Initializing the head and tail pointer for the start and end of the single linked list.
Node *pHead = NULL;
Node *pTail = NULL;

/**
 * @brief: addNode.
 * @details: Used to add a node to the single linked list.
 * @param: iVal (Input) - Value to assign to the node's data.
 * @return none.
 */
void addNode(int iVal)
{
    Node *tpTemp = new Node;
    
    if(NULL == tpTemp)
    {
        std::cout << "Memory allocation failed. Try Again....." << std::endl;
        return;
    }

    tpTemp->val = iVal;
    tpTemp->next = NULL;

    //If head is NULL then the node being created is the first node.
    if(NULL == pHead)
    {
        pHead = tpTemp;
        pTail = tpTemp;
    }

    //The head node already exists so add a node to the end of the single linked list and update the tail.
    else
    {
        pTail->next = tpTemp;
        pTail = pTail->next;
    }
}

/**
 * @brief: printListData.
 * @details: Used to print the single linked list.
 * @param: ipHeadPtr (Input) - Head pointer of the single linked list to be printed.
 * @return none.
 */
void printListData(Node *ipHeadPtr)
{
    if(NULL == ipHeadPtr)
    {
        std::cout << "Head Pointer is NULL. The single linked list is empty. Exiting....." << std::endl;
        return;
    }

    Node *tpNodePtr = ipHeadPtr;  //Temporary Pointer equal to head. Used for iteration.

    std::cout << "====>   ";

    while(NULL != tpNodePtr)
    {
        std::cout << tpNodePtr->val <<"    ";
        tpNodePtr = tpNodePtr->next;
    }

    std::cout << std::endl;
}

/**
 * @brief: swapList.
 * @details: Used to swap two nodes of a single linked list by unlinking and re-linking.
 * @param: ipNode1 (Input) - Node 1 pointer.
 * @param: ipNode2 (Input) - Node 2 pointer.
 * @return none.
 */
void swapList(Node *ipNode1,Node *ipNode2)
{
    //Swapping not required if both the nodes are same.
    if(ipNode1 == ipNode2)
    {
        return;
    }

    Node *tpPrevNode1 = NULL;
    Node *tpPrevNode2 = NULL;
    Node *tpNode1 = pHead;
    Node *tpNode2 = pHead;
    Node *tpTemp = NULL;
    
    //Search for ipNode1.
    while(tpNode1 != NULL && tpNode1 != ipNode1)
    {  
        tpPrevNode1 = tpNode1;  
        tpNode1 = tpNode1->next;  
    }  
      
    //Search for ipNode2.
    while(tpNode2 != NULL && tpNode2 != ipNode2)
    {
        tpPrevNode2 = tpNode2;  
        tpNode2 = tpNode2->next;  
    }
      
    if(tpNode1 != NULL && tpNode2 != NULL) 
    {   
        //If previous node to tpNode1 is not NULL then, it will point to tpNode2.
        if(tpPrevNode1 != NULL)
        {
            tpPrevNode1->next = tpNode2; 
        }       
        else
        {
            pHead = tpNode2;
        }
          
        //If previous node to tpNode2 is not NULL then, it will point to tpNode1.
        if(tpPrevNode2 != NULL)
        {
            tpPrevNode2->next = tpNode1;  
        }
        else
        {
            pHead  = tpNode1;
        }

        //Swaps the next nodes of tpNode1 and tpNode2.
        tpTemp = tpNode1->next;   
        tpNode1->next = tpNode2->next;   
        tpNode2->next = tpTemp;

        //If tpNode1 was tail, now tail is tpNode2 OR if tpNode2 was tail, now tail is tpNode1.
        if(pTail == tpNode1)
        {
            pTail = tpNode2;
        }
        else if(pTail == tpNode2)
        {
            pTail = tpNode1;
        }

        printListData(pHead);
    }
    else
    {
        std::cout << "Error in swapping function. Please check the code and try again....." << std::endl;
    }
}

/**
 * @brief: sortList.
 * @details: Used to sort the single linked list in ascending order.
 * @param: ipHeadPtr (Input) - Head pointer of the single linked list to be sorted.
 * @return none.
 */
void sortList(Node *ipHeadPtr)
{
    Node *tpNode1 = NULL;
    Node *tpNode2 = NULL;
    Node *tpTempNode = NULL;

    if(NULL == ipHeadPtr)
    {
        std::cout << "Head Pointer is NULL. The single linked list is empty. Exiting....." << std::endl;
        return;
    }

    tpNode1 = ipHeadPtr;

    //Outer loop for selection sort.
    while(NULL != tpNode1)
    {
        tpTempNode = tpNode1;
        tpNode2 = tpNode1->next;

        //Inner loop for selection sort.
        while(NULL != tpNode2)
        {
            //Outer loop is larger then selected value of inner loop.
            if(tpTempNode->val > tpNode2->val)
            {
                tpTempNode = tpNode2;   //tpTempNode points to the node containing the smaller value for swapping purpose.
            }

            tpNode2 = tpNode2->next;
        }

        //No need to swap if the selected node's value is already the smallest. Go to next node.
        if(tpNode1 == tpTempNode)
        {
            tpNode1 = tpNode1->next;
            continue;
        }

        //Swap tpNode1 with the node with smallest value (tpTempNode).
        swapList(tpNode1,tpTempNode);

        //Come back to the location of current outer loop iteration before going to the next since current iteration now holds replaced node.
        tpNode1 = tpTempNode;
        tpNode1 = tpNode1->next;
    }
}

int main()
{
    std::cout<<"Initializing.....Creating Nodes.....Target: "<<NODE_MAX<<" nodes....."<<std::endl<<std::endl;
    
    //Loop for creating the single linked list with random data and number of nodes = NODE_MAX.
    for(int tIterator = 0 ; tIterator<NODE_MAX ; tIterator++)
    {
        addNode(rand() % 50 + 1);   //Assign a random value in range [1,50] for node's data.
    }
    
    std::cout<<std::endl<<"Printing the single linked list data BEFORE sorting:"<<std::endl<<std::endl;
    printListData(pHead);

    std::cout<<std::endl<<"Performing sort....."<<std::endl;
    std::cout<<std::endl<<"Sorting Steps:"<<std::endl<<std::endl;
    
    printListData(pHead);
    sortList(pHead);

    std::cout<<std::endl<<std::endl<<"Printing the single linked list data AFTER sorting:"<<std::endl<<std::endl;
    printListData(pHead);

    return 0;
}