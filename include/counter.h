//
// Created by yuhao on 2023/2/27.
// 银行柜台
//

#ifndef BANK_ONE_COUNTER_H
#define BANK_ONE_COUNTER_H

#include "utils.h"

// 银行柜台
typedef struct counter {
    //编号
    /// 0 是 柜台1 以此类推
    int counter_id;
    //总共处理人数
    int all_handle_human_number;
    //当前处理人数
    int now_handle_human_number;
    //总共处理时间
    int all_handle_time;
    //当前需要处理的时间
    int now_handle_time;
    //办完业务的时间
    int complete_business_hour;
    int complete_business_minute;
    //总等待时间
    int wait_all_time;
} counter;

//对当前处理的人数进行排序
void bubble_sort(counter **counters);

#endif //BANK_ONE_COUNTER_H
