//
// Created by 13592 on 2019/11/22.
/* 串：链接实现
 * 2019.11.25 添加串的模式匹配：朴素匹配B-F算法
 * 2019.11.26 串的模式匹配：KMP算法
 */

#ifndef DATASTRUCTURE_STRING_H
#define DATASTRUCTURE_STRING_H

#include "../Exp2/List.h"

template <class T>
class String{
public:
    //默认构造一个空串
    String(){ String(0);}

    //使用一个数组来构造串
    String(int len, T arr[]){
        this->len = len;
        //使用数组来初始化数据域
        this->data = List<T>(len, arr);
    }

    //从字符数组构造一个字符串
    String(const char str[]){
        if(*str == '\0')String(0);
        else{
            this->data = List<char>(0);
            while (*str != '\0'){
                data.append(*str);
                str++;
            }
            this->len = data.getLen();
        }
    }

    //仅指定串长来构造串：不建议使用
    String(int len){ this->len = len;}

    //拷贝构造函数
    String(String<T> &another){
        this->len = another.getLen();
        this->data = List<T>(0);
        //复制串中的元素
        for(int index = 0; index < len; index++){
            this->data.append(another.getELe(index));
        }
    }


public:
    int getLen() const { return this->len;}

    //重写串
    void rewrite(int len) {
        T item;
        this->len = len;
        this->data = List<T>(0);
        for(int index = 0; index < len; index++){
            cout << "请输入第" << index+1 << "个元素：";
            cin >> item;
            this->data.append(item);
        }
    }

    //附加一个元素到串尾
    void add(T item){
        this->data.append(item);
        len++;
    }

    //输出串
    void printString() const {
        for(int index = 0; index < len; index++){
            cout << this->data.find(index)->data;
        }
        cout << endl;
    }

    //获取某个位置的元素
    T& getELe(int index) const {
        return data.find(index)->data;
    }

    //修改某个位置的元素
    void alter(int index, T value){
        this->data.alter(index, value);
    }

    //拼接两个串
    String<T> append(const String<T> &another){
        String<T> sln = *this;
        //在当前串尾附加
        for(int index = 0; index < another.getLen(); index++){
            //将another的元素逐个附加到当前串尾
            sln.add(another.getELe(index));
        }
        return sln;
    }

    //取位置index后的长度为len的串
    String<T> &cutStr(int index, int len) const {
        String<T> sln(0);
        for(int i = index; i < len + index - 1; i++){
            try {
                sln.append(data.find(index)->data);
            }catch (IndexOutException e){}
        }
        return sln;
    }

    //串的模式匹配（朴素匹配）：若匹配成功返回第一个匹配字符的下标，匹配失败返回-1
    int match(String<T> pattern){
        bool matched = false;
        //遍历目标串
        for(int targetIndex = 0; targetIndex < this->getLen(); targetIndex++){
            //遍历模式串
            for(int patternIndex = 0; patternIndex < pattern.getLen(); patternIndex++){
                //匹配失败，退回
                if(this->data.find(targetIndex + patternIndex)->data != pattern.getELe(patternIndex)) break;
                //匹配成功
                if(patternIndex == pattern.getLen()-1) return targetIndex;
            }
        }
        //匹配失败，返回-1
        return -1;
    }

    //串的模式匹配（KMP算法）若匹配成功则返回第一个匹配的字符的下标，匹配失败则返回-1
    int fastMatch(String<T> pattern){}

protected:
    List<T> data; //使用链表来储存
    int len; //串的长度
};

#endif //DATASTRUCTURE_STRING_H
