//
// Created by 13592 on 2019/12/18.
//

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

//#define DefaultSize 30

#include <iostream>
using namespace std;

//const int DefaultSize = 30; //默认的最大顶点数

template <class T, class E>
class Graph{
public:
    const E maxWeight = NULL; //代表无穷大的值
    Graph(int sz = DefaultSize); //构造函数
    ~Graph(); //析构函数

    //判空
    bool GraphEmpty()const{
        return numEdges == 0;
    }

    //判满
    bool GraphFull()const{
        return numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2;
    }

    //返回当前顶点数
    int NumberOfVertices(){ return numVertices;}

    //返回当前边数
    int NumberOfEdges(){ return numEdges;}

    //取顶点i的值，i不合理返回0
    virtual T getValue(int i) = 0;

    //取边(v1, v2)上的权值
    virtual E getWeight(int v1, int v2) = 0;

    //取顶点v的第一个邻接结点
    virtual int getFirstNeighbor(int v) = 0;

    //取邻接顶点w的下一个邻接顶点
    virtual int getNextNeighbor(int v, int w) = 0;

    //插入一个顶点vertex
    virtual bool insertVertex(const T& vertex) = 0;

    //插入边(v1, v2)，权为cost
    virtual bool insertEdge(int v1, int v2, E cost) = 0;

    //删去顶点v和所有相关的边
    virtual bool removeVertex(int v) = 0;

    //在图中删去边(v1, v2)
    virtual bool removeEdge(int v1, int v2) = 0;

protected:
    int maxVertices; //图中最大顶点数
    int numEdges; //当前边数
    int numVertices; //当前顶点数
    virtual int getVertexPos(T vertex) = 0; //给出顶点vertex在图中的位置
};

template<class T, class E>
Graph<T, E>::Graph(int sz) {
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
}

template<class T, class E>
Graph<T, E>::~Graph() {
//pass
}

#endif //DATASTRUCTURE_GRAPH_H
