// Created by 13592 on 2019/12/11.
// ͼ���ڽӱ�ʵ��

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include "../Exp1/LinearTable.h"
#include "../Exp2/List.h"
#include "../Exp5/Stack.h"

//�ߵĶ���
template <class T, class E>
struct Edge{
    //���캯��
    explicit Edge(int dest = 0, E cost = NULL):
        dest(dest), cost(cost){}

    int dest; //�ñ����ӵĶ��㣨ʹ�ñ�ű�ʾ��
    E cost; //���ϵ�Ȩֵ
    //Edge<T, E> *nextEdge; //��һ������

    //���е�
    bool operator ==(const Edge<T, E> &another) const {
        return (dest == another.dest) && (cost == another.cost);
    }
};


//����Ķ���
template <class T, class E>
struct GraphNode{
public:
    //���캯��
    explicit GraphNode(T value): value(value){}
    GraphNode(): value(0){}
    //�������캯��
    GraphNode(const GraphNode<T, E> &another){
        this->value = another.value;
        this->EdgeTable = another.EdgeTable;
    }
    T value; //�ö��������
    List<Edge<T, E>> EdgeTable; //�ö�������ӱ߱�
};


//ͼ�Ķ���
template <class T, class E>
class Graph{
public:
    //���캯��
    Graph(){}

    //�������캯��
    Graph(const Graph<T, E> &another){
        this->NodeTable = another.NodeTable;
    }

public:
    //��ӽ�㣨û����ȵĹ����㣩
    bool addNode(T value){
        this->NodeTable.append(GraphNode<T, E>(value));
    }


    //��ͼ�в���һ����
    bool addEdge(int nodeA, int nodeB, E cost){
        //��������A�ڵ�ı߱�
        NodeTable.find(nodeA)->data.EdgeTable.append(Edge<T, E>(nodeB, cost));
        //��������B�ڵ�ı߱�
        NodeTable.find(nodeB)->data.EdgeTable.append(Edge<T, E>(nodeA, cost));
        return true;
    }


    //������ȱ��������ر������������
    //ʹ��ջʵ�֣�����ÿ���ڵ�A���ȷ��ʣ�Ȼ��������ڽӱ���ȡ����һ���ڵ�B��Ȼ�󽫽ڵ�A��ջ��
    //���A���ڽӱ���û�нڵ㣬���ջ��ȥһ���ڵ㣬ֱ��ջ��
    static List<T> DFS(Graph<T, E> graph){
        List<T> result;
        Stack<GraphNode<T, E>*> stack(graph.numOfNode());
        GraphNode<T, E> *temp, *currentNode = graph.getNode(0);
        do{
            if(!currentNode->EdgeTable.isEmpty()){
                //�ӱ��Ϊ0�Ľڵ㿪ʼ�����ʵ�ǰ�ڵ�
                result.append(currentNode->value);

                stack.push(currentNode);
                //��currentNode�ı߱���ȡ��һ�����ڽڵ㣬
                //�������ļ�¼ɾ������ʾ�ѷ���
                temp = graph.getNode(currentNode->EdgeTable.getEle(0).dest);
                currentNode->EdgeTable.delByIndex(0);
                currentNode = temp;
            }
            else currentNode = stack.pop();
        } while(!stack.isEmpty()); //end while
        return result;
    }


    //������ȱ��������ر������������
    static List<T> BFS(Graph<T, E> graph){
        List<T> result;

        return result;
    }


    //�ڵ����
    int numOfNode(){
        return this->NodeTable.getLen();
    }


    //��ȡĳ���ڵ������ֵ
    T getElem(int index){
        return NodeTable.getEle(index).value;
    }


protected:
    List<GraphNode<T, E>> NodeTable; //������ڽӱ�

    //����ָ��ĳ���ڵ��ָ��
    GraphNode<T, E> *getNode(int index){
        return &(this->NodeTable.find(index)->data);
    }
};

#endif //DATASTRUCTURE_GRAPH_H
