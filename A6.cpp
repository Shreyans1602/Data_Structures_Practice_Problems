/**
 * @brief: A6.cpp.
 * 
 * @paragraph: Code Description - This code is used to implement hash table.
 * 
 * @paragraph: Problem Statement - Pick 20 words of various lengths, maximum length 8 and minimum length 3. The words will be of letters a-zA-Z and the space character. Insert them into a hash table. You can use a library for only the hash function. The collision resolution scheme should be open addressing - quadratic. Initially the table size is 31. The program should increase the table size and rehash at load factor of 0.5, it should automatically determine when the load factor goes above 0.5. So, after you inserted about 15 or 16 words, your program automatically doubles the table size and re-inserts (automatically) the old words and then continue the insert of additional words. You do not have to insert the words manually (one by one) but you can add the words in a file and let your program read from the file. At the end print the total number of collisions you get. Submit your code and print screen of your execution.
 * 
 * @author: Shreyans Patel (SSP210009)
 */
#include<iostream>
#include<string.h>

//Necessary Defines
#define NUM_WORDS 20        //Number of words in the list
#define NUM_CHARACTERS 27   //Alphabets and space
#define MAX_LEN 8           //Maximum length of a word

//This hardcoded list represents the words to be inserted into the hash table. Change the defines NUM_WORDS and MAX_LEN according to the changes you make in this list
const char* mWordsArr[NUM_WORDS] = {
    "Shreyans",
    "The",
    "Universe",
    "Texas",
    "Dallas",
    "And",
    "Cartoon",
    "Apology",
    "Discuss",
    "Coat",
    "Sample",
    "Fin Tech",
    "Pillow",
    "Treaty",
    "Rank",
    "Choke",
    "Camera",
    "Receipt",
    "Tissue",
    "Sheet",
};

//Global Variables
char** mDataTable = NULL;
bool* mVacancyArr = NULL;
int mTableSize = 0;
int mCollisions = 0;
int mTotalCollisions = 0;

/**
 * @brief: initializeTable.
 * @details: Used to initialize the hash table and dependent list of vacant indexes with given size.
 * @param: iSize - Size to allocate.
 * @return none.
 */
void initializeTable(int iSize)
{
    if(mVacancyArr != NULL)
    {
        delete mVacancyArr;
        mVacancyArr = NULL;
    }

    if(mDataTable != NULL)
    {
        for(int tIterator = 0; tIterator < mTableSize; tIterator++)
        {
            if(mDataTable[tIterator] != NULL)
            {
                delete mDataTable[tIterator];
                mDataTable[tIterator] = NULL;
            }
        }

        delete mDataTable;
        mDataTable = NULL;
    }

    mTableSize = iSize;
    
    mVacancyArr = new bool[iSize];

    if(mVacancyArr == NULL)
    {
        std::cout<<"Memory Allocation Failed"<<std::endl;
        return;
    }

    for(int tIterator = 0; tIterator < mTableSize; tIterator++)
    {
        mVacancyArr[tIterator] = false;
    }

    mDataTable = new char*[iSize];

    if(mDataTable == NULL)
    {
        std::cout<<"Memory Allocation Failed"<<std::endl;
        return;
    }

    for(int tIterator = 0; tIterator < mTableSize; tIterator++)
    {
        mDataTable[tIterator] = new char[MAX_LEN];
        
        if(mDataTable[tIterator] == NULL)
        {
            std::cout<<"Memory Allocation Failed"<<std::endl;
            return;
        }
    }

    std::cout<<"Table Size is: "<<mTableSize<<std::endl;
}

/**
 * @brief: hashFunction.
 * @details: Used to get an insertion index by converting a string into a unique key.
 * @param: iString - String to convert into a key.
 * @return int - Insertion index.
 */
int hashFunction(const char* iString) 
{
    std::string tString = iString;
    int tHashCode = 0;

    for(int tIterator = 0; tIterator < tString.length(); tIterator++) 
    {
        tHashCode = NUM_CHARACTERS * tHashCode + tString[tIterator];
    }

    tHashCode %= mTableSize;

    if(tHashCode < 0)
    {
        tHashCode += mTableSize;
    }

    return tHashCode;
}

/**
 * @brief: calculateLoad.
 * @details: Used to get the load factor of the table according to the number of inserted keys.
 * @param: iNumOfKeys - Number of keys in the table.
 * @return float - The load factor.
 */
float calculateLoad(int iNumOfKeys)
{
    return ((float)iNumOfKeys / (float)mTableSize);
}

/**
 * @brief: isPrimeCheck.
 * @details: Check if the number is prime.
 * @param: iNumber - Number for checking.
 * @return bool - True: Prime, False: Not Prime.
 */
bool isPrimeCheck(int iNumber) 
{
   if((iNumber == 2) || (iNumber == 3))
   {
       return true;
   }
   
   if((iNumber == 1) || (iNumber % 2 == 0))
   {
       return false;
   }

   for(int tIterator = 3; tIterator * tIterator <= iNumber; tIterator += 2)
   {
       if (iNumber % tIterator == 0)
       {
           return false;  
       }
   }

   return true;
}

/**
 * @brief: findNextPrime.
 * @details: Find the next prime number greater than or equal to the given number.
 * @param: iNumber - Number for checking.
 * @return int - Next prime number greater than or equal to the given number.
 */
int findNextPrime(int iNumber) 
{
   if(iNumber <= 0)
   {
       iNumber == 3;
   }

   if(iNumber % 2 == 0)
   {
       iNumber++;
   }

   for(; false == isPrimeCheck(iNumber); iNumber += 2);
   {
       return iNumber;
   }
}

/**
 * @brief: insertIntoHashTable.
 * @details: Insert the given string into the hash table.
 * @param: iString - String to insert.
 * @return none.
 */
void insertIntoHashTable(const char* iString)
{
    int tInsertIndex = hashFunction(iString);
    int tTempInsertIndex = tInsertIndex;
    int tMultiplier = 1;

    while(true == mVacancyArr[tTempInsertIndex])
    {
        std::cout<<"<<< Collision detected for '"<<iString<<"' at index "<<tTempInsertIndex<<" >>>"<<std::endl;
        mCollisions++;
        mTotalCollisions++;
        tTempInsertIndex = (tInsertIndex + (tMultiplier*tMultiplier)) % mTableSize;
        tMultiplier++;
    }

    std::cout<<"Inserting '"<<iString<<"' at index "<<tTempInsertIndex<<std::endl;
    strcpy(mDataTable[tTempInsertIndex], iString);
    mVacancyArr[tTempInsertIndex] = true;
}

/**
 * @brief: performInsertion.
 * @details: Used to insert the given word list into the hash table one at a time.
 * @return none.
 */
void performInsertion(void)
{
    std::cout<<std::endl<<"Starting Insertion: "<<std::endl;
    bool tInsertionDone = false;
    int tCount = 0;

    while(false == tInsertionDone)
    {
        for(int tIterator = 0; tIterator < NUM_WORDS; tIterator++)
        {
            insertIntoHashTable(mWordsArr[tIterator]);
            tCount++;
            
            if(0.5 <= calculateLoad(tCount))
            {
                std::cout<<std::endl<<"Load factor is >= 0.5, initializing resize process..."<<std::endl<<std::endl;
                tInsertionDone = false;
                break;
            }

            tInsertionDone = true;
        }

        if(false == tInsertionDone)
        {
            tCount = 0;
            mCollisions = 0;
            int tNewSize = mTableSize * 2;

            std::cout<<"New table size is: "<<tNewSize<<std::endl;

            tNewSize = findNextPrime(tNewSize);
            std::cout<<"We use the prime greater than or equal to the required size. Hence, new size is: "<<tNewSize<<std::endl;

            initializeTable(tNewSize);

            std::cout<<std::endl<<"Starting Re-insertion: "<<std::endl;
        }

        else
        {
            std::cout<<std::endl<<"Insertion Successful"<<std::endl;
            std::cout<<std::endl<<"Total collisions (Only Final Table): "<<mCollisions<<std::endl;
            std::cout<<"Total collisions (Since Beginning): "<<mTotalCollisions<<std::endl;
        }
    }
}

/**
 * @brief: main.
 * @details: Main Function.
 * @return int.
 */
int main(void)
{
    //Print list of words to insert
    std::cout<<"List of words to insert: ";
    for(int tIterator = 0; tIterator < NUM_WORDS; tIterator++)
    {
        if(tIterator == (NUM_WORDS-1))
        {
            std::cout<<mWordsArr[tIterator];
            break;
        }
        std::cout<<mWordsArr[tIterator]<<",";
    }
    std::cout<<std::endl<<std::endl;

    //Initialize the table with size 31 as given in the problem statement
    initializeTable(31);

    //Perform insertion of words into the table
    performInsertion();
    return 0;
}