//
// Created by 13592 on 2019/11/17.
// p85 2.12

#include "../../HeaderFiles/Exp2/List.h"
#include <list>

//���ȶ��嵥����������㷨
//����������㷨
template <class T>
void sort(List<T> &lt){
    int len = lt.getLen();
    T temp;
    //����������㷨
    for(int i = 0; i < len-1; i++){
        int k = i;
        for(int j = i+1; j < len; j++){
            if(lt.find(k)->data > lt.find(j)->data) k = j;
        }
        //ֵ����
        temp = lt.find(k)->data;
        lt.find(k)->data = lt.find(i)->data;
        lt.find(i)->data = temp;
    }
}

//����������㷨��������b���ӵ�����a����
template <class T>
List<T> listAppend(List<T> listA, List<T> listB){
    int len = listA.getLen() + listB.getLen();
    List<T> sln(len);
    for(int index = 0; index < len; index++){
        if(index < listA.getLen()){
            //�������a��Ԫ��
            sln.alter(index, listA.find(index)->data);
        }else{
            //�������b��Ԫ��
            //��index��ȥ����a�ĳ�����������b�е�����
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

