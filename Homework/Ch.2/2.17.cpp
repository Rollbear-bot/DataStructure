//
// Created by 13592 on 2019/11/17.
// p86 2.17

#include "../../HeaderFiles/Exp2/List.h"
//#include "../../HeaderFiles/Exp3/CircleList.h"

//题意等价于将链表倒序，定义以下单链表倒序算法
//单链表倒序算法：需要分表长为奇数和偶数的情况
template <class T>
void exchange(List<T> lt){
    int len = lt.getLen();
    T temp;
    //如果表长是偶数
    if(len%2 == 0){
        for(int index = 0; index <= len/2-1; index++){
            //下标为index的结点与下标为len-1-index的结点互换值
            temp = lt.find(index)->data;
            T value = lt.find(len-1-index)->data;
            lt.alter(index, value);
            lt.alter(len-1-index, temp);
        }
    }
    //如果表长是奇数
    else{
        for(int index = 0; index < (len-1)/2; index++){
            //下标为index的结点与下标为len-1-index的结点互换值
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

