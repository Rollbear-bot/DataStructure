//
// Created by 13592 on 2019/12/18.
//


//#ifndef DATASTRUCTURE_GRAPHMTX_H
//#define DATASTRUCTURE_GRAPHMTX_H

#include "Graph.h"

/**
 * 图的邻接矩阵实现
 * @tparam T
 * @tparam E
 */

/*
int maxWeight = 30;

template <class T,class E>
class Graphmtx: public Graph<T, E>{
    //template <class T, class E>
    friend istream &operator >>(istream &in, Graphmtx<T, E> &G); //输入
    //template <class T, class E>
    friend ostream &operator <<(ostream &out, Graphmtx<T, E> &G); //输出

public:
    //构造函数
    Graphmtx(int sz = DefaultSize);

    //析构函数
    ~Graphmtx(){
        delete [] VerticesList;
        delete [] Edge;
    }

public:
    //取顶点i的值，i不合理返回0
    T getValue(int i);

    //取边(v1, v2)上的权值
    E getWeight(int v1, int v2){
        return (v1!=-1 && v2!=-1)? Edge[v1][v2]: 0;
    }

    //取顶点v的第一个邻接结点
    virtual int getFirstNeighbor(int v);

    //取邻接顶点w的下一个邻接顶点
    virtual int getNextNeighbor(int v, int w);

    //插入一个顶点vertex
    virtual bool insertVertex(const T& vertex);

    //插入边(v1, v2)，权为cost
    virtual bool insertEdge(int v1, int v2, E cost);

    //删去顶点v和所有相关的边
    virtual bool removeVertex(int v);

    //在图中删去边(v1, v2)
    virtual bool removeEdge(int v1, int v2);

private:
    T *VerticesList; //顶点表
    E **Edge; //邻接矩阵

    //给出顶点vertex在图中的位置
    int getVertexPos(T vertex){
        for(int i = 0; i < numVertices; i++){
            if(VerticesList[i] == vertex)
                return i;
        }
        return -1;
    }
};

template<class T, class E>
Graphmtx<T, E>::Graphmtx(int sz): Graph(sz) {
    //构造函数
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    int i, j;
    VerticesList = new T[maxVertices]; //创建顶点表数组
    Edge = (E**)new E *[maxVertices]; //创建邻接矩阵数组
    //邻接矩阵初始化
    for(i = 0; i < maxVertices; i++){
        for(j = 0; j< maxVertices; j++)
            Edge[i][j] = (i==j)? 0: maxWeight;
    }
}

template<class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v) {
    //给出顶点位置为v的第一个邻接顶点的位置，如果找不到，函数返回-1
    if(v!=-1){
        for(int col = 0; col < numVertices; col++)
            if(Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
    }
    return -1;
}

template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w) {
    //给出顶点v的某个邻接点w的下一个邻接顶点
    if(v != -1 && w != -1){
        for(int col = w + 1; col < numVertices; col++){
            if(Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
        }
    }
    return -1;
}

template<class T, class E>
bool Graphmtx<T, E>::insertVertex(const T &vertex) {
    //插入顶点vertex
    if(numVertices == maxVertices)return false; //表满，不插入
    VerticesList[numVertices++] = vertex;
    return true;
}

template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v) {
    //删去顶点v和所有与它相邻的边
    if(v < 0 || v >= numVertices) return false; //v不在图中，不能删除
    if(numVertices == 1)return false; //只剩下一个顶点，不能删除
    int i, j;
    VerticesList[v] = VerticesList[numVertices -1];
    for(i = 0; i < numVertices; i++){
        //减去与v相关联的边数
        if(Edge[i][v] > 0 && Edge[i][v] < maxWeight) numEdges--;
    }
    for(i = 0; i < numVertices; i++){
        Edge[i][v] = Edge[i][numVertices-1]; //用最后一列填补第v列
    }
    numVertices--; //顶点数减一
    for(j = 0; j < numVertices; j++){
        //用最后一行填补第v行
        Edge[v][j] = Edge[numVertices][j];
    }
    return true;
}

template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost) {
    //插入边
    //插入条件
    if(v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && Edge[v1][v2] == maxWeight){
        Edge[v1][v2] = Edge[v2][v1] = cost;
        numEdges++;
        return true;
    }
    else return false;
}

template<class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2) {
    //在图中删去边(v1, v2)
    if(v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && Edge[v1][v2] > 0 && Edge[v1][v2] < maxWeight){
        Edge[v1][v2] = Edge[v2][v1] = maxWeight;
        numEdges--;
        return true;
    }
    return false;
}

template <class T, class E>
istream &operator>>(istream &in, Graphmtx<T, E> &G) {
    //输出友元重载
    int i, j, k, n=0, m=0;
    T e1, e2;
    E weight;
    //输入顶点数n和边数m
    cout << "输入顶点数和边数：" << endl;
    in >> n >> m;
    //建立顶点表数据
    for(i = 0; i< n; i++){
        in >> e1;
        G.insertVertex(e1);
    }
    i = 0;
    while(i < m){
        cout << "输入端点信息：" << endl;
        in >> e1 >> e2 >> weight; //输入端点信息
        //查顶点号
        j = G.getVertexPos(e1);
        k = G.getVertexPos(e2);
        if(j == -1 || k == -1) cout << "边两端信息有误，重新输入！" << endl;
        else {
            G.insertEdge(j, k, weight);
            i++;
        }
    }
    return in;
}

template <class T, class E>
ostream &operator<<(ostream &out, Graphmtx<T, E> &G) {
    //重载输出
    int i, j, n, m;
    T e1, e2;
    E w;
    n = G.NumberOfVertices();
    m = G.NumberOfEdges();
    out << n << ", " << m << endl; //输出顶点数和边数
    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++){
            w = G.getWeight(i, j);
            if(w > 0 && w < maxWeight){
                //有效，输出
                e1 = G.getValue(i);
                e2 = G.getValue(j);
                out << "(" << e1 << ", " << e2 << ", " << w << ")" << endl;
            }
        }
    }
    return out;
}

template<class T, class E>
T Graphmtx<T, E>::getValue(int i){
        return VerticesList[i];
}

#endif //DATASTRUCTURE_GRAPHMTX_H
*/