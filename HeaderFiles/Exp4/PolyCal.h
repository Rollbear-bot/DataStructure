//
// Created by 13592 on 2019/11/15.
// ����ʽ����

#ifndef DATASTRUCTURE_POLYCAL_H
#define DATASTRUCTURE_POLYCAL_H

#include "../Exp2/List.h"
#include "PolyByList.h"

template <class T>
class PolyCal{
public:
    PolyCal(){}

public:
    //���������е���������ʽ��ͨ��������ѡ����ӣ���������������ʽ������
    static PolyByList<T> &add(int index1, int index2){
        return data.find(index1)->data + data.find(index2)->data;
    }

    //���������е���������ʽ��ͨ��������ѡ���������������
    static PolyByList<T> &sub(int index1, int index2){
        return data.find(index1)->data - data.find(index2)->data;
    }

    //��������ѱ���Ķ���ʽ
    static void printPolys(){
        for(int index = 0; index < last; index++){
            cout << index << ": ";
            data.find(index)->data.printPoly();
            cout << endl;
        }
    }

private:
    //�����򣺴��Ҫ��������Ķ���ʽ
    static List<PolyByList<T>> data;
    static int last; //lastָ�����һ��Ԫ�ص���һ��λ��
};

//��̬��Ա�ĳ�ʼ��
template <class T>
List<PolyByList<T>> PolyCal<T>::data = List<PolyByList<T>>();

template <class T>
int PolyCal<T>::last = 0;

#endif //DATASTRUCTURE_POLYCAL_H
