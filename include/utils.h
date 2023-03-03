// 工具类
// Created by yuhao on 2023/2/27.
//

#ifndef BANK_ONE_UTILS_H
#define BANK_ONE_UTILS_H

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stddef.h>
#include <stdbool.h>
//上班时间
#define GO_WORK_TIME 9
//下班时间
#define OFF_WORK_TIME 17
//一天的最多人数
#define DAY_ALL_NUMBER 100
//柜台的数量
#define COUNTER_NUMBER 4
//一个人处理的时间
#define HANDLE_TIME 20

//产生随机数 根据传的整数进行产生
int get_rand(int, int);

//菜单
void menu_main();

void detailed_menu();

//初始化窗口
void init();

//改窗口大小
void SetSize(unsigned, unsigned);

#endif //BANK_ONE_UTILS_H
