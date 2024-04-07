#include<fstream>
#include"student.h"
#include"globalFile.h"
#include"orderFile.h"
#include"orderFile.h"
#include"functions.h"
using namespace std;
// 默认构造
Student::Student()
{
    
}

// 有参构造  参数：学号、姓名、密码
Student::Student(int id, std::string name, std::string passwd)
{
    //初始化属性
    this->m_Id = id;
    this->m_Name = name;
    this->m_PassWd = passwd;

    //初始化机房信息
    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);

    ComputerRoom com;
    while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
    {
        //将读取的信息放入到容器中
        vCom.push_back(com);
    }
    ifs.close();
}

// 菜单界面
void Student:: operMenu() 
{
    cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
    cout << "\t\t --------------------------------------\n"
         << "\t\t|                                      |\n"
         << "\t\t|              1.申请预约              |\n"
         << "\t\t|                                      |\n"
         << "\t\t|              2.查看我的预约          |\n"
         << "\t\t|                                      |\n"
         << "\t\t|              3.查看所有预约          |\n"
         << "\t\t|                                      |\n"
         << "\t\t|              4.取消预约              |\n"
         << "\t\t|                                      |\n"
         << "\t\t|              0.注销登录              |\n"
         << "\t\t|                                      |\n"
         << "\t\t --------------------------------------\n";
    cout << "请选择您的操作：" << endl;
}

// 申请预约
void Student::applyOrder()
{
    cout << "机房开放时间为周一至周五！" << endl;
    cout << "请输入申请预约的时间：" << endl;
    cout << "1、周一" << endl
         << "2、周二" << endl
         << "3、周三" << endl
         << "4、周四" << endl
         << "5、周五" << endl;

    int date = 0;   //日期
    int interval = 0;   //时间段
    int room = 0;   //机房编号

    while (true)
    {
        cin >> date;
        if(date >= 1 && date <= 5)
        {
            break;
        }
        else
        {
            cout << "输入有误，请重新输入" << endl;
        }
    }

    cout << "请输入申请预约的时间段：" << endl;
    cout << "1、上午" << endl;
    cout << "2、下午" << endl;
    while (true)
    {
        cin >> interval;
        if(interval >= 1 && interval <= 2)
        {
            break;
        }
        else
        {
            cout << "输入有误，请重新输入" << endl;
        }
    }

    cout << "请选择机房：" << endl;
    for(const auto& c : vCom)
    {
        cout << c.m_ComId << "号机房容量为：" << c.m_MaxNum << endl;
    }
    while (true)
    {
        cin >> room;
        if(room >= 1 && room <= 3)
        {
            break;
        }
        cout << "输入有误，请重新输入" << endl;
    }
    cout << "预约成功！审核中" << endl;

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);
    ofs << "date:" << date << " "
        << "interval:" << interval << " "
        << "stuId:" << this->m_Id << " "
        << "stuName:" << this->m_Name << " "
        << "roomId:" << room << " "
        << "status:" << 1 << endl;
    ofs.close();
    pause();
    clear();
    
    

}

// 查看自身预约
void Student::showMyOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "无预约记录！" << endl;
        pause();
        clear();
        return;
    }

    for(int i = 0; i < of.m_Size; i++)
    {
        //利用stoi将string转为int
        if(this->m_Id == stoi(of.m_orderData[i]["stuId"]))  //找到自身预约
        {
            cout << "预约日期：周" << of.m_orderData[i]["date"];
            cout << "   时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << "   机房号：" << of.m_orderData[i]["roomId"];
            string status = "状态：";
            //1 审核中  2 已预约    -1 预约失败 0 取消预约
            if(of.m_orderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            else if(of.m_orderData[i]["status"] == "2")
            {
                status += "预约成功";
            }
            else if(of.m_orderData[i]["status"] == "-1")
            {
                status += "预约失败，审核未通过";
            }
            else
            {
                status += "预约已取消";
            }
            cout << status << endl;
        }
    }
    pause();
    clear();
    
}

// 查看所有预约
void Student::showAllOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "无预约记录！" << endl;
        pause();
        clear();
        return;
    }
    int index = 0;
    for(auto& entry : of.m_orderData) 
    {
        index++;
        std::cout << index << "、";
        std::cout << "预约日期：周" << entry.second["date"];
        std::cout << "   时间段：" << (entry.second["interval"] == "1" ? "上午" : "下午");
        std::cout << "   学号：" << entry.second["stuId"];
        std::cout << "   姓名：" << entry.second["stuName"];
        std::cout << "   机房编号：" << entry.second["roomId"];

        std::string status;
        // 1审核中   2已预约  -1预约失败  0取消预约
        if(entry.second["status"] == "1")
        {
            status = "审核中";
        } 
        else if(entry.second["status"] == "2")
        {
            status = "预约成功";
        } 
        else if(entry.second["status"] == "-1")
        {
            status = "预约失败，审核未通过";
        } 
        else if (entry.second["status"] == "0")
        {
            status = "预约已取消";
        }
        else
        {
            status = "未知状态"; // 添加一个默认状态以处理异常情况
        }

        std::cout << "   状态：" << status << std::endl;
    }
    
    // for(int i = 0; i < of.m_Size; i++)
    // {
    //     cout << i + 1 << "、";
    //     cout << "预约日期：周" << of.m_orderData[i]["date"];
    //     cout << "   时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
    //     cout << "   学号：" << of.m_orderData[i]["stuId"];
    //     cout << "   姓名：" << of.m_orderData[i]["stuName"];
    //     cout << "   机房编号：" << of.m_orderData[i]["roomId"];
    //     string status = "状态：";
    //     //1审核中   2已预约  -1预约失败  0取消预约
    //     if(of.m_orderData[i]["status"] == "1")
    //     {
    //         status += "审核中";
    //     }
    //     else if(of.m_orderData[i]["status"] == "2")
    //     {
    //         status += "预约成功";
    //     }
    //     else if(of.m_orderData[i]["status"] == "-1")
    //     {
    //         status += "预约失败，审核未通过";
    //     }
    //     else if(of.m_orderData[i]["status"] == "0")
    //     {
    //         status += "预约已取消";
    //     }
    //     cout << status << endl;
    // }
    pause();
    clear();
}

// 取消预约
void Student::cancelOrder()
{
    OrderFile of;
    if(of.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        pause();
        clear();
        return;
    }
    cout << "审核中或预约成功的记录是可以取消的，请输入取消的记录：" << endl;
    vector<int> v;  //存放在最大容器中的下标编号
    int index = 1;
    for(int i = 0; i < of.m_Size; i++)
    {
        //先判断是自身学号
        if(this->m_Id == stoi(of.m_orderData[i]["stuId"]))
        {
            //再筛选状态 审核中或预约成功
            if(of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << "、";
                cout << "预约日期：周" << of.m_orderData[i]["date"];
                cout << "   时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
                cout << "   机房：" << of.m_orderData[i]["roomId"];
                string status = "   状态：";
                if(of.m_orderData[i]["status"] == "1")
                {
                    status += "审核中";
                }
                else if(of.m_orderData[i]["status"] == "2")
                {
                    status += "预约成功";
                }
                cout << status << endl;
            }
        }
    }
    cout << "请输入取消的记录，0代表返回：" << endl;
    int select = 0;
    while (true)
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
                of.m_orderData[v[select - 1]]["status"] = "0";

                of.updateOrder();

                cout << "已取消预约" << endl;
                break;
            }
        }
        cout << "输入有误，请重新输入" << endl;
    }
    pause();
    clear();
}
