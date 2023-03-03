//
// Created by yuhao on 2023/3/3.
//
#include "include/counter.h"


void bubble_sort(counter **counters) {
//做标识符 表示是否进行过交换
    bool flag = false;
    counter *temp;
    for (int i = 0; i < COUNTER_NUMBER - 1; i++) {
        for (int j = 0; j < COUNTER_NUMBER - 1 - i; j++) {
            if (counters[j]->now_handle_human_number > counters[j + 1]->now_handle_human_number) {
                flag = true;
                temp = counters[j];
                counters[j] = counters[j + 1];
                counters[j + 1] = temp;
            }
        }
        if (!flag) { break; }
        flag = false;//进行下次判断
    }
}
