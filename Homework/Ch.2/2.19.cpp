//
// Created by 13592 on 2019/11/17.
// p86 2.19 改造双向链表

/*
struct Nodex{
    Nodex(){}
    Nodex(int item, Nodex *next, Nodex *rLink){
        data = item;
        lLink = next;
        this->rLink = rLink;
    }
    int data;
    Nodex *lLink = nullptr;
    Nodex *rLink = nullptr;
};

//带表头结点的双向链表
class Listx{
public:
    //构造函数：题目要求的算法在此
    Listx(int len, int arr[]){
        //完成lLink的链接
        head = new Nodex;
        Nodex *flag = head;
        for(int count = 0; count <= len; count++){
            flag->lLink = new Nodex;
            flag = flag->lLink;
        }
        last = flag;

        //以下完成rLink的链接

    }

protected:
    Nodex *head; //指向表头结点，表头结点不存放数据
    Nodex *last; //指向最后一个数据结点的下一个结点
};*/

#include "../../HeaderFiles/Exp3/DoubleLinkedList.h"
#include "../../HeaderFiles/Exp2/List.h"

//双向链表的排序算法：函数模板
template <class T>
void sort(DoubleLinkedList<T> &lt){
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

//按元素值从小到大修改逆向指针的算法:
//先找出从小到大的排序，在按排序重构front指针
template <class T>
DoubleLinkedList<T> alterLinks(const DoubleLinkedList<T> lt){
    //用一个链表compare来储存双向链表中的元素大小关系：
    //元素越小下标排得越前
    List<int> compare(lt.getLen());
    //k为每轮比较中指向最小元素的索引
    int k;
    for(int i = 0; i < lt.getLen(); i++){
        k = i;
        for(int j = 0; j < lt.getLen(); j++){
            //如果索引j已经在compare中，则不比较这个元素
            if(compare.inList(j))break;
            if(lt.find(k)->data > lt.find(j)->data) k = j;
        }
        compare.alter(i, k);
    }
    DoubleLinkedList<T> sln = lt;
    //修改双向链表的逆向指针
    for(int index = 0; index < compare.getLen()-1; index++){
        int slnIndex = compare.find(index)->data;
        //当前结点的下一个结点的compare中的索引
        int nextSlnIndex = compare.find(index)->next->data;
        //结点的front指针指向下一个更大元素的结点
        sln.find(slnIndex)->front = sln.find(nextSlnIndex);
    }
    return sln;
}

/*
int main(){

}
 */