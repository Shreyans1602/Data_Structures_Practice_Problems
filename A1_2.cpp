/**
 * @brief: A1_2.cpp.
 * 
 * @paragraph: Code Description - This code is used to demonstrate a tertiary search algorithm on a sorted array of integers. It returns the index of the key passed by the user, if the key is available in the array. Otherwise, it intimates the user that key is not found.
 * 
 * @paragraph: Problem Statement - We covered binary search algorithm for an array. Write program similar to binary search, but now divide the list into 3 parts each time. So this would be tertiary search algorithm. Your program must be recursive, submit the code and screen shot of executions. Run it 2 times, once try to search a number in the list. Second time search a number not in the list. 
 * 
 * @author: Shreyans Patel (SSP210009)
 */

#include <iostream>
#include <stdlib.h>

//Number of elements. Change this to change the number of elements you need in the array.
#define ARRAY_MAX 15

/**
 * @brief: printArray.
 * @details: Used to print the array contents.
 * @param: iArr (Input) - Array that needs to be printed.
 * @return none.
 */
void printArray(int iArr[ARRAY_MAX])
{
    std::cout<<"====>   ";

    for(int tIterator = 0 ; tIterator<ARRAY_MAX ; tIterator++)
    {
        std::cout<<iArr[tIterator]<<"   ";
    }

    std::cout<<std::endl<<std::endl;
}

/**
 * @brief: sortArray.
 * @details: Used to sort the array in ascending order.
 * @param: iArr (Input) - Array that needs to be sorted.
 * @return none.
 */
void sortArray(int iArr[ARRAY_MAX])
{
    int tTemp = 0;
    bool tSwap = true;

    while(true == tSwap)
    {
        tSwap = false;

        for(int tIterator = 0 ; tIterator<(ARRAY_MAX-1) ; tIterator++)
        {
            if(iArr[tIterator] > iArr[tIterator+1])
            {
                tTemp = iArr[tIterator];
                iArr[tIterator] = iArr[tIterator+1];
                iArr[tIterator+1] = tTemp;
                tSwap = true;
            }
        }
    }
}

/**
 * @brief: tertiarySearch.
 * @details: Used to search the key in the array using tertiary search algorithm.
 * @param: iLeft (Input) - Left value of the array.
 * @param: iRight (Input) - Right value of the array.
 * @param: iKey (Input) - Key to find in the array.
 * @param: iArr (Input) - The array in which we have to search the key.
 * @return int - The index at which the key is found. Returns -1 if key is not found.
 */
int tertiarySearch(int iLeft, int iRight, int iKey, int iArr[ARRAY_MAX])
{
    //If the array contains more than or atleast 1 element.
    if(iRight >= iLeft) 
    {
        //Find the two middle points tMid1 and tMid2.
        int tMid1 = iLeft + ((iRight - iLeft) / 3);
        int tMid2 = iRight - ((iRight - iLeft) / 3);
 
        //Is the tMid1 same as the key? If yes, then return tMid1.
        if(iArr[tMid1] == iKey)
        {
            return tMid1;
        }

        //Is the tMid2 same as the key? If yes, then return tMid2.
        if(iArr[tMid2] == iKey) 
        {
            return tMid2;
        }
 
        //If key is not a mid point. Find the range in which key is present.
        //Key is less than tMid1.
        if(iKey < iArr[tMid1])
        {
            //Find the key between iLeft and tMid1.
            return tertiarySearch(iLeft, tMid1 - 1, iKey, iArr);
        }
        //Key is more than tMid2.
        else if (iKey > iArr[tMid2])
        {
            //Find the key between tMid2 and iRight.
            return tertiarySearch(tMid2 + 1, iRight, iKey, iArr);
        }
        //Key is more than tMid1 and less than tMid2.
        else 
        {
            //Find the key between tMid1 and tMid2.
            return tertiarySearch(tMid1 + 1, tMid2 - 1, iKey, iArr);
        }
    }

    //Key is not present in the array. Return -1 to indicate "Not found" status.
    return -1;
}

int main()
{
    std::cout<<"Initializing.....Creating Array.....Target: "<<ARRAY_MAX<<" elements....."<<std::endl<<std::endl;
    
    int tArr[ARRAY_MAX];
    int tResult = -1;
    int tKey = 0;

    //Loop for creating the array with random data and number of elements = ARRAY_MAX.
    for(int tIterator = 0 ; tIterator<ARRAY_MAX ; tIterator++)
    {
        tArr[tIterator] = rand() % 50 + 1;   //Assign a random value in range [1,50] for array's data.
    }

    sortArray(tArr);

    std::cout<<"Created array is given below: "<<std::endl<<std::endl;

    printArray(tArr);

    std::cout<<std::endl<<"Enter the key you want to search in the array: ";
    std::cin>>tKey;

    std::cout<<std::endl<<"Searching....."<<std::endl<<std::endl;

    tResult = tertiarySearch(0,(ARRAY_MAX-1),tKey,tArr);

    if(-1 == tResult)
    {
        std::cout<<"Key not found."<<std::endl<<std::endl<<"Exiting....."<<std::endl;
        return 0;
    }

    std::cout<<"Key "<<tKey<<" found at index: "<<tResult<<std::endl<<std::endl<<"Exiting....."<<std::endl;

    return 0;
}