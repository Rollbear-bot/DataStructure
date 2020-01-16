//
// Created by 13592 on 2019/11/13.
/* 使用单链表实现的多项式
 * 2019.11.23 未实现多项式的乘积运算
 * */

#ifndef DATASTRUCTURE_POLYBYLIST_H
#define DATASTRUCTURE_POLYBYLIST_H

#include "..//Exp2//List.h"

template <class T>
class PolyByList{
public:
    //必须给定最高次来构造多项式
    PolyByList(int Highest){
        this->hig = Highest;
        //表长应该为最高次数+1，因为有零次项
        this->data = List<T>(Highest+1);
    }

    //给定最高次项的同时初始化
    PolyByList(int Highest, T arr[]){
        this->hig = Highest;
        this->data = List<T>(Highest+1, Highest+1, arr);
    }

    //拷贝构造函数
    PolyByList(PolyByList<T> &another){
        this->data = another.data;
        this->hig = another.hig;
    }

public:
    //返回某项的系数值
    T& find(int index){
        return this->data.find(index)->data;
    }

    //修改某项的值
    void alter(int index, T value){
        this->data.alter(index, value);
    }

    //输出多项式
    void printPoly(){
        for(int index = hig; index > 0; index--){
            T item = this->data.find(index)->data;
            //次数为1时省略次数
            if(index == 1){
                if(item < 0)cout << "(" << item << ")" << "x" << " + ";
                else if(item > 0)cout << item << "x" << " + ";
            //次数不为1时要写次数
            } else{
                if(item < 0)cout << "(" << item << ")" << "x^" << index << " + ";
                else if(item > 0)cout << item << "x^" << index << " + ";
            }
            //0次项不用写"x"
        }
        if(data.find(0)->data < 0)cout << "(" << data.find(0)->data << ")" << endl;
        else cout << data.find(0)->data << endl;
    }

    //运算符重载+
    PolyByList<T> operator+(PolyByList<T> another){
        PolyByList<T> sln(1);
        if(this->hig >= another.hig){
            sln = *this;
            for(int index = 0; index <= another.hig; index++){
                sln.data.find(index)->data += another.data.find(index)->data;
            }
        } else{
            sln = another;
            for(int index = 0; index <= this->hig; index++){
                sln.data.find(index)->data += this->data.find(index)->data;
            }
        }
        return sln;
    }

    //运算符重载-
    //有问题
    PolyByList<T> operator-(PolyByList<T> another){
        PolyByList<T> sln(1);
        if(this->hig >= another.hig){
            sln = *this;
            for(int index = 0; index <= another.hig; index++){
                sln.data.find(index)->data -= another.data.find(index)->data;
            }
        }
        else{
            sln = another;
            for(int index = 0; index <= this->hig; index++){
                sln.data.find(index)->data -= this->data.find(index)->data;
            }
        }
        return sln;
    }

    int getHig(){return this->hig;}

protected:
    List<T> data;
    int hig;
};

#endif //DATASTRUCTURE_POLYBYLIST_H