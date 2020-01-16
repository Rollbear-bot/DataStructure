// Created by 13592 on 2019/12/11.
//

#ifndef DATASTRUCTURE_HASHTABLE_H
#define DATASTRUCTURE_HASHTABLE_H

#include <cstdio>

#define MAX 50

//哈希结点
template <class K, class T>
struct HashNode{
    HashNode(K key, T data): key(key), data(data){}
    HashNode(): key(NULL), data(0){}
    K key;
    T data;
};

//哈希表
template <class K, class T>
class HashTable{
public:
    HashTable(){}

public:
    //enter and hash, exit when HashError
    bool append(HashNode<K, T> node){
        if(data[hash(node.key)].key != NULL)return false;
        data[hash(node.key)] = node;
        lastValue = hash(node.key);
        return true;
    }

    //hash search
    T search(K key){
        return data[hash(key)].data;
    }

    //print hash table
    void printTable(){
        for(int index = 0; index <= lastValue; index++){
            if(data[index].key == NULL)continue;
            cout << "Key:" << data[index].key << '\t' << "Value:" << data[index].data << endl;
        }
    }

protected:
    //哈希函数，求模取余法
    int hash(K key) { return (int)(key)%MAX;}

    HashNode<K, T> data[MAX];
    int lastValue = 0;
};

#endif //DATASTRUCTURE_HASHTABLE_H