/**
 * @brief: A3.cpp.
 * 
 * @paragraph: Code Description - This code is used to demonstrate heap sorting.
 * 
 * @paragraph: Problem Statement - Implement heap sort. 1) Make an array of 15 numbers. Make sure the array is not sorted and the numbers do not make a heap. You may hard code this array in your main program. 2) Convert the array into a heap, using Floyd's algorithm. Print the array before making a heap, print the new array and print the new array after making it a heap. 3) Sort the array into descending order using heap sort method. Print the array.
 * 
 * @author: Shreyans Patel (SSP210009)
 */

#include <iostream>
#include <stdlib.h>

//The array given as per the problem statement. Make changes here to change the input as desired.
int DataArr[] = {40, 60, 20, 80, 50, 10, 30, 15, 5, 35, 25, 45, 55, 70, 90};

//Derive number of elements from the array
int DataArrElementNum = (sizeof(DataArr)/sizeof(DataArr[0]));

/**
 * @brief: printArray.
 * @details: Used to print the array passed.
 * @param: iArr (Input) - Array to print.
 * @param: iArrSize (Input) - Array size.
 * @return none.
 */
void printArray(int *iArr, int iArrSize)
{
    std::cout<<"====>   ";

    //Print individual elements of the array
    for(int tIterator = 0; tIterator < iArrSize; tIterator++)
    {
        std::cout<<iArr[tIterator]<<"    ";
    }

    std::cout<<std::endl<<std::endl;

    return;
}

/**
 * @brief: copyArrayElements.
 * @details: Used to copy elements from heap to normal array or normal array to heap according to the value of a flag.
 * @param: iHeapArr (Input) - Heap array.
 * @param: iOriginalArr (Input) - Original array.
 * @param: iMakeAHeap (Input) - true: Copy from original array to heap array. false: Copy from heap array to original array.
 * @return none.
 */
void copyArrayElements(int *iHeapArr, int *iOriginalArr, bool iMakeAHeap)
{
    for(int tIterator = 0; tIterator < DataArrElementNum; tIterator++)
    {
        //Copy operation is from original array to heap array
        if(iMakeAHeap)
        {
            iHeapArr[tIterator+1] = iOriginalArr[tIterator];
        }

        //Copy operation is from head array to original array
        else
        {
            iOriginalArr[tIterator] = iHeapArr[tIterator+1];
        }
    }
}

/**
 * @brief: percolateDown.
 * @details: Used to percolate down from the given index in the heap.
 * @param: iHeapArr (Input) - Heap array.
 * @param: iIndex (Input) - The start index for percolate down.
 * @return none.
 */
void percolateDown(int *iHeapArr, int iIndex)
{
    //Used to check if a child with smaller value is found or not. If found, this variable gives its location
    int tSwapIdx = -1;

    while(iIndex <= iHeapArr[0])
    {
        //Both child are present. Compare present element with both child and find the smaller child if exist
        if(iHeapArr[0] >= ((iIndex * 2) + 1))
        {
            (iHeapArr[(iIndex * 2) + 1] < iHeapArr[iIndex * 2]) ? 
            (iHeapArr[(iIndex * 2) + 1] < iHeapArr[iIndex] ? tSwapIdx = (iIndex * 2) + 1 : tSwapIdx = -1) :
            (iHeapArr[(iIndex * 2)] < iHeapArr[iIndex] ? tSwapIdx = iIndex * 2 : tSwapIdx = -1);
        }

        //Only one child is present. Compare present element with the child and find if child is smaller
        else if(iHeapArr[0] >= (iIndex * 2))
        {
            if(iHeapArr[(iIndex * 2)] < iHeapArr[iIndex])
            {
                tSwapIdx = iIndex * 2;
            }
        }

        //No child is present. Percolate down further not possible. Return
        else
        {
            break;
        }

        //Found a smaller child. Now replace smaller child with present element and percolate down again
        if(-1 != tSwapIdx)
        {
            int tTemp = iHeapArr[tSwapIdx];
            iHeapArr[tSwapIdx] = iHeapArr[iIndex];
            iHeapArr[iIndex] = tTemp;
            iIndex = tSwapIdx;
            tSwapIdx = -1;
        }

        //Smaller child not found so further percolate down is not required. Return
        else
        {
            return;
        }
    }
}

/**
 * @brief: convertToMinHeap.
 * @details: Convert the given array to a min heap using Floyd's Algorithm.
 * @param: iHeapArr (Input) - Heap array.
 * @return none.
 */
void convertToMinHeap(int *iHeapArr)
{
    //Used to find last parent to start from
    int tIdx = iHeapArr[0] / 2;

    //Used to check if a child with smaller value is found or not. If found, this variable gives its location
    int tSwapIdx = -1;

    while(1 <= tIdx)
    {
        //Both child are present. Compare present element with both child and find the smaller child if exist
        if(iHeapArr[0] >= ((tIdx * 2) + 1))
        {
            (iHeapArr[(tIdx * 2) + 1] < iHeapArr[tIdx * 2]) ? 
            (iHeapArr[(tIdx * 2) + 1] < iHeapArr[tIdx] ? tSwapIdx = (tIdx * 2) + 1 : tSwapIdx = -1) :
            (iHeapArr[(tIdx * 2)] < iHeapArr[tIdx] ? tSwapIdx = tIdx * 2 : tSwapIdx = -1);
        }

        //Only one child is present. Compare present element with the child and find if child is smaller
        else if(iHeapArr[0] >= (tIdx * 2))
        {
            if(iHeapArr[(tIdx * 2)] < iHeapArr[tIdx])
            {
                tSwapIdx = tIdx * 2;
            }
        }

        //Found a smaller child. Now replace smaller child with present element and percolate down
        if(-1 != tSwapIdx)
        {
            int tTemp = iHeapArr[tSwapIdx];
            iHeapArr[tSwapIdx] = iHeapArr[tIdx];
            iHeapArr[tIdx] = tTemp;
            percolateDown(iHeapArr,tSwapIdx);
            tSwapIdx = -1;
        }

        //For going to the next parent
        tIdx -= 1;
    }
}

/**
 * @brief: heapSort.
 * @details: Perform heap sort for min heap.
 * @param: iHeapArr (Input) - Heap array.
 * @return none.
 */
void heapSort(int *iHeapArr)
{
    while(1 != iHeapArr[0])
    {
        int tTemp = iHeapArr[iHeapArr[0]];
        iHeapArr[iHeapArr[0]] = iHeapArr[1];
        iHeapArr[1] = tTemp;
        iHeapArr[0] = iHeapArr[0] - 1;
        percolateDown(iHeapArr,1);
    }

    //Sorting is done so modify 0th index of the heap to show the number of elements in it
    iHeapArr[0] = DataArrElementNum;
}

int main()
{
    //Print original array
    std::cout<<std::endl<<"Given array to sort:"<<std::endl<<std::endl;
    printArray(&DataArr[0], DataArrElementNum);

    //Make a new array with an extra element for storing number of elements at 0th index. This array will further be made into a heap
    int tHeapArr[DataArrElementNum+1];
    tHeapArr[0] = DataArrElementNum;

    copyArrayElements(&tHeapArr[0], &DataArr[0], true);
    std::cout<<std::endl<<"Array before making a heap:"<<std::endl<<std::endl;
    printArray(&tHeapArr[0], DataArrElementNum+1);

    //Now convert the array to heap
    convertToMinHeap(&tHeapArr[0]);
    std::cout<<std::endl<<"Array after making a heap:"<<std::endl<<std::endl;
    printArray(&tHeapArr[0], DataArrElementNum+1);

    //Print heap before heap sort
    std::cout<<std::endl<<"Before heap sort:"<<std::endl<<std::endl;
    printArray(&tHeapArr[0], DataArrElementNum+1);

    //Heap sort and then print the sorted heap
    heapSort(&tHeapArr[0]);
    std::cout<<std::endl<<"After heap sort:"<<std::endl<<std::endl;
    printArray(&tHeapArr[0], DataArrElementNum+1);

    //Modify the original array using the sorted heap to make it sorted and print it
    copyArrayElements(&tHeapArr[0], &DataArr[0], false);
    std::cout<<std::endl<<"Array after sorting:"<<std::endl<<std::endl;
    printArray(&DataArr[0], DataArrElementNum);
    
    return 0;
}