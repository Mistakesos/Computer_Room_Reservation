#include<vector>
#include"teacher.h"
#include"orderFile.h"
#include"functions.h"
using namespace std;

    //默认构造
    Teacher::Teacher()
    {

    }

    //有参构造
    Teacher::Teacher(int empId, std::string name, std::string passwd)
    {
        this->m_EmpId = empId;
        this->m_Name = name;
        this->m_PassWd = passwd;
    }

    //菜单界面
    void Teacher::operMenu()
    {
        cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
        cout << "\t\t --------------------------------------\n"
             << "\t\t|                                      |\n"
             << "\t\t|              1.查看所有预约          |\n"
             << "\t\t|                                      |\n"
             << "\t\t|              2.审核预约              |\n"
             << "\t\t|                                      |\n"
             << "\t\t|              0.注销登录              |\n"
             << "\t\t|                                      |\n"
             << "\t\t --------------------------------------\n";
        cout << "请输入您的操作：" << endl;

    }

    //查看所有预约
    void Teacher::showAllOrder()
    {
        OrderFile of;
        if(of.m_Size == 0)
        {
            cout << "无预约记录" << endl;
            pause();
            clear();
            return;
        }
        int index = 0;
        for(auto& i : of.m_orderData)
        {
            index++;
            cout << index << "、";
            cout << "预约日期：周" << i.second["date"];
            cout << "   时间段：" << (i.second["interval"] == "1" ? "上午" : "下午");
            cout << "   学号：" << i.second["stuId"];
            cout << "   姓名：" << i.second["stuName"];
            cout << "   机房编号：" << i.second["roomId"];
            string status = "   状态：";
            //1审核中  2已预约  -1预约失败  0取消预约
            if(i.second["status"] == "1")
            {
                status += "审核中";
            }
            else if(i.second["status"] == "2")
            {
                status += "预约成功";
            }
            else if(i.second["status"] == "-1")
            {
                status += "预约失败，审核未通过";
            }
            else
            {
                status += "预约已取消";
            }
            cout << status << endl;
        }
        pause();
        clear();
    }

    //审核预约
    void Teacher::validOrder()
    {
        OrderFile of;
        if(of.m_Size == 0)
        {
            cout << "无预约记录" << endl;
            pause();
            clear();
            return;
        }

        vector<int> v;
        int index = 0;
        int temp = 0;
        cout << "待审核的预约记录如下：" << endl;
        for(auto& i : of.m_orderData)
        {
            if(i.second["status"] == "1")
            {
                v.push_back(index);
                cout << ++temp << "1、";
                cout << "预约日期：周" << i.second["date"];
                cout << "   时间段：" << (i.second["interval"] == "1" ? "上午" : "下午");
                cout << "   学生编号：" << i.second["stuId"];
                cout << "   学生姓名：" << i.second["stuName"];
                cout << "   机房编号：" << i.second["roomId"];
                string status = "   状态：审核中";
                cout << status << endl;
                index++;
            }
        }
        cout << "请输入审核的预约记录，0代表返回：" << endl;
        int select = 0; //接收用户选择的预约记录
        int ret = 0;    //接收预约结果记录
        while(true)
        {
            cin >> select;
            if(select >= 0 && select <= v.size())
            {
                if(select == 0)
                {
                    break;
                }
                else
                {
                    cout << "请输入审核结果：" << endl;
                    cout << "1、通过" << endl;
                    cout << "2、不通过" << endl;
                    cin >> ret;
                    if(ret == 1)
                    {
                        //通过的情况
                        of.m_orderData[v[select - 1]]["status"] = "2";
                    }
                    else
                    {
                        //不通过的情况
                        of.m_orderData[v[select - 1]]["status"] = "-1";
                    }
                    of.updateOrder();   //更新预约记录
                    cout << "审核完毕" << endl;
                    break;
                }
            }
            cout << "输入有误，请重新输入" << endl;
        }
        pause();
        clear();
    }
