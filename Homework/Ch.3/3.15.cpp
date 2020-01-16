//
// Created by 13592 on 2019/11/17.
// p132 3.15

#include "../../HeaderFiles/Exp2/List.h"

//求最大整数的递归算法
int maxInt(List<int> lt, int index, int max){
    //index到达链表尾时跳出递归
    if(index == lt.getLen()-1)return max;
    if(max < lt.find(index)->data)max = lt.find(index)->data;
    //index递增，继续递归
    index += 1;
    maxInt(lt, index, max);
}

//求链表结点个数的递归算法
int countNodes(List<int> lt, int index){
    //index到达链表尾时跳出递归，此时index+1即为结点的个数（即表长）
    if(lt.find(index)->next == lt.getLast())return index+1;
    //index递增，继续递归
    index++;
    countNodes(lt, index);
}

//求所有整数平均值的递归算法：原理与上两个算法相近
double aver(List<int> lt, double index, int sum, double sln){
    if(lt.find(index)->next == lt.getLast())return sln;
    sum += lt.find(index)->data;
    sln = sum/(index+1);
    index++;
    aver(lt, index, sum, sln);
}
/*
int main(){
    int arr[] = {1,5,6,3,2};
    List<int> lt(5, arr);
    cout << "最大整数为：" << maxInt(lt, 0, lt.find(0)->data) << endl;
    cout << "结点个数为：" << countNodes(lt, 0) << endl;
    cout << "平均值为：" << aver(lt, 0, 0, 0) << endl;
    return 0;
}*/