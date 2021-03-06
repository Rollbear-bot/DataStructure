// 附加头结点的单链表
// 注意last指向的空间不存放数据，仅为链表结束的标志
// Created by rollbear on 2019/10/31.
/*
 * 2019.11.18 起修改为附加头结点的单链表
 * 2019.11.23 添加了表合并算法add
 */

#ifndef DATASTRUCTURE_LIST_H
#define DATASTRUCTURE_LIST_H

#include "../DsException.h"

//链表结点
template <class T>
struct ListNode{
    ListNode():next(nullptr){} //地址域的默认值为nullptr
    ListNode(ListNode *next, T data):next(next), data(data){}
    ListNode* next;
    T data;
};

//单链表类模板定义
template <class T>
class List{
public:
    //赋值运算符重载
    void operator =(const List<T> &operand){
        this->len = operand.len;
        this->first = new ListNode<T>;
        ListNode<T> *flag = first;
        //复制表中的值
        for(int index = 0; index < len; index++){
            flag->next = new ListNode<T>;
            flag = flag->next;
            flag->data = operand.find(index)->data;
        }
        flag->next = new ListNode<T>;
        flag = flag->next;
        this->last = flag;
        return;
    }

    //判等
    bool operator ==(const List<T> &another){
        if(this->length() != another.length()) return false;
        bool equal = false;
        for(int index = 0; index < this->length(); index++)
            if(!(this->getElem(index) == another.getElem(index))) return false;
        return true;
    }


    //下标运算符重载
    T &operator [](int index){
        return (find(index)->data);
    }


    //在构造函数中建表
    List(int len = 0){
        this->len = len;
        if(!len){
            //first指向附加头节点
            this->first = new ListNode<T>;
            //last尾指针指向头节点的下一个结点，链表长度为0
            first->next = new ListNode<T>;
            this->last = first->next;
        }
        else{
            //为附加头节点申请空间
            this->first = new ListNode<T>;
            ListNode<T> *flag = first;
            for(int count = 0; count <= len; count++){
                flag->next = new ListNode<T>;
                flag = flag->next;
            }
            //尾指针last指向一个空的位置（最后一个有效数据的下一个位置）
            this->last = flag;
        }
    }

    //在构造函数中使用数组来初始化链表
    List(int len, T arr[]){
        this->len = len;
        //如果长度为0，表空
        if(!len){
            //为附加头节点申请空间
            this->first = new ListNode<T>;
            //last尾指针指向头节点的下一个结点，链表长度为0
            first->next = new ListNode<T>;
            this->last = first->next;
        }
        //长度不为零时建立表
        else {
            //为附加头节点申请空间
            this->first = new ListNode<T>;
            ListNode<T> *flag = first;
            for(int count = 0; count <= len; count++) {
                flag->next = new ListNode<T>;
                flag = flag->next;
            }
            last = flag;
            //以下使用数组的数据来初始化链表
            //flag指向头节点的下一个结点，即第一个有效结点
            flag = this->first->next;
            for(int index = 0; index < len; index++){
                flag->data = arr[index];
                flag = flag->next;
            }
        }
    }

    //定义拷贝构造函数
    List(const List<T> &another){
        this->len = another.len;
        this->first = new ListNode<T>;
        ListNode<T> *flag = first;
        //复制表中的值
        for(int index = 0; index < len; index++){
            flag->next = new ListNode<T>;
            flag = flag->next;
            flag->data = another.find(index)->data;
        }
        flag->next = new ListNode<T>;
        flag = flag->next;
        this->last = flag;
    }


    //析构函数
    ~List(){
        //todo::有问题的析构函数
        //clear_recursion(first);
    }

public:
    //追加到链表尾
    void append(T item){
            last->data = item;
            last->next = new ListNode<T>;
            last = last->next;
            len++;
    }


    //删除结点（根据下标来查找）
    void removeByIndex(int index){
        //flag指向要删除的结点的前一个结点
        ListNode<T> *flag = preFind(index);
        //temp指向要删除的结点
        ListNode<T> *temp = flag->next;
        //链表中丢弃了所指定的元素
        flag->next = temp->next;
        //释放删除结点的空间
        delete temp;
        len--;
    }


    //删除节点（根据元素值）
    void removeByValue(T value){
        removeByIndex(locate(value));
    }


    //根据下标返回指向该节点的指针
    ListNode<T> *find(int index) const {
        //链表未初始化，不能查找
        if(first==nullptr)throw NullPointer();
        if(index > len || index < 0)throw IndexOutException();
        ListNode<T> *flag = first;
        for(int count = 0; count <= index; count++){
            flag = flag->next;
        }
        return flag;
    }

    //返回下标表示的前一个结点的指针，index=0时返回头指针first
    ListNode<T> *preFind(int index) const {
        if(index > len || index < 0)throw IndexOutException();
        if(this->first==nullptr)throw NullPointer();
        if(index == 0)return first;
        else return find(index-1);
    }

    //插入元素
    void insert(int index, T item){
            //temp指向插入前该索引的结点
            ListNode<T> *temp = this->find(index);
            //为插入的元素建立新结点，链接到索引的上一个结点的地址域，并将索引原结点链接到新结点的地址域
            this->preFind(index)->next = new ListNode<T>(temp, item);
            len++;
    }

    //修改某个结点的值
    void alter(int index, T value){
        if(isEmpty())throw NullPointer();
        if(index >= len || index < 0)throw IndexOutException();
        this->find(index)->data = value;
    }

    //输出表
    void printList() const {
        if(isEmpty())throw NullPointer();
        //flag指向第一个有效数据结点
        ListNode<T> *flag = first->next;
        while(true){
            if(flag == last)break;
            cout << flag->data << " ";
            //flag移动到下一个结点
            flag = flag->next;
        }
        cout << endl;
    }

    //切割为子表（获取两个索引中间的元素）
    List<T> subList(const int left, const int right){
        List<T> res;
        if(left >= right) throw IndexOutException();
        for(int index = left; index < right; index++){
            res.append(this->getElem(index));
        }
        return res;
    }

    //根据值返回第一个定位到的结点的下标值，未找到则返回-1
    int locate(T item) const {
        for(int index = 0; index < len; index++){
            if(find(index)->data == item)return index;
        }
        return -1;
    }

    //所查找元素是否在链表中
    bool inList(T item) const {
        if(isEmpty()) return false;
        return locate(item) != -1;
    }

    //判空
    bool isEmpty() const {
        return len == 0;
    }


    //链表置空
    void clear(){
        clear_recursion(first); //释放所有空间
        //重新初始化
        this->first = new ListNode<T>;
        first->next = new ListNode<T>;
        this->last = first->next;
        this->len = 0;
    }

    //表合并：将另一个表附加到当前表尾，函数返回新表
    static List<T> add(List<T> preList, List<T> postList){
        ListNode<T> *cur = preList.preFind(preList.length());
        cur->next = postList.first->next;
        preList.len += postList.len;
        return preList;
    }


    //插入排序：从小到大
    void insertSort(){
        int i, j, k;
        T temp;
        for(i = 0; i < this->len-1; i++){
            k = i;
            for(j = i + 1; j < len; j++){
                if(getElem(k) > getElem(j)) {
                    k = j;
                }
            }
            //交换k和i的值
            temp = getElem(i);
            alter(i, getElem(k));
            alter(k, temp);
        }
    }

    //获取某个索引位置的元素的值
    T getElem(int index) const {
        return find(index)->data;
    }


    //从链表的头部弹出一个元素，并将它删除（将表视为队列来使用）
    T quit(){
        T tmp = getElem(0);
        removeByIndex(0);
        return tmp;
    }


    //交换两个位置的值
    void swap(int indexA, int indexB){
        if(indexA >= len || indexB >= len
        || indexA < 0 || indexB < 0) throw IndexOutException();
        T tmp = getElem(indexA);
        alter(indexA, getElem(indexB));
        alter(indexB, tmp);
    }


    /**
     * 生成一个含n个随机数的序列（用于测试排序）
     * @param l 需要的序列长度
     * @return 生成的序列
     */
    static List<int> randomIntegerList(int l){
        List<int> res;
        for(int count = 0; count < l; count++){
            res.append(rand());
        }
        return res;
    }


    /**
     * 检查序列是否有序
     * @param 是否从大到小（默认从小到大）
     * @return 布尔值
     */
    bool orderly(bool reverseOrder = false) const {
        if(reverseOrder){
            for(int index = 0; index < len-1; index++){
                if(getElem(index) < getElem(index+1)) return false;
            }
        }
        else {
            for(int index = 0; index < len-1; index++){
                if(getElem(index) > getElem(index+1)) return false;
            }
        }
        return true;
    }


    /**
     * 用链表中的元素生成一个数组
     * todo::内存泄漏
     */
     void toArr(T *arr) const {
         for(int index = 0; index < len; index++)
             arr[index] = getElem(index);
     }


    //返回链表中的最大元素
    T maxElem() const {
         if(first == nullptr || first->next == nullptr) throw NullPointer();
         T max = first->next->data;
         for(ListNode<T> *i = first->next; i != last; i = i->next){
             if(max < i->data) max = i->data;
         }
         return max;
     }


    ListNode<T> *getFirst(){return this->first;}
    ListNode<T> *getLast(){ return this->last;}
    int length() const { return this->len;}

protected:
    int len; //辅助计数
    ListNode<T> *first; //first指向附加头节点，该节点不存放有效数据
    ListNode<T> *last; //last指向的结点不存放数据，仅为链表结束的标志


    //递归删除该节点和其后继的所有节点
    void clear_recursion(ListNode<T> *cur){
        if(cur->next == nullptr) {
            delete cur;
            return; //递归出口
        }
        clear_recursion(cur->next);
    }
};

#endif //DATASTRUCTURE_LIST_H