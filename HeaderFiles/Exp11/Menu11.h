// ͼ������Բ˵�
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
        string choices[] = {"��Ӷ���",
                            "��ӱ�",
                            "�鿴ͼ�еĶ���",
                            "�鿴ͼ�еı�",
                            "���������ȱ�������",
                            "���������ȱ�������",
                            "��С��������Kruskal�㷨",
                            "��С��������Prim�㷨",
                            "���·����dijkstra�㷨"};
        Graph<char, int> graph, mst;
        cout << "�ѽ�����ͼ" << endl;
        do{
            input = UiCollection::choices("ͼ�������",
                    9, choices, false);
            switch (input){
                case 1:
                    try{
                        UiCollection::printLine();
                        cout << "���붥�������ֵ��";
                        cin >> value;
                        graph.addNode(value);
                        cout << "���������ɣ�" << endl;
                        UiCollection::pauseAndClear();
                    }catch (exception &e){ cout<<e.what()<<endl;}
                    break;
                case 2:
                    try{
                        UiCollection::printLine();
                        cout << "��ǰͼ�еĶ�������£�" << endl;
                        graph.printAllNodes();
                        cout << "�����������ı�������ţ�";
                        cin >> indexA;
                        cout << "�����������ı��յ����ţ�";
                        cin >> indexB;
                        cout << "�����������ıߵ�Ȩֵ��";
                        cin >> cost;
                        graph.addEdge(Edge<char, int>(indexA, indexB, cost));
                        cout << "�����ɣ�" << endl;
                        UiCollection::pauseAndClear();
                    }catch (exception &e){ cout<<e.what()<<endl;}
                    break;
                case 3:
                    try{
                        UiCollection::printLine();
                        cout << "��ǰͼ�еĶ�������£�" << endl;
                        graph.printAllNodes();
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 4:
                    try{
                        UiCollection::printLine();
                        cout << "��ǰͼ�е����б����£�" << endl;
                        graph.printAllEdges();
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 5:
                    try{
                        UiCollection::printLine();
                        cout << "�����������ȱ���������ţ�";
                        cin >> indexA;
                        cout << "ͼ�Ĺ�����ȱ������У�" << endl;
                        Graph<char, int>::recursionBFS(graph, indexA).printList();
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 6:
                    try{
                        UiCollection::printLine();
                        cout << "������������ȱ���������ţ�";
                        cin >> indexA;
                        cout << "ͼ��������ȱ������У�" << endl;
                        Graph<char, int>::recursionDFS(graph, indexA).printList();
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 7:
                    try{
                        UiCollection::printLine();
                        if(graph.recursionBFS(graph).length() < graph.numOfNode()){
                            cout << "��ǰͼ����ͨͼ�����ܹ���������" << endl;
                        }
                        else {
                            mst = Graph<char, int>::MST_Kruskal(graph);
                            cout << "��С������������" << endl;
                            cout << "��С��������������ȱ���Ϊ��" << endl;
                            Graph<char, int>::recursionDFS(mst).printList();
                            cout << "��С�������Ĺ�����ȱ���Ϊ��" << endl;
                            Graph<char, int>::recursionBFS(mst).printList();
                        }
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 8:
                    try{
                        UiCollection::printLine();
                        if(graph.recursionBFS(graph).length() < graph.numOfNode()){
                            cout << "��ǰͼ����ͨͼ�����ܹ���������" << endl;
                        }
                        else {
                            mst = Graph<char, int>::MST_Kruskal(graph);
                            cout << "��С������������" << endl;
                            cout << "��С��������������ȱ���Ϊ��" << endl;
                            Graph<char, int>::recursionDFS(mst).printList();
                            cout << "��С�������Ĺ�����ȱ���Ϊ��" << endl;
                            Graph<char, int>::recursionBFS(mst).printList();
                        }
                        UiCollection::pauseAndClear();
                    }catch (exception &e){cout << e.what() << endl;}
                    break;
                case 9:
                    try{
                        UiCollection::printLine();
                        //todo::δ���
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

//��̬��Ա�ĳ�ʼ��
int Menu11::input = 0;

#endif //DATASTRUCTURE_MENU11_H
