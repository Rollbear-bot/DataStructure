// Created by 13592 on 2019/12/11.
// ͼ���ڽӱ�ʵ��

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include "../Exp1/LinearTable.h"
#include "../Exp2/List.h"

//����
template <class T, class E>
struct GraphNode{
public:
public:
    GraphNode(E key, T data): key(key), data(data){}
    E key;
    T data;
    //bool visited; //���ʱ��
};

//ͼ���ڽӱ�ʵ��
template <class T, class E>
class Graph{
public:
    //���캯��
    Graph(){}

public:
    //��ӽ��
    bool addNode(E key, T data){
        List<GraphNode<E, T>> neighborList(0);
        neighborList.append(GraphNode(key, data));
        this->nodesList.append(neighborList);
        return true;
    }

    //��ӱ�
    bool addEdge(E keyA, E keyB){

    }

    //depth first search
    bool DFS(E key){
        List<E> hasVisited(0);
        for(int nodesListIndex: this->nodesList){

        }
    }

    //breadth first search
    T BFS(E key){
        List<E> hasVisited(0);
        for(int nodesListIndex = 0; nodesListIndex < nodesList.getLen(); nodesListIndex++){
            if(this->nodesList.find(nodesListIndex)->data.isEmpty())continue;
            for(int neighborIndex = 0; neighborIndex < nodesList.find(nodesListIndex)->data.getLen(); neighborIndex++){
                E currentKey = nodesList.find(nodesListIndex)->data.find(neighborIndex)->data.key;
                if(hasVisited.locate(currentKey) == -1)continue;
                if(currentKey == key)return nodesList.find(nodesListIndex)->data.find(neighborIndex)->data.data;
                hasVisited.append(currentKey);
            }
        }
        return NULL;
    }


protected:
    List<List<GraphNode<T, E>>> nodesList; //�����


};

#endif //DATASTRUCTURE_GRAPH_H
