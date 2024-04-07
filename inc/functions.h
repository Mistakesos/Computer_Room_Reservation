#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<string>
#include"identity.h"
//暂停
void pause();

//清屏
void clear();

//显示登录菜单
void showMenu();

//登录功能  参数1：操作文件名   参数2：操作身份类型
void LoginIn(std::string, int);

//进入管理员子菜单界面
void managerMenu(Identity* &manager);

#endif  //FUNCTIONS_H



/*

\033[0m：重置颜色

设置文本颜色：
\033[30m：黑色
\033[31m：红色
\033[32m：绿色
\033[33m：黄色
\033[34m：蓝色
\033[35m：洋红色
\033[36m：青色
\033[37m：白色

设置背景颜色：
\033[40m：黑色背景
\033[41m：红色背景
\033[42m：绿色背景
\033[43m：黄色背景
\033[44m：蓝色背景
\033[45m：洋红色背景
\033[46m：青色背景
\033[47m：白色背景









*/