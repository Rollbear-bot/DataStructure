// Created by 13592 on 2019/12/11.
// 图：邻接表实现

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include "../Exp1/LinearTable.h"
#include "../Exp2/List.h"
#include "../Exp5/Stack.h"

//边的定义
template <class T, class E>
struct Edge{
    //构造函数
    explicit Edge(int dest = 0, E cost = NULL):
        dest(dest), cost(cost){}

    int dest; //该边连接的顶点（使用编号表示）
    E cost; //边上的权值
    //Edge<T, E> *nextEdge; //下一条边链

    //边判等
    bool operator ==(const Edge<T, E> &another) const {
        return (dest == another.dest) && (cost == another.cost);
    }
};


//顶点的定义
template <class T, class E>
struct GraphNode{
public:
    //构造函数
    explicit GraphNode(T value): value(value){}
    GraphNode(): value(0){}
    //拷贝构造函数
    GraphNode(const GraphNode<T, E> &another){
        this->value = another.value;
        this->EdgeTable = another.EdgeTable;
    }
    T value; //该顶点的数据
    List<Edge<T, E>> EdgeTable; //该顶点的链接边表
};


//图的定义
template <class T, class E>
class Graph{
public:
    //构造函数
    Graph(){}

    //拷贝构造函数
    Graph(const Graph<T, E> &another){
        this->NodeTable = another.NodeTable;
    }

public:
    //添加结点（没有入度的孤立点）
    bool addNode(T value){
        this->NodeTable.append(GraphNode<T, E>(value));
    }


    //在图中插入一条边
    bool addEdge(int nodeA, int nodeB, E cost){
        //将边链入A节点的边表
        NodeTable.find(nodeA)->data.EdgeTable.append(Edge<T, E>(nodeB, cost));
        //将边链入B节点的边表
        NodeTable.find(nodeB)->data.EdgeTable.append(Edge<T, E>(nodeA, cost));
        return true;
    }


    //深度优先遍历：返回遍历结果的链表
    //使用栈实现，对于每个节点A，先访问，然后从它的邻接表中取出第一个节点B，然后将节点A入栈；
    //如果A的邻接表中没有节点，则从栈顶去一个节点，直到栈空
    static List<T> DFS(Graph<T, E> graph){
        List<T> result;
        Stack<GraphNode<T, E>*> stack(graph.numOfNode());
        GraphNode<T, E> *temp, *currentNode = graph.getNode(0);
        do{
            if(!currentNode->EdgeTable.isEmpty()){
                //从编号为0的节点开始，访问当前节点
                result.append(currentNode->value);

                stack.push(currentNode);
                //从currentNode的边表中取出一个相邻节点，
                //并将它的记录删除，表示已访问
                temp = graph.getNode(currentNode->EdgeTable.getEle(0).dest);
                currentNode->EdgeTable.delByIndex(0);
                currentNode = temp;
            }
            else currentNode = stack.pop();
        } while(!stack.isEmpty()); //end while
        return result;
    }


    //广度优先遍历：返回遍历结果的链表
    static List<T> BFS(Graph<T, E> graph){
        List<T> result;

        return result;
    }


    //节点个数
    int numOfNode(){
        return this->NodeTable.getLen();
    }


    //获取某个节点的数据值
    T getElem(int index){
        return NodeTable.getEle(index).value;
    }


protected:
    List<GraphNode<T, E>> NodeTable; //顶点表（邻接表）

    //返回指向某个节点的指针
    GraphNode<T, E> *getNode(int index){
        return &(this->NodeTable.find(index)->data);
    }
};

#endif //DATASTRUCTURE_GRAPH_H
