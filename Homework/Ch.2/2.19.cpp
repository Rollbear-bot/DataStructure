//
// Created by 13592 on 2019/11/17.
// p86 2.19 ����˫������

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

//����ͷ����˫������
class Listx{
public:
    //���캯������ĿҪ����㷨�ڴ�
    Listx(int len, int arr[]){
        //���lLink������
        head = new Nodex;
        Nodex *flag = head;
        for(int count = 0; count <= len; count++){
            flag->lLink = new Nodex;
            flag = flag->lLink;
        }
        last = flag;

        //�������rLink������

    }

protected:
    Nodex *head; //ָ���ͷ��㣬��ͷ��㲻�������
    Nodex *last; //ָ�����һ�����ݽ�����һ�����
};*/

#include "../../HeaderFiles/Exp3/DoubleLinkedList.h"
#include "../../HeaderFiles/Exp2/List.h"

//˫������������㷨������ģ��
template <class T>
void sort(DoubleLinkedList<T> &lt){
    int len = lt.getLen();
    T temp;
    //����������㷨
    for(int i = 0; i < len-1; i++){
        int k = i;
        for(int j = i+1; j < len; j++){
            if(lt.find(k)->data > lt.find(j)->data) k = j;
        }
        //ֵ����
        temp = lt.find(k)->data;
        lt.find(k)->data = lt.find(i)->data;
        lt.find(i)->data = temp;
    }
}

//��Ԫ��ֵ��С�����޸�����ָ����㷨:
//���ҳ���С����������ڰ������ع�frontָ��
template <class T>
DoubleLinkedList<T> alterLinks(const DoubleLinkedList<T> lt){
    //��һ������compare������˫�������е�Ԫ�ش�С��ϵ��
    //Ԫ��ԽС�±��ŵ�Խǰ
    List<int> compare(lt.getLen());
    //kΪÿ�ֱȽ���ָ����СԪ�ص�����
    int k;
    for(int i = 0; i < lt.getLen(); i++){
        k = i;
        for(int j = 0; j < lt.getLen(); j++){
            //�������j�Ѿ���compare�У��򲻱Ƚ����Ԫ��
            if(compare.inList(j))break;
            if(lt.find(k)->data > lt.find(j)->data) k = j;
        }
        compare.alter(i, k);
    }
    DoubleLinkedList<T> sln = lt;
    //�޸�˫�����������ָ��
    for(int index = 0; index < compare.getLen()-1; index++){
        int slnIndex = compare.find(index)->data;
        //��ǰ������һ������compare�е�����
        int nextSlnIndex = compare.find(index)->next->data;
        //����frontָ��ָ����һ������Ԫ�صĽ��
        sln.find(slnIndex)->front = sln.find(nextSlnIndex);
    }
    return sln;
}

/*
int main(){

}
 */