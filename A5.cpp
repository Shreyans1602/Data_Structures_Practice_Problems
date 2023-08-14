/**
 * @brief: A5.cpp.
 * 
 * @paragraph: Code Description - This code is used to demonstrate DFS and BFS topological sort with cycle detection.
 * 
 * @paragraph: Problem Statement -  For the two given graphs (A5_images1.png and A5_images2.png): a.) Write a program to do DFS topological sort. Your program must be able to catch the loop. Run the program on the attached graphs. b.) Write a program to do BFS topological sort. Your program must be able to catch the loop. Run the program on the attached graphs. Submit screen shots of execution results. Submit the code.
 * 
 * @author: Shreyans Patel (SSP210009)
 */
#include<iostream>
#include<queue>

//Necessary Defines
#define GRAPH_1 1
#define GRAPH_2 2
#define NUM_VERTICES_GRAPH_1 8
#define NUM_VERTICES_GRAPH_2 14

//Structure Defines
struct graphStruct;
struct adjacentVertex;

//Global Variables
graphStruct *Graph1[NUM_VERTICES_GRAPH_1];
graphStruct *Graph2[NUM_VERTICES_GRAPH_2];
bool visitedGraph1[NUM_VERTICES_GRAPH_1] = {false};
bool visitedGraph2[NUM_VERTICES_GRAPH_2] = {false};
bool doneGraph1[NUM_VERTICES_GRAPH_1] = {false};
bool doneGraph2[NUM_VERTICES_GRAPH_2] = {false};
int vertexMappingG1[NUM_VERTICES_GRAPH_1];
char vertexMappingG2[NUM_VERTICES_GRAPH_2];
int inDegreeListGraph1[NUM_VERTICES_GRAPH_1] = {0};
int inDegreeListGraph2[NUM_VERTICES_GRAPH_2] = {0};
std::queue<int> topoQGraph1;
std::queue<int> topoQGraph2;

//Structure of a graph for adjacency list representation
struct graphStruct
{
    int vertex;
    adjacentVertex *adjacent;   //Vertex adjacent to current vertex

    graphStruct()
    {
        vertex = -1;
        adjacent = NULL;
    }
};

//Structure of an adjacent vertex for adjacency list
struct adjacentVertex
{
    graphStruct *vertexAddr;    //Vertex represented by the adjacent node in a graph
    adjacentVertex *next;

    adjacentVertex()
    {
        vertexAddr = NULL;
        next = NULL;
    }
};

/**
 * @brief: insertEdgeInGraph1.
 * @details: Used to add an edge in Graph1 (Number Format (1 is index 0)).
 * @param: iVertex - Source Vertex.
 * @param: iAdjacentVertex - Destination Vertex.
 * @return none.
 */
void insertEdgeInGraph1(int iVertex, int iAdjacentVertex)
{
    int tInsertAtVertex = iVertex - 1;
    int tVertexToInsert = iAdjacentVertex - 1;

    adjacentVertex *tpAdjacent = Graph1[tInsertAtVertex]->adjacent;

    if(NULL == tpAdjacent)
    {
        tpAdjacent = new adjacentVertex;

        if(NULL == tpAdjacent)
        {
            return;
        }

        tpAdjacent->vertexAddr = Graph1[tVertexToInsert];
        tpAdjacent->next = NULL;
        Graph1[tInsertAtVertex]->adjacent = tpAdjacent;
        return;
    }

    while(tpAdjacent->next != NULL)
    {
        tpAdjacent = tpAdjacent->next;
    }

    tpAdjacent->next = new adjacentVertex;

    if(NULL == tpAdjacent->next)
    {
        return;
    }

    tpAdjacent->next->vertexAddr = Graph1[tVertexToInsert];
    tpAdjacent->next->next = NULL;
}

/**
 * @brief: insertEdgeInGraph2.
 * @details: Used to add an edge in Graph2 (Alphabet Format (m is index 0)).
 * @param: iVertex - Source Vertex.
 * @param: iAdjacentVertex - Destination Vertex.
 * @return none.
 */
void insertEdgeInGraph2(char iVertex, char iAdjacentVertex)
{
    int tInsertAtVertex = (int)iVertex - 109;
    int tVertexToInsert = (int)iAdjacentVertex - 109;

    adjacentVertex *tpAdjacent = Graph2[tInsertAtVertex]->adjacent;

    if(NULL == tpAdjacent)
    {
        tpAdjacent = new adjacentVertex;

        if(NULL == tpAdjacent)
        {
            return;
        }

        tpAdjacent->vertexAddr = Graph2[tVertexToInsert];
        tpAdjacent->next = NULL;
        Graph2[tInsertAtVertex]->adjacent = tpAdjacent;
        return;
    }

    while(tpAdjacent->next != NULL)
    {
        tpAdjacent = tpAdjacent->next;
    }

    tpAdjacent->next = new adjacentVertex;

    if(NULL == tpAdjacent->next)
    {
        return;
    }

    tpAdjacent->next->vertexAddr = Graph2[tVertexToInsert];
    tpAdjacent->next->next = NULL;
}

/**
 * @brief: createGraph1.
 * @details: Used to create Graph1 in adjacency list representation and its in-degree list.
 * @return none.
 */
void createGraph1(void)
{
    int tIterator = 0;

    for(tIterator = 0; tIterator < NUM_VERTICES_GRAPH_1; tIterator++)
    {
        graphStruct *tpGraph1 = new graphStruct;

        if(NULL == tpGraph1)
        {
            return;
        }

        tpGraph1->vertex = tIterator;

        Graph1[tIterator] = tpGraph1;

        tpGraph1 = NULL;

        vertexMappingG1[tIterator] = tIterator + 1;
    }

    insertEdgeInGraph1(1,2);
    insertEdgeInGraph1(1,5);
    insertEdgeInGraph1(1,6);
    insertEdgeInGraph1(2,3);
    insertEdgeInGraph1(2,5);
    insertEdgeInGraph1(2,7);
    insertEdgeInGraph1(3,4);
    insertEdgeInGraph1(4,5);
    insertEdgeInGraph1(5,7);
    insertEdgeInGraph1(5,8);
    insertEdgeInGraph1(6,5);
    insertEdgeInGraph1(6,8);
    insertEdgeInGraph1(7,4);
    insertEdgeInGraph1(7,8);

    for(tIterator = 0; tIterator < NUM_VERTICES_GRAPH_1; tIterator++)
    {
        adjacentVertex *tpAdjacent = Graph1[tIterator]->adjacent;

        while(tpAdjacent != NULL)
        {
            inDegreeListGraph1[tpAdjacent->vertexAddr->vertex] += 1;
            tpAdjacent = tpAdjacent->next;
        }
    }
}

/**
 * @brief: createGraph2.
 * @details: Used to create Graph2 in adjacency list representation and its in-degree list.
 * @return none.
 */
void createGraph2(void)
{
    int tIterator = 0;

    for(tIterator = 0; tIterator < NUM_VERTICES_GRAPH_2; tIterator++)
    {
        graphStruct *tpGraph2 = new graphStruct;

        if(NULL == tpGraph2)
        {
            return;
        }

        tpGraph2->vertex = tIterator;

        Graph2[tIterator] = tpGraph2;

        tpGraph2 = NULL;

        vertexMappingG2[tIterator] = tIterator + 109;
    }

    insertEdgeInGraph2('m','q');
    insertEdgeInGraph2('m','r');
    insertEdgeInGraph2('m','x');
    insertEdgeInGraph2('n','o');
    insertEdgeInGraph2('n','q');
    insertEdgeInGraph2('n','u');
    insertEdgeInGraph2('o','r');
    insertEdgeInGraph2('o','s');
    insertEdgeInGraph2('o','v');
    insertEdgeInGraph2('p','o');
    insertEdgeInGraph2('p','s');
    insertEdgeInGraph2('p','z');
    insertEdgeInGraph2('q','t');
    insertEdgeInGraph2('r','u');
    insertEdgeInGraph2('r','y');
    insertEdgeInGraph2('s','r');
    insertEdgeInGraph2('u','t');
    insertEdgeInGraph2('v','w');
    insertEdgeInGraph2('v','x');
    insertEdgeInGraph2('w','z');
    insertEdgeInGraph2('y','v');

    for(tIterator = 0; tIterator < NUM_VERTICES_GRAPH_2; tIterator++)
    {
        adjacentVertex *tAdjacent = Graph2[tIterator]->adjacent;

        while(tAdjacent != NULL)
        {
            inDegreeListGraph2[tAdjacent->vertexAddr->vertex] += 1;
            tAdjacent = tAdjacent->next;
        }
    }
}

/**
 * @brief: createGraph.
 * @details: Used to create both the given graphs.
 * @return none.
 */
void createGraph(void)
{
    createGraph1();
    createGraph2();
}

/**
 * @brief: printGraph.
 * @details: Used to the graph in adjacency list representation.
 * @param: iGraph - Graph to be printed.
 * @param: iSize - Number of vertices in the graph.
 * @return none.
 */
void printGraph(graphStruct *iGraph[], int iSize)
{
    graphStruct **tppGraph = iGraph;
    int tIterator = 0;

    for(tIterator = 0; tIterator < iSize; tIterator++)
    {
        switch(iSize)
        {
            case NUM_VERTICES_GRAPH_1:
            {
                std::cout<<vertexMappingG1[tppGraph[tIterator]->vertex];
                break;
            }
            case NUM_VERTICES_GRAPH_2:
            {
                std::cout<<vertexMappingG2[tppGraph[tIterator]->vertex];
                break;
            }
            default:
            {
                return;
            }
        }

        adjacentVertex *tpAdjacent = tppGraph[tIterator]->adjacent;

        while(tpAdjacent != NULL)
        {
            switch(iSize)
            {
                case NUM_VERTICES_GRAPH_1:
                {
                    std::cout<<" -> "<<vertexMappingG1[tpAdjacent->vertexAddr->vertex];
                    break;
                }
                case NUM_VERTICES_GRAPH_2:
                {
                    std::cout<<" -> "<<vertexMappingG2[tpAdjacent->vertexAddr->vertex];
                    break;
                }
                default:
                {
                    return;
                }
            }
            tpAdjacent = tpAdjacent->next;
        }

        std::cout<<" -> null";
        std::cout<<std::endl;
    }
}

/**
 * @brief: topoSort.
 * @details: Used to topologically sort the Graph using DFS.
 * @param: iVertex - Vertex to start from.
 * @param: iVisitedArr - List of visited vertexes of the graph.
 * @param: iDoneArr - List of done vertexes of the graph.
 * @param: iGraph - Graph under topological sort.
 * @return bool - True(No Cycle) or False(Cycle Detected).
 */
bool topoSort(int iVertex, bool iVisitedArr[], bool iDoneArr[], graphStruct *iGraph[], int iSize)
{
    if(true == iDoneArr[iVertex])
    {
        return true;
    }

    iVisitedArr[iVertex] = true;

    adjacentVertex *tpAdjacent = iGraph[iVertex]->adjacent;

    while(tpAdjacent != NULL)
    {
        if(false == iDoneArr[tpAdjacent->vertexAddr->vertex])
        {
            if(true == iVisitedArr[tpAdjacent->vertexAddr->vertex])
            {
                return false;
            }
            
            if(false == topoSort(tpAdjacent->vertexAddr->vertex, iVisitedArr, iDoneArr, iGraph, iSize))
            {
                return false;
            }
        }
        
        tpAdjacent = tpAdjacent->next;
    }

    iDoneArr[iVertex] = true;
    
    //We can also push this vertex to queue instead. We are printing it here so we can see where we encountered a loop.
    switch(iSize)
    {
        case NUM_VERTICES_GRAPH_1:
        {
            std::cout<<vertexMappingG1[iVertex]<<" ";
            break;
        }
        case NUM_VERTICES_GRAPH_2:
        {
            std::cout<<vertexMappingG2[iVertex]<<" ";
            break;
        }
        default:
        {
            break;
        }
    }
    
    return true;
}

/**
 * @brief: dfsGraph.
 * @details: Used to perform DFS on the given graph.
 * @param: iSize - Number of vertices in the graph.
 * @param: iVisitedArr - List of visited vertexes of the graph.
 * @param: iDoneArr - List of done vertexes of the graph.
 * @param: iGraph - Graph tp perform DFS on.
 * @return none.
 */
void dfsGraph(int iSize, bool iVisitedArr[], bool iDoneArr[], graphStruct *iGraph[])
{
    int tIterator = 0;

    for(tIterator = 0; tIterator < iSize; tIterator++)
    {
        if(false == topoSort(tIterator, iVisitedArr, iDoneArr, iGraph, iSize))
        {
            std::cout<<"Cycle Detected. Exiting....."<<std::endl;
            return;
        }
    }
}

/**
 * @brief: bfsGraph.
 * @details: Used to perform BFS on the given graph.
 * @param: iGraph - Graph tp perform BFS on.
 * @param: iNumVertex - Number of vertices in the graph.
 * @param: iInDegreeList - List of in-degrees of the graph vertices.
 * @param: iOutputQueue - Queue for topological output after BFS.
 * @return none.
 */
bool bfsGraph(graphStruct *iGraph[], int iNumVertex, int *iInDegreeList, std::queue<int> &iOutputQueue)
{
    std::queue<int> tVertexQueue;
    int tVisitedCount = 0;

    for(int i = 0; i < iNumVertex; i++)
    {
        if(0 == iInDegreeList[i])
        {
            tVertexQueue.push(i);
        }
    }

    while(false == tVertexQueue.empty())
    {
        int tVertex = tVertexQueue.front();
        tVertexQueue.pop();
        iOutputQueue.push(tVertex);

        adjacentVertex *tAdjacent = iGraph[tVertex]->adjacent;

        while(tAdjacent != NULL)
        {
            iInDegreeList[tAdjacent->vertexAddr->vertex] -= 1;
            if(0 == iInDegreeList[tAdjacent->vertexAddr->vertex])
            {
                tVertexQueue.push(tAdjacent->vertexAddr->vertex);
            }
            tAdjacent = tAdjacent->next;
        }

        tVisitedCount += 1;
    }

    if(tVisitedCount != iNumVertex)
    {
        return false;
    }

    return true;
}

/**
 * @brief: printQueue.
 * @details: Used to print the vertexes in a given queue.
 * @param: iQueue - Queue to print.
 * @param: iGraphNum - Graph to which the queue belongs.
 * @return none.
 */
void printQueue(std::queue<int> iQueue, int iGraphNum)
{
    switch(iGraphNum)
    {
        case GRAPH_1:
        {
            while(false == iQueue.empty())
            {
                std::cout<<vertexMappingG1[iQueue.front()]<<" ";
                iQueue.pop();
            }
            break;
        }
        case GRAPH_2:
        {
            while(false == iQueue.empty())
            {
                std::cout<<vertexMappingG2[iQueue.front()]<<" ";
                iQueue.pop();
            }
            break;
        }
        default:
        {
            return;
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
    //Create graphs and their in-degree lists.
    createGraph();

    //Print adjacency lists of both the graphs.
    std::cout<<"Adjacency List of Graph 1:"<<std::endl;
    printGraph(Graph1,NUM_VERTICES_GRAPH_1);
    std::cout<<std::endl; 
    
    std::cout<<"Adjacency List of Graph 2:"<<std::endl;
    printGraph(Graph2,NUM_VERTICES_GRAPH_2);
    std::cout<<std::endl;

    //Perform DFS topological sort and show output for both of the graphs.
    std::cout<<"DFS Topological Sorting of Graph 1: ";
    dfsGraph(NUM_VERTICES_GRAPH_1, visitedGraph1, doneGraph1, Graph1);
    std::cout<<std::endl;

    std::cout<<"DFS Topological Sorting of Graph 2: ";
    dfsGraph(NUM_VERTICES_GRAPH_2, visitedGraph2, doneGraph2, Graph2);
    std::cout<<std::endl<<std::endl;

    //Print in-degree lists of both the graphs.
    std::cout<<"In-Degree List of Graph 1:"<<std::endl;
    for(int i = 0; i < NUM_VERTICES_GRAPH_1; i++)
    {
        std::cout<<vertexMappingG1[i]<<" -> "<<inDegreeListGraph1[i]<<std::endl;
    }
    std::cout<<std::endl;

    std::cout<<"In-Degree List of Graph 2:"<<std::endl;
    for(int i = 0; i < NUM_VERTICES_GRAPH_2; i++)
    {
        std::cout<<vertexMappingG2[i]<<" -> "<<inDegreeListGraph2[i]<<std::endl;
    }
    std::cout<<std::endl;

    //Perform BFS topological sort and show output for both of the graphs.
    std::cout<<"BFS Topological Sorting of Graph 1: ";
    if(false == bfsGraph(Graph1, NUM_VERTICES_GRAPH_1, inDegreeListGraph1, topoQGraph1))
    {
        printQueue(topoQGraph1,GRAPH_1);
        std::cout<<"Cycle Detected. Exiting.....";
    }
    else
    {
        printQueue(topoQGraph1,GRAPH_1);
    }
    std::cout<<std::endl<<std::endl;

    std::cout<<"BFS Topological Sorting of Graph 2: ";
    if(false == bfsGraph(Graph2, NUM_VERTICES_GRAPH_2, inDegreeListGraph2, topoQGraph2))
    {
        printQueue(topoQGraph2,GRAPH_2);
        std::cout<<"Cycle Detected. Exiting.....";
    }
    else
    {
        printQueue(topoQGraph2,GRAPH_2);
    }
    std::cout<<std::endl;

    return 0;
}