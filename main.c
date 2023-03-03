
#include "include/bank.h"

static int choice = 0;
static bool loop = true;
static bool is_detail = true;

int main() {
    srand((int) time(NULL));  //用时间作为种子对随机数进行操作
    //初始化
    init();
    start();
    while (loop) {
        main:
        menu_main();
        scanf("%d", &choice);
        is_detail = choice_function_main(choice, &loop);
        //判断是否要详细搜索
        if (is_detail) {
            //仔细搜索
            while (is_detail) {
                //菜单
                detailed_menu();
                //选择
                scanf("%d", &choice);
                //业务处理
                is_detail = choice_function_detailed(choice);
                if(is_detail){
                    system("pause");
                }
            }
            goto main;
        }
        system("pause");
    }
    return 0;
}
