// 工具类
// Created by yuhao on 2023/2/27.
//
#include "include/utils.h"

int get_rand(int start, int end) {
    return rand() % abs(end - start) + start;
}


void SetSize(unsigned uCol, unsigned uLine) {
    char cmd[64];
    sprintf(cmd, "mode con cols=%d lines=%d", uCol, uLine);
    //system(cmd);
}

void init() {
    //修改窗口颜色
    system("color 70");
    //修改窗口大小
    SetSize(80, 50);
    //修改标题
    SetConsoleTitle("银行业务模拟与离散事件模拟");
}

void menu_main() {
    //清屏
    system("cls");
    printf("\t\t\t\t\t-------------银行------------\n");
    printf("\t\t\t\t\t      ---- 功能列表 ----     \n");
    printf("\t\t\t\t\t|      1.查看所有客户信息    |\n");
    printf("\t\t\t\t\t|      2.查看所有柜台信息    |\n");
    printf("\t\t\t\t\t|       3.  详细搜索         |\n");
    printf("\t\t\t\t\t|       4.   退出            |\n");
    printf("\n");
    printf("\t\t\t\t\t请输入功能选项:");
}

void detailed_menu() {
    system("cls");
    printf("\t\t\t\t\t-------------银行------------\n");
    printf("\t\t\t\t\t         详细功能列表    \n");
    printf("\t\t\t\t\t        1.查看所有时间段     \n");
    printf("\t\t\t\t\t        2.查看自定义时间段     \n");
    printf("\t\t\t\t\t        3.查看无等待的客户     \n");
    printf("\t\t\t\t\t        4.查看有等待的客户    \n");
    printf("\t\t\t\t\t        5.查看各个柜台     \n");
    printf("\t\t\t\t\t        6.查看指定柜台     \n");
    printf("\t\t\t\t\t        7.查看指定时间段     \n");
    printf("\t\t\t\t\t      8.查看指定柜台的指定时间段     \n");
    printf("\t\t\t\t\t         9.返回上一级     \n");
    printf("\n");
    printf("\t\t\t\t\t请输入功能选项:");
}

