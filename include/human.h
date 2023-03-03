//
// Created by yuhao on 2023/2/27.
// 客户
//

#ifndef BANK_ONE_HUMAN_H
#define BANK_ONE_HUMAN_H
#include "utils.h"
// 客户
typedef struct human {
    //编号
    int human_id;
    //进入的时间（时）
    int into_bank_hour;
    //进入的时间（分）
    int into_bank_minute;
    //需要处理的时间
    int handle_time;
    //办理完的时间
    int out_bank_hour;
    int out_bank_minute;
    //是哪个柜台处理的
    /// 0 是 柜台1 以此类推
    int counter;
    //等待时间
    int wait_time;
} human;
//快速排序
void quick_sort_hour(human *humans[], int low, int high );
void sort_minute(human *humans[], int low, int high );
#endif //BANK_ONE_HUMAN_H
