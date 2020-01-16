//
// Created by 13592 on 2019/11/21.
// 多项式顺序表实现

#ifndef DATASTRUCTURE_POLYBYLINEARTABLE_H
#define DATASTRUCTURE_POLYBYLINEARTABLE_H

#include "../../HeaderFiles/Exp1/LinearTable.h"
#include "PolyByList.h"

template <class T>
class PolyByLinearTable{
public:
    //必须至少给出最高次项次数来构造
    PolyByLinearTable(int hig){
        this->hig = hig;
        this->data = LinearTable<T>(hig + 1);
    }

    //从链表实现的多项式构造
    PolyByLinearTable(PolyByList<T> pl){
        this->hig = pl.getHig();
        //将pl数据域中的数据复制到本对象的数据域
        T temp;
        for(int index = 0; index <= hig; index++){
            temp = pl.find(index);
            this->data.alter(index, temp);
        }
    }

    //拷贝构造函数
    PolyByLinearTable(PolyByLinearTable<T> &another){
        this->hig  = another.hig;
        //复制data中的数据值
        for(int index = 0; index <= hig; index++){
            this->data.find(index) = another.find(index);
        }//end for
    }

public:
    //获取某项的系数值
    T& find(int index){
        return this->data.find(index);
    }

    //修改某项的系数值
    void alter(int index, T value){
        this->data.alter(index, value);
    }

    //输出多项式
    void printPoly(){
        for(int index = hig; index > 0; index--){
            T item = this->data.find(index);
            if(index == 1){
                //次数为1时省略次数
                if(item < 0)cout << "(" << item << ")" << "x" << " + ";
                else if(item > 0)cout << item << "x" << " + ";
            } else{
                //次数不为1时要写次数
                if(item < 0)cout << "(" << item << ")" << "x^" << index << " + ";
                else if(item > 0)cout << item << "x^" << index << " + ";
            }
            //0次项不用写"x"
        }//end for
        if(data.find(0) < 0)cout << "(" << data.find(0) << ")" << endl;
        else cout << data.find(0) << endl;
    }

    //运算符重载+
    PolyByLinearTable<T> operator+(PolyByLinearTable<T> another){
        PolyByLinearTable<T> sln(1);
        if(this->hig >= another.hig){
            //本多项式的最高次大于another的最高次时
            sln = *this;
            for(int index = 0; index <= another.hig; index++){
                sln.data.find(index) += another.data.find(index);
            }
        } else{
            //本多项式的最高次小于another的最高次时
            sln = another;
            for(int index = 0; index <= this->hig; index++){
                sln.data.find(index) += this->data.find(index);
            }
        }
        return sln;
    }


protected:
    LinearTable<T> data; //数据域：使用顺序表储存
    int hig; //最高次项次数
};

#endif //DATASTRUCTURE_POLYBYLINEARTABLE_H
