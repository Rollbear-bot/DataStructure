//
// Created by 13592 on 2019/11/17.
// p85 2.12

#include "../../HeaderFiles/Exp2/List.h"
#include <list>

//首先定义单链表的排序算法
//链表的排序算法
template <class T>
void sort(List<T> &lt){
    int len = lt.getLen();
    T temp;
    //插入排序的算法
    for(int i = 0; i < len-1; i++){
        int k = i;
        for(int j = i+1; j < len; j++){
            if(lt.find(k)->data > lt.find(j)->data) k = j;
        }
        //值交换
        temp = lt.find(k)->data;
        lt.find(k)->data = lt.find(i)->data;
        lt.find(i)->data = temp;
    }
}

//链表的扩充算法：将链表b链接到链表a后面
template <class T>
List<T> listAppend(List<T> listA, List<T> listB){
    int len = listA.getLen() + listB.getLen();
    List<T> sln(len);
    for(int index = 0; index < len; index++){
        if(index < listA.getLen()){
            //填充链表a的元素
            sln.alter(index, listA.find(index)->data);
        }else{
            //填充链表b的元素
            //将index减去链表a的长度来修正在b中的索引
            sln.alter(index, listB.find(index - listA.getLen())->data);
        }
    }//end for
    sort(sln);
    return sln;
}
/*
int main(){
    try {
        int arr[] = {1, 5, 2, 4, 3};
        List<int> lt(5, arr);
        int arrB[]  = {7, 9, 10};
        List<int> ltB(3, arrB);
        listAppend(lt, ltB).printList();
        return 0;
    }
    catch(IndexOutException e){
        e.print();
    }catch(NullPointer e){
        e.print();
    }catch (OverFlowException e){
        e.print();
    }


}*/

