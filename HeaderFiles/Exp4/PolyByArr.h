//
// Created by 13592 on 2019/11/20.
// ����ʵ�ֵĶ���ʽ��ʾ

#ifndef DATASTRUCTURE_POLYBYARR_H
#define DATASTRUCTURE_POLYBYARR_H

#include "../DsException.h"
#include "PolyByList.h"

template <class T>
class PolyByArr{
public:
    //�������ʽ���������ߴ�
    //����ߴ���������
    PolyByArr(int hig){
        //��ߴ��������������ĳ���ʱ�ڴ����
        if(hig >= 50)throw OverFlowException();
        this->H = hig;
    }

    //�������ʽ��ͬʱʹ����������ʼ��
    PolyByArr(int hig, T arr[]){
        if(hig >= 50)throw OverFlowException();
        this->H = hig;
        //ʹ�ò�����������ʼ��data������
        for(int index = 0; index <= hig; index++){
            this->data[index] = arr[index];
        }
    }

    //������ʵ�ֵĶ���ʽ����
    PolyByArr(PolyByList<T> pl){
        this->H = pl.hig;
        //ʹ��pl��data����ʼ���������������
        for(int index = 0; index <= H; index++){
            this->data[index] = pl.data.find(index)->data;
        }
    }

    //�������캯��
    PolyByArr(PolyByArr<T> &another){
        this->H  = another.H;
        //����data�е�����ֵ
        for(int index = 0; index <= H; index++){
            this->data[index] = another.data[index];
        }//end for
    }

public:
    //�޸�ĳ���ϵ��ֵ
    void alter(int index, T value){
        this->data[index] = value;
    }

    //�������ʽ
    void printPoly(){
        for(int index = H; index > 0; index--){
            T item = this->data[index];
            //����Ϊ1ʱʡ�Դ���
            if(index == 1){
                if(item < 0)cout << "(" << item << ")" << "x" << " + ";
                else if(item > 0)cout << item << "x" << " + ";
                //������Ϊ1ʱҪд����
            } else{
                if(item < 0)cout << "(" << item << ")" << "x^" << index << " + ";
                else if(item > 0)cout << item << "x^" << index << " + ";
            }
            //0�����д"x"
        }
        if(data[0] < 0)cout << "(" << data[0] << ")" << endl;
        else cout << data[0] << endl;
    }

    //���������+
    PolyByArr<T> operator+(PolyByArr<T> another){
        PolyByArr<T> sln(1);
        if(this->H >= another.H){
            //������ʽ����ߴδ���another����ߴ�ʱ
            sln = *this;
            for(int index = 0; index <= another.H; index++){
                sln.data[index] += another.data[index];
            }
        } else{
            //������ʽ����ߴ�С��another����ߴ�ʱ
            sln = another;
            for(int index = 0; index <= this->H; index++){
                sln.data[index] += this->data[index];
            }
        }
        return sln;
    }

protected:
    T data[50] = {0}; //������ʹ���������������
    int H; //��ߴδ���
};

#endif //DATASTRUCTURE_POLYBYARR_H
