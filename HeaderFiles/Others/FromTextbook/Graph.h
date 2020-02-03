//
// Created by 13592 on 2019/12/18.
//

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

//#define DefaultSize 30

#include <iostream>
using namespace std;

//const int DefaultSize = 30; //Ĭ�ϵ���󶥵���

template <class T, class E>
class Graph{
public:
    const E maxWeight = NULL; //����������ֵ
    Graph(int sz = DefaultSize); //���캯��
    ~Graph(); //��������

    //�п�
    bool GraphEmpty()const{
        return numEdges == 0;
    }

    //����
    bool GraphFull()const{
        return numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2;
    }

    //���ص�ǰ������
    int NumberOfVertices(){ return numVertices;}

    //���ص�ǰ����
    int NumberOfEdges(){ return numEdges;}

    //ȡ����i��ֵ��i��������0
    virtual T getValue(int i) = 0;

    //ȡ��(v1, v2)�ϵ�Ȩֵ
    virtual E getWeight(int v1, int v2) = 0;

    //ȡ����v�ĵ�һ���ڽӽ��
    virtual int getFirstNeighbor(int v) = 0;

    //ȡ�ڽӶ���w����һ���ڽӶ���
    virtual int getNextNeighbor(int v, int w) = 0;

    //����һ������vertex
    virtual bool insertVertex(const T& vertex) = 0;

    //�����(v1, v2)��ȨΪcost
    virtual bool insertEdge(int v1, int v2, E cost) = 0;

    //ɾȥ����v��������صı�
    virtual bool removeVertex(int v) = 0;

    //��ͼ��ɾȥ��(v1, v2)
    virtual bool removeEdge(int v1, int v2) = 0;

protected:
    int maxVertices; //ͼ����󶥵���
    int numEdges; //��ǰ����
    int numVertices; //��ǰ������
    virtual int getVertexPos(T vertex) = 0; //��������vertex��ͼ�е�λ��
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
