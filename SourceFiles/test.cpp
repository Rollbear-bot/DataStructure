#if 0

#include <ctime>

#include "../HeaderFiles/TestSystem.h"
#include "../HeaderFiles/Others/HashTable.h"
#include "../HeaderFiles/Others/FromTextbook/Graphmtx.h"
#include "../HeaderFiles/Exp12/Sort.h"
#include "../HeaderFiles/Others/Heap.h"
#include "../HeaderFiles/Exp8/BinTreeByLink.h"
#include "../HeaderFiles/Exp11/Graph.h"
#include "../HeaderFiles/Exp2/Set.h"
#include "../HeaderFiles/Exp9/ThreadTree.h"

int main(){
    try {
        clock_t start, end;
        //������

        Graph<char, int> graph, mst, mst2;
        graph.addNode('A');//0
        graph.addNode('B');//1
        graph.addNode('C');//2
        graph.addNode('D');//3
        graph.addNode('E');//4
        graph.addNode('F');//5
        graph.addNode('G');//6
        graph.addNode('H');//7
        graph.addNode('I');//8
        graph.addEdge(Edge<char, int>(0, 1, 2));
        graph.addEdge(Edge<char, int>(1, 2, 11));
        graph.addEdge(Edge<char, int>(2, 5, 9));
        graph.addEdge(Edge<char, int>(5, 8, 10));
        graph.addEdge(Edge<char, int>(7, 8, 8));
        graph.addEdge(Edge<char, int>(6, 7, 6));
        graph.addEdge(Edge<char, int>(3, 6, 5));
        graph.addEdge(Edge<char, int>(0, 3, 1));
        graph.addEdge(Edge<char, int>(3, 4, 4));
        graph.addEdge(Edge<char, int>(1, 4, 3));
        graph.addEdge(Edge<char, int>(4, 8, 7));


/*
        start = clock();
        cout << "graph_DFS_recursion:" << endl;
        Graph<char, int>::recursionBFS(graph).printList();
        graph.printAllEdges();
        end = clock();
        cout << "In time " << end - start << "ms" << endl;
*/
        start = clock();
        List<int> cost = graph.shortestPath(0);
        end = clock();

        cout << "In time " << end - start << "ms" << endl;



/*�������
        List<int> randomInt = List<int>::randomIntegerList(20);
        List<int> randomInt2 = randomInt;

        start = clock();
        Sort<int>::insertSort(randomInt);
        end = clock();
        //randomInt.printList();
        if(randomInt.orderly()) cout<< "done" << endl;
        cout << "In " << end - start << "ms" << endl;

        start = clock();
        Sort<int>::mergeSort(randomInt2);
        end = clock();
        //randomInt2.printList();
        if(randomInt2.orderly()) cout<< "done" << endl;
        cout << "In " << end - start << "ms" << endl;


        int *arr = new int;
        randomInt2.toArr(arr);
        cout << "hello";
        */
    }
    catch (exception &e){
        cout << e.what() << endl;
    }
    return 0;
}

#endif