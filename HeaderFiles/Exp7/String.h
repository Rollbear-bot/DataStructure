//
// Created by 13592 on 2019/11/22.
/* ��������ʵ��
 * 2019.11.25 ��Ӵ���ģʽƥ�䣺����ƥ��B-F�㷨
 * 2019.11.26 ����ģʽƥ�䣺KMP�㷨
 */

#ifndef DATASTRUCTURE_STRING_H
#define DATASTRUCTURE_STRING_H

#include "../Exp2/List.h"

template <class T>
class String{
public:
    //Ĭ�Ϲ���һ���մ�
    String(){ String(0);}

    //ʹ��һ�����������촮
    String(int len, T arr[]){
        this->len = len;
        //ʹ����������ʼ��������
        this->data = List<T>(len, arr);
    }

    //���ַ����鹹��һ���ַ���
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

    //��ָ�����������촮��������ʹ��
    String(int len){ this->len = len;}

    //�������캯��
    String(String<T> &another){
        this->len = another.getLen();
        this->data = List<T>(0);
        //���ƴ��е�Ԫ��
        for(int index = 0; index < len; index++){
            this->data.append(another.getELe(index));
        }
    }


public:
    int getLen() const { return this->len;}

    //��д��
    void rewrite(int len) {
        T item;
        this->len = len;
        this->data = List<T>(0);
        for(int index = 0; index < len; index++){
            cout << "�������" << index+1 << "��Ԫ�أ�";
            cin >> item;
            this->data.append(item);
        }
    }

    //����һ��Ԫ�ص���β
    void add(T item){
        this->data.append(item);
        len++;
    }

    //�����
    void printString() const {
        for(int index = 0; index < len; index++){
            cout << this->data.find(index)->data;
        }
        cout << endl;
    }

    //��ȡĳ��λ�õ�Ԫ��
    T& getELe(int index) const {
        return data.find(index)->data;
    }

    //�޸�ĳ��λ�õ�Ԫ��
    void alter(int index, T value){
        this->data.alter(index, value);
    }

    //ƴ��������
    String<T> append(const String<T> &another){
        String<T> sln = *this;
        //�ڵ�ǰ��β����
        for(int index = 0; index < another.getLen(); index++){
            //��another��Ԫ��������ӵ���ǰ��β
            sln.add(another.getELe(index));
        }
        return sln;
    }

    //ȡλ��index��ĳ���Ϊlen�Ĵ�
    String<T> &cutStr(int index, int len) const {
        String<T> sln(0);
        for(int i = index; i < len + index - 1; i++){
            try {
                sln.append(data.find(index)->data);
            }catch (IndexOutException e){}
        }
        return sln;
    }

    //����ģʽƥ�䣨����ƥ�䣩����ƥ��ɹ����ص�һ��ƥ���ַ����±꣬ƥ��ʧ�ܷ���-1
    int match(String<T> pattern){
        bool matched = false;
        //����Ŀ�괮
        for(int targetIndex = 0; targetIndex < this->getLen(); targetIndex++){
            //����ģʽ��
            for(int patternIndex = 0; patternIndex < pattern.getLen(); patternIndex++){
                //ƥ��ʧ�ܣ��˻�
                if(this->data.find(targetIndex + patternIndex)->data != pattern.getELe(patternIndex)) break;
                //ƥ��ɹ�
                if(patternIndex == pattern.getLen()-1) return targetIndex;
            }
        }
        //ƥ��ʧ�ܣ�����-1
        return -1;
    }

    //����ģʽƥ�䣨KMP�㷨����ƥ��ɹ��򷵻ص�һ��ƥ����ַ����±꣬ƥ��ʧ���򷵻�-1
    int fastMatch(String<T> pattern){}

protected:
    List<T> data; //ʹ������������
    int len; //���ĳ���
};

#endif //DATASTRUCTURE_STRING_H
