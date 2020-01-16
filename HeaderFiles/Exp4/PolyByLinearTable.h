//
// Created by 13592 on 2019/11/21.
// ����ʽ˳���ʵ��

#ifndef DATASTRUCTURE_POLYBYLINEARTABLE_H
#define DATASTRUCTURE_POLYBYLINEARTABLE_H

#include "../../HeaderFiles/Exp1/LinearTable.h"
#include "PolyByList.h"

template <class T>
class PolyByLinearTable{
public:
    //�������ٸ�����ߴ������������
    PolyByLinearTable(int hig){
        this->hig = hig;
        this->data = LinearTable<T>(hig + 1);
    }

    //������ʵ�ֵĶ���ʽ����
    PolyByLinearTable(PolyByList<T> pl){
        this->hig = pl.getHig();
        //��pl�������е����ݸ��Ƶ��������������
        T temp;
        for(int index = 0; index <= hig; index++){
            temp = pl.find(index);
            this->data.alter(index, temp);
        }
    }

    //�������캯��
    PolyByLinearTable(PolyByLinearTable<T> &another){
        this->hig  = another.hig;
        //����data�е�����ֵ
        for(int index = 0; index <= hig; index++){
            this->data.find(index) = another.find(index);
        }//end for
    }

public:
    //��ȡĳ���ϵ��ֵ
    T& find(int index){
        return this->data.find(index);
    }

    //�޸�ĳ���ϵ��ֵ
    void alter(int index, T value){
        this->data.alter(index, value);
    }

    //�������ʽ
    void printPoly(){
        for(int index = hig; index > 0; index--){
            T item = this->data.find(index);
            if(index == 1){
                //����Ϊ1ʱʡ�Դ���
                if(item < 0)cout << "(" << item << ")" << "x" << " + ";
                else if(item > 0)cout << item << "x" << " + ";
            } else{
                //������Ϊ1ʱҪд����
                if(item < 0)cout << "(" << item << ")" << "x^" << index << " + ";
                else if(item > 0)cout << item << "x^" << index << " + ";
            }
            //0�����д"x"
        }//end for
        if(data.find(0) < 0)cout << "(" << data.find(0) << ")" << endl;
        else cout << data.find(0) << endl;
    }

    //���������+
    PolyByLinearTable<T> operator+(PolyByLinearTable<T> another){
        PolyByLinearTable<T> sln(1);
        if(this->hig >= another.hig){
            //������ʽ����ߴδ���another����ߴ�ʱ
            sln = *this;
            for(int index = 0; index <= another.hig; index++){
                sln.data.find(index) += another.data.find(index);
            }
        } else{
            //������ʽ����ߴ�С��another����ߴ�ʱ
            sln = another;
            for(int index = 0; index <= this->hig; index++){
                sln.data.find(index) += this->data.find(index);
            }
        }
        return sln;
    }


protected:
    LinearTable<T> data; //������ʹ��˳�����
    int hig; //��ߴ������
};

#endif //DATASTRUCTURE_POLYBYLINEARTABLE_H
