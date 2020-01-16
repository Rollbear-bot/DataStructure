//
// Created by 13592 on 2019/11/20.
// 数组实现的多项式表示

#ifndef DATASTRUCTURE_POLYBYARR_H
#define DATASTRUCTURE_POLYBYARR_H

#include "../DsException.h"
#include "PolyByList.h"

template <class T>
class PolyByArr{
public:
    //构造多项式必须给定最高次
    //用最高次数来构造
    PolyByArr(int hig){
        //最高次项次数超过数组的长度时内存溢出
        if(hig >= 50)throw OverFlowException();
        this->H = hig;
    }

    //构造多项式的同时使用数组来初始化
    PolyByArr(int hig, T arr[]){
        if(hig >= 50)throw OverFlowException();
        this->H = hig;
        //使用参数数组来初始化data数据域
        for(int index = 0; index <= hig; index++){
            this->data[index] = arr[index];
        }
    }

    //从链表实现的多项式构造
    PolyByArr(PolyByList<T> pl){
        this->H = pl.hig;
        //使用pl的data来初始化本对象的数据域
        for(int index = 0; index <= H; index++){
            this->data[index] = pl.data.find(index)->data;
        }
    }

    //拷贝构造函数
    PolyByArr(PolyByArr<T> &another){
        this->H  = another.H;
        //复制data中的数据值
        for(int index = 0; index <= H; index++){
            this->data[index] = another.data[index];
        }//end for
    }

public:
    //修改某项的系数值
    void alter(int index, T value){
        this->data[index] = value;
    }

    //输出多项式
    void printPoly(){
        for(int index = H; index > 0; index--){
            T item = this->data[index];
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
        if(data[0] < 0)cout << "(" << data[0] << ")" << endl;
        else cout << data[0] << endl;
    }

    //运算符重载+
    PolyByArr<T> operator+(PolyByArr<T> another){
        PolyByArr<T> sln(1);
        if(this->H >= another.H){
            //本多项式的最高次大于another的最高次时
            sln = *this;
            for(int index = 0; index <= another.H; index++){
                sln.data[index] += another.data[index];
            }
        } else{
            //本多项式的最高次小于another的最高次时
            sln = another;
            for(int index = 0; index <= this->H; index++){
                sln.data[index] += this->data[index];
            }
        }
        return sln;
    }

protected:
    T data[50] = {0}; //数据域：使用数组来存放数据
    int H; //最高次次数
};

#endif //DATASTRUCTURE_POLYBYARR_H
