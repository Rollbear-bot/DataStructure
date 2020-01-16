//
// Created by 13592 on 2019/11/17.
// p132 3.10 借助栈实现单链表上的逆置运算

#include "../../HeaderFiles/Exp2/List.h"
#include "../../HeaderFiles/Exp5/Stack.h"

//借助栈实现单链表逆置的算法
template <class T>
List<T> inversion(List<T> &lt){
    //构造一个与链表lt等长的栈
    Stack<T> st(lt.getLen());
    for(int index = 0; index < lt.getLen(); index++){
        //将索引为index的元素入栈
        st.push(lt.find(index)->data);
    }
    List<T> sln(0);
    while (!st.isEmpty()){
        //元素出栈并链入新链表
        sln.append(st.pop());
    }
    return sln;
}
/*
int main(){
    int arr[] = {1,5,2,3,4};
    List<int> lt(5, arr);
    inversion(lt).printList();
    return 0;
}*/
