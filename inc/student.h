#ifndef STUDENT_H
#define STUDENT_H
#include<vector>
#include"identity.h"
#include"computerRoom.h"

//学生类
class Student :public Identity
{
public:
    //默认构造
    Student();

    //有参构造  参数：学号、姓名、密码
    Student(int id, std::string name, std::string passwd);

    //菜单界面
    virtual void operMenu();

    //申请预约
    void applyOrder();

    //查看自身预约
    void showMyOrder();

    //查看所有预约
    void showAllOrder();

    //取消预约
    void cancelOrder();

    //学生编号
    int m_Id;

    //机房容器
    std::vector<ComputerRoom> vCom;








};






#endif  //STUDENT_H