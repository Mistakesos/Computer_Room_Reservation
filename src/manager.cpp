#include<fstream>
#include<algorithm>
#include"manager.h"
#include"globalFile.h"
#include"functions.h"
using namespace std;
    //默认构造
    Manager::Manager()
    {

    }

    //有参构造
    Manager::Manager(string name, string passwd)
    {
        // 初始化管理员信息
        this->m_Name = name;
        this->m_PassWd = passwd;

        // 初始化容器
        this->initVector();

        // 初始化机房信息
        ifstream ifs;
        ifs.open(COMPUTER_FILE, ios::in);
        ComputerRoom com;
        while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
        {
            vCom.push_back(com);
        }
        ifs.close();
        cout << "机房的数量为：" << vCom.size() << endl;
    }

    //菜单界面
    void Manager::operMenu()
    {
        cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
        cout << "\t\t --------------------------------------\n"
             << "\t\t|                                      |\n"
             << "\t\t|              1.添加账号              |\n"
             << "\t\t|                                      |\n"
             << "\t\t|              2.查看账号              |\n"
             << "\t\t|                                      |\n"
             << "\t\t|              3.查看机房              |\n"
             << "\t\t|                                      |\n"
             << "\t\t|              4.清空预约              |\n"
             << "\t\t|                                      |\n"
             << "\t\t|              0.注销登录              |\n"
             << "\t\t|                                      |\n"
             << "\t\t --------------------------------------\n";
        cout << "请输入您的选择：" << endl;

    }

    //添加账号
    void Manager::addPerson()
    {
        string fileName; // 操作文件名
        string tip;      // 提示id号
        string errortip;    //重复错误提示

        ofstream ofs; // 文件操作对象

        int select = 0;
        while(true)
        {
            cout << "请输入添加账号类型：" << endl
                 << "1、添加学生" << endl
                 << "2、添加老师" << endl
                 << "3、取消操作" << endl;

            cin >> select; // 接受用户选项

            switch (select)
            {
            case 1: //添加的是学生
                fileName = STUDENT_FILE;
                tip = "请输入学号：";
                errortip = "学号重复！请重新输入。";
                break;
            case 2:
                fileName = TEACHER_FILE;
                tip = "请输入职工号：";
                errortip = "职工号重复！请重新输入。";
                break;
            case 3:
                cout << "操作已取消！" << endl;
                pause();
                clear();
                return;
                break;
            default:
                clear();
                Manager::operMenu();
                cout << "输入有误，请重新输入！" << endl;
                continue;
            }
            // 利用追加的方式写文件
            ofs.open(fileName, ios::out | ios::app);

            int id;        // 学号/职工号
            string name;   // 姓名
            string passwd; // 密码

            cout << tip << endl;
            while(true)
            {
                cin >> id;
                bool ret = checkRepeat(id, select);
                if(ret) //有重复
                {
                    cout << errortip << endl;
                }
                else
                {
                    break;
                }
            }


            cout << "请输入姓名：" << endl;
            cin >> name;

            cout << "请输入密码：" << endl;
            cin >> passwd;

            // 向文件中添加数据
            ofs << id << " " << name << " " << passwd << " " << endl;
            cout << "添加成功" << endl;

            pause();
            clear();
            ofs.close();

            //初始化容器
            this->initVector();

            return;
        }
    }

    //查看账号
    void Manager::showPerson()
    {
        cout << "请选择查看的内容：" << endl;
        cout << "1、查看所有的学生" << endl;
        cout << "2、查看所有的老师" << endl;

        int select = 0; //接收用户的选择
        cin >> select;

        if(select == 1)
        {
            //查看学生
            cout << "所有学生信息如下：" << endl;
            for(const auto& s : vStu)
            {
                cout << "学号：" << s.m_Id << "    姓名：" << s.m_Name << "    密码：" << s.m_PassWd << endl;
            }
        }
        else if(select == 2)
        {
            //查看老师
            cout << "所有老师信息如下：" << endl;
            for(const auto& t : vTea)
            {
                cout << "职工号：" << t.m_EmpId << "    姓名：" << t.m_Name << "    密码：" << t.m_PassWd << endl;
            }
        }
        else
        {
            cout << "输入有误！" << endl;
            pause();
            clear();
            return;
        }
        pause();
        clear();
    }

    //查看机房信息
    void Manager::showComputer()
    {
        cout << "机房的信息如下：" << endl;
        for(const auto& c : vCom)
        {
            cout << "机房编号：" << c.m_ComId << "  机房最大容量：" << c.m_MaxNum << endl;
        }
        pause();
        clear();
    }

    //清空预约记录
    void Manager::cleanFile()
    {
        ofstream ofs(ORDER_FILE, ios::trunc);
        ofs.close();
        cout << "清空成功！" << endl;
        pause();
        clear();
    }

    // 初始化容器
    void Manager::initVector()
    {
        //确保容器是清空的
        vStu.clear();
        vTea.clear();

        //读取信息  学生、老师
        ifstream ifs;
        ifs.open(STUDENT_FILE, ios::in);
        if(!ifs.is_open())
        {
            cout << "文件读取失败！" << endl;
            return;
        }

        Student s;
        while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_PassWd)
        {
            vStu.push_back(s);
        }

        cout << "当前学生数量为：" << vStu.size() << endl;
        ifs.close();

        //读取信息 老师
        ifs.open(TEACHER_FILE, ios::in);
        Teacher t;
        while(ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_PassWd)
        {
            vTea.push_back(t);
            cout << "当前老师数量为：" << vStu.size() << endl;
            ifs.close();
        }
        
    }

    // 检测重复 参数1：检测学号/职工号   参数2：检测类型
    bool Manager::checkRepeat(int id, int type)
    {
        if(type == 1)
        {
            //检测学生
            for(const auto& s : this->vStu)
            {
                if(id == s.m_Id)
                {
                    return true;
                }
            }
        }
        else if(type == 2)
        {
            //检测老师
            for(const auto& t : this->vTea)
            {
                if(id == t.m_EmpId)
                {
                    return true;
                }
            }
        }
        // 没有重复
        return false;
    }
