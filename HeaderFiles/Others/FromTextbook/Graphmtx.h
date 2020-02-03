//
// Created by 13592 on 2019/12/18.
//


//#ifndef DATASTRUCTURE_GRAPHMTX_H
//#define DATASTRUCTURE_GRAPHMTX_H

#include "Graph.h"

/**
 * ͼ���ڽӾ���ʵ��
 * @tparam T
 * @tparam E
 */

/*
int maxWeight = 30;

template <class T,class E>
class Graphmtx: public Graph<T, E>{
    //template <class T, class E>
    friend istream &operator >>(istream &in, Graphmtx<T, E> &G); //����
    //template <class T, class E>
    friend ostream &operator <<(ostream &out, Graphmtx<T, E> &G); //���

public:
    //���캯��
    Graphmtx(int sz = DefaultSize);

    //��������
    ~Graphmtx(){
        delete [] VerticesList;
        delete [] Edge;
    }

public:
    //ȡ����i��ֵ��i��������0
    T getValue(int i);

    //ȡ��(v1, v2)�ϵ�Ȩֵ
    E getWeight(int v1, int v2){
        return (v1!=-1 && v2!=-1)? Edge[v1][v2]: 0;
    }

    //ȡ����v�ĵ�һ���ڽӽ��
    virtual int getFirstNeighbor(int v);

    //ȡ�ڽӶ���w����һ���ڽӶ���
    virtual int getNextNeighbor(int v, int w);

    //����һ������vertex
    virtual bool insertVertex(const T& vertex);

    //�����(v1, v2)��ȨΪcost
    virtual bool insertEdge(int v1, int v2, E cost);

    //ɾȥ����v��������صı�
    virtual bool removeVertex(int v);

    //��ͼ��ɾȥ��(v1, v2)
    virtual bool removeEdge(int v1, int v2);

private:
    T *VerticesList; //�����
    E **Edge; //�ڽӾ���

    //��������vertex��ͼ�е�λ��
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
    //���캯��
    maxVertices = sz;
    numVertices = 0;
    numEdges = 0;
    int i, j;
    VerticesList = new T[maxVertices]; //�������������
    Edge = (E**)new E *[maxVertices]; //�����ڽӾ�������
    //�ڽӾ����ʼ��
    for(i = 0; i < maxVertices; i++){
        for(j = 0; j< maxVertices; j++)
            Edge[i][j] = (i==j)? 0: maxWeight;
    }
}

template<class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v) {
    //��������λ��Ϊv�ĵ�һ���ڽӶ����λ�ã�����Ҳ�������������-1
    if(v!=-1){
        for(int col = 0; col < numVertices; col++)
            if(Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
    }
    return -1;
}

template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w) {
    //��������v��ĳ���ڽӵ�w����һ���ڽӶ���
    if(v != -1 && w != -1){
        for(int col = w + 1; col < numVertices; col++){
            if(Edge[v][col] > 0 && Edge[v][col] < maxWeight) return col;
        }
    }
    return -1;
}

template<class T, class E>
bool Graphmtx<T, E>::insertVertex(const T &vertex) {
    //���붥��vertex
    if(numVertices == maxVertices)return false; //������������
    VerticesList[numVertices++] = vertex;
    return true;
}

template<class T, class E>
bool Graphmtx<T, E>::removeVertex(int v) {
    //ɾȥ����v�������������ڵı�
    if(v < 0 || v >= numVertices) return false; //v����ͼ�У�����ɾ��
    if(numVertices == 1)return false; //ֻʣ��һ�����㣬����ɾ��
    int i, j;
    VerticesList[v] = VerticesList[numVertices -1];
    for(i = 0; i < numVertices; i++){
        //��ȥ��v������ı���
        if(Edge[i][v] > 0 && Edge[i][v] < maxWeight) numEdges--;
    }
    for(i = 0; i < numVertices; i++){
        Edge[i][v] = Edge[i][numVertices-1]; //�����һ�����v��
    }
    numVertices--; //��������һ
    for(j = 0; j < numVertices; j++){
        //�����һ�����v��
        Edge[v][j] = Edge[numVertices][j];
    }
    return true;
}

template<class T, class E>
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost) {
    //�����
    //��������
    if(v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && Edge[v1][v2] == maxWeight){
        Edge[v1][v2] = Edge[v2][v1] = cost;
        numEdges++;
        return true;
    }
    else return false;
}

template<class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2) {
    //��ͼ��ɾȥ��(v1, v2)
    if(v1 > -1 && v1 < numVertices && v2 > -1 && v2 < numVertices && Edge[v1][v2] > 0 && Edge[v1][v2] < maxWeight){
        Edge[v1][v2] = Edge[v2][v1] = maxWeight;
        numEdges--;
        return true;
    }
    return false;
}

template <class T, class E>
istream &operator>>(istream &in, Graphmtx<T, E> &G) {
    //�����Ԫ����
    int i, j, k, n=0, m=0;
    T e1, e2;
    E weight;
    //���붥����n�ͱ���m
    cout << "���붥�����ͱ�����" << endl;
    in >> n >> m;
    //�������������
    for(i = 0; i< n; i++){
        in >> e1;
        G.insertVertex(e1);
    }
    i = 0;
    while(i < m){
        cout << "����˵���Ϣ��" << endl;
        in >> e1 >> e2 >> weight; //����˵���Ϣ
        //�鶥���
        j = G.getVertexPos(e1);
        k = G.getVertexPos(e2);
        if(j == -1 || k == -1) cout << "��������Ϣ�����������룡" << endl;
        else {
            G.insertEdge(j, k, weight);
            i++;
        }
    }
    return in;
}

template <class T, class E>
ostream &operator<<(ostream &out, Graphmtx<T, E> &G) {
    //�������
    int i, j, n, m;
    T e1, e2;
    E w;
    n = G.NumberOfVertices();
    m = G.NumberOfEdges();
    out << n << ", " << m << endl; //����������ͱ���
    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++){
            w = G.getWeight(i, j);
            if(w > 0 && w < maxWeight){
                //��Ч�����
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