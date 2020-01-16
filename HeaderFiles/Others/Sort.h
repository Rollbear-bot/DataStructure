//
// Created by @rollbear on 2019/12/29.
//

#ifndef DATASTRUCTURE_SORT_H
#define DATASTRUCTURE_SORT_H

#include "../Exp1/LinearTable.h"

/**
 * 排序算法的集合
 * @tparam T
 */
template <class T>
class Sort {
public:
    /**
     * 方法：希尔排序
     * 通过调用私有类方法来递归实现
     * 算法中缩小间隔（增量）的方式是gap = (gap/3)取整 + 1
     * @param lt 传入数据表
     */
    static void shellSort(LinearTable<T> &lt){
        shellSortRecursion(lt, 0, lt.getLast());
    }

    /**
     * 方法：快速排序
     * 通过调用私有方法来递归实现，调用私有方法来实现其中的“划分”功能
     * @param lt 传入数据表
     */
    static void quickSort(LinearTable<T> &lt){
        quickSortRecursion(lt, 0, lt.getLast());
    }

private:
    /**
     * 递归实现希尔排序
     * @param lt 传入的数据表
     * @param left 要排序区域的左边缘
     * @param right 要排序区域的右边缘
     */
    static void shellSortRecursion(LinearTable<T> &lt, const int left, const int right){
        int i, j, gap = right - left - 1; //增量的初始值
        T temp; //用于元素交换的额外空间
        do{
            //算法中缩小间隔（增量）的方式是gap = (gap/3)取整 + 1
            gap = gap/3 + 1; //求下一增量值

            for(i = left + gap; i <= right; i++){ //各子序列交替处理
                if(lt.find(i) < lt.find(i-gap)){ //逆序
                    temp = lt.find(i);
                    j = i - gap;

                    do{
                        lt.alter(j+gap, lt.find(j)); //后移元素
                        j = j - gap; //再比较前一元素
                    }while(j >= left && temp < lt.find(j));

                    lt.alter(j+gap, temp); //将vector[i]回送
                }//end for
            }
        }while(gap > 1);
    }

    /**
     * 递归实现快速排序
     * @param lt 传入的待排序数据表
     * @param left 待排序区域的左边界
     * @param right 待排序区域的右边界
     */
    static void quickSortRecursion(LinearTable<T> &lt, const int left, const int right){
        if(left < right){ //即仅当待排序序列长度大于一时才执行
            //划分，寻找基准元素
            int pivotPos = quickSortPartition(lt, left, right);

            //对基准左侧的序列施行快速排序
            quickSortRecursion(lt, left, pivotPos-1);

            //对基准右侧的序列施行快速排序
            quickSortRecursion(lt, pivotPos+1, right);
        }
        //元素序列长度小于或者等于1时不处理
    }

    /**
     * 快速排序子方法：寻找基准元素
     * @param low 待处理序列左边缘
     * @param high 待处理序列右边缘
     * @return 基准元素的下标
     */
    static int quickSortPartition(LinearTable<T> lt, const int low, const int high){
        int pivotPos = low;
        T pivot = lt.find(low); //基准元素
        for(int i = low + 1; i <= high; i++){ //检测整个序列，进行划分
            if(lt.find(i) < pivot){
                pivotPos++;
                //小于基准元素的交换到左侧去
                if(pivotPos!=i) lt.swap(pivotPos, i);
            }
        }
        lt.alter(low, lt.find(pivotPos));
        lt.alter(pivotPos, pivot); //基准元素就位

        return pivotPos; //返回基准元素位置
    }
};


#endif //DATASTRUCTURE_SORT_H
