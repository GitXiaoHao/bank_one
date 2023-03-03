//
// Created by yuhao on 2023/3/2.
//

#include "include/human.h"

void merge_minute(human** humans, int start, int mid, int end) {
    human* result[DAY_ALL_NUMBER];
    int k = 0;
    int i = start;
    int j = mid + 1;
    while (i <= mid && j <= end) {
        if (humans[i]->into_bank_minute < humans[j]->into_bank_minute){
            result[k++] = humans[i++];
        }
        else{
            result[k++] = humans[j++];
        }
    }
    if (i == mid + 1) {
        while(j <= end)
            result[k++] = humans[j++];
    }
    if (j == end + 1) {
        while (i <= mid)
            result[k++] = humans[i++];
    }
    for (j = 0, i = start ; j < k; i++, j++) {
        humans[i] = result[j];
    }
}

void merge_sort_minute(human** humans, int start, int end) {
    if (start >= end)
        return;
    int mid = ( start + end ) / 2;
    merge_sort_minute(humans, start, mid);
    merge_sort_minute(humans, mid + 1, end);
    merge_minute(humans, start, mid, end);
}


//对人的进入银行的时间（时）排序
//快速排序
void quick_sort_hour(human **humans, int low, int high) {
    int i, j;
    human *temp = NULL;
    human *tmp = NULL;
    i = low;
    j = high;
    tmp = humans[low];   //任命为中间分界线，左边比他小，右边比他大,通常第一个元素是基准数

    if (i > j)  //如果下标i大于下标j，函数结束运行
    {
        return;
    }

    while (i != j) {
        while (humans[j]->into_bank_hour >= tmp->into_bank_hour && j > i) {
            j--;
        }

        while (humans[i]->into_bank_hour <= tmp->into_bank_hour && j > i) {
            i++;
        }

        if (j > i) {
            temp = humans[j];
            humans[j] = humans[i];
            humans[i] = temp;
        }
    }

    humans[low] = humans[i];
    humans[i] = tmp;

    quick_sort_hour(humans, low, i - 1);
    quick_sort_hour(humans, i + 1, high);
}


void sort_minute(human **humans, int low, int high) {
    //对人的时间进行排序
    quick_sort_hour(humans,low,high - 1);//对分
    //设置一个数 排序每个时间段
    int i = 0;
    int start = 0;
    int hour = humans[i]->into_bank_hour;
    for (i = low; i < high; ++i) {
        if (hour != humans[i]->into_bank_hour) {
            //已经完成
            merge_sort_minute(humans,start,i-1);
            start = i;
            hour = humans[i]->into_bank_hour;
        }
    }
    //最后一轮
    merge_sort_minute(humans,start,i-1);
}

