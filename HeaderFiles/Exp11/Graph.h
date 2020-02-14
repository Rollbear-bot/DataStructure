// Created by 13592 on 2019/12/11.
// 图：邻接表实现

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include "../Exp1/LinearTable.h"
#include "../Exp2/List.h"
#include "../Exp5/Stack.h"
#include "../Exp6/Queue.h"

//边的定义
template <class T, class E>
struct Edge{
    //构造函数
    explicit Edge(int start = 0, int dest = 0, E cost = NULL):
        start(start), dest(dest), cost(cost){}

    //拷贝构造函数
    Edge(const Edge<T, E> &another){
        this->start = another.start;
        this->dest = another.dest;
        this->cost = another.cost;
    }

    //边判等（逻辑运算符重载）
    bool operator ==(const Edge<T, E> &another) const {
        return (start == another.start)
        && (dest == another.dest)
        && (cost == another.cost);
    }

    //权值比较
    bool operator <(const Edge<T, E> &another){
        return this->cost < another.cost;
    }
    bool operator >(const Edge<T, E> &another){
        return this->cost > another.cost;
    }

    //赋值重载
    Edge<T, E> operator =(const Edge<T, E> &operand){
        this->cost = operand.cost;
        this->start = operand.start;
        this->dest = operand.dest;
        return Edge<T, E>(start, dest, cost);
    }

    int dest; //该边的终点（使用编号表示）
    int start; //边的起点
    E cost; //边上的权值

    //Edge<T, E> *nextEdge; //下一条边链，这里因为用了List结构来储存边，
    //因此就不需要next这个地址域了
};


//顶点的定义
template <class T, class E>
struct GraphNode{
public:
    //构造函数
    explicit GraphNode(T value, int index): value(value), index(index){}
    GraphNode(): value(0){}
    //拷贝构造函数
    GraphNode(const GraphNode<T, E> &another){
        this->value = another.value;
        this->EdgeTable = another.EdgeTable;
        this->index = another.index;
    }
    //判等
    bool operator ==(const GraphNode<T, E> &another){
        return value == another.value;
        //节点相等不需要满足“与他们相连的边也一样”
    }

    T value; //该顶点的数据
    List<Edge<T, E>> EdgeTable; //该顶点的链接边表
    int index = 0;
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

    //析构函数
    ~Graph(){
        //todo::销毁图
    }

    //赋值运算符重载
    Graph<T, E> operator =(const Graph<T, E> &operand){
        this->NodeTable = operand.NodeTable;
        return Graph<T,E>(*this);
    }

    //图判等
    bool operator ==(const Graph<T, E> &operand) const {
        return this->NodeTable == operand.NodeTable;
    }

public:
    //添加结点（没有入度的孤立点）
    bool addNode(T value){
        this->NodeTable.append(GraphNode<T, E>(value, NodeTable.getLen()));
        return true;
    }


    //在图中插入一条边
    bool addEdge(const Edge<T, E> &edge){
        //将边链入A节点的边表
        NodeTable.find(edge.start)->data.EdgeTable.append(
                Edge<T, E>(edge.start, edge.dest, edge.cost));
        //将边链入B节点的边表
        NodeTable.find(edge.dest)->data.EdgeTable.append(
                Edge<T, E>(edge.dest, edge.start, edge.cost));
        return true;
    }


    //深度优先遍历：返回遍历结果的链表
    //使用栈实现，对于每个节点A，先访问，然后从它的邻接表中取出第一个节点B，然后将节点A入栈；
    //如果A的邻接表中没有节点，则从栈顶去一个节点，直到栈空
    static List<T> DFS(Graph<T, E> graph, int start){
        List<T> result;
        Stack<GraphNode<T, E>*> stack(2*graph.numOfNode());
        GraphNode<T, E> *temp, *currentNode = graph.getNode(0);
        do{
            if(!currentNode->EdgeTable.isEmpty()){
                //从编号为0的节点开始，访问当前节点
                result.append(currentNode->value);

                stack.push(currentNode);
                //从currentNode的边表中取出一个相邻节点
                temp = graph.getNode(currentNode->EdgeTable.getElem(0).dest);

                //删除所有终点为currentNode的边,todo::效率很低，需要遍历所有边表
                /*
                for(int index = 0; index < graph.NodeTable.getLen(); index++){
                    for(int i = 0; i < graph.getNode(index)->EdgeTable.getLen(); i++){
                        if(graph.NodeTable.getElem(
                                graph.getNode(index)->EdgeTable.getElem(i).dest)
                                == *currentNode){
                            //若发现某条边的终点是该节点，删除该条边
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


    //广度优先遍历：返回遍历结果的链表
    //使用队列实现，对于每个节点，首先访问它，然后将它的所有临接点入队列，
    //从队头取节点，重复以上（注意设置“已访问”标记）直到队列空
    static List<T> BFS(Graph<T, E> graph, int start){
        List<T> result;
        Queue<GraphNode<T, E>*> queue(2*graph.numOfNode());
        List<GraphNode<T, E>*> visited(graph.numOfNode()); //访问标记
        GraphNode<T, E> *current;
        queue.enter(graph.getNode(start)); //从编号为start的节点开始访问

        do{
            current = queue.quit();
            if(visited.inList(current)) continue; //如果当前节点已经访问过，跳过

            result.append(current->value); //访问当前节点
            visited.append(current); //记录已访问
            //将它的所有邻接点入队列
            while(!current->EdgeTable.isEmpty()){
                queue.enter(graph.getNode(current->EdgeTable.getElem(0).dest));
                current->EdgeTable.delByIndex(0);
            }
        }while(!queue.isEmpty());

        return result;
    }


    //最小生成树：克鲁斯卡尔算法
    static Graph<T, E> MST_Kruskal(const Graph<T, E> &graph){
        //首先取出所有的边，将他们组成一个集合，并按照权值从小到大的顺序排序
        int numOfEdges = 0;
        //计算边集合需要的大小
        for(int index = 0; index < graph.numOfNode(); index++){
            numOfEdges += graph.NodeTable.getElem(index).EdgeTable.getLen();
        }
        List<Edge<T, E>> edges = graph.getNode(0)->EdgeTable;
        /*
        for(int index = 0; index < graph.numOfNode(); index++)
            for(int edgeIndex = 0;
            edgeIndex < graph.getNode(index)->EdgeTable.getLen();
            edgeIndex++)
                //添加所有边到edges表
                edges.append(graph.getNode(index)->EdgeTable.getElem(edgeIndex));
        */

        for(int index = 1; index < graph.numOfNode(); index++){
            edges = List<Edge<T, E>>::add(edges, graph.getNode(index)->EdgeTable);
        }

        edges.insertSort(); //按照权值从小到大排序

        List<Edge<T, E>> result; //结果的边集
        int maxEdges = graph.numOfNode()-1;
        Edge<T, E> curEdge(0);
        Graph<T, E> tree;
        //开始构造生成树，每次从边表中取出权值最小的一条边，判断它是否是可用边，
        //结果集中的边数到达顶点数-1时（二叉树的边数==结点数-1）停止
        while (result.getLen() < maxEdges){
            //从表edges首部取出一条边
            curEdge = edges.quit();
            //判断它是否是有效的边，非有效则跳过
            if(!tree.isEmpty())
                if(accessible(tree, curEdge.start, curEdge.dest)
                || (curEdge.start == curEdge.dest))
                    continue;
            result.append(curEdge);
            //将新的点加入生成树tree
            if(!tree.NodeTable.inList(*graph.getNode(curEdge.start)))
                tree.addNode(graph.getElem(curEdge.start));
            if(!tree.NodeTable.inList(*graph.getNode(curEdge.dest)))
                tree.addNode(graph.getElem(curEdge.dest));
            //将新的边加入生成树
            tree.addEdge(curEdge);
        }

        //todo::如何从一个具有二叉树特征的图建立二叉树的链接结构
        //然后从结果边集构造二叉树
        return tree;
    }


    //最小生成树：Prim算法
    static BinTreeByLink<T> MST_Prim(const Graph<T, E> &graph){

    }


    //判断图中的两个点是否在同一个连通分量上
    static bool accessible(const Graph<T, E> &graph, int nodeA, int nodeB){
        if(nodeA >= graph.NodeTable.getLen()
        || nodeB >= graph.NodeTable.getLen())
            return false;
        //通过广度遍历的结果来判断是否联通（不在遍历结果中即不可达）
        return BFS(graph, nodeA).inList(graph.getElem(nodeB));
    }


    //节点个数
    int numOfNode() const {
        return this->NodeTable.getLen();
    }


    //获取某个节点的数据值，序号为顶点表NodeTable中的序号
    T getElem(int index) const {
        return NodeTable.getElem(index).value;
    }


    //打印所有边
    void printAllEdges() const {
        Edge<T, E> curEdge;
        for(int index = 0; index < numOfNode(); index++){
            for(int i = 0; i < NodeTable.getElem(index).EdgeTable.getLen(); i++){
                curEdge = NodeTable.getElem(index).EdgeTable.getElem(i);
                cout << "(" << curEdge.start << ", " << curEdge.dest << ") ";
            }
        }
        cout << endl;
    }


protected:
    List<GraphNode<T, E>> NodeTable; //顶点表（邻接表）

    //返回指向某个节点的指针
    GraphNode<T, E> *getNode(int index) const {
        return &(this->NodeTable.find(index)->data);
    }

    bool isEmpty(){
        return NodeTable.isEmpty();
    }
};

#endif //DATASTRUCTURE_GRAPH_H
