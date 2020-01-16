//
// Created by 13592 on 2019/11/25.
/* ��̬������ʹ�����Ա�ʵ��
 * 2019.11.25 ��Ӳ��ҷ�ʽ��˳����ҡ����ֲ���
 * */

#ifndef DATASTRUCTURE_STATICSEARCH_H
#define DATASTRUCTURE_STATICSEARCH_H

#include "../Exp1/LinearTable.h"

template <class T>
class StaticSrhTable: public LinearTable<T>{
public:
    //Ӧ���ڹ��캯�����������
    //�ڹ��캯���г�ʼ������LinearTable
    StaticSrhTable(int maxLen): LinearTable<T>(maxLen){}
    StaticSrhTable(int maxLen, int arrLen, T arr[]):
        LinearTable<T>(maxLen, arrLen, arr){ insertSort(); }

    //�������캯����ʹ����һ����������ʼ������
    StaticSrhTable(StaticSrhTable<T> &another):
        LinearTable<T>(another.getMax(), another.getMax(), another.data){}

public:
    //˳����ң���������
    int orderSearch(T item){
        for(int index = 0; index < LinearTable<T>::last; index++){
            if(LinearTable<T>::data[index] == item)return index;
        }
        throw NoFound();
    }

    //���ֲ��ң���������
    int binarySearch(T item){
        insertSort();
        int sln = 0;
        int start = 0;
        int end = LinearTable<T>::last-1;
        int mid = end/2;
        bool found = false;
        while (true){
            if(LinearTable<T>::data[mid] == item){
                //���ҵ����˳�
                sln = mid;
                found = true;
                break;
            }
            if(LinearTable<T>::data[end] == item){
                //���ҵ����˳�
                sln = end;
                found = true;
                break;
            }
            //δ�ҵ��������������˳�
            if(start == mid || end == mid)break;
            if(item < LinearTable<T>::data[mid]){
                //������Χ��СΪ���
                end = mid;
                mid = end/2;
            }else {
                //������Χ��СΪ�Ҳ�
                start = mid;
                mid = (start + end)/2;
            }
        }//end while
        if(!found)throw NoFound();
        return sln;
    }

public:
    //���������������������
    //�������򣺴�С����
    void insertSort(){
        int i, j, k;
        T temp;
        for(int i = 0; i < this->last-1; i++){
            k = i;
            for(int j = i + 1; j < this->last; j++){
                if(LinearTable<T>::data[k] > LinearTable<T>::data[j]) k = j;
            }
            //��������Ϊi��k��Ԫ�ص�ֵ
            temp = LinearTable<T>::data[i];
            LinearTable<T>::data[i] = LinearTable<T>::data[k];
            LinearTable<T>::data[k] = temp;
        }
    }

    /*
    //�鲢����ʹ�õݹ�
    void mergeSort(){
        int i;
        T temp;
        int mid = (last-1)/2;
    }
     */
};

#endif //DATASTRUCTURE_STATICSEARCH_H
