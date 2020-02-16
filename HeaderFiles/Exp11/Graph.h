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
    explicit Edge(int start = 0, int dest = 0, E cost = 0):
        start(start), dest(dest), cost(cost){}

    //�������캯��
    Edge(const Edge<T, E> &another){
        this->start = another.start;
        this->dest = another.dest;
        this->cost = another.cost;
    }

    //���еȣ��߼���������أ�
    bool operator ==(const Edge<T, E> &another) const {
        return (start == another.start)
        && (dest == another.dest)
        && (cost == another.cost);
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
        this->start = operand.start;
        this->dest = operand.dest;
        return Edge<T, E>(start, dest, cost);
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
        this->index = another.index;
    }
    //�е�
    bool operator ==(const GraphNode<T, E> &another){
        return value == another.value && index == another.index;
        //�ڵ���Ȳ���Ҫ���㡰�����������ı�Ҳһ����
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
    //�ṩ��������ӽڵ�ĺ���������������ʹ�ã����ܻᵼ�½ڵ����Ŵ���
    bool addNode(T value){
        this->NodeTable.append(GraphNode<T, E>(value, NodeTable.getLen()));
        return true;
    }


    //��ͼ�в���һ����
    bool addEdge(const Edge<T, E> &edge){
        //��������A�ڵ�ı߱�
        NodeTable.find(edge.start)->data.EdgeTable.append(
                Edge<T, E>(edge.start, edge.dest, edge.cost));
        //��������B�ڵ�ı߱�
        NodeTable.find(edge.dest)->data.EdgeTable.append(
                Edge<T, E>(edge.dest, edge.start, edge.cost));
        return true;
    }


    //������ȱ������ǵݹ飩�����ر������������
    //ʹ��ջʵ�֣�����ÿ���ڵ�A���ȷ��ʣ�Ȼ��������ڽӱ���ȡ����һ���ڵ�B��Ȼ�󽫽ڵ�A��ջ��
    //���A���ڽӱ���û�нڵ㣬���ջ��ȥһ���ڵ㣬ֱ��ջ��
    static List<T> DFS(Graph<T, E> graph, int start = 0){
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


    //������ȱ������ǵݹ�)�����ر����������������ָ����ʼ�Ľڵ�
    //ʹ�ö���ʵ�֣�����ÿ���ڵ㣬���ȷ�������Ȼ�����������ٽӵ�����У�
    //�Ӷ�ͷȡ�ڵ㣬�ظ����ϣ�ע�����á��ѷ��ʡ���ǣ�ֱ�����п�
    static List<T> BFS(Graph<T, E> graph, int start = 0){
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
                current->EdgeTable.removeByIndex(0);
            }
        }while(!queue.isEmpty());

        return result;
    }


    //������ȱ������ݹ�ʵ�ֵķ�װ
    static List<T> recursionBFS(Graph<T, E> graph, int start = 0){
        return BFS_recursion(graph,
                             *graph.getNode(start),
                             List<T>(),
                             new Queue<GraphNode<T, E>>(graph.numOfNode()));
    }


    //������ȱ������ݹ�ʵ�ֵķ�װ
    static List<T> recursionDFS(Graph<T, E> graph, int start = 0){
        return DFS_recursion(graph,
                *graph.getNode(start),
                List<T>(),
                new Stack<GraphNode<T, E>>(graph.numOfNode()));
    }


    //��С����������³˹�����㷨
    static Graph<T, E> MST_Kruskal(const Graph<T, E> &graph){
        //����ȡ�����еıߣ����������һ�����ϣ�������Ȩֵ��С�����˳������
        List<Edge<T, E>> edges = graph.getNode(0)->EdgeTable;

        //������бߵ�edges��
        for(int index = 1; index < graph.numOfNode(); index++){
            edges = List<Edge<T, E>>::add(edges, graph.getNode(index)->EdgeTable);
        }
        edges.insertSort(); //����Ȩֵ��С��������

        List<Edge<T, E>> result; //����ı߼�
        int maxEdges = graph.numOfNode()-1;
        Edge<T, E> curEdge;
        Graph<T, E> mst;
        //��ʼ������������ÿ�δӱ߱���ȡ��Ȩֵ��С��һ���ߣ��ж����Ƿ��ǿ��ñߣ�
        //������еı������ﶥ����-1ʱ���������ı���==�����-1��ֹͣ
        while (result.getLen() < maxEdges){
            //�ӱ�edges�ײ�ȡ��һ���ߣ��������ӱ�ɾ��
            curEdge = edges.quit();
            //�ж����Ƿ�����Ч�ıߣ�����Ч������
            if(!mst.isEmpty())
                if(accessible(mst, curEdge.start, curEdge.dest)
                || (curEdge.start == curEdge.dest))
                    continue;
            result.append(curEdge);
            //���µĵ����������tree
            if(!mst.NodeTable.inList(*graph.getNode(curEdge.start)))
                //mst.addNode(graph.getElem(curEdge.start)); //������Ŵ���
                mst.NodeTable.append(
                        GraphNode<T, E>(graph.getElem(curEdge.start),
                                graph.getNode(curEdge.start)->index));
            if(!mst.NodeTable.inList(*graph.getNode(curEdge.dest)))
                //mst.addNode(graph.getElem(curEdge.dest)); //������Ŵ���
                mst.NodeTable.append(
                        GraphNode<T, E>(graph.getElem(curEdge.dest),
                                graph.getNode(curEdge.dest)->index));
            //���µı߼���������
            mst.addEdge(curEdge);
        }

        //todo::��δ�һ�����ж�����������ͼ���������������ӽṹ
        //Ȼ��ӽ���߼����������
        return mst;
    }


    //��С��������Prim�㷨
    //����ָ����ʼ�ڵ㣬��ָ����ӱ��Ϊ0�Ľڵ㿪ʼ
    static Graph<T, E> MST_Prim(const Graph<T, E> &graph, int start = 0){
        Graph<T, E> mst;
        List<Edge<T, E>*> compare;
        Edge<T, E> *miniEdge;
        mst.addNode(graph.getElem(start));

        //���нڵ㶼�ڽ����mst��ʱ���㷨����
        while(mst.numOfNode() < graph.numOfNode()){
            compare = List<Edge<T, E>*>(); //��ʼ��
            //ȡ�����дӡ�����㼯���еĽڵ�����ı�
            for(int i = 0, index; i < mst.NodeTable.getLen(); i++){
                index = mst.getNode(i)->index;
                compare = compare.add(compare, getEdges(graph, index));
            }
            //�������ĳ�ߵ��յ��Ѿ��ڽ����mst�У��򽫸ñ��Ƴ�
            for(int edgeIndex = 0; edgeIndex < compare.getLen(); edgeIndex++){
                for(int nodeIndex = 0; nodeIndex < mst.NodeTable.getLen(); nodeIndex++){
                    if(mst.getNode(nodeIndex)->index == compare.getElem(edgeIndex)->dest){
                        compare.removeByIndex(edgeIndex);
                        edgeIndex--; //����������һ��Ԫ��
                        break;
                    }
                }
            }
            //���߰�Ȩֵ��С��������ȡ��Ȩֵ��С�ıߣ����ñߡ��ñ��ϵĵ��������
            compare.insertSort();
            miniEdge = compare.quit();

            //mst.addNode(graph.getElem(miniEdge->dest)); //�������±�д��ţ�����ֱ����Ӵ���
            mst.NodeTable.append(GraphNode<T, E>(graph.getElem(miniEdge->dest),
                    graph.getNode(miniEdge->dest)->index));
            mst.addEdge(*miniEdge);
        } //end while

        return mst;
    }


    //�ж�ͼ�е��������Ƿ���ͬһ����ͨ������
    static bool accessible(const Graph<T, E> &graph, int nodeA, int nodeB){
        if(nodeA >= graph.NodeTable.getLen()
        || nodeB >= graph.NodeTable.getLen())
            return false;
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


    //��ӡ���б�
    void printAllEdges() const {
        Edge<T, E> curEdge;
        List<Edge<T, E>> edges;
        for(int index = 0; index < numOfNode(); index++){
            for(int i = 0; i < NodeTable.getElem(index).EdgeTable.getLen(); i++){
                curEdge = NodeTable.getElem(index).EdgeTable.getElem(i);
                if(edges.inList(Edge<T, E>(curEdge.start, curEdge.dest, curEdge.cost))
                || edges.inList(Edge<T, E>(curEdge.dest, curEdge.start, curEdge.cost)))
                    continue;
                edges.append(curEdge);
            }
        }

        for(int index = 0; index < edges.getLen(); index++){
            curEdge = edges.getElem(index);
            cout << "(" << NodeTable.getElem(curEdge.start).value << ", "
                 << NodeTable.getElem(curEdge.dest).value << ") ";
        }
        cout << endl;
    }


protected:
    List<GraphNode<T, E>> NodeTable; //������ڽӱ�


    //����ָ��ĳ���ڵ��ָ��
    GraphNode<T, E> *getNode(int index) const {
        return &(this->NodeTable.find(index)->data);
    }


    bool isEmpty(){
        return NodeTable.isEmpty();
    }


    //���Ҵ�ĳ���ڵ���������б�
    static List<Edge<T, E>*> getEdges(Graph<T, E> graph, int start){
        Edge<T, E> *cur;
        List<Edge<T, E>*> res;
        for(int index = 0; index < graph.NodeTable.getLen(); index++){
            for(int i = 0; i < graph.getNode(index)->EdgeTable.getLen(); i++){
                cur = &(graph.getNode(index)->EdgeTable.find(i)->data);
                if(cur->start == start) res.append(cur);
            }
        }
        return res;
    }


    //������ȱ������ݹ�ʵ��
    static List<T> BFS_recursion(Graph<T, E> graph,
            GraphNode<T, E> curNode,
            List<T> res,
            Queue<GraphNode<T, E>> * const queue){
        //���ʵ�ǰ��㣬Ȼ��������������бߵ��յ��������ʶ��У��ѷ��ʹ��Ľڵ����
        res.append(curNode.value);
        List<Edge<T, E>*> tmp = getEdges(graph, curNode.index);

        Edge<T, E> *curEdge;
        for(int index = 0; index < tmp.getLen(); index++){
            curEdge = tmp.getElem(index);
            if(res.inList(graph.getElem(curEdge->dest))
            || queue->inTable(*graph.getNode(curEdge->dest)))
                continue; //���ýڵ��ѷ��ʹ�������
            //�����������ʶ���
            queue->enter(*graph.getNode(curEdge->dest));
        }

        if(queue->isEmpty()) return res; //�ݹ����
        //�Ӷ���ͷȡ���ڵ㣬��������
        return BFS_recursion(graph, queue->quit(), res, queue);
    }


    //������ȱ������ݹ�ʵ��
    static List<T> DFS_recursion(Graph<T, E> graph,
            GraphNode<T, E> curNode,
            List<T> res,
            Stack<GraphNode<T, E>> *const stack){
        //���ƶ�������ǰ�����������ջ
        //���ʵ�ǰ�ڵ�
        res.append(curNode.value);
        //��ȡ�ӵ�ǰ�ڵ���������б�
        List<Edge<T, E>*> edges = graph.getEdges(graph, curNode.index);

        Edge<T, E> *curEdge;
        //����edges�����бߣ��Ƴ���Щ�յ��Ѿ����ʹ���
        for(int index = 0; index < edges.getLen(); index++){
            curEdge = edges.getElem(index);
            if(res.inList(graph.getElem(curEdge->dest))
               || stack->inStack(*graph.getNode(curEdge->dest)))
                continue; //���ýڵ��ѷ��ʹ�������
            //������������ջ
            stack->push(*graph.getNode(curEdge->dest));
        }

        if(stack->isEmpty()) return res; //�ݹ����
        else return DFS_recursion(graph, stack->pop(), res, stack);
    }
};

#endif //DATASTRUCTURE_GRAPH_H
