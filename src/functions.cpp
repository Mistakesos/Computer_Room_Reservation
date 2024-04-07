#include"functions.h"
#include"globalFile.h"
#include"identity.h"
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include<iostream>
#include<fstream>

using namespace std;

//暂停
void pause()
{
    cout << "按任意键继续..." << endl;
    system("read");
}

//清空
void clear()
{
    system("clear");
}

//进入学生子菜单界面
void studentMenu(Identity* &student)
{
    while (true)
    {
        //调用学生子菜单
        student->operMenu();

        Student* stu = (Student*)student;
        int select = 0;
        cin >> select;  //接收用户选择
        switch(select)
        {
            case 1: //申请预约
            {
                stu->applyOrder();
            }
                break;
            case 2: //查看自身预约
            {
                stu->showMyOrder();
            }
                break;
            case 3: //查看所有人预约
            {
                stu->showAllOrder();
            }
                break;
            case 4: //取消预约
            {
                stu->cancelOrder();
            }
                break;
            default: //注销登录
            {
                if(student != nullptr)
                {
                    delete student;
                    student = nullptr;
                }
                cout << "注销成功！" << endl;
                cout << "\033[0m";
                pause();
                clear();
                return;
            }
                break;
        }
        
    }
    
}

//进入教师子菜单
void teacherMenu(Identity* &teacher)
{
    while(teacher != nullptr)
    {
        //调用子菜单界面
        teacher->operMenu();

        Teacher* tea = (Teacher*)teacher;

        int select = 0;
        cin >> select;

        switch (select)
        {
        case 1: //查看所有预约
            tea->showAllOrder();
            break;
        case 2: //审核预约
            tea->validOrder();
            break;
        default:
            delete teacher;
            teacher = nullptr;
            cout << "注销成功" << endl;
            cout << "\033[0m";  //将颜色复位
            pause();
            clear();
            break;
        }

        // if(select == 1)
        // {
        //     tea->showAllOrder();
        // }
        // else if(select == 2)
        // {
        //     tea->validOrder();
        // }
        // else
        // {
        //     delete teacher;
        //     teacher = nullptr;
        //     cout << "Logouted" << endl;
        //     cout << "\033[0m";
        //     pause();
        //     clear();
        //     break;
        // }
    }
    
}

//进入管理员子菜单界面
void managerMenu(Identity* &manager)
{
    while (true)
    {
        //调用管理员子菜单
        manager->operMenu();

        //将父类指针转为子类指针，调用了子类里其他接口
        Manager* man = (Manager*)manager;

        int select = 0;
        //接收用户的选择
        cin >> select;

        switch (select)
        {
        case 1: //添加账号
        {
            //cout << "添加账号" << endl;
            man->initVector();  //每次添加人之前，初始化容器以重新检测是否重复
            man->addPerson();
        }
            break;
        case 2: //查看账号
        {
            //cout << "查看账号" << endl;
            man->showPerson();
        }
            break;
        case 3: //查看机房
        {
            //cout << "查看机房" << endl;
            man->showComputer();
        }
            break;
        case 4: //清空预约
        {
            //cout << "清空预约" << endl;
            man->cleanFile();
        }
            break;
        
        default:
        {
            if(manager != nullptr)
            {
                delete manager; //销毁堆区对象
                manager = nullptr;  //将指针置空
            }
            cout << "注销成功" << endl; //管理员注销后把颜色恢复默认
            cout << "\033[0m";
            pause();
            clear();
            return;
        }
        }
    }
    
}

//显示登录菜单
void showMenu()
{
    cout << "====================    欢迎来到终端机房预约系统    ====================" << endl;
    cout << endl
         << "请输入您的身份：" << endl;
    cout << "\t\t --------------------------------------\n"
         << "\t\t|                                      |\n"
         << "\t\t|              1.学生代表              |\n"
         << "\t\t|                                      |\n"
         << "\t\t|              2.老    师              |\n"
         << "\t\t|                                      |\n"
         << "\t\t|              3.管 理 员              |\n"
         << "\t\t|                                      |\n"
         << "\t\t|              0.退    出              |\n"
         << "\t\t|                                      |\n"
         << "\t\t --------------------------------------\n";
    cout << "输入你的选择：";
}

//登录功能  参数1：操作文件名   参数2：操作身份类型
void LoginIn(string fileName, int type)
{
    //父类指针， 用于指向子类对象
    Identity* person = nullptr;

    //读文件
    ifstream ifs;
    ifs.open(fileName, ios::in);

    //判断文件是否存在
    if(!ifs.is_open())
    {
        cout << "文件不存在！" << endl;
        ifs.close();
        return;
    }

    //准备接收用户信息
    int id = 0;
    string name;
    string passwd;

    //判断身份
    if(type == 1)   //学生身份
    {
        cout << "请输入你的学号：" << endl;
        cin >> id;

        cout << "请输入用户名：" << endl;
        cin >> name;

        cout << "请输入密码：" << endl;
        cin >> passwd;
    }
    else if(type == 2)
    {
        cout << "请输入您的职工号：" << endl;
        cin >> id;

        cout << "请输入用户名：" << endl;
        cin >> name;

        cout << "请输入密码：" << endl;
        cin >> passwd;
    }
    else if(type == 3)
    {
        cout << "请输入用户名：" << endl;
        cin >> name;

        cout << "请输入密码：" << endl;
        cin >> passwd;
    }

    switch(type)
    {
        case 1: //学生身份验证
        {
            int fId;    //从文件中读取id号
            string fName;   //从文件中获取的姓名
            string fPasswd; //从文件中获取密码
            while(ifs >> fId && ifs >> fName && ifs >> fPasswd)
            {
                //与用户输入的信息做对比
                if(fId == id && fName == name && fPasswd == passwd)
                {
                    cout << "\033[32m"; //学生登录成功后改变颜色为绿色
                    cout << "学生验证登录成功！" << endl;
                    pause();
                    clear();
                    person = new Student(id, name, passwd);
                    //进入学生身份的子菜单
                    studentMenu(person);
                    return;
                }
            }
        }
            break;
        case 2: //教师身份验证
        {
            int fId;    //从文件中获取的id号
            string fName;   //从文件中获取的姓名
            string fPasswd; //从文件中获取的密码
            while (ifs >> fId && ifs >> fName && ifs >> fPasswd)
            {
                if(fId == id && fName == name && fPasswd == passwd)
                {
                    cout << "\033[33m"; //教师登录成功后改变颜色为黄色

                    cout << "教师验证登录成功！" << endl;
                    pause();
                    clear();
                    person = new Teacher(id, name, passwd);
                    //进入教师子菜单
                    teacherMenu(person);
                    return;
                }
            }
                        
        }
            break;
        case 3: //管理员身份验证
        {
            string fName;   //从文件中获取姓名
            string fPasswd; //从文件中获取的姓名

            while (ifs >> fName && ifs >> fPasswd)
            {
                if(name == fName && passwd == fPasswd)
                {
                    cout << "\033[31m"; //管理员登录成功后改变颜色为红色

                    cout << "管理员验证登录成功！" << endl;
                    pause();
                    clear();

                    person = new Manager(name, passwd);
                    //进入管理员子菜单界面
                    managerMenu(person);
                    return;
                }
            }
            
        }
            break;
    }
    cout << "验证登录身份失败！" << endl;
    pause();
    clear();
}
