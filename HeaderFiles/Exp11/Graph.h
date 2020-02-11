// Created by 13592 on 2019/12/11.
// ͼ���ڽӱ�ʵ��

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include "../Exp1/LinearTable.h"
#include "../Exp2/List.h"
#include "../Exp5/Stack.h"
#include "../Exp6/Queue.h"

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

    //�е�
    bool operator ==(const GraphNode<T, E> &another){
        return value == another.value && EdgeTable == another.EdgeTable;
    }
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
        Stack<GraphNode<T, E>*> stack(2*graph.numOfNode());
        GraphNode<T, E> *temp, *currentNode = graph.getNode(0);
        do{
            if(!currentNode->EdgeTable.isEmpty()){
                //�ӱ��Ϊ0�Ľڵ㿪ʼ�����ʵ�ǰ�ڵ�
                result.append(currentNode->value);

                stack.push(currentNode);
                //��currentNode�ı߱���ȡ��һ�����ڽڵ�
                temp = graph.getNode(currentNode->EdgeTable.getElem(0).dest);

                //ɾ�������յ�ΪcurrentNode�ı�,todo::Ч�ʺܵͣ���Ҫ�������б߱�
                /*
                for(int index = 0; index < graph.NodeTable.getLen(); index++){
                    for(int i = 0; i < graph.getNode(index)->EdgeTable.getLen(); i++){
                        if(graph.NodeTable.getElem(
                                graph.getNode(index)->EdgeTable.getElem(i).dest)
                                == *currentNode){
                            //������ĳ���ߵ��յ��Ǹýڵ㣬ɾ��������
                            graph.getNode(index)->EdgeTable.delByIndex(i);
                            i--;
                        }
                    }
                }
                 */
                //currentNode->EdgeTable.delByIndex(0);

                currentNode = temp;
            }
            else currentNode = stack.pop();
        } while(!stack.isEmpty()); //end while
        return result;
    }


    //������ȱ��������ر������������
    //ʹ�ö���ʵ�֣�����ÿ���ڵ㣬���ȷ�������Ȼ�����������ٽӵ�����У�
    //�Ӷ�ͷȡ�ڵ㣬�ظ����ϣ�ע�����á��ѷ��ʡ���ǣ�ֱ�����п�
    static List<T> BFS(Graph<T, E> graph){
        List<T> result;
        Queue<GraphNode<T, E>*> queue(2*graph.numOfNode());
        List<GraphNode<T, E>*> visited(graph.numOfNode()); //���ʱ��
        GraphNode<T, E> *current;
        queue.enter(graph.getNode(0)); //�ӱ��Ϊ0�Ľڵ㿪ʼ����

        do{
            current = queue.quit();
            if(visited.inList(current)) continue; //�����ǰ�ڵ��Ѿ����ʹ�������

            result.append(current->value); //���ʵ�ǰ�ڵ�
            visited.append(current); //��¼�ѷ���
            //�����������ڽӵ������
            while(!current->EdgeTable.isEmpty()){
                queue.enter(graph.getNode(current->EdgeTable.getElem(0).dest));
                current->EdgeTable.delByIndex(0);
            }
        }while(!queue.isEmpty());

        return result;
    }


    //�ڵ����
    int numOfNode() const {
        return this->NodeTable.getLen();
    }


    //��ȡĳ���ڵ������ֵ
    T getElem(int index) const {
        return NodeTable.getElem(index).value;
    }


protected:
    List<GraphNode<T, E>> NodeTable; //������ڽӱ�

    //����ָ��ĳ���ڵ��ָ��
    GraphNode<T, E> *getNode(int index){
        return &(this->NodeTable.find(index)->data);
    }
};

#endif //DATASTRUCTURE_GRAPH_H
