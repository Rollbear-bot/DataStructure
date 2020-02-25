// Created by 13592 on 2019/12/11.
// 图：邻接表实现

#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include "../Exp1/LinearTable.h"
#include "../Exp2/List.h"
#include "../Exp5/Stack.h"
#include "../Exp6/Queue.h"
#include "../Exp2/Set.h"

//边的定义
template <class T, class E>
struct Edge{
    //构造函数
    explicit Edge(int start = 0, int dest = 0, E cost = 0):
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
    Edge<T, E> &operator =(const Edge<T, E> operand){
        this->cost = operand.cost;
        this->start = operand.start;
        this->dest = operand.dest;
        return *this;
    }

    int dest = 0; //该边的终点（使用编号表示）
    int start = 0; //边的起点
    E cost = 0; //边上的权值

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
        return value == another.value && index == another.index;
        //节点相等不需要满足“与他们相连的边也一样”
    }

    //比较编号的大小
    bool operator <(const GraphNode<T, E> &a){return index<a.index;}
    bool operator >(const GraphNode<T, E> &a){return index>a.index;}

    T value; //该顶点的数据
    List<Edge<T, E>> EdgeTable; //该顶点的链接边表
    int index = 0;
};


//图的定义
template <class T, class E>
class Graph{
public:
    //构造函数：默认使用“#”代表无效的顶点
    Graph(T nullValue = '#'): nullValue(nullValue){}

    //拷贝构造函数
    Graph(const Graph<T, E> &another){
        this->NodeTable = another.NodeTable;
        this->nullValue = another.nullValue;
    }

    //析构函数
    ~Graph(){
        //todo::销毁图
    }

    //赋值运算符重载
    Graph<T, E> &operator =(const Graph<T, E> operand){
        this->NodeTable = operand.NodeTable;
        this->nullValue = operand.nullValue;
        return *this;
    }

    //图判等
    bool operator ==(const Graph<T, E> &operand) const {
        return this->NodeTable == operand.NodeTable;
    }

public:
    //添加结点（没有入度的孤立点）
    //提供给类外添加节点的函数，避免在类内使用，可能会导致节点的序号错乱
    bool addNode(T value){
        this->NodeTable.append(GraphNode<T, E>(value, NodeTable.length()));
        return true;
    }


    //在图中插入一条边
    bool addEdge(const Edge<T, E> &edge){

        for(int index = 0; index < NodeTable.length(); index++){
            //找到编号对应的顶点
            if(NodeTable[index].index == edge.start)
                {NodeTable[index].EdgeTable.append(
                        Edge<T, E>(edge.start, edge.dest, edge.cost));}
            if(NodeTable[index].index == edge.dest)
                {NodeTable[index].EdgeTable.append(
                        Edge<T, E>(edge.dest, edge.start, edge.cost));}
        }
        /*
        //将边链入A节点的边表
        NodeTable.find(edge.start)->data.EdgeTable.append(
                Edge<T, E>(edge.start, edge.dest, edge.cost));
        //将边链入B节点的边表
        NodeTable.find(edge.dest)->data.EdgeTable.append(
                Edge<T, E>(edge.dest, edge.start, edge.cost));
                */
        return true;
    }


    //深度优先遍历（非递归）：返回遍历结果的链表
    //使用栈实现，对于每个节点A，先访问，然后从它的邻接表中取出第一个节点B，然后将节点A入栈；
    //如果A的邻接表中没有节点，则从栈顶去一个节点，直到栈空
    static List<T> DFS(Graph<T, E> graph, int start = 0){
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
                for(int index = 0; index < graph.NodeTable.length(); index++){
                    for(int i = 0; i < graph.getNode(index)->EdgeTable.length(); i++){
                        if(graph.NodeTable.getElem(
                                graph.getNode(index)->EdgeTable.getElem(i).dest)
                                == *currentNode){
                            //若发现某条边的终点是该节点，删除该条边
                            graph.getNode(index)->EdgeTable.removeByIndex(i);
                            i--;
                        }
                    }
                }
                 */
                //currentNode->EdgeTable.removeByIndex(0);

                currentNode = temp;
            }
            else currentNode = stack.pop();
        } while(!stack.isEmpty()); //end while
        return result;
    }


    //广度优先遍历（非递归)：返回遍历结果的链表，可以指定开始的节点
    //使用队列实现，对于每个节点，首先访问它，然后将它的所有临接点入队列，
    //从队头取节点，重复以上（注意设置“已访问”标记）直到队列空
    static List<T> BFS(Graph<T, E> graph, int start = 0){
        List<T> result;
        Queue<GraphNode<T, E>*> queue(2*graph.numOfNode());
        List<GraphNode<T, E>*> visited(graph.numOfNode()); //访问标记
        GraphNode<T, E> *current;
        if(!graph.realNode(start)) return result; //若start不在图中，返回空表
        queue.enter(graph.getNode(start)); //从编号为start的节点开始访问

        do{
            current = queue.quit();
            if(visited.inList(current)) continue; //如果当前节点已经访问过，跳过

            result.append(current->value); //访问当前节点
            visited.append(current); //记录已访问
            //将它的所有邻接点入队列
            while(!current->EdgeTable.isEmpty()){
                queue.enter(graph.getNode(current->EdgeTable.getElem(0).dest));
                current->EdgeTable.removeByIndex(0);
            }
        }while(!queue.isEmpty());

        return result;
    }


    //广度优先遍历：递归实现的封装
    static List<T> recursionBFS(Graph<T, E> graph, int start = 0){
        return BFS_recursion(graph,
                             *graph.getNode(start),
                             List<T>(),
                             new Queue<GraphNode<T, E>>(graph.numOfNode()));
    }


    //深度优先遍历：递归实现的封装
    static List<T> recursionDFS(Graph<T, E> graph, int start = 0){
        return DFS_recursion(graph,
                *graph.getNode(start),
                List<T>(),
                new Stack<GraphNode<T, E>>(graph.numOfNode()));
    }


    //最小生成树：克鲁斯卡尔算法
    static Graph<T, E> MST_Kruskal(const Graph<T, E> &graph){
        //首先取出所有的边，将他们组成一个集合，并按照权值从小到大的顺序排序
        List<Edge<T, E>> edges = graph.getNode(0)->EdgeTable;

        //添加所有边到edges表
        for(int index = 1; index < graph.numOfNode(); index++){
            edges = List<Edge<T, E>>::add(edges, graph.getNode(index)->EdgeTable);
        }
        edges.insertSort(); //按照权值从小到大排序

        List<Edge<T, E>> result; //结果的边集
        int maxEdges = graph.numOfNode()-1;
        Edge<T, E> curEdge;
        Graph<T, E> mst;
        int maxLimb = graph.numOfNode()-1; //二叉树的边数等于节点数减一
        //开始构造生成树，每次从边表中取出权值最小的一条边，判断它是否是可用边，
        //结果集中的边数到达(顶点数-1)时（二叉树的边数==结点数-1）停止
        while (result.length() < maxLimb){
            //从表edges首部取出一条边，并将它从表删除
            curEdge = edges.quit();
            //判断它是否是有效的边，非有效则跳过
            if(!mst.isEmpty()){
                //若当前边的起点和终点联通，则跳过
                if(accessible(mst, curEdge.start, curEdge.dest)
                   || (curEdge.start == curEdge.dest))
                    continue;
            }
            //将新的点加入生成树tree
            if(!mst.NodeTable.inList(*graph.getNode(curEdge.start)))
                mst.NodeTable.append(
                        GraphNode<T, E>(graph.getElem(curEdge.start),
                                graph.getNode(curEdge.start)->index));
            if(!mst.NodeTable.inList(*graph.getNode(curEdge.dest)))
                mst.NodeTable.append(
                        GraphNode<T, E>(graph.getElem(curEdge.dest),
                                graph.getNode(curEdge.dest)->index));
            //将新的边加入生成树
            mst.addEdge(curEdge);
            result.append(curEdge);
        }

        //todo::如何从一个具有二叉树特征的图建立二叉树的链接结构
        //然后从结果边集构造二叉树
        return mst;
    }


    //最小生成树：Prim算法
    //可以指定开始节点，不指定则从编号为0的节点开始
    static Graph<T, E> MST_Prim(const Graph<T, E> &graph, int start = 0){
        Graph<T, E> mst;
        List<Edge<T, E>> compare; //compare中的类型从指针改为Edge实体，否则不能比较权值大小
        Edge<T, E> miniEdge;
        //这里不能使用addNode来添加顶点，会导致原图中顶点和生成树中的顶点序号不同，产生错乱
        mst.NodeTable.append(GraphNode<T, E>(graph.getNode(start)->value, start));

        //所有节点都在结果集mst中时，算法结束
        while(mst.numOfNode() < graph.numOfNode()){
            compare = List<Edge<T, E>>(); //初始化

            //取出所有从“结果点集”中的节点出发的边
            //这里需要注意索引i的取值范围，最大的编号值未必是NodeTable的长度
            for(int i = 0, index; i <= mst.NodeTable.maxElem().index; i++){
                if(!mst.realNode(i)) continue; //这个编号的顶点不存在，则跳过
                index = mst.getNode(i)->index;
                compare = compare.add(compare, getEdges_entity(graph, index));
            }

            //如果存在某边的终点已经在结果集mst中，则将该边移除
            for(int edgeIndex = 0; edgeIndex < compare.length(); edgeIndex++){
                for(int nodeIndex = 0; nodeIndex <= mst.NodeTable.maxElem().index; nodeIndex++){
                    if(!mst.realNode(nodeIndex)) continue;
                    if(nodeIndex == compare.getElem(edgeIndex).dest){
                        compare.removeByIndex(edgeIndex);
                        edgeIndex--; //链表中少了一个元素，索引同步减一
                        break;
                    }
                }
            }
            //将边按权值从小到大排序，取出权值最小的边，将该边、该边上的点加入结果集
            compare.insertSort();
            miniEdge = compare.quit();

            //mst.addNode(graph.getElem(miniEdge->dest)); //不能重新编写序号，会出现边连接错误
            mst.NodeTable.append(GraphNode<T, E>(graph.getElem(miniEdge.dest),
                    graph.getNode(miniEdge.dest)->index));
            mst.addEdge(miniEdge);
        } //end while
        return mst;
    }


    //最短路径：Dijkstra算法
    //open和closed表改为使用集合Set类型存储（不允许添加重复元素）
    //函数返回一个表，表示起始点到i位置的最小距离是List[i]
    List<E> shortestPath(int start) const {
        List<E> cost(numOfNode());
        Set<GraphNode<T, E>> open; //所有已生成而未考察的节点
        Set<GraphNode<T, E>> closed; //所有已访问的节点
        //从start节点开始
        closed.append(*getNode(start));
        cost.alter(start, 0);
        //start节点的所有邻接点进入open
        for(int index = 0; index < getNode(start)->EdgeTable.length(); index++)
            open.append(
                    *getNode(getNode(start)->EdgeTable.getElem(index).dest));

        //List<Edge<T, E>> edges;
        //Edge<T, E> curEdge, minEdge;
        while(!open.isEmpty()){
            /*
            //获取所有从closed中的点出发的边
            for(int index = 0; index < closed.getLen(); index++)
                edges = getEdges_ptrOnly(*this, closed.getElem(index).index);
            //去除终点也在closed中的部分
            for(int index = 0; index < closed.length(); index++)
                for(int edgeIndex = 0; edgeIndex < edges.length(); edgeIndex++)
                    if(edges.getElem(edgeIndex).dest == getNode(index)->index)
                        edges.removeByIndex(edgeIndex);
            */

            //在这里计算open中的节点的cost
            Edge<T, E> tmpEdge;
            GraphNode<T, E> tmpNode;
            E curCost;
            for(int index = 0; index < open.length(); index++){
                tmpNode = open[index];
                for(int edgeIndex = 0;
                edgeIndex < tmpNode.EdgeTable.length();
                edgeIndex++){
                    //遍历open中的所有点涉及的所有边
                    tmpEdge = tmpNode.EdgeTable[edgeIndex];
                    //只有连接open和closed的点才考虑
                    if(closed.inList(*getNode(tmpEdge.dest))){
                        curCost = cost[tmpEdge.dest] + tmpEdge.cost;
                        if(curCost < cost[tmpNode.index]){
                            //只有当前的cost比表中的小才修改，保持cost最小值
                            cost[tmpNode.index] = curCost;
                        }
                    }
                }
            }

            /*
            for(int nodeIndex = 0; nodeIndex < open.length(); nodeIndex++){
                for(int edgeIndex = 0;
                edgeIndex < open.getElem(nodeIndex).EdgeTable.length();
                edgeIndex++){
                    curEdge = open.getElem(nodeIndex).EdgeTable.getElem(edgeIndex);
                    if(closed.inList(*getNode(curEdge.dest)))
                        edges.append(curEdge);
                }
            }
            edges.insertSort(); //由小到大排序
            minEdge = edges.quit(); //取出连接最近点的边
             */

            //从open中找出cost最小的点
            GraphNode<T, E> node = open[0];
            for(int index = 0; index < open.length(); index++){
                if(cost[open[index].index] < cost[node.index])
                    node = open[index];
            }
            //点的所有临界点加入open
            closed.append(node);
            for(int index = 0;
            index < node.EdgeTable.length();
            index++){
                //open会自动跳过重复的元素，因为它是一个集合
                open.append(getElem(node.EdgeTable[index].dest));
            }
            //把加入了closed的点从open里移除
            open.removeByIndex(open.locate(node));
        }//end while
        return cost;
    }


    //判断图中的两个点是否在同一个连通分量上
    static bool accessible(const Graph<T, E> &graph, int nodeA, int nodeB){
        //注意序号问题
        //通过广度遍历的结果来判断是否联通（不在遍历结果中即不可达）
        return BFS(graph, nodeA).inList(graph.getElem(nodeB));
    }


    //节点个数
    int numOfNode() const {
        return this->NodeTable.length();
    }


    //获取某个节点的数据值，序号为顶点表NodeTable中的序号
    T getElem(int index) const {
        //return NodeTable.getElem(index).value;
        //注意序号
        return getNode(index)->value;
    }


    //打印所有边
    void printAllEdges() const {
        Edge<T, E> curEdge;
        List<Edge<T, E>> edges;
        int num = numOfNode();
        E sum = 0;

        //注意顶点的序号
        for(int index = 0; index < num; index++){
            for(int i = 0; i < getNode(index)->EdgeTable.length(); i++){
                curEdge = getNode(index)->EdgeTable.getElem(i);
                if(edges.inList(Edge<T, E>(curEdge.start, curEdge.dest, curEdge.cost))
                || edges.inList(Edge<T, E>(curEdge.dest, curEdge.start, curEdge.cost)))
                    continue;
                edges.append(curEdge);
            }
        }

        for(int index = 0; index < edges.length(); index++){
            curEdge = edges.getElem(index);
            cout << "(" << getElem(curEdge.start) << ", "
                 << getElem(curEdge.dest) << ") "
                 << "cost = " << curEdge.cost << endl;
            sum += curEdge.cost;
        }
        cout << "sum of cost: " << sum << endl;
    }


    //打印所有顶点
    void printAllNodes() const {
        T value;
        for(int index = 0; index  < NodeTable.length(); index++){
            value = getElem(index);
            if(value != nullValue)
                cout << index << ": " << value << endl;
        }
    }


protected:
    List<GraphNode<T, E>> NodeTable; //顶点表（邻接表）
    T nullValue; //代表无效顶点的值

    //返回指向某个节点的指针
    GraphNode<T, E> *getNode(int index) const {
        //注意序号
        for(int i = 0; i < NodeTable.length(); i++){
            if(NodeTable.getElem(i).index == index)
                return &(NodeTable.find(i)->data); //找到序号为index的顶点
        }
        //return &(this->NodeTable.find(index)->data);
        //未找到
        return new GraphNode<T, E>(nullValue, -1);
    }


    bool isEmpty(){
        return NodeTable.isEmpty();
    }


    bool realNode(int index){
        return getNode(index)->value != nullValue;
    }


    //查找从某个节点出发的所有边（返回指针集）
    static List<Edge<T, E>*> getEdges_ptrOnly(Graph<T, E> graph, int start){
        Edge<T, E> *cur;
        List<Edge<T, E>*> res;
        for(int index = 0; index < graph.NodeTable.length(); index++){
            for(int i = 0; i < graph.getNode(index)->EdgeTable.length(); i++){
                cur = &(graph.getNode(index)->EdgeTable.find(i)->data);
                if(cur->start == start) res.append(cur);
            }
        }
        return res;
    }


    //查找从某个节点出发的所有边（返回实体集）
    static List<Edge<T, E>> getEdges_entity(Graph<T, E> graph, int start){
        Edge<T, E> cur;
        List<Edge<T, E>> res;
        for(int index = 0; index < graph.NodeTable.length(); index++){
            for(int i = 0; i < graph.getNode(index)->EdgeTable.length(); i++){
                cur = graph.getNode(index)->EdgeTable.find(i)->data;
                if(cur.start == start) res.append(cur);
            }
        }
        return res;
    }


    //广度优先遍历：递归实现
    static List<T> BFS_recursion(Graph<T, E> graph,
            GraphNode<T, E> curNode,
            List<T> res,
            Queue<GraphNode<T, E>> * const queue){
        //访问当前结点，然后从它出发的所有边的终点进入待访问队列，已访问过的节点除外
        res.append(curNode.value);
        List<Edge<T, E>*> tmp = getEdges_ptrOnly(graph, curNode.index);

        Edge<T, E> *curEdge;
        for(int index = 0; index < tmp.length(); index++){
            curEdge = tmp.getElem(index);
            if(res.inList(graph.getElem(curEdge->dest))
            || queue->inTable(*graph.getNode(curEdge->dest)))
                continue; //若该节点已访问过则跳过
            //否则进入待访问队列
            queue->enter(*graph.getNode(curEdge->dest));
        }

        if(queue->isEmpty()) return res; //递归出口
        //从队列头取出节点，继续访问
        return BFS_recursion(graph, queue->quit(), res, queue);
    }


    //深度优先遍历：递归实现
    static List<T> DFS_recursion(Graph<T, E> graph,
            GraphNode<T, E> curNode,
            List<T> res,
            Stack<GraphNode<T, E>> *const stack){
        //类似二叉树的前序遍历，利用栈
        //访问当前节点
        res.append(curNode.value);
        //获取从当前节点出发的所有边
        List<Edge<T, E>*> edges = graph.getEdges_ptrOnly(graph, curNode.index);

        Edge<T, E> *curEdge;
        //遍历edges的所有边，移除那些终点已经访问过的
        for(int index = 0; index < edges.length(); index++){
            curEdge = edges.getElem(index);
            if(res.inList(graph.getElem(curEdge->dest))
               || stack->inStack(*graph.getNode(curEdge->dest)))
                continue; //若该节点已访问过则跳过
            //否则进入待访问栈
            stack->push(*graph.getNode(curEdge->dest));
        }

        if(stack->isEmpty()) return res; //递归出口
        else return DFS_recursion(graph, stack->pop(), res, stack);
    }
};

#endif //DATASTRUCTURE_GRAPH_H
