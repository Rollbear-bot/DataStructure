//
// Created by 13592 on 2019/11/17.
// p86 2.17

#include "../../HeaderFiles/Exp2/List.h"
//#include "../../HeaderFiles/Exp3/CircleList.h"

//����ȼ��ڽ������򣬶������µ��������㷨
//���������㷨����Ҫ�ֱ�Ϊ������ż�������
template <class T>
void exchange(List<T> lt){
    int len = lt.getLen();
    T temp;
    //�������ż��
    if(len%2 == 0){
        for(int index = 0; index <= len/2-1; index++){
            //�±�Ϊindex�Ľ�����±�Ϊlen-1-index�Ľ�㻥��ֵ
            temp = lt.find(index)->data;
            T value = lt.find(len-1-index)->data;
            lt.alter(index, value);
            lt.alter(len-1-index, temp);
        }
    }
    //�����������
    else{
        for(int index = 0; index < (len-1)/2; index++){
            //�±�Ϊindex�Ľ�����±�Ϊlen-1-index�Ľ�㻥��ֵ
            temp = lt.find(index)->data;
            T value = lt.find(len-1-index)->data;
            lt.alter(index, value);
            lt.alter(len-1-index, temp);
        }
    }
}
/*
int main(){
    int arr[] = {1,5,2,3,7};
    List<int> lt(5,arr);
    lt.printList();
    exchange(lt);
    lt.printList();
    return 0;
}*/

