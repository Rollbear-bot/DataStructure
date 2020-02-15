#if 1

#include "../HeaderFiles/TestSystem.h"
#include "../HeaderFiles/Others/HashTable.h"
#include "../HeaderFiles/Others/FromTextbook/Graphmtx.h"
#include "../HeaderFiles/Others/Sort.h"
#include "../HeaderFiles/Others/Heap.h"
#include "../HeaderFiles/Exp8/BinTreeByLink.h"
#include "../HeaderFiles/Exp11/Graph.h"

int main(){
    try {
        //²âÊÔÇø
        Graph<char, int> graph;
        graph.addNode('A');
        graph.addNode('B');
        graph.addNode('C');
        graph.addNode('D');
        graph.addEdge(Edge<char, int>(0, 1, 0));
        graph.addEdge(Edge<char, int>(0, 2, 0));
        graph.addEdge(Edge<char, int>(1, 2, 0));
        graph.addEdge(Edge<char, int>(1, 3, 0));

        Graph<char, int> MST = Graph<char, int>::MST_Prim(graph);
        cout << "MST:";
        Graph<char, int>::BFS(MST).printList();
        cout << "edges of MST:";
        MST.printAllEdges();

        return 0;
    }
    /*
    catch (Ex ex){
        ex.printInfo();
    }
     */
    catch (NoFound nf){
        nf.print();
    }
    catch (IndexOutException of){
        of.print();
    }
    catch(OverFlowException ofe){
        ofe.print();
    }
    catch (NullPointer np){
        np.print();
    }
    return 0;
}

#endif