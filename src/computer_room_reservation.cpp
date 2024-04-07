#include<iostream>
#include<fstream>
#include"functions.h"
#include"identity.h"
#include"globalFile.h"
using namespace std;


int main ()
{

    int select = 0; //接收用户选择

    while (true)
    {
        // 显示登录菜单
        showMenu();

        cin >> select;

        switch (select)
        {
        case 1: //学生身份
            LoginIn(STUDENT_FILE, 1);
            break;
        case 2: //老师身份
            LoginIn(TEACHER_FILE, 2);
            break;
        case 3: //管理员身份
            LoginIn(ADMIN_FILE, 3);
            break;
        case 0: //退出系统
            cout << "欢迎下次使用" << endl;
            pause();
            return 0;
            break;
        default:
            cout << "输入有误，请重新选择！" << endl;
            pause();
            clear();
            break;
        }
        
    }
    


    return 0;
}