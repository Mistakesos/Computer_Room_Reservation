#ifndef TEACHER_H
#define TEACHER_H
#include"identity.h"

//教师类设计
class Teacher :public Identity
{
public:
    //默认构造
    Teacher();

    //有参构造
    Teacher(int empId, std::string name, std::string passwd);

    //菜单界面
    virtual void operMenu();

    //查看所有预约
    void showAllOrder();

    //审核预约
    void validOrder();

    //职工号
    int m_EmpId;
};



#endif  //TEACHER_H