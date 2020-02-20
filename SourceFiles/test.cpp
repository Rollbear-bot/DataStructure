#if 1

#include <ctime>

#include "../HeaderFiles/TestSystem.h"
#include "../HeaderFiles/Others/HashTable.h"
#include "../HeaderFiles/Others/FromTextbook/Graphmtx.h"
#include "../HeaderFiles/Others/Sort.h"
#include "../HeaderFiles/Others/Heap.h"
#include "../HeaderFiles/Exp8/BinTreeByLink.h"
#include "../HeaderFiles/Exp11/Graph.h"
#include "../HeaderFiles/Exp2/Set.h"
#include "../HeaderFiles/Exp9/ThreadTree.h"

int main(){
    try {
        //²âÊÔÇø
        Graph<char, int> graph;
        graph.addNode('A');
        graph.addNode('B');
        graph.addNode('C');
        graph.addNode('D');
        graph.addNode('E');
        graph.addNode('F');

        graph.addEdge(Edge<char, int>(0, 1, 0));
        graph.addEdge(Edge<char, int>(1, 2, 0));
        graph.addEdge(Edge<char, int>(2, 3, 0));
        graph.addEdge(Edge<char, int>(1, 4, 0));
        graph.addEdge(Edge<char, int>(2, 5, 0));

        clock_t start, end;

        //string gt = "A(B(D,E(G(Z,X(L(M,N),)),(O,P(Q,(R,S))))),C(J,F(H,I)))";
        //BinTreeByLink<char> bt(gt);

        start = clock();
        cout << "graph_DFS_recursion:";
        Graph<char, int>::recursionBFS(graph).printList();
        graph.printAllEdges();
        end = clock();
        cout << "In time " << end - start << "ms" << endl;

        start = clock();
        cout << "graph_DFS:";
        Graph<char, int>::BFS(graph).printList();
        graph.printAllEdges();
        end = clock();
        cout << "In time " << end - start << "ms" << endl;


        /*
        start = clock();
        cout << "shortest path from 'A' to 'F'" << endl;
        List<int> cost = graph.shortestPath(0);
        end = clock();
        cout << cost[5] << endl;
        cout << "In time " << end - start << "ms" << endl;
*/


        //cout << "ThreadTree:" << endl;
        //ThreadTree<char> threadTree(gt);
        //threadTree.inOrderTraversal().printList();
    }
    /*
    catch (Ex ex){
        ex.printInfo();
    }
     */
    catch (exception &e){
        cout << e.what() << endl;
    }
    return 0;
}

#endif