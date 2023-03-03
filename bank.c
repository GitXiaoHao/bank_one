//
// Created by yuhao on 2023/2/27.
//
#include "include/bank.h"

static counter *counters[COUNTER_NUMBER];
static human *humans[DAY_ALL_NUMBER];


void start() {
    //初始化柜台
    init_counter();
    //初始化人
    init_human();
    //对每个人进行排序
    sort_minute(humans, 0, DAY_ALL_NUMBER);
    //进行办理业务
    handle_business();
    printf("\t\t\t\t\t\t今日业务已完成\n");
    printf("\t\t\t\t\t\t");
    system("pause");
}

void handle_business() {
    counter *now_counter;
    human *now_human;
    int i;
    for (i = 0; i < DAY_ALL_NUMBER; ++i) {
        //对柜台排队人数进行排序
        bubble_sort(counters);
        //取柜台的第一个
        now_counter = counters[0];
        now_human = humans[i];
        //看处理时间
        //判断柜台办完业务的时间
        if (now_counter->now_handle_time != 0) {
            //目前有人
            //判断是否需要等待
            //判断这个前一个人办理柜台的业务时间minute 没有到下一个小时 如果小于 当前人进来的时间就可以直接办理
            if (now_counter->complete_business_hour == now_human->into_bank_hour) {
                //如果相等
                //柜台办完业务的分钟 小于 当前人进来的分钟 就 直接办理 如果 大于 就加上等待时间
                if (now_counter->complete_business_minute > now_human->into_bank_minute) {
                    //大于 需要等待
                    now_human->wait_time = now_counter->complete_business_minute - now_human->into_bank_minute;
                }
            }
        }
        //人数++
        ++(now_counter->now_handle_human_number);
        ++(now_counter->all_handle_human_number);
        //处理的时间++
        now_counter->now_handle_time = now_human->handle_time;
        now_counter->all_handle_time += now_human->handle_time;
        //办完业务的时间
        //办理时间 + 进来的时间 + 等待时间
        if (now_human->handle_time + now_human->into_bank_minute + now_human->wait_time >= 60) {
            //如果办完业务的时间超过了这个小时的时间 到了下一个小时
            now_counter->complete_business_hour = now_human->into_bank_hour + 1;
        } else {
            now_counter->complete_business_hour = now_human->into_bank_hour;
        }
        now_counter->wait_all_time += now_human->wait_time;
        now_counter->complete_business_minute =
                (now_human->into_bank_minute + now_human->handle_time + now_human->wait_time) % 60;
        now_human->counter = now_counter->counter_id;
        //出去的时间 办完业务的时间就是出去的时间
        now_human->out_bank_hour = now_counter->complete_business_hour;
        now_human->out_bank_minute = now_counter->complete_business_minute;
    }
}

void init_counter() {
    int i;
    for (i = 0; i < COUNTER_NUMBER; ++i) {
        counter *now_counter;
        now_counter = (struct counter *) malloc(sizeof(struct counter));
        now_counter->counter_id = i + 1;
        now_counter->wait_all_time =
        now_counter->all_handle_human_number =
        now_counter->all_handle_time =
        now_counter->now_handle_human_number =
        now_counter->now_handle_time =
        now_counter->complete_business_hour =
        now_counter->complete_business_minute = 0;
        //now_counter->now_counter_humans = (struct human *) malloc(sizeof(struct human) * DAY_ALL_NUMBER);
        counters[i] = now_counter;
    }
}

void init_human() {
    int i;
    for (i = 0; i < DAY_ALL_NUMBER; ++i) {
        human *now_human = (struct human *) malloc(sizeof(struct human));
        //进入的时间
        //进入的时
        now_human->into_bank_hour = get_rand(GO_WORK_TIME, OFF_WORK_TIME);
        //分
        now_human->into_bank_minute = get_rand(0, 60);
        //需要处理的时间
        now_human->handle_time = get_rand(1, HANDLE_TIME);
        //其他的
        now_human->human_id = i + 1;
        now_human->wait_time =
        now_human->counter =
        now_human->out_bank_hour =
        now_human->out_bank_minute = 0;
        humans[i] = now_human;
    }
}

void print_all_human_information(int start, int end, int is_condition) {
    //顺便算平均等待时间
    double wait_all_time = 0.0;
    //算办理业务总时间
    double handle_all_time = 0;
    int number = 0;
    printf("客户姓名\t进入时间\t办理时间\t等待时间\t离开时间\t办理柜台\n");
    int i;
    for (i = start; i < end; ++i) {
        human *now_human = humans[i];
        switch (is_condition) {
            case -1:
                //有等待的
                if (now_human->wait_time == 0) {
                    continue;
                }
                break;
            case -2:
                //没有等待的
                if (now_human->wait_time != 0) {
                    continue;
                }
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                //柜台一
                if (now_human->counter != is_condition) {
                    continue;
                }
                break;
            default:
                break;
        }
        printf(" 客户\t\t %02d:%02d\t\t %02d分钟\t\t %2d分钟\t\t %02d:%02d\t\t 柜台%d\n",
                //now_human]->human_id,
               now_human->into_bank_hour, now_human->into_bank_minute,
               now_human->handle_time,
               now_human->wait_time,
               now_human->out_bank_hour, now_human->out_bank_minute,
               now_human->counter);
        wait_all_time += now_human->wait_time;
        handle_all_time += now_human->handle_time;
        ++number;
    }
    printf("\n\t\t\t\t总人数：%d人", number);
    if (is_condition != -2) {
        printf("\n\t\t总等待时间:%.0f分钟,平均等待时间:%.0f分钟", wait_all_time, ((wait_all_time / number) + 0.5));
    }
    printf("\n\t\t总办理时间:%.0f分钟,平均办理时间:%.0f分钟\n", handle_all_time, ((handle_all_time / number) + 0.5));

}

void print_all_counter_information(int start, int end) {
    //顺便算平均等待时间
    double wait_all_time = 0.0;
    //算办理业务总时间
    double handle_all_time = 0.0;
    printf(" 柜台\t\t处理人数\t办理总时间\t\t等待总时间\t\t最后完成时间\n");
    int i;
    for (i = start; i < end; ++i) {
        printf(" 柜台%d\t\t %2d人\t\t %3d分钟\t\t %3d分钟\t\t %02d:%02d \n",
               counters[i]->counter_id,
               counters[i]->all_handle_human_number,
               counters[i]->all_handle_time,
               counters[i]->wait_all_time,
               counters[i]->complete_business_hour, counters[i]->complete_business_minute
        );
        wait_all_time += counters[i]->wait_all_time;
        handle_all_time += counters[i]->all_handle_time;
    }
    printf("\n\t\t总等待时间:%.0f分钟,平均等待时间:%.0f分钟", wait_all_time, (wait_all_time / (end - start) + 0.5));
    printf("\n\t\t总办理时间:%.0f分钟,平均办理时间:%.0f分钟\n", handle_all_time,
           (handle_all_time / (end - start) + 0.5));

}

void all_time_slot() {
    int i;
    //分时间段
    int start = 0;
    int hour = humans[0]->into_bank_hour;
    for (i = 0; i < DAY_ALL_NUMBER; ++i) {
        if (hour != humans[i]->into_bank_hour) {
            printf("\n\t-------------------------------%d点-------------------------------\n", hour);
            //已经完成
            print_all_human_information(start, i - 1, 0);
            start = i;
            hour = humans[i]->into_bank_hour;
        }
    }
    printf("\n\t-------------------------------%d点-------------------------------\n", hour);
    //最后一轮
    print_all_human_information(start, i - 1, 0);
}

void custom_time_slot() {
    //自定义时间段
    int start_hour = 0;
    int start_minute = 0;
    int end_hour = 0;
    int end_minute = 0;
    printf("\t\t\t\t\t请输入起始时间(GO_WORK_TIME-OFF_WORK_TIME)：");
    scanf("%d", &start_hour);
    if (start_hour > OFF_WORK_TIME || start_hour < GO_WORK_TIME) {
        //开始时间错误
        printf("\t\t\t\t\t起始时间错误!\n");
        return;
    }
    printf("\t\t\t\t\t请输入起始分钟(0-5GO_WORK_TIME)：");
    scanf("%d", &start_minute);
    if (start_minute > 59 || start_minute < 0) {
        //开始的分钟错误
        printf("\t\t\t\t\t起始分钟错误!\n");
        return;
    }
    printf("\t\t\t\t\t请输入结束时间(GO_WORK_TIME-OFF_WORK_TIME)：");
    scanf("%d", &end_hour);
    if (end_hour > OFF_WORK_TIME || end_hour < GO_WORK_TIME) {
        //结束时间错误
        printf("\t\t\t\t\t结束时间错误!\n");
        return;
    }
    if (start_hour > end_hour) {
        //开始时间大于结束时间
        printf("结束时间大于开始时间!\n");
        return;
    }
    printf("\t\t\t\t\t请输入结束分钟(0-5GO_WORK_TIME)：");
    scanf("%d", &end_minute);
    if (end_minute > 59 || end_minute < 0) {
        //结束的分钟错误
        printf("\t\t\t\t\t结束分钟错误!\n");
        return;
    }
    ///基本错误排除完了
    if (start_hour == end_hour) {
        if (end_minute < start_minute) {
            //小时相同，但是 开始的分钟大于结束的分钟
            printf("\t\t\t\t\t分钟有误!\n");
            return;
        }
    }
    //开始
    ///客户的时间本来就是有序的
    int i;
    int start = 0;
    int end = 0;
    //判断是否找到了开始的人
    bool start_flag = false;

    for (i = 0; i < DAY_ALL_NUMBER - 1; ++i) {
        human *now_human = humans[i];
        human *next_human = humans[i + 1];
        if (!start_flag) {
            //时间相同
            if (now_human->into_bank_hour == start_hour) {
                //分钟
                if (now_human->into_bank_minute == start_minute) {
                    start = i;
                    start_flag = true;
                } else if (now_human->into_bank_minute < start_minute && next_human->into_bank_minute > start_minute) {
                    start = i + 1;
                    start_flag = true;
                } else if (now_human->into_bank_minute < start_minute && next_human->into_bank_hour > start_hour) {
                    start = i + 1;
                    start_flag = true;
                }
            }
        }

        //结束时间相同
        if (now_human->into_bank_hour == end_hour) {
            //分钟
            if (now_human->into_bank_minute == end_minute) {
                end = i;
            } else if (now_human->into_bank_minute < end_minute && next_human->into_bank_minute > end_minute) {
                end = i + 1;
            } else if (now_human->into_bank_minute < end_minute && next_human->into_bank_hour > end_hour) {
                end = i + 1;
            } else {
                continue;
            }
            break;
        }
    }
    if (end == 0) {
        end = DAY_ALL_NUMBER;
    }
    printf("\t\t--------------------- %d:%02d 到 %d:%02d------------------------\n", start_hour, start_minute, end_hour,
           end_minute);
    print_all_human_information(start, end,
                                0);

}

void not_wait_human() {
    //没有等待的人
    printf("\t----------------无等待的客户------------------\n");
    print_all_human_information(0, DAY_ALL_NUMBER, -2);
}

void wait_human() {
    //查看有等待的客户
    printf("\t\t----------------有等待的客户------------------\n");
    print_all_human_information(0, DAY_ALL_NUMBER, -1);
}

void one_and_one_counter() {
    //查看各个柜台
    int i;
    for (i = 0; i < COUNTER_NUMBER;) {
        printf("\n\t--------------------------------柜台%d--------------------------------\n", i + 1);
        print_all_human_information(0, DAY_ALL_NUMBER, ++i);
    }
}

void appoint_counter() {
    int num = 0;
    printf("\t\t\t\t\t您要查看的柜台是:");
    scanf("%d", &num);
    if (num <= 0 || num > COUNTER_NUMBER) {
        printf("输入错误!\n");
    } else {
        printf("\n\t--------------------------------柜台%d--------------------------------\n", num);
        print_all_human_information(0, DAY_ALL_NUMBER, num);
    }
}

void appoint_time() {
    int time_num = 0;
    printf("\t\t\t\t\t您要查看的时间段是:");
    scanf("%d", &time_num);
    if (time_num < GO_WORK_TIME || time_num > OFF_WORK_TIME) {
        printf("输入错误!\n");
        return;
    }
    //找当前时间段的
    int i;
    int start = 0;
    bool start_loop = false;
    int end = 0;
    for (i = 0; i < DAY_ALL_NUMBER; ++i) {
        human *now_human = humans[i];
        if (!start_loop) {
            if (now_human->into_bank_hour == time_num) {
                start = i;
                start_loop = true;
            }
        }else {
            if (now_human->into_bank_hour != time_num) {
                end = i - 1;
                break;
            }
        }
    }
    printf("\n\t-------------------------------%d点-------------------------------\n", time_num);
    print_all_human_information(start, end, 0);
}

bool choice_function_main(int choice, bool *loop) {
    system("cls");
    switch (choice) {
        case 1: //查看所有客户信息
            print_all_human_information(0, DAY_ALL_NUMBER, 0);
            break;
        case 2: //查看所有柜台信息
            print_all_counter_information(0, COUNTER_NUMBER);
            break;
        case 3: //详细搜索
            return true;
        case 4: //退出
            *loop = false;
            break;
        default:
            printf("请重新输入\n");
    }
    return false;
}

bool choice_function_detailed(int choice) {
    system("cls");
    switch (choice) {
        case 1: //查看所有时间段
            all_time_slot();
            break;
        case 2: //查看自定义时间段
            custom_time_slot();
            break;
        case 3: //查看无等待的客户
            not_wait_human();
            break;
        case 4: //查看有等待的客户
            wait_human();
            break;
        case 5: //查看各个柜台
            one_and_one_counter();
            break;
        case 6://查看指定柜台
            appoint_counter();
            break;
        case 7://查看指定时间段
            appoint_time();
            break;
        case 8: //返回上一级
            return false;
        default:
            printf("请重新输入\n");
    }
    return true;
}
