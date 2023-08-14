/**
 * @brief: A2.cpp.
 * 
 * @paragraph: Code Description - This code is used to demonstrate a delete operation from a Binary Search Tree (BST).
 * 
 * @paragraph: Problem Statement - We have discussed Binary Search Trees (BST). Write a program to implement a delete operation from BST. You will have to write the program to insert nodes in the BST also (we already did the algorithm in detail in the class for insert). DO NOT USE ANY LIBRARIES. Insert the following nodes in the order mentioned here. 40, 60, 20, 80, 50, 10, 30, 15, 5, 35, 25, 45, 55, 70, 90, 32, 33, 48, 46. Do an inorder traversal. Now delete 40 (you decide predecessor or successor). Do inorder traversal again. Now delete 20. Do inorder traversal.
 * 
 * @author: Shreyans Patel (SSP210009)
 */

#include <iostream>
#include <stdlib.h>

//Defines for the two values to be deleted as per the problem statement. Change these to test different values. Add defines for testing more values. main function contents will change accordingly if the defines are increased or decreased. Reference can be taken from code in main function.
#define VAL_1_TO_DELETE 40
#define VAL_2_TO_DELETE 20

//The array given as per the problem statement. Make changes here and update the number of elements to change the input as desired.
int DataArr[19] = {40, 60, 20, 80, 50, 10, 30, 15, 5, 35, 25, 45, 55, 70, 90, 32, 33, 48, 46};

//Derive number of elements from the array
int DataArrElementNum = (sizeof(DataArr)/sizeof(DataArr[0]));

//Node structure of the BST. Each node has an integer value and pointers to left child and right child of type "BSTNode".
struct BSTNode
{
    int val;            //val: Variable with integer value.
    BSTNode *left;      //left: Pointer to left child.
    BSTNode *right;     //right: Pointer to right child.
    
    //Initializing structure members with default values.
    BSTNode()
    {
        val = 0;
        left = NULL;
        right = NULL;
    }
};

//Initializing the root BSTNode pointer for the BST.
BSTNode *pRoot = NULL;

/**
 * @brief: getNewBSTNode.
 * @details: Used to create a new BSTNode with the given value.
 * @param: iVal (Input) - Value to assign to the node's data.
 * @return BSTNode* - The newly created BST node.
 */
BSTNode* getNewBSTNode(int iVal)
{
    BSTNode *tpNode = NULL;

    tpNode = new BSTNode;

    if(NULL == tpNode)
    {
        std::cout<<"Memory allocation failed.....exiting....."<<std::endl;
    }

    tpNode->val = iVal;

    return tpNode;
}

/**
 * @brief: insertBSTNode.
 * @details: Used to add a new node to the BST.
 * @param: iBSTNode (Input) - Node to add to the BST.
 * @return none.
 */
void insertBSTNode(BSTNode *iBSTNode)
{
    //New node is null.
    if(NULL == iBSTNode)
    {
        return;
    }

    //If root node is null, then the node being added is the first node to be added in the BST i.e. it becomes the root node.
    if(NULL == pRoot)
    {
        pRoot = iBSTNode;
        return;
    }

    BSTNode *tpBSTNode = pRoot;  //For traversal purpose without modifying the root node.

    while(true)
    {
        //If value of node to be added is greater than or equal to the current node.
        if(tpBSTNode->val <= iBSTNode->val)
        {
            //If right child is null, new node becomes the right child.
            if(NULL == tpBSTNode->right)
            {
                tpBSTNode->right = iBSTNode;
                return;
            }

            //Traverse to the right child.
            tpBSTNode = tpBSTNode->right;
        }

        //If value of node to be added is smaller than the current node.
        if(tpBSTNode->val > iBSTNode->val)
        {
            //If left child is null, new node becomes the left child.
            if(NULL == tpBSTNode->left)
            {
                tpBSTNode->left = iBSTNode;
                return;
            }

            //Traverse to the left child.
            tpBSTNode = tpBSTNode->left;
        }
    }
}

/**
 * @brief: createRequiredTree.
 * @details: Used to create BST automatically by adding all values of the pre-defined array to the BST. It is used for initialization.
 * @return none.
 */
void createRequiredTree(void)
{
    //This is used to automate the BST creation process and avoid hardcoded sections in main for adding each node to the BST.
    for(int tIterator = 0; tIterator < DataArrElementNum; tIterator++)
    {
        BSTNode *tpBSTNode = getNewBSTNode(DataArr[tIterator]);

        if(NULL == tpBSTNode)
        {
            return;
        }

        insertBSTNode(tpBSTNode);

        tpBSTNode = NULL;
    }
}

/**
 * @brief: printByInorderTraversal.
 * @details: Used to print the BST contents by inorder traversal.
 * @param: ipBSTRootNode (Input) - Root node of the BST.
 * @return none.
 */
void printByInorderTraversal(BSTNode *ipBSTRootNode)
{
    //Root is null.
    if(NULL == ipBSTRootNode)
    {
        return;
    }

    printByInorderTraversal(ipBSTRootNode->left);
    std::cout<<ipBSTRootNode->val<<"    ";          //For proper data representation.
    printByInorderTraversal(ipBSTRootNode->right);
}

/**
 * @brief: deleteBSTNode.
 * @details: Used to delete a BST node from the BST using its data value.
 * @param: iVal (Input) - Data value of the BST node to be deleted.
 * @return none.
 */
void deleteBSTNode(int iVal)
{
    //Root is null.
    if(NULL == pRoot)
    {
        return;
    }
    
    BSTNode *tpBSTNode = pRoot;                 //Used for traversal.
    BSTNode *tpBSTNodeToDelete = NULL;          //Used for saving the address of node to be deleted.
    BSTNode *tpBSTSuccessorNodeParent = NULL;   //Used for saving the address of successor's parent for linking/unlinking as per need.
    BSTNode *tpBSTSuccessorNode = NULL;         //Used for saving the successor of the node to be deleted.

    //This loop will traverse until we get the node which is to be deleted and it points to the parent of this node by tpBSTSuccessorNodeParent.
    while(true)
    {
        //Value matched. Update tpBSTNodeToDelete.
        if(tpBSTNode->val == iVal)
        {
            tpBSTNodeToDelete = tpBSTNode;
            break;
        }

        //Value is smaller, traverse to the left and find.
        if(tpBSTNode->val > iVal)
        {
            //Nothing left on left. Value not found.
            if(NULL == tpBSTNode->left)
            {
                return;
            }

            tpBSTSuccessorNodeParent = tpBSTNode;
            tpBSTNode = tpBSTNode->left;
        }

        //Value is larger, traverse to the right and find.
        if(tpBSTNode->val < iVal)
        {
            //Nothing left on right. Value not found.
            if(NULL == tpBSTNode->right)
            {
                return;
            }

            tpBSTSuccessorNodeParent = tpBSTNode;
            tpBSTNode = tpBSTNode->right;
        }
    }

    //If node to be deleted is the leaf node.
    if((NULL == tpBSTNodeToDelete->right) && (NULL == tpBSTNodeToDelete->left))
    {
        //Root Node is the node to delete and it is also the leaf node.
        if(pRoot == tpBSTNodeToDelete)
        {
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
            pRoot = NULL;
            return;
        }

        //If leaf node is the left child of its parent.
        if(tpBSTSuccessorNodeParent->left == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = NULL;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }

        //If leaf node is the right child of its parent.
        else if(tpBSTSuccessorNodeParent->right == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->right = NULL;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }
        return;
    }

    //Node to delete only has left child.
    if((NULL == tpBSTNodeToDelete->right) && (NULL != tpBSTNodeToDelete->left))
    {
        //Root Node is the node to delete and it has only a left child.
        if(pRoot == tpBSTNodeToDelete)
        {
            pRoot = tpBSTNodeToDelete->left;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
            return;
        }

        //If node to delete is the left child of the parent.
        if(tpBSTSuccessorNodeParent->left == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = tpBSTNodeToDelete->left;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }

        //If node to delete is the right child of the parent.
        else if(tpBSTSuccessorNodeParent->right == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->right = tpBSTNodeToDelete->left;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }
        return;
    }

    //Node to delete only has right child
    if((NULL != tpBSTNodeToDelete->right) && (NULL == tpBSTNodeToDelete->left))
    {
        //Root Node is the node to delete and it has only a right child
        if(pRoot == tpBSTNodeToDelete)
        {
            pRoot = tpBSTNodeToDelete->right;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
            return;
        }

        //If node to delete is the left child of the parent.
        if(tpBSTSuccessorNodeParent->left == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = tpBSTNodeToDelete->right;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }

        //If node to delete is the right child of the parent.
        else if(tpBSTSuccessorNodeParent->right == tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->right = tpBSTNodeToDelete->right;
            delete tpBSTNodeToDelete;
            tpBSTNodeToDelete = NULL;
        }
        return;
    }

    //Initialize successor and successor parent node for using deletion by successor method.
    tpBSTSuccessorNode = tpBSTNodeToDelete;
    tpBSTSuccessorNodeParent = tpBSTSuccessorNode;

    //Go right for one time for finding the successor.
    tpBSTSuccessorNode = tpBSTSuccessorNode->right;

    //Go to the left child until null is encountered. Last node is the successor.
    while(NULL != tpBSTSuccessorNode->left)
    {
        tpBSTSuccessorNodeParent = tpBSTSuccessorNode;
        tpBSTSuccessorNode = tpBSTSuccessorNode->left;
    }

    //Swap the data values.
    tpBSTNodeToDelete->val = tpBSTSuccessorNode->val;

    //If the successor has a right child.
    if(NULL != tpBSTSuccessorNode->right)
    {
        //Link parent to successor's right child.
        if(tpBSTSuccessorNodeParent != tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = tpBSTSuccessorNode->right;
        }

        //If the successor is the right child of node to be deleted -> there was no left child after that. Then, link parent to its right child.
        else
        {
            tpBSTSuccessorNodeParent->right = tpBSTSuccessorNode->right;
        }
    }

    //If the successor does not have a right child.
    else
    {
        //Make parent's left node null.
        if(tpBSTSuccessorNodeParent != tpBSTNodeToDelete)
        {
            tpBSTSuccessorNodeParent->left = NULL;
        }
        //If the successor is the right child of node to be deleted -> there was no left child after that. Then, make parent's right child null.
        else
        {
            tpBSTSuccessorNodeParent->right = NULL;
        }
    }

    //Delete the successor node.
    delete tpBSTSuccessorNode;
    tpBSTSuccessorNode = NULL;
}

int main()
{
    std::cout<<std::endl<<"Creating the BST tree from the given array....."<<std::endl<<std::endl;
    createRequiredTree();   //Prepare the BST tree as per the given data.

    std::cout<<"Initial inorder traversal after creating the BST: "<<std::endl<<std::endl;
    std::cout<<"====>   ";
    printByInorderTraversal(pRoot);
    std::cout<<std::endl<<std::endl;

    deleteBSTNode(VAL_1_TO_DELETE);      //Delete node with given value.
    std::cout<<"Inorder traversal after deleting "<<VAL_1_TO_DELETE<<": "<<std::endl<<std::endl;
    std::cout<<"====>   ";
    printByInorderTraversal(pRoot);
    std::cout<<std::endl<<std::endl;

    deleteBSTNode(VAL_2_TO_DELETE);      //Delete node with given value.
    std::cout<<"Inorder traversal after deleting "<<VAL_2_TO_DELETE<<": "<<std::endl<<std::endl; 
    std::cout<<"====>   ";
    printByInorderTraversal(pRoot);
    std::cout<<std::endl<<std::endl;

    std::cout<<"Execution completed, exiting....."<<std::endl<<std::endl;
    return 0;
}