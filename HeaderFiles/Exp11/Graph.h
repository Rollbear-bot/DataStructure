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
    explicit Edge(int start = 0, int dest = 0, E cost = NULL):
        start(start), dest(dest), cost(cost){}

    //���еȣ��߼���������أ�
    bool operator ==(const Edge<T, E> &another) const {
        return (dest == another.dest) && (cost == another.cost);
    }

    //Ȩֵ�Ƚ�
    bool operator <(const Edge<T, E> &another){
        return this->cost < another.cost;
    }
    bool operator >(const Edge<T, E> &another){
        return this->cost > another.cost;
    }

    //��ֵ����
    Edge<T, E> operator =(const Edge<T, E> &operand){
        this->cost = operand.cost;
        this->dest = operand.start;
        this->dest = operand.dest;
    }

    int dest; //�ñߵ��յ㣨ʹ�ñ�ű�ʾ��
    int start; //�ߵ����
    E cost; //���ϵ�Ȩֵ

    //Edge<T, E> *nextEdge; //��һ��������������Ϊ����List�ṹ������ߣ�
    //��˾Ͳ���Ҫnext�����ַ����
};


//����Ķ���
template <class T, class E>
struct GraphNode{
public:
    //���캯��
    explicit GraphNode(T value, int index): value(value), index(index){}
    GraphNode(): value(0){}
    //�������캯��
    GraphNode(const GraphNode<T, E> &another){
        this->value = another.value;
        this->EdgeTable = another.EdgeTable;
    }
    //�е�
    bool operator ==(const GraphNode<T, E> &another){
        return value == another.value && EdgeTable == another.EdgeTable;
    }

    T value; //�ö��������
    List<Edge<T, E>> EdgeTable; //�ö�������ӱ߱�
    int index = 0;
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

    //��������
    ~Graph(){
        //todo::����ͼ
    }

    //��ֵ���������
    Graph<T, E> operator =(const Graph<T, E> &operand){
        this->NodeTable = operand.NodeTable;
        return Graph<T,E>(*this);
    }

    //ͼ�е�
    bool operator ==(const Graph<T, E> &operand) const {
        return this->NodeTable == operand.NodeTable;
    }

public:
    //��ӽ�㣨û����ȵĹ����㣩
    bool addNode(T value){
        this->NodeTable.append(GraphNode<T, E>(value, NodeTable.getLen()));
        return true;
    }


    //��ͼ�в���һ����
    bool addEdge(int nodeA, int nodeB, E cost){
        //��������A�ڵ�ı߱�
        NodeTable.find(nodeA)->data.EdgeTable.append(Edge<T, E>(nodeA, nodeB, cost));
        //��������B�ڵ�ı߱�
        NodeTable.find(nodeB)->data.EdgeTable.append(Edge<T, E>(nodeB, nodeA, cost));
        return true;
    }


    //������ȱ��������ر������������
    //ʹ��ջʵ�֣�����ÿ���ڵ�A���ȷ��ʣ�Ȼ��������ڽӱ���ȡ����һ���ڵ�B��Ȼ�󽫽ڵ�A��ջ��
    //���A���ڽӱ���û�нڵ㣬���ջ��ȥһ���ڵ㣬ֱ��ջ��
    static List<T> DFS(Graph<T, E> graph, int start){
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
    static List<T> BFS(Graph<T, E> graph, int start){
        List<T> result;
        Queue<GraphNode<T, E>*> queue(2*graph.numOfNode());
        List<GraphNode<T, E>*> visited(graph.numOfNode()); //���ʱ��
        GraphNode<T, E> *current;
        queue.enter(graph.getNode(start)); //�ӱ��Ϊstart�Ľڵ㿪ʼ����

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


    //��С����������³˹�����㷨
    static BinTreeByLink<T> MST_Kruskal(const Graph<T, E> &graph){
        //����ȡ�����еıߣ����������һ�����ϣ�������Ȩֵ��С�����˳������
        int numOfEdges = 0;
        //����߼�����Ҫ�Ĵ�С
        for(int index = 0; index < graph.numOfNode(); index++){
            numOfEdges += graph.NodeTable.getElem(index).EdgeTable.getLen();
        }
        List<Edge<T, E>> edges(numOfEdges);
        for(int index = 0; index < graph.numOfNode(); index++){
            edges.add(graph.NodeTable.getElem(index).EdgeTable); //��ȡ���б�
        }
        edges.insertSort(); //����Ȩֵ��С��������

        List<Edge<T, E>> result; //����ı߼�
        int maxEdges = graph.numOfNode()-1;
        Edge<T, E> curEdge;
        Graph<T, E> tree;
        //��ʼ������������ÿ�δӱ߱���ȡ��Ȩֵ��С��һ���ߣ��ж����Ƿ��ǿ��ñߣ�
        //������еı������ﶥ����-1ʱ���������ı���==�����-1��ֹͣ
        while (result.getLen() < maxEdges){
            //�ӱ�edges�ײ�ȡ��һ����
            curEdge = edges.quit();
            //�ж����Ƿ�����Ч�ıߣ�����Ч������
            if(!tree.isEmpty()){
                if(!accessible(tree, curEdge.start, curEdge.dest)) continue;
                else result.append(curEdge);
            }
            //���µĵ����������tree
            if(!tree.NodeTable.inList(graph.getElem(curEdge.start)))
                tree.addNode(graph.getElem(curEdge.start));
            if(!tree.NodeTable.inList(graph.getElem(curEdge.dest)))
                tree.addNode(graph.getElem(curEdge.dest));
            //���µı߼���������
            tree.addEdge(curEdge);
        }

        //Ȼ��ӽ���߼����������


    }


    //��С��������Prim�㷨
    static BinTreeByLink<T> MST_Prim(const Graph<T, E> &graph){

    }


    //�ж�ͼ�е��������Ƿ���ͬһ����ͨ������
    static bool accessible(const Graph<T, E> &graph, int nodeA, int nodeB){
        //ͨ����ȱ����Ľ�����ж��Ƿ���ͨ�����ڱ�������м����ɴ
        return BFS(graph, nodeA).inList(graph.getElem(nodeB));
    }


    //�ڵ����
    int numOfNode() const {
        return this->NodeTable.getLen();
    }


    //��ȡĳ���ڵ������ֵ�����Ϊ�����NodeTable�е����
    T getElem(int index) const {
        return NodeTable.getElem(index).value;
    }


protected:
    List<GraphNode<T, E>> NodeTable; //������ڽӱ�

    //����ָ��ĳ���ڵ��ָ��
    GraphNode<T, E> *getNode(int index){
        return &(this->NodeTable.find(index)->data);
    }

    bool isEmpty(){
        return NodeTable.isEmpty();
    }
};

#endif //DATASTRUCTURE_GRAPH_H
