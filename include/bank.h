//
// Created by yuhao on 2023/2/27.
//

#ifndef BANK_ONE_BANK_H
#define BANK_ONE_BANK_H

#include "utils.h"
#include "counter.h"
#include "human.h"

//开始
void start();

//初始化柜台
void init_counter();

//初始化人
void init_human();

//进行办理业务
void handle_business();

//打印全部客户的全部信息
/// 最后一个是条件  如果是0 就无条件 如果是-1就是查看等待的人  如果是-2就是查看无等待的人
/// 1是柜台1 2是柜台2 3是柜台三 4是柜台四
void print_all_human_information(int,int,int);

//打印柜台全部信息
void print_all_counter_information(int,int);

//用户选择哪个 如果要仔细搜索的话返回true
bool choice_function_main(int, bool *);

//详细搜索 返回上一级就为false
bool choice_function_detailed(int);

//查看所有时间段
void all_time_slot();

//查看自定义时间段
void custom_time_slot();

//查看无等待的客户
void not_wait_human();

//查看有等待的客户
void wait_human();

//查看各个柜台
void one_and_one_counter();
//查看指定柜台
void appoint_counter();
//查看指定时间段
void appoint_time();

#endif //BANK_ONE_BANK_H
