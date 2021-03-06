// 图计算测试菜单
// Created by @rollbear on 2020/2/22.

#ifndef DATASTRUCTURE_MENU11_H
#define DATASTRUCTURE_MENU11_H

#include "Graph.h"
#include "../UiCollection.h"

class Menu11{
public:
    static void menu(){
        char value;
        int cost, indexA, indexB;
        string choices[] = {"添加顶点",
                            "添加边",
                            "查看图中的顶点",
                            "查看图中的边",
                            "输出广度优先遍历序列",
                            "输出深度优先遍历序列",
                            "最小生成树：Kruskal算法",
                            "最小生成树：Prim算法",
                            "最短路径：dijkstra算法"};
        Graph<char, int> graph, mst;

        graph.addNode('A');//0
        graph.addNode('B');//1
        graph.addNode('C');//2
        graph.addNode('D');//3
        graph.addNode('E');//4
        graph.addNode('F');//5
        graph.addNode('G');//6
        graph.addNode('H');//7
        graph.addNode('I');//8
        graph.addEdge(Edge<char, int>(0, 1, 2));
        graph.addEdge(Edge<char, int>(1, 2, 11));
        graph.addEdge(Edge<char, int>(2, 5, 9));
        graph.addEdge(Edge<char, int>(5, 8, 10));
        graph.addEdge(Edge<char, int>(7, 8, 8));
        graph.addEdge(Edge<char, int>(6, 7, 6));
        graph.addEdge(Edge<char, int>(3, 6, 5));
        graph.addEdge(Edge<char, int>(0, 3, 1));
        graph.addEdge(Edge<char, int>(3, 4, 4));
        graph.addEdge(Edge<char, int>(1, 4, 3));
        graph.addEdge(Edge<char, int>(4, 8, 7));

        cout << "已建立空图" << endl;
        do{
            input = UiCollection::choices("图计算测试",
                    9, choices, false);
            switch (input){
                case 1:
                    try{
                        UiCollection::printLine();
                        cout << "输入顶点的数据值：";
                        cin >> value;
                        graph.addNode(value);
                        cout << "顶点添加完成！" << endl;
                        UiCollection::pauseAndClear();
                    }catch (exception &e){ cout<<e.what()<<endl;}
                    break;
                case 2:
                    try{
                        UiCollection::printLine();
                        cout << "当前图中的顶点表如下：" << endl;
                        graph.printAllNodes();
                        cout << "请输入新增的边起点的序号：";
                        cin >> indexA;
                        cout << "请输入新增的边终点的序号：";
                        cin >> indexB;
                        cout << "请输入新增的边的权值：";
                        cin >> cost;
                        graph.addEdge(Edge<char, int>(indexA, indexB, cost));
                        cout << "添加完成！" << endl;
                        UiCollection::pauseAndClear();
                    }catch (exception &e){ cout<<e.what()<<endl;}
                    break;
                case 3:
                    try{
                        UiCollection::printLine();
                        cout << "当前图中的顶点表如下：" << endl;
                        graph.printAllNodes();
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 4:
                    try{
                        UiCollection::printLine();
                        cout << "当前图中的所有边如下：" << endl;
                        graph.printAllEdges();
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 5:
                    try{
                        UiCollection::printLine();
                        cout << "请输入广度优先遍历起点的序号：";
                        cin >> indexA;
                        cout << "图的广度优先遍历序列：" << endl;
                        Graph<char, int>::recursionBFS(graph, indexA).printList();
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 6:
                    try{
                        UiCollection::printLine();
                        cout << "请输入深度优先遍历起点的序号：";
                        cin >> indexA;
                        cout << "图的深度优先遍历序列：" << endl;
                        Graph<char, int>::recursionDFS(graph, indexA).printList();
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 7:
                    try{
                        UiCollection::printLine();
                        if(graph.recursionBFS(graph).length() < graph.numOfNode()){
                            cout << "当前图非连通图，不能构造生成树" << endl;
                        }
                        else {
                            mst = Graph<char, int>::MST_Kruskal(graph);
                            cout << "最小生成树已生成" << endl;
                            cout << "最小生成树的深度优先遍历为：" << endl;
                            Graph<char, int>::recursionDFS(mst).printList();
                            cout << "最小生成树的广度优先遍历为：" << endl;
                            Graph<char, int>::recursionBFS(mst).printList();
                            cout << "最小生成树的所有边：" << endl;
                            mst.printAllEdges();
                        }
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 8:
                    try{
                        UiCollection::printLine();
                        if(graph.recursionBFS(graph).length() < graph.numOfNode()){
                            cout << "当前图非连通图，不能构造生成树" << endl;
                        }
                        else {
                            mst = Graph<char, int>::MST_Kruskal(graph);
                            cout << "最小生成树已生成" << endl;
                            cout << "最小生成树的深度优先遍历为：" << endl;
                            Graph<char, int>::recursionDFS(mst).printList();
                            cout << "最小生成树的广度优先遍历为：" << endl;
                            Graph<char, int>::recursionBFS(mst).printList();
                            cout << "最小生成树的所有边：" << endl;
                            mst.printAllEdges();
                        }
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 9:
                    try{
                        UiCollection::printLine();
                        cout << "请输入路径的起点的序号：";
                        cin >> indexA;
                        cout << "请输入路径的终点的序号：";
                        cin >> indexB;
                        if(indexA>=graph.numOfNode()||indexB>=graph.numOfNode()
                        ||indexA<0||indexB<0){
                            cout << "无效的编号" << endl;
                            break;
                        }
                        cout << "从" << graph.getElem(indexA) << "到"
                        << graph.getElem(indexB) << "的最短路径为："
                        << graph.shortestPath(indexA).getElem(indexB) << endl;
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}


                default:
                    break;
            }//end switch
        }while(input != 0);
    }

private:
    static int input;
};

//静态成员的初始化
int Menu11::input = 0;

#endif //DATASTRUCTURE_MENU11_H
