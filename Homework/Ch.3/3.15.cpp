//
// Created by 13592 on 2019/11/17.
// p132 3.15

#include "../../HeaderFiles/Exp2/List.h"

//����������ĵݹ��㷨
int maxInt(List<int> lt, int index, int max){
    //index��������βʱ�����ݹ�
    if(index == lt.getLen()-1)return max;
    if(max < lt.find(index)->data)max = lt.find(index)->data;
    //index�����������ݹ�
    index += 1;
    maxInt(lt, index, max);
}

//������������ĵݹ��㷨
int countNodes(List<int> lt, int index){
    //index��������βʱ�����ݹ飬��ʱindex+1��Ϊ���ĸ�����������
    if(lt.find(index)->next == lt.getLast())return index+1;
    //index�����������ݹ�
    index++;
    countNodes(lt, index);
}

//����������ƽ��ֵ�ĵݹ��㷨��ԭ�����������㷨���
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
    cout << "�������Ϊ��" << maxInt(lt, 0, lt.find(0)->data) << endl;
    cout << "������Ϊ��" << countNodes(lt, 0) << endl;
    cout << "ƽ��ֵΪ��" << aver(lt, 0, 0, 0) << endl;
    return 0;
}*/