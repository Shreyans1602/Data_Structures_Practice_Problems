/**
 * @brief: A4.cpp.
 * 
 * @paragraph: Code Description - This code is used to demonstrate applyDijkstra's algorithm.
 * 
 * @paragraph: Problem Statement - Implement applyDijkstra's algorithm. Your graphMatrix must have at least 10 vertices and 20 edges.Print out the graphMatrix - list of vertices and edges (pair of vertices). Run applyDijkstra's algorithm. Print the tree that results - list of vertices in the tree (same as above) and list of edges that make up the tree. You may use heap library. That is the only library you can use. Submit the code and screen shots of execution results.
 * 
 * @author: Shreyans Patel (SSP210009)
 */

#include<iostream>

//Necessary Defines
#define NUM_VERTEX 10
#define SOURCE_VERTEX 0
#define INFINITY 9999

//Global Variables
int graphMatrix[NUM_VERTEX][NUM_VERTEX];
int distanceArr[NUM_VERTEX];
int parentArr[NUM_VERTEX];
bool visitedArr[NUM_VERTEX];

/**
 * @brief: createGraph.
 * @details: Used to create the required graph. It creates a directed graph hence you will get a proper answer only if your source has a path to all the other vertices. 9999 distance represents infinity.
 * @return none.
 */
void createGraph(void)
{
    int tOuterLoop = 0;
    int tInnerLoop = 0;

    //Initialize the graph matrix
    for(tOuterLoop = 0; tOuterLoop <= NUM_VERTEX; tOuterLoop++)
    {
        for(tInnerLoop = 0; tInnerLoop <= NUM_VERTEX; tInnerLoop++)
        {
            graphMatrix[tOuterLoop][tInnerLoop] = 0;
        }
    }

    //Set edges and weight
    graphMatrix[0][1] = 9;
    graphMatrix[0][5] = 14;
    graphMatrix[0][6] = 15;
    graphMatrix[1][2] = 24;
    graphMatrix[2][3] = 8;
    graphMatrix[2][4] = 4;
    graphMatrix[2][8] = 20;
    graphMatrix[3][7] = 6;
    graphMatrix[3][8] = 12;
    graphMatrix[3][9] = 6;
    graphMatrix[4][3] = 11;
    graphMatrix[4][7] = 16;
    graphMatrix[4][8] = 10;
    graphMatrix[5][2] = 18;
    graphMatrix[5][4] = 30;
    graphMatrix[5][6] = 5;
    graphMatrix[6][4] = 20;
    graphMatrix[6][7] = 44;
    graphMatrix[8][9] = 10;
    graphMatrix[9][7] = 19;
}

/**
 * @brief: printGraph.
 * @details: Used to print the required graph.
 * @return none.
 */
void printGraph(void)
{
    int tIterator = 0;
    int tOuterLoop = 0;
    int tInnerLoop = 0;
    
    std::cout<<"Vertices: ";
    //Print list of vertices
    for(tIterator = 0; tIterator < NUM_VERTEX; tIterator++)
    {
        std::cout<<tIterator<<" ";
    }
    std::cout<<std::endl;

    std::cout<<"Edge(Src,Dest)\tDistance"<<std::endl;

    //Print edges and weights
    for(tOuterLoop = 0; tOuterLoop <= NUM_VERTEX; tOuterLoop++)
    {
        for(tInnerLoop = 0; tInnerLoop <= NUM_VERTEX; tInnerLoop++)
        {
            if(0 != graphMatrix[tOuterLoop][tInnerLoop])
            {
                std::cout<<"("<<tOuterLoop<<","<<tInnerLoop<<")"<<"\t\t"<<graphMatrix[tOuterLoop][tInnerLoop]<<std::endl;
            }
        }
    }
}

/**
 * @brief: getMinDistanceVertex.
 * @details: Used to get the vertex with the minimum distance while performing Dijkstra's algorithm.
 * @return int - The vertex with minimum distance.
 */
int getMinDistanceVertex(void)
{
    int tMin = INFINITY;
    int tMinDistVertex = INFINITY;
    int tVertex = 0;

    for(tVertex = 0; tVertex < NUM_VERTEX; tVertex++)
    {
        //If the vertex is not visited and its distance is less than or equal to current minimum distance
        if((false == visitedArr[tVertex]) && (distanceArr[tVertex] <= tMin))
        {
            tMin = distanceArr[tVertex];
            tMinDistVertex = tVertex;
        }
    }

    return tMinDistVertex;
}

/**
 * @brief: printPath.
 * @details: Used to print the path to the given vertex from the source.
 * @param: iVertex(input) - The destination vertexx from the source in the path.
 * @return none.
 */
void printPath(int iVertex)
{
    //If the vertex has no parent
    if (-1 == parentArr[iVertex])
    {
        return;
    }

    printPath(parentArr[iVertex]);

    std::cout<<iVertex<<" ";
}

/**
 * @brief: applyDijkstra.
 * @details: Used to apply Dijkstra's Algorithm on the graph created.
 * @return none.
 */
void applyDijkstra(void)
{
    int tIterator = 0;

    //Initially, no vertex will have a parent, all distances to each vertex is infinity and no vertex is visited
    for(tIterator = 0; tIterator < NUM_VERTEX; tIterator++)
    {
        parentArr[tIterator] = -1;
        distanceArr[tIterator] = INFINITY;
        visitedArr[tIterator] = false;
    }

    //Source distance is to be set 0
    distanceArr[SOURCE_VERTEX] = 0;

    for(tIterator = 0; tIterator < NUM_VERTEX; tIterator++)
    {
        int tMinDistVertex = getMinDistanceVertex();
        int tVertex = 0;

        visitedArr[tMinDistVertex] = true;

        for(tVertex = 0; tVertex < NUM_VERTEX; tVertex++)
        {
            if((false == visitedArr[tVertex]) && (graphMatrix[tMinDistVertex][tVertex]) && ((distanceArr[tMinDistVertex] + graphMatrix[tMinDistVertex][tVertex]) < distanceArr[tVertex]))
            {
                parentArr[tVertex]  = tMinDistVertex;
                distanceArr[tVertex] = (distanceArr[tMinDistVertex] + graphMatrix[tMinDistVertex][tVertex]);
            }
        }
    }

    std::cout<<"(Src,Dest)\tDistance\tPath"<<std::endl;
    
    for(tIterator = 0; tIterator < NUM_VERTEX; tIterator++)
    {
        std::cout<<"("<<SOURCE_VERTEX<<","<<tIterator<<")\t\t"<<distanceArr[tIterator]<<"\t\t"<<SOURCE_VERTEX<<" ";
        printPath(tIterator);
        std::cout<<std::endl;
    }
}

/**
 * @brief: printResult.
 * @details: Used to print the end result after operation is done.
 * @return none.
 */
void printResult(void)
{
    int tIterator = 0;
    
    std::cout<<"Vertices: ";
    for(tIterator = 0; tIterator < NUM_VERTEX; tIterator++)
    {
        std::cout<<tIterator<<" ";
    }
    std::cout<<std::endl;
    
    std::cout<<"Edge(Src,Dest)\tDistance"<<std::endl;

    for(int i = 0; i < NUM_VERTEX; i++)
    {
        if(parentArr[i] == -1)
        {
            continue;
        }
        std::cout<<"("<<parentArr[i]<<","<<i<<")"<<"\t\t"<<graphMatrix[parentArr[i]][i]<<std::endl;
    }
}

/**
 * @brief: main.
 * @details: Main function.
 * @return int.
 */
int main(void)
{
    int tIterator = 0;

    //Create Graph Section
    createGraph();
    std::cout<<"Given Graph:"<<std::endl;;
    printGraph();
    std::cout<<std::endl;

    //Dijkstra's Algorithm Section
    std::cout<<"Result after running Dijkstra's algorithm with source vertex "<<SOURCE_VERTEX<<":"<<std::endl;
    applyDijkstra();
    std::cout<<std::endl;

    //Final Result Section
    std::cout<<"Final Result:"<<std::endl;
    printResult();

    return 0;
}