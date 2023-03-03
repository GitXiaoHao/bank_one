cmake_minimum_required(VERSION 3.24)
project(bank_one C)
# 改变编码
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fexec-charset=GBK")
#set(CMAKE_C_STANDARD 11)

add_executable(bank_one main.c include/counter.h include/human.h include/bank.h bank.c include/utils.h utils.c human.c counter.c)
